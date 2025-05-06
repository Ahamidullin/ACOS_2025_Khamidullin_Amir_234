#include <stdio.h>

void fred(int arg)
{
  printf("interposed fred: %d\n", arg);
}

void john(double x)
{
  printf("interposed john: %.2f\n", x);
}
