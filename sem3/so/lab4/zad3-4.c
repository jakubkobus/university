#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64
#define MAX_PIPES 16

typedef struct Command {
  char **argv;
  int argc;

  char *inFile;
  char *outFile;
  char *errFile;

  bool append;
} Command;

void SIGCHLDHandler(int signal);
void trim(char *s);
void processLine(char *line);
char **splitByPipe(char *line, int *num_segments);
Command tokenizeCommand(char *cmd);
void executePipeline(Command *cmds, int n, bool background);
void handleRedirection(Command *cmd);
void freeCommand(Command *cmd);

int main(void) {
  char line[MAX_CMD_LEN];

  signal(SIGINT, SIG_IGN);
  signal(SIGCHLD, SIGCHLDHandler);

  while(true) {
    printf("lsh> ");
    fflush(stdout);

    if(!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    line[strcspn(line, "\n")] = '\0';
    trim(line);

    if(strlen(line) == 0)
      continue;

    if(strcmp(line, "exit") == 0)
      break;

    if(strncmp(line, "cd", 2) == 0 && (line[2] == ' ' || line[2] == '\0')) {
      char *path = line + 2;
      trim(path);

      if(strlen(path) == 0)
        path = getenv("HOME");

      if(chdir(path) != 0)
        perror("cd");

      continue;
    }

    processLine(line);
  }

  return EXIT_SUCCESS;
}

void SIGCHLDHandler(int signal) {
  while(waitpid(-1, NULL, WNOHANG) > 0);
}

void trim(char *str) {
  if(!str) return;

  char *start = str;
  while(*start && isspace((unsigned char)*start))
    start++;

  if(start != str)
    memmove(str, start, strlen(start) + 1);

  size_t len = strlen(str);
  while(len > 0 && isspace((unsigned char)str[len - 1]))
    str[--len] = '\0';
}

void processLine(char *line) {
  bool background = false;
  size_t len = strlen(line);

  if(len > 0 && line[len - 1] == '&') {
    background = true;
    line[len - 1] = '\0';
    trim(line);
  }

  int n = 0;
  char **segments = splitByPipe(line, &n);

  if(n == 0) {
    free(segments);
    return;
  }

  Command *cmds = malloc(sizeof(Command) * n);
  for(int i = 0; i < n; i++)
    cmds[i] = tokenizeCommand(segments[i]);
  
  executePipeline(cmds, n, background);

  for(int i = 0; i < n; i++) {
    freeCommand(&cmds[i]);
    free(segments[i]);
  }

  free(cmds);
  free(segments);
}

char **splitByPipe(char *line, int *n) {
  *n = 0;
  char **cmds = malloc(MAX_PIPES * sizeof(char *));

  char *token = strtok(line, "|");
  while(token != NULL && *n < MAX_PIPES) {
    cmds[*n] = strdup(token);
    trim(cmds[*n]);
    (*n)++;
    token = strtok(NULL, "|");
  }

  return cmds;
}

Command tokenizeCommand(char *cmd) {
  Command result;
  result.argv = malloc(MAX_ARGS * sizeof(char *));
  result.argc = 0;
  result.inFile = NULL;
  result.outFile = NULL;
  result.errFile = NULL;
  result.append = false;

  trim(cmd);
  char *token = strtok(cmd, " \t\n");

  while(token != NULL && result.argc < MAX_ARGS - 1) {
    if(strcmp(token, "<") == 0) {
      token = strtok(NULL, " \t\n");
      if(token)
        result.inFile = strdup(token);
    } else if(strcmp(token, ">") == 0) {
      token = strtok(NULL, " \t\n");
      if(token) {
        result.outFile = strdup(token);
        result.append = false;
      }
    } else if(strcmp(token, ">>") == 0) {
      token = strtok(NULL, " \t\n");
      if(token) {
        result.outFile = strdup(token);
        result.append = true;
      }
    } else if(strcmp(token, "2>") == 0) {
      token = strtok(NULL, " \t\n");
      if(token)
        result.errFile = strdup(token);
    } else if(strcmp(token, "2>>") == 0) {
      token = strtok(NULL, " \t\n");
      if(token) {
        result.errFile = strdup(token);
        result.append = true;
      }
    } else {
      result.argv[result.argc++] = strdup(token);
    }

    token = strtok(NULL, " \t\n");
  }

  result.argv[result.argc] = NULL;
  return result;
}

void executePipeline(Command *cmds, int n, bool background) {
  if(n == 0) return;

  int (*pipes)[2] = NULL;
  if(n > 1) {
    pipes = malloc(sizeof(int[2]) * (n - 1));
    for(int i = 0; i < n - 1; i++) {
      if(pipe(pipes[i]) < 0) {
        perror("pipe");
        return;
      }
    }
  }

  pid_t *pids = malloc(sizeof(pid_t) * n);

  for(int i = 0; i < n; i++) {
    pid_t pid = fork();

    if(pid < 0) {
      perror("fork");
      continue;
    }

    if(pid == 0) {
      signal(SIGINT, SIG_DFL);

      if(i > 0)
        dup2(pipes[i - 1][0], STDIN_FILENO);

      if(i < n - 1)
        dup2(pipes[i][1], STDOUT_FILENO);

      if(pipes) {
        for(int j = 0; j < n - 1; j++) {
          close(pipes[j][0]);
          close(pipes[j][1]);
        }
      }
        

      handleRedirection(&cmds[i]);

      if(cmds[i].argc > 0 && cmds[i].argv[0]) {
        execvp(cmds[i].argv[0], cmds[i].argv);
        perror("execvp");
      }

      exit(EXIT_FAILURE);
    }

    pids[i] = pid;
  }

  if(pipes) {
    for(int i = 0; i < n - 1; i++) {
      close(pipes[i][0]);
      close(pipes[i][1]);
    }

    free(pipes);
  }

  if(!background)
    for(int i = 0; i < n; i++)
      waitpid(pids[i], NULL, 0);
  else
    printf("PID: %d\n", pids[n - 1]);

  free(pids);
}

void handleRedirection(Command *cmd) {
  if(cmd->inFile) {
    int fd = open(cmd->inFile, O_RDONLY);
    if(fd < 0) {
      perror("open input");
      exit(EXIT_FAILURE);
    }

    dup2(fd, STDIN_FILENO);
    close(fd);
  }

  if(cmd->outFile) {
    int flags = O_WRONLY | O_CREAT;

    flags |= cmd->append ? O_APPEND : O_TRUNC;
    int fd = open(cmd->outFile, flags, 0644);
    if(fd < 0) {
      perror("open output");
      exit(EXIT_FAILURE);
    }

    dup2(fd, STDOUT_FILENO);
    close(fd);
  }

  if(cmd->errFile) {
    int flags = O_WRONLY | O_CREAT;

    flags |= cmd->append ? O_APPEND : O_TRUNC;
    int fd = open(cmd->errFile, flags, 0644);
    if(fd < 0) {
      perror("open error output");
      exit(EXIT_FAILURE);
    }

    dup2(fd, STDERR_FILENO);
    close(fd);
  }
}

void freeCommand(Command *cmd) {
  if(!cmd) return;
  
  if(cmd->argv) {
    for(int i = 0; i < cmd->argc; i++)
      free(cmd->argv[i]);

    free(cmd->argv);
  }

  free(cmd->inFile);
  free(cmd->outFile);
  free(cmd->errFile);
}