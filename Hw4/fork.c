#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pid = fork();
  if (pid == 0) {
    int pid2 = fork();
    if (pid2 == 0) {
      printf("Hello from Grandchild\n");
    } else {
      wait(NULL);
      printf("Hello from Child\n");
    }
  } else {
    wait(NULL);
    printf("Hello from Parent\n");
  }
  return 0;
}
