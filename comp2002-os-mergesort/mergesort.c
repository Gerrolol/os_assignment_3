/**
 * This file implements parallel mergesort.
 */

#include "mergesort.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> /* for malloc */
#include <string.h> /* for memcpy */

/* this function will be called by mergesort() and also by parallel_mergesort().
 */
void merge(int leftstart, int leftend, int rightstart, int rightend) {}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right) {}

/* this function will be called by the testing program. */
void* parallel_mergesort(void* arg) {
  struct argument* args = (struct argument*)arg;
  if (args->right - args->left <= 0) return NULL;
  if (args->level == cutoff)
    my_mergesort(args->left, args->right);
  else {
    int center = (args->left + args->right) / 2;
    pthread_t loThread;
    pthread_t hiThread;
    struct argument* loArgs =
        buildArgs(args->left, center - 1, args->level + 1);
    struct argument* hiArgs = buildArgs(center, args->right, args->level + 1);
    pthread_create(&loThread, NULL, parallel_mergesort, loArgs);
    pthread_create(&hiThread, NULL, parallel_mergesort, hiArgs);
    pthread_join(loThread, NULL);
    pthread_join(hiThread, NULL);
    merge(args->left, center - 1, center, args->right);
  }
  return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument* buildArgs(int left, int right, int level) {
  struct argument* arg = (struct argument*)malloc(sizeof(struct argument));
  arg->left = left;
  arg->right = right;
  arg->level = level;
  return arg;
}