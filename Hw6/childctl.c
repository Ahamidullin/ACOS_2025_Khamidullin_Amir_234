#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define CHECK_ERR(x) do { if ((x) == -1) { perror(#x); exit(EXIT_FAILURE); } } while (0)

static volatile sig_atomic_t q_hits = 0;
static int signalQ;
static pid_t child_pid = -1;

static void generic_handler(int sig)
{
  if (sig == signalQ) {
    ++q_hits;
    dprintf(STDERR_FILENO,
            "\n[Got %s: %d/3]\n", strsignal(sig), q_hits);
  } else {
    dprintf(STDERR_FILENO,
            "\n[Caught: %s]\n", strsignal(sig));
  }
}

static void sigchld_handler(int sig)
{
  (void)sig;
  int status;
  while (waitpid(-1, &status, WNOHANG) > 0) {
    if (WIFSIGNALED(status))
      psignal(WTERMSIG(status), "Child terminated");
    else if (WIFEXITED(status))
      fprintf(stderr, "Child exited with %d\n", WEXITSTATUS(status));
    child_pid = -1;
  }
}

extern int lookup_signal(const char *);

int main(int argc, char *argv[])
{
  if (argc < 4) {
    fprintf(stderr,
            "Usage: %s <interval> <signalQ> <catch1> [catch2 …]\n", argv[0]);
    return EXIT_FAILURE;
  }

  int interval = atoi(argv[1]);
  if (interval <= 0) {
    fprintf(stderr, "Interval must be positive\n");
    return EXIT_FAILURE;
  }

  signalQ = lookup_signal(argv[2]);
  if (signalQ == -1) {
    fprintf(stderr, "Unknown signalQ: %s\n", argv[2]);
    return EXIT_FAILURE;
  }


  child_pid = fork();
  CHECK_ERR(child_pid);
  if (child_pid == 0) {
    while (1) pause();
  }

  printf("Forked child %d\n", child_pid);
  fflush(stdout);


  struct sigaction sa = { .sa_handler = generic_handler, .sa_flags = SA_RESTART };
  sigemptyset(&sa.sa_mask);

  for (int i = 3; i < argc; ++i) {
    int s = lookup_signal(argv[i]);
    if (s == -1 || s == SIGKILL || s == SIGSTOP) {
      fprintf(stderr, "Cannot handle %s – skipping\n", argv[i]);
      continue;
    }
    CHECK_ERR(sigaction(s, &sa, NULL));
  }


  struct sigaction sc = { .sa_handler = sigchld_handler, .sa_flags = SA_RESTART };
  sigemptyset(&sc.sa_mask);
  CHECK_ERR(sigaction(SIGCHLD, &sc, NULL));


  unsigned long tick = 0;
  for (;;) {
    printf("%d: tick %lu\n", (int)getpid(), tick++);
    fflush(stdout);

    unsigned rem = interval;
    while ((rem = sleep(rem)) != 0)
      ;

    if (q_hits >= 3) {
      fprintf(stderr, "signalQ hit 3 times – shutting down\n");
      if (child_pid > 0) {
        kill(child_pid, SIGTERM);
        waitpid(child_pid, NULL, 0);
      }
      break;
    }
  }
  return EXIT_SUCCESS;
}
