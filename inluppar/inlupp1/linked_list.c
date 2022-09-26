#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct link
{
    int value;
    struct link *next;
};

typedef struct link link_t;

struct list
{
    link_t *head;
    int size;
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

/// @brief Insert at the end of a linked list in O(1) time
/// @param list the linked list that will be appended
/// @param value the value to be appended
void ioopm_linked_list_append(ioopm_list_t *list, int value)
{
    if (list->size == 0)
    {
        ioopm_linked_list_prepend(list, value);
    }
    else
    {
        link_t *link = list->head;
        for (int i = 0; i < list->size; i++)
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

/*
static link_t *find_previous_link_for_value(ioopm_list_t *list, int value)
{
    link_t *link = list->head;
    while (link->next != NULL && link->next->value < value)
    {
        link = link->next;
    }
    return link;
} */

/// @brief Insert an element into a linked list in O(n) time.
/// The valid values of index are [0,n] for a list of n elements,
/// where 0 means before the first element and n means after
/// the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @param value the value to be inserted
void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value) // index = 1
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

/// @brief Remove an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @param list the linked list
/// @param index the position in the list
/// @return the value removed
int ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
    link_t *link = list->head;
    if (index < 0 || index > list->size)
    {
        return -999;
    }
    else if (index == 0)
    {
        int result = link->value;
        free(link);
        list->size--;
        return result;
    }
    else
    {
        for (int i = 0; i < index - 1; i++)
        {
            link = link->next;
        }
        link_t *remove = link->next;   // den vi vill ta bort
        link->next = link->next->next; // connecta 1 med 3
        list->size--;
        int result = remove->value;
        free(remove);
        return result;
    }
    // link är den innan
    // link->next = adressen till den vi vill ta bort
    // link->next->next = adressen till den efter vi vill ta bort
    // connecta den innan till adressen av den efter
}

/// @brief Retrieve an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @return the value at the given position
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
int ioopm_linked_list_size(ioopm_list_t *list)
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
} */

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
        if (prop(link->value, extra) == false)
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

bool hasallvalues(ioopm_list_t *list, int value)
{
    return ioopm_linked_list_all(list, value_equiv, &value);
}

bool has_any_value(ioopm_list_t *list, int value)
{
    return ioopm_linked_list_any(list, value_equiv, &value);
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
        fun(link->value, extra);
        link = link->next;
    }
}