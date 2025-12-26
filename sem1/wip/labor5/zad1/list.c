#include "list.h"

#include <stdio.h>
#include <stdlib.h>

bool isEmpty(List_t *list) {
  return !list->length;
}

int pop(List_t *list) {
  Node *n = list->first;
  int e = n->element;
  list->first = n->next;

  if(list->first == NULL)
    list->last = NULL;

  list->length--;
  
  free(n);
  return e;
}

void push(List_t *list, int element) {
  Node *n = malloc(sizeof(Node));
  n->element = element;
  n->next = list->first;
  list->first = n;

  if(list->last == NULL)
    list->last = n;

  list->length++;
}

void append(List_t *list, int element) {
  Node *n = malloc(sizeof(Node));
  n->element = element;
  
  if(list->first == NULL)
    list->first = n;
  else
    list->last->next = n;
  
  list->last = n;

  list->length++;
}

void print(List_t *list) {
  Node *n = list->first;
  
  while(n != NULL) {
    printf(" %d ", n->element);
    n = n->next;
  }

  printf(" ( %d )\n", list->length);
}

int length(List_t *list) {
  int len = 0;
  Node *n = list->first;
  
  while(n != NULL && ++len)
    n = n->next;

  return len;
}

int get(List_t *list, int index) {
  Node *n = list->first;
  for(int i = 1; i < index; i++)
    n = n->next;

  return n->element;
}

void put(List_t *list, int index, int element) {
  Node *n = list->first;
  for(int i = 1; i < index; i++)
    n = n->next;
  
  n->element = element;
}

void insert(List_t *list, int index, int element) {
  Node *n = malloc(sizeof(Node));
  n->element = element;

  if(index == 1) {
    n->next = list->first;
    list->first = n;
    if(list->length == 0)
      list->last = n;
  } else {
    Node *prev = list->first;
    for(int i = 1; i < index - 1; i++)
      prev = prev->next;

    n->next = prev->next;
    prev->next = n;

    if(n->next == NULL)
      list->last = n;
  }

  list->length++;
}

void delete(List_t *list, int index) {
  if(index == 1) {
    pop(list);
    return;
  }

  Node *n = list->first;
  for(int i = 1; i < index - 1; i++)
    n = n->next;

  Node *tmp = n->next;
  n->next = tmp->next;

  if(n->next == NULL)
    list->last = n;

  free(tmp);
  list->length--;
}

void clean(List_t *list) {
  while(!isEmpty(list))
    pop(list);
}