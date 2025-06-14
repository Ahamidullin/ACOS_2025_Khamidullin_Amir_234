#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  mqd_t mqd;
  struct mq_attr attr;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 2048;
  mqd = mq_open("/queue", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, &attr);

  char *buf;
  size_t n;
  unsigned int prio;
  printf("MQ start polling..\n");
  while (1) {
    buf = malloc(attr.mq_msgsize);
    n = mq_receive(mqd, buf, attr.mq_msgsize, &prio);
    buf[n] = '\0';
    if (!strcmp(buf, "QUIT"))
      break;
    printf("Received: %s\n", buf);
    free(buf);
  }
  printf("Received QUIT, unlinking and exiting.\n");
  mq_unlink("/queue");
  return 0;
}