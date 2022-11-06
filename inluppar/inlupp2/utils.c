#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool not_empty(char *str)
{
  return strlen(str) > 0;
}

void clear_buffer(char *buf) {
    for(int i = 0; i < sizeof(buf); i++) {
        i[buf] = 0; // Just cause
    }
}

void clear_input_buffer() {
    char c;
    do {
        c = getchar();
    } while (c != '\n');
}

bool is_number(char *str) {
    char chr = '\0';
    for(int i = 0; i < strlen(str); i++) {
        chr = str[i];
        if(chr < 48 || chr > 57) {
            return false;
        }
    }
    return true;
}  

int read_string(char *buf, int buf_siz) {
    int i;
    char c;
    // Without clear_buffer causes previous inputs that were rejected to be carried over 
    // into a shorter validated input or may cause shorter valid inputs to be rejected
    clear_buffer(buf); 
    for(i = 0; i < buf_siz-1; i++) {
        c = getchar();
        if(c != '\n') {
            buf[i] = c;
        } else break;
    }
    if(i == 0) {return 0;}
    buf[i+1] = '\0';
    return i;
}

answer_t ask_question(char *question, check_func check, convert_func convert) {
    char buf[255] = {0};
    do {
        puts(question);
        read_string(buf, 255);
    } while(!check(buf));
    return convert(buf);
}

char *ask_question_string(char *question)
{
    return ask_question(question, not_empty, (convert_func) strdup).string_value;
}

int ask_question_int(char *question)
{
    answer_t answer = ask_question(question, is_number, (convert_func) atoi);
    return answer.int_value; // svaret som ett heltal
}

char get_char(char *buf) {
  return buf[0];
}

char ask_question_char(char *question)
{
    return ask_question(question, not_empty, (convert_func) get_char).char_value;
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
        char *correctanswers = "LETRGHIAQS";

        for (int i = 0; i < strlen(correctanswers); i++)
        {
            if (correctanswers[i] == newans) return true;
        }
    }
    return false;
}

char *ask_question_menu(char *question)
{
    return ask_question(question, is_menu_answer, (convert_func) strdup).string_value;
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
