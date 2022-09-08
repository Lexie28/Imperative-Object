#include <stdio.h>
#include <stdbool.h>
#include "utils.h"



void clear_input_buffer()
{
    int c;
      do
        {
          c = getchar();
        }
      while (c != '\n' && c != EOF);
    
}

int ask_question_int(char *question)
{

  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", question);
      conversions = scanf("%d", &result);
      
      clear_input_buffer();

    }
  while (conversions < 1);
  return result;
}



int read_string(char *buf, int buf_siz)
{

 char c;
 int j = 0;
      do
        {
          c = getchar();
          buf[j] = c;
          j++;
        }
      while (c != '\n' && c != EOF && j < buf_siz);
      buf[j-1] = '\0';

      return (j-1);

}


char *ask_question_string(char *question, char *buf, int buf_siz)

{
    int lengthchar;
    
    do
    {
        printf("%s\n", question);
        lengthchar = read_string(buf, buf_siz); 
        
    } while (lengthchar == 0);
    return buf;
    
}

