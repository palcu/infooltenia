#include <stdio.h>
#include <math.h>

int main()
{
  int x, y;

  fscanf(fopen("sum.in", "r"), "%d%d", &x, &y);
  fprintf(fopen("sum.out", "w"), "%d\n", x + y);
  return(0);
}
