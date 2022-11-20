#include "common.h"
#include <stdbool.h>
#include <string.h>

bool elem_equality_func_int(elem_t a, elem_t b)
{    
    return a.i == b.i;
}



bool elem_equality_func_str(elem_t a, elem_t b)
{    
    if (strcmp(a.p, b.p) == 0) //If the characters/strings are equal, return true.
    { 
        return true;
    }
    else // If it is not true for any of these, return false.
    {
        return false;
    }
}

bool elem_equality_func_unsig_int(elem_t a, elem_t b)
{    
    if (a.u == b.u) //If the unsigned integers are equal, return true.
    { 
        return true;
    }
    else // If it is not true for any of these, return false.
    {
        return false;
    }
} 

bool elem_equality_func_bool(elem_t a, elem_t b)
{    
    if (a.b == b.b) //If the bools are equal, return true.
    { 
        return true;
    }
    else // If it is not true for any of these, return false.
    {
        return false;
    }
} 

bool elem_equality_func_float(elem_t a, elem_t b)
{    
    if (a.b == b.b) //If the floats are equal, return true.
    { 
        return true;
    }
    else // If it is not true for any of these, return false.
    {
        return false;
    }
} 
