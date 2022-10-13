#pragma once

#include <stdbool.h>

extern char *strdup(const char *);

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool (*check_func)(char *);
typedef answer_t (*convert_func)(char *);

extern char *strdup(const char *);
int read_string(char *buf, int buf_siz);
bool is_number(char *str);
bool not_empty(char *str);
answer_t ask_question(char *question, check_func check, convert_func convert);
char *ask_question_string(char *question);
int ask_question_int(char *question);
bool is_menu_answer(char *menuans);
char ask_question_menu(char *question);
char ask_question_char(char *question);
bool is_shelf(char *shelf);

