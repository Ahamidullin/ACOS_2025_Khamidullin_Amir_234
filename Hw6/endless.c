#include <stdio.h>
#include <unistd.h>

int main(void)
{
  for (int i = 0;; ++i) {
    sleep(1);
    printf("%d\n", i);
    fflush(stdout);
  }
  return 0;
}

