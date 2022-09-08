#include <stdio.h>
#include <string.h>

int string_length (char* str)
{
    int i = 0;
    while(str[i] != '\0') i++;
    return i;
}
/*
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s words or string", argv[0]);
  }
  else
  {
    for (int i = 1; i < argc; ++i)
    {
      int expected = strlen(argv[i]);
      int actual   = string_length(argv[i]);
      printf("strlen(\"%s\")=%d\t\tstring_length(\"%s\")=%d\n",
             argv[i], expected, argv[i], actual);
    }
  }
  return 0;
}

*/

void print(char chr)
{
  while (chr != '\0')
  {
    putchar(chr);
    chr++;
  }
}

int main()
{
    print("Hej");
}



//???????


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