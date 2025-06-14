#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

#define CHECK_ERR(x) do { if ((x) == -1) { perror(#x); exit(EXIT_FAILURE); } } while (0)

static volatile sig_atomic_t caught = 0;

static void handler(int sig)
{
  const char *txt = strsignal(sig);
  if (txt)
    write(STDERR_FILENO, "[Caught: ", 9);
  if (txt) {
    write(STDERR_FILENO, txt, strlen(txt));
    write(STDERR_FILENO, "]", 1);
  }
  caught = 1;
}

static int str2sig(const char *s);

int main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <interval_sec> <SIG1> [SIG2 …]\n", argv[0]);
    return EXIT_FAILURE;
  }

  int interval = atoi(argv[1]);
  if (interval <= 0) {
    fprintf(stderr, "Interval must be positive\n");
    return EXIT_FAILURE;
  }

  struct sigaction sa = { .sa_handler = handler, .sa_flags = SA_RESTART };
  sigemptyset(&sa.sa_mask);

  for (int i = 2; i < argc; ++i) {
    int sig = str2sig(argv[i]);
    if (sig == -1) {
      fprintf(stderr, "Unknown/uncatchable signal: %s\n", argv[i]);
      continue;
    }
    if (sig == SIGKILL || sig == SIGSTOP) {
      fprintf(stderr, "Signal %s cannot be caught, skipping\n", argv[i]);
      continue;
    }
    CHECK_ERR(sigaction(sig, &sa, NULL));
  }

  pid_t me = getpid();
  unsigned long cnt = 0;

  for (;;) {
    printf("%d: %lu\n", (int)me, cnt++);
    fflush(stdout);

    unsigned rem = interval;
    while ((rem = sleep(rem)) != 0)
      ;
    if (caught) { write(STDERR_FILENO, "\n", 1); caught = 0; }
  }
}


#include <ctype.h>
static int str2sig(const char *s)
{
  extern int lookup_signal(const char *);   /* из killn.c */
  return lookup_signal(s);
}
