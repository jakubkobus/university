#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>
#include <stdbool.h>

#define  MAX_CLIENTS  10
#define  BUF_SIZE     1024

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

typedef struct {
  int fd;
  bool isLoggedIn;
  char login[32];
} Client;

void handleClientData(int index);
void sendMessage(int fd, char *message);

Client clients[MAX_CLIENTS];
int maxFd;

int main(int argc, char *argv[]) {
  if(argc < 2) {
    printf("Usage: %s <port>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int listener, newFd;
  sockaddr_in serverAddress, clientAddress;
  socklen_t addressLength;
  fd_set mainSet, readFds;

  for(int i = 0; i < MAX_CLIENTS; i++) {
    clients[i].fd = 0;
    clients[i].isLoggedIn = false;
  }

  if((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  int yes = 1;
  setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(atoi(argv[1]));
  memset(&(serverAddress.sin_zero), '\0', 8);

  if(bind(listener, (sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
    perror("bind");
    exit(1);
  }

  if(listen(listener, 10) == -1) {
    perror("listen");
    exit(1);
  }

  FD_ZERO(&mainSet);
  FD_SET(listener, &mainSet);
  maxFd = listener;

  printf("Server listens on port %s...\n", argv[1]);

  int j;
  while(true) {
    readFds = mainSet;

    if(select(maxFd + 1, &readFds, NULL, NULL, NULL) == -1) {
      perror("select");
      exit(1);
    }

    for(int i = 0; i <= maxFd; i++) {
      if(FD_ISSET(i, &readFds)) {
        if(i == listener) {
          addressLength = sizeof(clientAddress);
          newFd = accept(listener, (sockaddr *)&clientAddress, &addressLength);

          if(newFd == -1) {
            perror("accept");
          } else {
            for(j = 0; j < MAX_CLIENTS; j++) {
              if(clients[j].fd == 0) {
                clients[j].fd = newFd;
                sendMessage(newFd, "Login: ");

                if(newFd > maxFd)
                  maxFd = newFd;

                FD_SET(newFd, &mainSet);

                break;
              }
            }

            if(j == MAX_CLIENTS) {
              sendMessage(newFd, "Server is full\n");
              close(newFd);
            }
          }
        } else {
          int clientIndex = -1;
          for(int k = 0; k < MAX_CLIENTS; k++)
            if(clients[k].fd == i)
              clientIndex = k;

          handleClientData(clientIndex);
          if(clients[clientIndex].fd == 0)
            FD_CLR(i, &mainSet);
        }
      }
    }
  }

  return 0;
}

void sendMessage(int fd, char *message) {
  send(fd, message, strlen(message), 0);
}

void handleClientData(int index) {
  char buffer[BUF_SIZE];
  int nBytes = recv(clients[index].fd, buffer, sizeof(buffer) - 1, 0);

  if(nBytes <= 0) {
    if(nBytes == 0)
      printf("User disconnected: %s\n", clients[index].login);
    else
      perror("recv");

    close(clients[index].fd);
    clients[index].fd = 0;
    clients[index].isLoggedIn = false;
    return;
  }

  buffer[nBytes] = '\0';
  char *newline = strchr(buffer, '\n');
  if(newline)
    *newline = '\0';

  if(!clients[index].isLoggedIn) {
    strncpy(clients[index].login, buffer, 31);
    clients[index].isLoggedIn = true;

    printf("Logged in: %s (ID: %d)\n", clients[index].login, index);

    char listMessage[BUF_SIZE] = "Logged in users:\n";
    for(int i = 0; i < MAX_CLIENTS; i++) {
      if(clients[i].fd > 0 && clients[i].isLoggedIn) {
        char entry[64];

        sprintf(entry, "- %s (ID: %d)\n", clients[i].login, i);
        strcat(listMessage, entry);
      }
    }

    sendMessage(clients[index].fd, listMessage);
  } else {
    if(strncmp(buffer, "QUIT", 4) == 0) {
      close(clients[index].fd);
      clients[index].fd = 0;
    } else if(strncmp(buffer, "SEND", 4) == 0) {
      char targetLogin[32], messageContent[BUF_SIZE];
      int parsed = sscanf(buffer + 5, "%s %[^\n]", targetLogin, messageContent);

      if(parsed < 2) {
        sendMessage(clients[index].fd, "[ERROR] Usage: SEND <login> <message>\n");
      } else {
        bool found = false;
        for(int i = 0; i < MAX_CLIENTS; i++) {
          if(clients[i].fd > 0 && strcmp(clients[i].login, targetLogin) == 0) {
            char finalMessage[BUF_SIZE];

            sprintf(finalMessage, "FROM %s: %s\n", clients[index].login, messageContent);
            sendMessage(clients[i].fd, finalMessage);
            found = true;

            break;
          }
        }

        if(!found)
          sendMessage(clients[index].fd, "[ERROR] User not found\n");
      }
    }
  }
}