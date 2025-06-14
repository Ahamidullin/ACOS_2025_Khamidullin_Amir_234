#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define CHECK_ERR(x) do { if ((x) == -1) { perror(#x); exit(EXIT_FAILURE); } } while (0)

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <interval_sec>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int interval = atoi(argv[1]);
  if (interval <= 0) {
    fprintf(stderr, "Interval must be positive\n");
    return EXIT_FAILURE;
  }

  pid_t me = getpid();
  unsigned long counter = 0;

  for (;;) {
    printf("%d: %lu\n", (int)me, counter++);
    fflush(stdout);

    unsigned rem = interval;
    while ((rem = sleep(rem)) != 0)
      ;
  }
}
