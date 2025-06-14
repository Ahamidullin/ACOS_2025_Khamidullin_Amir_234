#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s /queue Message\n", argv[0]);
    return -1;
  }
  mqd_t mqd;
  unsigned int prio;
  mqd = mq_open(argv[1], O_WRONLY);
  mq_send(mqd, argv[2], strlen(argv[2]), 1);
  return 0;
}