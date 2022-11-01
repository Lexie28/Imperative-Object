#pragma once
#include <stdbool.h>

extern char *strdup(const char *);

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
  char char_value;
} answer_t;

typedef bool(*check_func)(char *);

typedef answer_t(*convert_func)(char *);

/// @brief Reads string from stdin into buf up until buf is full
/// @param buf string buffer  
/// @param buf_siz string buffer size
/// @return real string size
int read_string(char *buf, int buf_siz);

/// @brief Checks if str is a numbers
/// @param str 
/// @return If str is a number
bool is_number(char *str);

/// @brief Asks question and checks if valid int
/// @param question 
/// @return User input int
int ask_question_int(char *question);

/// @brief Asks question and checks if its a valid string
/// @param question 
/// @return User input string
char *ask_question_string(char *question);

/// @brief Checks if str is empty or not
/// @param str 
/// @return 
bool not_empty(char *str);

/// @brief
/// @param question user promt in console
/// @param check    checking function to validate user input
/// @param convert  convert function from a type to answer_t
/// @return 
answer_t ask_question(char *question, check_func check, convert_func convert);

/// @brief checking that a string is a valid input as a shelf (written correctly, e.g. "A45")
/// @param shelf the shelf we want to check to be a valid input
/// @return a bool returning true if the input is valid as a shelf
bool is_shelf(char *shelf);

/// @brief checking that the input is of correct type and structure for our menu's options
/// @param menuans the answer we're checking if it is a valid input
/// @return a bool returning true if the input is valid for our menu
bool is_menu_answer(char *menuans);

/// @brief
/// @param 
/// @return
char *ask_question_menu(char *question);

/// @brief
/// @param 
/// @return
char ask_question_char(char *question);
