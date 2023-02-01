#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5
#define NUM_MEALS 3

#define LOW_THINK_TIME 100
#define HIGH_THINK_TIME 2000
#define LOW_SLEEP_TIME 25
#define HIGH_SLEEP_TIME 50

pthread_mutex_t forks[NUM_FORKS];
pthread_t philosophers[NUM_PHILOSOPHERS];

unsigned int getThinkTime() {
  return (rand() % (HIGH_THINK_TIME - LOW_THINK_TIME + 1)) + LOW_THINK_TIME;
}

unsigned int getEatTime() {
  return (rand() % (HIGH_SLEEP_TIME - LOW_SLEEP_TIME + 1)) + LOW_SLEEP_TIME;
}

void think(int id) {
  printf("Philosopher %d starts thinking.\n", id);
  usleep(getThinkTime() * 1000);
  printf("Philosopher %d finished thinking.\n", id);
}

void eat(int id, int leftFork, int rightFork) {
  pthread_mutex_lock(&forks[leftFork]);
  pthread_mutex_lock(&forks[rightFork]);
  printf("Philosopher %d starts eating om nom nom nom.\n", id);
  usleep(getEatTime() * 1000);
  printf("Philosopher %d finished eating.\n", id);
  pthread_mutex_unlock(&forks[leftFork]);
  pthread_mutex_unlock(&forks[rightFork]);
}

void *philosopher(void *id) {
  int philosopherId = *(int *)id;
  int leftFork = philosopherId;
  int rightFork = (philosopherId + 1) % NUM_FORKS;

  for (int i = 0; i < NUM_MEALS; i++) {
    think(philosopherId);
    eat(philosopherId, leftFork, rightFork);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  for (int i = 0; i < NUM_FORKS; i++) {
    pthread_mutex_init(&forks[i], NULL);
  }

  int ids[NUM_PHILOSOPHERS];
  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    ids[i] = i;
    pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
  }

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_join(philosophers[i], NULL);
  }

  return 0;
}
