#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

extern char *strdup(const char *);

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;


typedef bool (*check_func)(char *);
typedef answer_t (*convert_func)(char *);

bool not_empty(char *str)
{
  return strlen(str) > 0;
}

answer_t ask_question(char *question, check_func check, convert_func convert)
{
    int buf_siz=255;
    char buf[buf_siz];

    while (check(buf) == false)
    {
    
    printf("%s", question);
    read_string(buf,buf_siz);
    }
    return convert(buf);

}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).string_value;
}


int main(int argc, char const *argv[])
{
   char * answer = ask_question_string("Hej?");  
   printf("%s",answer);
    return 0;


}

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

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.int_value; // svaret som ett heltal
}

