#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

struct link
{
    int value;
    struct link *next;
};

typedef struct link link_t;

struct list
{
    link_t *head;
    size_t size;
};

typedef struct list ioopm_list_t;


ioopm_list_t *ioopm_linked_list_create(void)
{
    ioopm_list_t *result = calloc(1, sizeof(ioopm_list_t));
    return result;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
    ioopm_linked_list_clear(list);
    free(list);
}

static link_t *create_link(int v, link_t *n)
{
    link_t *newlink = calloc(1, sizeof(link_t));
    newlink->value = v;
    newlink->next = n;
    return newlink;
}


void ioopm_linked_list_append(ioopm_list_t *list, int value)
{
    if (list->size == 0)
    {
        ioopm_linked_list_prepend(list, value);
    }
    else
    {
        link_t *link = list->head;
        for (int i = 1; i < list->size; i++)
        {
            link = link->next;
        }
        link->next = create_link(value, NULL);
        list->size++;
    }
}



/// @brief Insert at the front of a linked list in O(1) time
/// @param list the linked list that will be prepended to
/// @param value the value to be prepended
void ioopm_linked_list_prepend(ioopm_list_t *list, int value)
{
    link_t *firstlink = list->head; // pekare till första entryt
    link_t *newfirstlink = create_link(value, firstlink);
    list->head = newfirstlink;
    list->size++;
}

void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
{
    if (index < 0 || index > list->size)
    {
        return;
    }
    if (index == 0)
    {
        ioopm_linked_list_prepend(list, value);
        return;
    }

    if (index == list->size)
    {
        ioopm_linked_list_append(list, value);
        return;
    }

    link_t *link = list->head;
    for (int i = 0; i < index - 1; i++)
    {
        link = link->next;
    }
    link_t *next = link->next;
    link->next = create_link(value, next);
    list->size++;
}

int ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
    link_t *link = list->head;
    if (index < 0 || index > list->size)
    {
        return -999;
    }
    else if (index == 0)
    {
        int removeVal = link->value; // Get return value of remove entry.
        list->head = link->next;     // Set new head
        free(link);                  // Free memory used by head.
        list->size--;                // Decrease size.
        return removeVal;            // Return value of head.
    }
    else
    {
        for (int i = 0; i < index - 1; i++) // Get to the link entry BEFORE the one we want to remove.
        {
            link = link->next;
        }
        link_t *remove = link->next;   // Get the entry we want to remove
        link->next = link->next->next; // Connect the entries before and after remove entry.
        list->size--;                  // Decrease our list size value.
        int result = remove->value;    // The value of index we want to remove (return val)
        free(remove);                  // Free memory used by the entry.
        return result;                 // Return deleted value of entry.
    }
}


int ioopm_linked_list_get(ioopm_list_t *list, int index)
{
    if (index < 0 || index > list->size)
    {
        return -999;
    }

    link_t *link = list->head;
    for (int i = 0; i < index; i++)
    {
        link = link->next;
    }

    return link->value;
}

/// @brief Test if an element is in the list
/// @param list the linked list
/// @param element the element sought
/// @return true if element is in the list, else false
bool ioopm_linked_list_contains(ioopm_list_t *list, int element)
{
    link_t *link = list->head;
    for (int i = 0; i < list->size; i++)
    {
        if (link->value == element)
        {
            return true;
        }
        else
        {
            link = link->next;
        }
    }
    return false;
}

/// @brief Lookup the number of elements in the linked list in O(1) time
/// @param list the linked list
/// @return the number of elements in the list
size_t ioopm_linked_list_size(ioopm_list_t *list)
{
    return list->size;
    /* int m = 0;
     link_t *link = list->head;
     while (link)
     {
         link = link->next;
         m++;
     }
     return m; */
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
    if (ioopm_linked_list_size(list) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ioopm_linked_list_clear(ioopm_list_t *list)
{
    if (ioopm_linked_list_is_empty(list) == true)
    {
        return;
    }
    link_t *link = list->head;
    while (link != NULL)
    {
        link_t *a = link->next;
        free(link);
        link = a;
    }
    list->size = 0;
}

static bool value_equiv(int value, void *x)
{
    int *other_value_ptr = x;
    int other_value = *other_value_ptr;
    return value == other_value;
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
    int j = 0;
    link_t *link = list->head;
    while (link != NULL)
    {
        j++;
        if (prop(link->value, extra) == false)
            return false;
        link = link->next;
    }
    if (j == 0)
        return false;
    return true;
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
    link_t *link = list->head;
    while (link != NULL)
    {
        if (prop(link->value, extra) == true)
            return true;
        link = link->next;
    }
    return false;
}

bool hasallvalues(ioopm_list_t *list, int value)
{
    return ioopm_linked_list_all(list, value_equiv, &value);
}

bool has_any_value(ioopm_list_t *list, int value)
{
    return ioopm_linked_list_any(list, value_equiv, &value);
}


void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra)
{
    link_t *link = list->head;
    while (link != NULL)
    {
        fun(&link->value, extra);
        link = link->next;
    }
}