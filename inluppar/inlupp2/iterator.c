#include "iterator.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct link
{
    elem_t value;
    struct link *next;
};

typedef struct link link_t;

struct iterator
{
    link_t *current;
    ioopm_list_t *list; 
};

typedef struct iterator ioopm_list_iterator_t;

struct list
{
    link_t *head;
    size_t size;
};

typedef struct list ioopm_list_t;

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list)
{
  ioopm_list_iterator_t *result = calloc(1, sizeof(ioopm_list_iterator_t));
  result->current = list->head;
  result->list = list; /// Iterator remembers where it came from

  return result; 
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter)
{
    if (iter->current == NULL)
    {
        return false;
    }
    else if (iter->current->next == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter)
{
    if (ioopm_iterator_has_next(iter) == false)
    {
        return ptr_elem(NULL);
    }
    else
    {
        iter->current = iter->current->next;
        return iter->current->value;
    }
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
{
    iter->current = iter->list->head;
}

elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter)
{
    return iter->current->value;
}

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free (iter);
}
