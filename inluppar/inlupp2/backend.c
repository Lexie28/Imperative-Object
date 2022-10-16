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

int int_hash(elem_t key) {
    return key.i % 17;
}

db_t *db_create()
{
    db_t *db = calloc(1, sizeof(db_t));
    db->namemerch = ioopm_hash_table_create(string_eq, string_sum_hash);
    db->shelftoname = ioopm_hash_table_create(string_eq, string_sum_hash);
    db->carts = ioopm_hash_table_create(elem_equality_func_int, int_hash);
    db->carts_amnt = 0;
    return db;
}

merch_t *create_merch(char *name, char *description, int price)
{
    merch_t *merch = calloc(1, sizeof(merch_t));
    merch->name = name;
    merch->description = description;
    merch->price = price;
    ioopm_list_t *locs = ioopm_linked_list_create(string_eq); //TODO???
    merch->locs = locs;
    return merch;
}

void destroy_shelf(shelf_t *shelf)
{
    free(shelf);
}

static void destroylocslist(elem_t key, elem_t *value, void *x)
{
    destroy_shelf((*value).p);
}


static void destroyhtnamemerch(elem_t key, elem_t *value, void *x)
{
    destroy_merch((*value).p);
}

void destroy_merch(merch_t *merch)
{
    ioopm_linked_list_apply_to_all(merch->locs, destroylocslist, NULL);
    ioopm_linked_list_destroy(merch->locs);
    free(merch->name);
    free(merch->description);
    free(merch);
}

void db_destroy(db_t *db)
{
    ioopm_hash_table_apply_to_all(db->namemerch, destroyhtnamemerch, NULL);
    ioopm_hash_table_destroy(db->shelftoname);
    ioopm_hash_table_destroy(db->carts); //TODO
    ioopm_hash_table_destroy(db->namemerch);
    free(db);
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
    ioopm_hash_table_remove(ht, ptr_elem(name));
    destroy_merch(merch);
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
        ioopm_hash_table_remove(ht, ptr_elem(name));
        destroy_merch(merch);
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

listtype_t *get_merchandise(db_t *db)
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
    add_merchandise(db, newname, strdup(merch->description), merch->price);
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
    free(merch->description);
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

void show_stock(db_t *db, char *name) //bygg om så den blir som get-funktionen o returnar en array så att vi kan keys_sort-a den också
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t lookup = ioopm_hash_table_lookup(ht, ptr_elem(name));
    bool success = lookup.success;
    if (success == false)
    {
        return;
    }
    merch_t *merch = lookup.value.p;
    ioopm_list_t *listoflocations = merch->locs;
    ioopm_list_iterator_t *iter = ioopm_list_iterator(listoflocations);
    while (ioopm_iterator_has_next(iter)) //TODO!!! NU MISSAR DEN SISTA GREJEN
    {
        elem_t shelf_elem = ioopm_iterator_current(iter);
        shelf_t *shelf = shelf_elem.p;
        printf("%s: %d\n", shelf->shelf, shelf->quantity);
        ioopm_iterator_next(iter);
        /*elem_t shelf_elem = ioopm_iterator_next(iter); //har en dummy i början, osäker om vår linked list har det??
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

bool replenish_stock(db_t *db, char *name, char *shelftoreplenish, int amount) //for-loop med i=0, i++, i < size så vi når sista grejen
{
    show_stock(db, name);

    bool isshelf = is_shelf(shelftoreplenish); //kollar att tar rätt input
    if (isshelf == false) return false;

    option_t name_lookup = ioopm_hash_table_lookup(db->namemerch, ptr_elem(name));
    if (!name_lookup.success) return false;
    merch_t *merch = name_lookup.value.p;

    option_t lookup = ioopm_hash_table_lookup(db->shelftoname, ptr_elem(shelftoreplenish));
    if (!lookup.success)
    {
        shelf_t *shelf = create_shelf(shelftoreplenish, amount);
        ioopm_linked_list_append(merch->locs, ptr_elem(shelf));
        ioopm_hash_table_insert(db->shelftoname, ptr_elem(shelftoreplenish), ptr_elem(name));
        return true;
    }
    else if (strcmp(lookup.value.p, name))
    {
        ioopm_list_t *listoflocations = merch->locs;
        ioopm_list_iterator_t *iter = ioopm_list_iterator(listoflocations);
        while (ioopm_iterator_has_next(iter)) //TODO!!! NU MISSAR DEN SISTA GREJEN
        {
            elem_t shelf_elem = ioopm_iterator_current(iter);
            shelf_t *shelf = shelf_elem.p;
            if (strcmp(shelftoreplenish, shelf->shelf) == 0)
            {
                shelf->quantity += amount;
                return true;
            }
            ioopm_iterator_next(iter);
        }
        return false;
    }
    else
    {
        return false;
    }
}

void cart_create(db_t *db)
{
    ioopm_hash_table_t *ht = db->carts; //outer hashtable. int (vilket cart) till lilla hashtablet
    ioopm_hash_table_t *cart = ioopm_hash_table_create(string_eq, string_sum_hash); //inner hashtable. name of merch till amount to order
    db->carts_amnt++;
    ioopm_hash_table_insert(ht, int_elem(db->carts_amnt), ptr_elem(cart));
}

//REMOVE
//ta in carts_amnt vilken du vill ta bort
bool cart_remove (db_t *db, int carttoremove)
{
    //lookup carttoremove
    //om inte finns return false
    //annars, htdestroy det lilla och htremova entry't i stora ht'et.
}

int totalstockofmerch(db_t *db, char *nameofmerch)
{
    //count up total stock number of merch across its stock locations
}

int totalordersofmerch(db_t *db, char *nameofmerch)
{
    //count up how many in the carts currently
}

bool add_to_cart(db_t *db, int carttoaddto, char *nameofmerch, int quantity)
{
    //if total stock - total order - quantity >= 0, då får vi lägga till till carten
    //annars fail
}

bool remove_from_cart(db_t *db, int cart, char *nameofmerch, int quantity)
{
    //lookup i lilla hashtable på hur många orders du har på said vara i din cart
    //om mängden orders - quantity > 0, så behlver vi bara ändra quantityn i lilla ht (eller ny ht-insert med samma key (denna kommer replacas - det är så vi gjorde ht-insert))
    //annars gör ht remove i lilla ht
}

int calc_costofmerch(db_t *db, char *name, int quantity)
{
    //lookup på namnet och hitta dess pris
    //returnera pris x quantity
}

int calculate_cost(db_t *db, int cart)
{
    //gå igenom allt i carten
    //för varje merch calculate cost of merch
    //apply to all eller hämta ut keys and values och flr varje par calc cost of merch
    //summa och returnera summa
}

void removestock(db_t *db, char *name, int quantity)
{
    //gör en lookup på namnet, hämta ut listan av shelves, och gå igenom listan och ta ut från de olika stocken tills det adds upp till hur mycket du vill ta bort
}

void checkout(db_t *db, int cart)
{
    //gå igenom allt i den carten vi har valt att checka ut


}