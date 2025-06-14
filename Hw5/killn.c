#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

int lookup_signal(const char *s);

int main(int argc, char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <PID> <SIGNAL>\n", argv[0]);
    return EXIT_FAILURE;
  }

  errno = 0;
  char *end;
  long pid_long = strtol(argv[1], &end, 10);
  if (*end != '\0' || errno || pid_long <= 0) {
    fprintf(stderr, "Invalid PID: %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  pid_t pid = (pid_t)pid_long;

  int sig = lookup_signal(argv[2]);
  if (sig == -1) {
    fprintf(stderr, "No such signal: %s\n", argv[2]);
    return EXIT_FAILURE;
  }

  if (kill(pid, sig) == -1) {
    perror("kill");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
