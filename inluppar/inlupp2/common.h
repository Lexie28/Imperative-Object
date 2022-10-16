#pragma once
#include <stdbool.h>
#define int_elem(x) (elem_t) { .i=(x) }
#define ptr_elem(x) (elem_t) { .p=(x) }
#define unsigned_int_elem(x) (elem_t) { .u=(x) }
#define bool_elem(x) (elem_t) { .b=(x) }
#define float_elem(x) (elem_t) { .f=(x) }

/**
 * @file common.h
 * @author Alexandra Dahlberg & Anthony Melinder
 * @date 06 October 2022
 * @brief Simple structs and functions used across all of the hash_table, linked_list and iterator-files.
 *
This header-file lists and defines all functions that are written for and used to make our hash table, linked lists and iterator structures. 
 */

typedef union elem elem_t;

union elem
{
  /// TODO: update the names of the fields to something better? 
  void *p;
  int i;
  unsigned int u;
  bool b;
  float f;
  /// other choices certainly possible
};

/// Compares two elements and returns true if they are equal
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);

/// @brief Check if two elements are equal (for integers)
/// @param a the first element 
/// @param b the second element
/// @return Boolean depending on if the elements are equal or not.
bool elem_equality_func_int(elem_t a, elem_t b);

/// @brief Check if two elements are equal (for char *)
/// @param a the first element 
/// @param b the second element
/// @return Boolean depending on if the elements are equal or not.
bool elem_equality_func_str(elem_t a, elem_t b);

/// @brief Check if two elements are equal (for unsigned integers)
/// @param a the first element 
/// @param b the second element
/// @return Boolean depending on if the elements are equal or not.
bool elem_equality_func_unsig_int(elem_t a, elem_t b);

/// @brief Check if two elements are equal (for booleans)
/// @param a the first element 
/// @param b the second element
/// @return Boolean depending on if the elements are equal or not.
bool elem_equality_func_bool(elem_t a, elem_t b); 

/// @brief Check if two elements are equal (for floats)
/// @param a the first element 
/// @param b the second element
/// @return Boolean depending on if the elements are equal or not.
bool elem_equality_func_float(elem_t a, elem_t b);