#include <stdio.h>
#include "utils.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "frontend.h"

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


bool not_empty(char *str)
{
  return strlen(str) > 0;
}


answer_t ask_question(char *question, check_func check, convert_func convert)
{
    int buf_siz=255;
    char buf[buf_siz];

    do
    {
    printf("%s", question);
    read_string(buf,buf_siz);
    } while (check(buf) == false);
    return convert(buf);

}


char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).string_value;
}


int ask_question_int(char *question)
{
 return ask_question(question, is_number, (convert_func) atoi).int_value;
}

char ask_question_char(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).string_value[0];
}


void clear_input_buffer()
{
    int c;
      do
        {
          c = getchar();
        }
      while (c != '\n' && c != EOF);
    
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

bool is_menu_answer(char *menuans)
{

    if (strlen(menuans) > 1) 
    {
        return false;
    }
    else 
    {
        char newans = toupper(menuans[0]);
        char *correctanswers = "LETRGHAQ";

        for (int i = 0; i < strlen(correctanswers); i++)
        {
            if (correctanswers[i] == newans) return true;
        }
    }
    return false;
}


char ask_question_menu(char *question)
{
    return ask_question(question, is_menu_answer, (convert_func) strdup).string_value[0];
}

bool is_shelf(char *shelf)
{
    if (strlen(shelf) >= 2 && isalpha(shelf[0]))
    {
        for (int i = 1; i < strlen(shelf); i++)
        {
            if (isdigit(shelf[i]) == false)
            {
                return false;
            }
        }
        return true;
    }
    else {
        return false;
    }
}