#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

struct link
{
    elem_t value;
    struct link *next;
};

typedef struct link link_t;

struct list
{
    link_t *head;
    link_t *tail;
    size_t size;
    ioopm_eq_function eq_func;
};

typedef struct list ioopm_list_t;

static bool value_equiv(elem_t value, void *x)
{
    int *other_value_ptr = x;
    int other_value = *other_value_ptr;
    return value.i == other_value;
}

ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function func)
{
    ioopm_list_t *result = calloc(1, sizeof(ioopm_list_t));
    result->eq_func = func; //We set the equality function from our input.
    return result;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
    ioopm_linked_list_clear(list);
    free(list);
}

static link_t *create_link(elem_t v, link_t *n)
{
    link_t *newlink = calloc(1, sizeof(link_t));
    newlink->value = v;
    newlink->next = n;
    return newlink;
}

void destroy_link(link_t *link)
{
    free(link);
}

void addfirstlink(ioopm_list_t *list, elem_t value) //adds first link in empty list. defines head and last pointer.
{
    link_t *firstlink = create_link(value, NULL);
    list->head = firstlink;
    list->tail = firstlink;
    list->size++;
}

void ioopm_linked_list_append(ioopm_list_t *list, elem_t value)
{
    if (list->size == 0)
    {
        ioopm_linked_list_prepend(list, value);
    }
    else
    {
        link_t *link = list->tail;
        link->next = create_link(value, NULL);
        list->tail = link->next;
        list->size++;
    }
}


void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t value)
{
    if (list->size == 0)
    {
        addfirstlink(list, value);
    }
    else
    {
    link_t *firstlink = list->head; // pekare till första entryt
    link_t *newfirstlink = create_link(value, firstlink);
    list->head = newfirstlink;
    list->size++;
    }
}


void ioopm_linked_list_insert(ioopm_list_t *list, int index, elem_t value) // index = 1
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


elem_t ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
    link_t *link = list->head;
    if (index < 0 || index > list->size)
    {
        return int_elem(-999);
    }
    else if (index == 0)
    {

        elem_t removeVal = link->value; // Get return value of remove entry.
        list->head = link->next;        // Set new head
        free(link);                     // Free memory used by head.
        list->size--;                   // Decrease size.
        return removeVal;               // Return value of head.
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
        elem_t result = remove->value; // The value of index we want to remove (return val)
        free(remove);                  // Free memory used by the entry.
        if (link->next == NULL)
        {
            list->tail = link;
        }
        return result;                 // Return deleted value of entry.
    }
}


elem_t ioopm_linked_list_get(ioopm_list_t *list, int index)
{
    if (index < 0 || index > list->size)
    {
        return int_elem(-999);
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
bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element)
{
    link_t *link = list->head;
    for (int i = 0; i < list->size; i++)
    {
        if ((list->eq_func(link->value, element)) == true)
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
    /*int m = 0;
    link_t *link = list->head;
    while (link)
    {
        link = link->next;
        m++;
    }*/
    return list->size;
}
/*
int listsizehelper(link_t *link)
{
    if (link == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + listsizehelper(link->next);
    }
}

int ioopm_linked_list_size_recursive(ioopm_list_t *list)
{
    link_t *link = list->head;
    if (link == NULL)
        return 0;
    else
    {
        return listsizehelper(link);
    }
}*/
/// @brief Test whether a list is empty or not
/// @param list the linked list
/// @return true if the number of elements int the list is 0, else false
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

/// @brief Remove all elements from a linked list
/// @param list the linked list
void ioopm_linked_list_clear(ioopm_list_t *list)
{
    if (ioopm_linked_list_is_empty(list) == true)
    {
        return;
    }
    link_t *link = list->head; // Get the head
    while (link != NULL)
    {
        link_t *a = link->next;
        free(link);
        link = a;
    }
    list->size = 0;
}

bool hasallvalues(ioopm_list_t *list, elem_t value) // Check if value of entry is equal to extra.
{
    return ioopm_linked_list_all(list, value_equiv, &value);
}

bool has_any_value(ioopm_list_t *list, elem_t value) // Check if value of entry is equal to extra.
{
    return ioopm_linked_list_any(list, value_equiv, &value);
}
/// @brief Test if a supplied property holds for all elements in a list.
/// The function returns as soon as the return value can be determined.
/// @param list the linked list
/// @param prop the property to be tested (function pointer)
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of prop
/// @return true if prop holds for all elements in the list, else false
bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
    int j = 0;
    link_t *link = list->head;
    while (link != NULL)
    {
        j++;
        if (prop(link->value, extra) == false) // added null since ioopm_int_predicate expects three inputs and no char value.
            return false;
        link = link->next;
    }
    if (j == 0)
        return false;
    return true;
}

/// @brief Test if a supplied property holds for any element in a list.
/// The function returns as soon as the return value can be determined.
/// @param list the linked list
/// @param prop the property to be tested
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of prop
/// @return true if prop holds for any elements in the list, else false
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
void changeallvaluestoarg(elem_t *value, void *arg) // arg = "7"
{
    *value = *(elem_t *)arg;
    // värdeöverföring med pekare
    // skickar med adressen till värdet som existerar i linken, då går vi till det adressen pekar på och skriver om det till det vi får in som argument
    // kopia av adressen
    // avreferera - går till platsen som adressen pekar på (alltså vårt value)
    // skriver om värdet i den platsen till värdet som arg pekar på
    // int * = själva adressen. vi sätter inte value till adressen
    //*(int *) = då hämtar vi ut värdet från adressen
    // om det stått int *arg i argumentet hade vi kunnat skriva *value = *arg
}
/// @brief Apply a supplied function to all elements in a list.
/// @param list the linked list
/// @param fun the function to be applied
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of fun
void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra)
{
    link_t *link = list->head;
    while (link != NULL)
    {
        fun(&link->value, extra);
        link = link->next;
    }
}