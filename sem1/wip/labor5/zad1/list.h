#pragma once

#include <stdbool.h>

typedef struct Node {
  int element;
  struct Node *next;
} Node;

typedef struct List_t {
  Node *first;
  Node *last;
  int length;
} List_t;

bool isEmpty(List_t *list);

int  pop(List_t *list);
void push(List_t *list, int element);
void append(List_t *list, int element);

int  get(List_t *list, int index);
void put(List_t *list, int index, int element);
void insert(List_t *list, int index, int element);
void delete(List_t *list, int index);

void print(List_t *list);
int  length(List_t *list);
void clean(List_t *list);