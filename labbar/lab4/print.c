#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


void print(char *str)
{
  while (*str != '\0')
  {
    putchar(*str);
    *str++;
  }
}

void main()
{
    print("Hej \n");
}

////////////////////////////////////////////////////////////

/*

void print (char str[])
{
  int word = 0;
  while (str[word] != '\0')
  {
    putchar(str[word]);
    word++;
  }
}

void println(char str[])
{
  print(str);
  printf("\n");
}

*/