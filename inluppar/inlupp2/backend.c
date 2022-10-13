#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include "frontend.h"
#include "backend.h"
#include "iterator.h"


typedef struct merch merch_t;
typedef struct shelf shelf_t;
typedef struct listtype listtype_t;


int string_sum_hash(elem_t e) // tar en sträng och ger den ett hash-värde. värde som sen bestämmer vilken bucket vi lägger in varje ord i
//vi använder den här för att kunna bestämma vilken bucket vårt entry ska i när vår key är en sträng
{
    char *str = e.p;
    int result = 0;
    // printf("%s, ", str);
    do
    {
        if (*str < 0)
        {
            result += -*str;
        }
        else
        {
        result += *str;
        }
    } while (*++str != '\0');
    // printf("%d \n", result);
    return result;
}

bool string_eq(elem_t e1, elem_t e2)
{
    //printf("%d", strcmp(e1.p, "vel"));
    return (strcmp((char *)e1.p, (char *)e2.p) == 0);
}

db_t *db_create()
{
    db_t *db = calloc(1, sizeof(db_t));
    db->namemerch = ioopm_hash_table_create(string_eq, string_sum_hash);
    db->shelftoname = ioopm_hash_table_create(string_eq, string_sum_hash);
    db->carts = ioopm_hash_table_create(string_eq, string_sum_hash);
    return db;
}

merch_t *create_merch(char *name, char *description, int price)
{
    merch_t *merch = calloc(1, sizeof(merch_t));
    merch->name = name;
    merch->description = description;
    merch->price = price;
    merch->locs = ioopm_linked_list_create(NULL); //TODO???
    return merch;
}

void destroy_merch(merch_t *merch)
{
    ioopm_linked_list_destroy(merch->locs);
    free(merch);
}

bool add_merchandise(db_t *db, char *name, char *description, int price)
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t hasname = ioopm_hash_table_lookup(ht, ptr_elem(name));
    if (hasname.success == true)
    {
        return false;
    }
    merch_t *merch = create_merch(name, description, price);
    ioopm_hash_table_insert(ht, ptr_elem(name), ptr_elem(merch));
    return true; 
}

bool remove_merchandise(db_t *db, char *name)
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t lookup = ioopm_hash_table_lookup(ht, ptr_elem(name));
    bool success = lookup.success;
    if (success == false)
    {
        return false;
    }
    merch_t *merch = lookup.value.p;
    ioopm_list_t *list = merch->locs;
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    for (int i = 0; i > ioopm_linked_list_size(list); i++)
    {
        char *nameofshelf = ioopm_iterator_current(iter).p;
        ioopm_iterator_next(iter);
        ioopm_hash_table_remove(db->shelftoname, ptr_elem(nameofshelf));
    }
    ioopm_iterator_destroy(iter);
    destroy_merch(merch);
    ioopm_hash_table_remove(ht, ptr_elem(name));
    return true;
}

bool edit_remove_merchandise(db_t *db, char *name)
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t lookup = ioopm_hash_table_lookup(ht, ptr_elem(name));
    bool success = lookup.success;
    if (success == false)
    {
        return false;
    }
    merch_t *merch = lookup.value.p;
    ioopm_list_t *list = merch->locs;
        ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
        for (int i=0; i > ioopm_linked_list_size(list); i++)
        {
            char *nameofshelf = ioopm_iterator_current(iter).p;
            ioopm_iterator_next(iter);
            ioopm_hash_table_remove(db->shelftoname, ptr_elem(nameofshelf));
        }
        ioopm_iterator_destroy(iter);
        destroy_merch(merch);
        ioopm_hash_table_remove(ht, ptr_elem(name));
        return true;
}

static int cmpstringp(const void *p1, const void *p2)
{
    return strcmp(*(char *const *)p1, *(char *const *)p2);
}

void sort_keys(char *keys[], size_t no_keys)
{
    qsort(keys, no_keys, sizeof(char *), cmpstringp);
}

listtype_t *makelisttype(char **arr, int size)
{
    listtype_t *listtype = calloc(1, sizeof(listtype_t));
    listtype->size = size;
    listtype->arr = arr;
    return listtype;
}

listtype_t *get_merchandise(db_t *db) //remake so that it returns size and array of keys
{
    ioopm_hash_table_t *ht = db->namemerch;
    int size = ioopm_hash_table_size(ht);
    ioopm_list_t *listofkeys = ioopm_hash_table_keys(ht);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(listofkeys);
    char **keys_arr = calloc(size, sizeof(char *));
    for (int i = 0; i < size; i++)
    {
        keys_arr[i] = ioopm_iterator_current(iter).p;
        ioopm_iterator_next(iter);
    }
    ioopm_iterator_destroy(iter);
    sort_keys(keys_arr, size); //return keys_arr
    listtype_t *result = makelisttype(keys_arr, size);
    //free(keys_arr);
    return result;
}

bool edit_merchandise_name(db_t *db, char *name, char *newname)
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t lookup = ioopm_hash_table_lookup(ht, ptr_elem(name));
    bool success = lookup.success;
    if (success == false)
    {
        return false;
    }
    merch_t *merch = lookup.value.p;
    add_merchandise(db, newname, merch->description, merch->price);
    edit_remove_merchandise(db, name);
    return true;
}

bool edit_merchandise_description(db_t *db, char *name, char *newdescription)
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t lookup = ioopm_hash_table_lookup(ht, ptr_elem(name));
    bool success = lookup.success;
    if (success == false)
    {
        return false;
    }
    merch_t *merch = lookup.value.p;
    merch->description = newdescription;
    return true;
}

bool edit_merchandise_price(db_t *db, char *name, int newprice)
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t lookup = ioopm_hash_table_lookup(ht, ptr_elem(name));
    bool success = lookup.success;
    if (success == false)
    {
        return false;
    }
    merch_t *merch = lookup.value.p;
    merch->price = newprice;
    return true;
}

//linked_list är en lista med shelf_t som entries

void show_stock(db_t *db, char *name) 
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t lookup = ioopm_hash_table_lookup(ht, ptr_elem(name));
    bool success = lookup.success;
    if (success == false)
    {
        printf("This item does not exist!");
        return;
    }
    merch_t *merch = lookup.value.p;
    ioopm_list_t *listoflocations = merch->locs;
    ioopm_list_iterator_t *iter = ioopm_list_iterator(listoflocations);
    while (ioopm_iterator_has_next(iter))
    {
        elem_t shelf_elem = ioopm_iterator_current(iter);
        shelf_t *shelf = shelf_elem.p;
        printf("%s: %d\n", shelf->shelf, shelf->quantity);
        ioopm_iterator_next(iter);
        
        /*
        elem_t shelf_elem = ioopm_iterator_next(iter); //har en dummy i början, osäker om vår linked list har det??
        shelf_t *shelf = shelf_elem.p;
        printf("%s: %d\n", shelf->shelf, shelf->quanitity); */
    }
}

shelf_t *create_shelf(char *newshelf, int newquantity)
{
    shelf_t *sh = calloc(1, sizeof(shelf_t));
    sh->shelf = newshelf;
    sh->quantity = newquantity;
    return sh;
}

bool replenish_stock(db_t *db, char *name, char *shelftoreplenish)
{
    show_stock(db, name);
    bool isshelf = is_shelf(shelftoreplenish); //kollar att tar rätt input
    if (isshelf == true)
    {
        ioopm_hash_table_t *ht = db->namemerch;
        option_t lookup = ioopm_hash_table_lookup(ht, ptr_elem(name));
        merch_t *merch = lookup.value.p;
        ioopm_list_t *listoflocations = merch->locs;
        ioopm_list_iterator_t *iter = ioopm_list_iterator(listoflocations);
        while (ioopm_iterator_has_next(iter))
        {
            elem_t shelf_elem = ioopm_iterator_current(iter);
            shelf_t *shelf = shelf_elem.p;
            if (strcmp(shelftoreplenish, shelf->shelf) == 0)
            {
                shelf->quantity++;
                return true;
            }
            ioopm_iterator_next(iter);
        }
        shelf_t *shelf = create_shelf(shelftoreplenish, 1);
        ioopm_linked_list_append(listoflocations, ptr_elem(shelf));
        return true;
    }
    else
    {
        return false;
    }
}

