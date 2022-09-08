#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <ctype.h>

bool is_number(char *str)
{
    int i = 0;
    int size = strlen(str);

    if (size == 1 && str[0] == '-') return false;

    if (str[0] == '-') i = 1;

    for (; i < size; i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (argc > 1 && is_number(argv[1]))
{
  printf("%s is a number\n", argv[1]);
}
else
{
  if (argc > 1)
  {
    printf("%s is not a number\n", argv[1]);
  }
  else
  {
    printf("Please provide a command line argument!\n");
  }
}

}