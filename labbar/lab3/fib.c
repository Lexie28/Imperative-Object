#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fib_rec(int i)
{
    if (i == 0)
    {
        return 1;
    }
    else if (i == 1)
    {
        return 1;
    }
    else
    {
        return (fib_rec(i-1) + fib_rec(i-2));
    }
}

int main(int argc, char *argv[]) //argc är hur många argument och argv är liksom listan med argument där du kan plocka ut indexet
{
  if (argc != 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    int n = atoi(argv[1]);
    if (n < 2)
    {
      printf("fib(%d) = %d\n", n, n);
    }
    else
    {
      printf("fib(%s) = %d\n", argv[1], fib_rec(n));
    }
  }
  return 0;
}