#include <bits/types/siginfo_t.h>
#include <fcntl.h>
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sigint_handler(int signum, siginfo_t *siginfo, void *idk) {
  printf("Received SIGINT, unlinking and exiting.\n");
  if (!mq_unlink("/queue")) {
    perror("Error unlinking queue.");
  }
  exit(0);
}

int main() {
  struct sigaction sigint;
  sigint.sa_sigaction = &sigint_handler;

  sigaction(SIGINT, &sigint, NULL);
  mqd_t mqd;
  struct mq_attr attr;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 2048;
  mqd = mq_open("/queue", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, &attr);
  if (mqd == -1) {
    perror("Error opening queue. Exiting.");
    return 0;
  }

  char *buf;
  size_t n;
  unsigned int prio;
  printf("MQ start polling..\n");
  while (1) {
    buf = malloc(attr.mq_msgsize);
    n = mq_receive(mqd, buf, attr.mq_msgsize, &prio);

    if (n == -1) {
      perror("Error receiving message. Skipping..");
      continue;
    }

    buf[n] = '\0';
    if (!strcmp(buf, "QUIT"))
      break;
    printf("Received: %s\n", buf);
    free(buf);
  }
  printf("Received QUIT, unlinking and exiting.\n");
  if (!mq_unlink("/queue")) {
    perror("Error unlinking queue.");
  }
  return 0;
}