#pragma once
#include <stdbool.h>
#include <stddef.h>

#define int_elem(x) (elem_t) { .i=(x) }
#define ptr_elem(x) (elem_t) { .p=(x) }
#define unsigned_int_elem(x) (elem_t) { .u=(x) }
#define bool_elem(x) (elem_t) { .b=(x) }
#define float_elem(x) (elem_t) { .f=(x) }

typedef union elem elem_t;

union elem
{
  /// TODO: update the names of the fields to something better? 
  int i;
  unsigned int u;
  bool b;
  float f;
  void *p;
  /// other choices certainly possible
};

//Compares two elements and returns true if they are equal
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);