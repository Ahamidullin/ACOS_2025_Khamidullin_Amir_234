#define _POSIX_C_SOURCE 200809L
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int sum = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

struct sum_args {
  size_t start, end;
  const int *arr;
};

void *thread_sum(void *arg)
{
  const struct sum_args *a = arg;
  long local = 0;

  for (size_t i = a->start; i < a->end; ++i)
    local += a->arr[i];

  pthread_mutex_lock(&mtx);
  sum += local;
  pthread_mutex_unlock(&mtx);
  return NULL;
}

int main(void)
{
  srand((unsigned)time(NULL));

  size_t n;
  if (scanf("%zu", &n) != 1 || n < 1) {
    fprintf(stderr, "Bad N\n");
    return EXIT_FAILURE;
  }

  int *arr = malloc(n * sizeof *arr);
  if (!arr) { perror("malloc"); return EXIT_FAILURE; }

  for (size_t i = 0; i < n; ++i) {
    arr[i] = rand() % 10;
    printf("%d ", arr[i]);
  }
  puts("");

  const int THREADS = 4;
  pthread_t tid[THREADS];
  struct sum_args args[THREADS];
  size_t part = (n + THREADS - 1) / THREADS;

  for (int i = 0; i < THREADS; ++i) {
    args[i].start = i * part;
    size_t end = (i + 1) * part;
    args[i].end  = end > n ? n : end;
    args[i].arr  = arr;

    if (pthread_create(&tid[i], NULL, thread_sum, &args[i])) {
      perror("pthread_create");
      free(arr);
      return EXIT_FAILURE;
    }
  }

  for (int i = 0; i < THREADS; ++i)
    pthread_join(tid[i], NULL);

  printf("Sum = %d\n", sum);

  pthread_mutex_destroy(&mtx);
  free(arr);
  return EXIT_SUCCESS;
}
