#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void replace_with_regexp(const char *pattern, const char *text, const char* replacement) {
  regex_t regex;
  regmatch_t regmatch;
  int status;
  if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
    printf("Error compiling regex\n");
    return;
  }
  size_t bufsize = strlen(text) + 1;
  char *buffer = (char*) malloc(bufsize);
  if (buffer == NULL) {
    printf("Error allocating memory\n");
    regfree(&regex);
    return;
  }
  buffer[0] = '\0';
  const char *current = text;
  while ((status = regexec(&regex, current, 1, &regmatch, 0)) == 0) {
    size_t prefix_len = regmatch.rm_so;
    size_t needed_size = bufsize + prefix_len + strlen(replacement) + 1;
    if (needed_size > bufsize) {
      char *old = buffer;
      bufsize = needed_size * 2;
      buffer = (char*) realloc(buffer, bufsize); // bufsize - полный размер
      if (buffer == NULL) {
        free(old);
        printf("Error reallocating memory\n");
        regfree(&regex);
        return;
      }
    }
    strncat(buffer, current, prefix_len);
    strcat(buffer, replacement);
    current += regmatch.rm_eo;
  }
  strcat(buffer, current);
  printf("%s\n", buffer);
  regfree(&regex);
  free(buffer);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: %s <regexp> <text> <replacement>\n", argv[0]);
    return 1;
  }
  replace_with_regexp(argv[1], argv[2], argv[3]);
  return 0;
}
// функции 3 параметра с заменой
// строковые функции

/*

cat
cat lives in a cathouse
dog


dog lives in a doghouse


[0-9]+
It is the year 2025. I am 35 years old this year.
NUMBER

It is the year NUMBER. I am NUMBER years old this year.
*/