#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

int main() {
  char command[20];
  bool cont = true;
  int v, i;
  List_t *list = malloc(sizeof(List_t));
  list->first = list->last = NULL;

  while (cont) {
    printf("Command: ");
    scanf("%s", command);

    if(!strcmp(command, "pop")) {
      if(!isEmpty(list)) {
        v = pop(list);
        printf("Result: %d\n", v);
      } else
        printf("[Error] stack is empty\n");
    } else if(!strcmp(command, "push")) {
      printf("Value: ");
      scanf("%d", &v);
      push(list, v);
      printf("Result: OK\n");
    } else if(!strcmp(command, "append")) {
      printf("Value: ");
      scanf("%d", &v);
      append(list, v);
      printf("Result: OK\n");
    } else if(!strcmp(command, "print")) {
      printf("Result: ");
      print(list);
    } else if(!strcmp(command, "length")) {
      v = length(list);
      printf("Result: %d\n", v);
    } else if(!strcmp(command, "get")) {
      printf("Index: ");
      scanf("%d", &i);
      if(i >= 1 && i <= list->length) {
        v = get(list, i);
        printf("Result: %d\n", v);
      } else
        printf("[Error] index out of bounds!\n");
    } else if(!strcmp(command, "put")) {
      printf("Index: ");
      scanf("%d", &i);
      printf("Value: ");
      scanf("%d", &v);
      if(i >= 1 && i <= list->length) {
        put(list, i, v);
        printf("Result: OK\n");
      } else
        printf("[Error] index out of bounds!\n");
    } else if(!strcmp(command, "insert")) {
      printf("Index: ");
      scanf("%d", &i);
      printf("Value: ");
      scanf("%d", &v);
      if(i >= 1 && i <= list->length + 1) {
        insert(list, i, v);
        printf("Result: OK\n");
      } else
        printf("[Error] index out of bounds!\n");
    } else if(!strcmp(command, "delete")) {
      printf("Index: ");
      scanf("%d", &i);
      if(i >= 1 && i <= list->length) {
        delete(list, i);
        printf("Result: OK\n");
      } else
        printf("[Error] index out of bounds!\n");
    } else if(!strcmp(command, "clean")) {
      clean(list);
      printf("Result: OK\n");
    } else if(!strcmp(command, "exit")) {
      cont = false;
    } else
      printf("Unknown command!\n");
  }

  clean(list);
  free(list);
  return 0;
}
