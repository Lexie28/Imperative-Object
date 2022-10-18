#pragma once

#include <stdbool.h>


/**
 * @file utils.h
 * @author Alexandra Dahlberg & Vincent Andersson
 * @date 18 Oktober 2022
 * @brief Utility functions for a functioning database (e.g. to be used by a store)
 *
This header-file lists and defines all utility functions that are written for and used to make our database.
 */

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

/// @brief checking if our input is a number
/// @param str a string which is our input (which we are checking if it is a number)
/// @return a bool indicating whether our string is a number. is_number returns true if it is.
bool is_number(char *str);

/// @brief checking if our string is an empty string
/// @param str the string we want to check
/// @return a bool returning true is the string is not empty
bool not_empty(char *str);

/// @brief a compressed way to answer a question, check that our input is valid, and eventually convert the input
/// @param question the question we ask the user
/// @param check a function checking that our input is valid
/// @param convert a function that converts the user input to the type we want
/// @return the answer to the question we asked
answer_t ask_question(char *question, check_func check, convert_func convert);

/// @brief asking a question that takes a string as an input
/// @param question the question that is asked
/// @return the string-answer
char *ask_question_string(char *question);

/// @brief asking a question that takes an int as an input
/// @param question the question that is asked
/// @return the int-answer
int ask_question_int(char *question);

/// @brief checking that the input is of correct type and structure for our menu's options
/// @param menuans the answer we're checking if it is a valid input
/// @return a bool returning true if the input is valid for our menu
bool is_menu_answer(char *menuans);

/// @brief asking a question for an input that is valid for our menu
/// @param question the question that is asked
/// @return the character-answer
char ask_question_menu(char *question);

/// @brief asking a question which takes a character as an input
/// @param question the question that is asked
/// @return the character-answer
char ask_question_char(char *question);

/// @brief checking that a string is a valid input as a shelf (written correctly, e.g. "A45")
/// @param shelf the shelf we want to check to be a valid input
/// @return a bool returning true if the input is valid as a shelf
bool is_shelf(char *shelf);

