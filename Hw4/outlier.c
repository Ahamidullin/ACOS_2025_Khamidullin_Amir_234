#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s command output_filename\n", argv[0]);
    return 1;
  }

  char *command = argv[1];
  char *output_filename = argv[2];
  FILE *output_file = fopen(output_filename, "w");

  if (output_file == NULL) {
    perror("fopen");
    return 1;
  }
  if (freopen(output_filename, "w", stdout) == NULL) {
    perror("freopen");
    return 1;
  }
  int ret = system(command);
  if (ret == -1) {
    perror("system");
    return 1;
  }
  return 0;
}
