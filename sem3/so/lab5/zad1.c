#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int *buffer,
    M, N,
    head,
    tail;

pthread_mutex_t mutex;
sem_t empty, full;

void putItem(int x);
int getItem();
void *producer(void *arg);
void *consumer(void *arg);

int main(int argc, char *argv[]) {
  if(argc != 3) {
    printf("Usage: %s <M> <N>\n", argv[0]);
    return 1;
  }

  M = atoi(argv[1]);
  N = atoi(argv[2]);
  buffer = malloc(sizeof(int) * N);

  pthread_mutex_init(&mutex, NULL);
  sem_init(&empty, 0, N);
  sem_init(&full, 0, 0);

  pthread_t p1, p2, c1, c2;
  int *id;

  id = malloc(sizeof(int));
  *id = 1;
  pthread_create(&p1, NULL, producer, id);
  id = malloc(sizeof(int));
  *id = 2;
  pthread_create(&p2, NULL, producer, id);

  id = malloc(sizeof(int));
  *id = 1;
  pthread_create(&c1, NULL, consumer, id);
  id = malloc(sizeof(int));
  *id = 2;
  pthread_create(&c2, NULL, consumer, id);

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(c1, NULL);
  pthread_join(c2, NULL);

  pthread_mutex_destroy(&mutex);
  sem_destroy(&empty);
  sem_destroy(&full);
  free(buffer);

  return 0;
}

void putItem(int x) {
  buffer[head] = x;
  head = (head + 1) % N;
}

int getItem() {
  int item = buffer[tail];
  tail = (tail + 1) % N;
  return item;
}

void *producer(void *argument) {
  int id = *(int *)argument;
  int itemsToProduce = M / 2;

  int item;
  for(int i = 0; i < itemsToProduce; i++) {
    item = id * 1000 + i;

    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    putItem(item);
    printf(
      "[P%d] Produced: %d (Slot: %d)\n",
      id,
      item,
      (head - 1 + N) % N
    );

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
  }

  free(argument);
  return NULL;
}

void *consumer(void *argument) {
  int id = *(int *)argument;
  int itemsToConsume = M / 2;

  for(int i = 0; i < itemsToConsume; i++) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    int item = getItem();
    printf("\t[C%d] Consumed: %d\n", id, item);

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
  }

  free(argument);
  return NULL;
}