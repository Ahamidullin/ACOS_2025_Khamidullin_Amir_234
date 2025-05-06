#include <stdio.h>

void bill(char *arg)
{
  printf("interposed bill: %s\n", arg);
}

void sam(double x)
{
  printf("interposed sam: %.2f\n", x);
}
