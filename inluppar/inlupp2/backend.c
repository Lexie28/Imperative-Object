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
typedef struct hash_table ioopm_hash_table_t;
typedef struct entry entry_t;
typedef struct nametuple nametuple_t;

struct nametuple
{
    char *oldname;
    char *newname;
};

struct orderamnt
{
    int *totalstock;
    char *merchname;
};

struct hash_table
{
    entry_t buckets[17];       // The buckets
    ioopm_eq_function key_eq_fn;       // Function for checking if keys are equal.
    ioopm_hash_function hash_function; // Function for determining the keys of inputs elem_t.
};




/*
struct entry
{
    elem_t key;       // holds the key (int)
    elem_t value;   // holds the value (char *)
    entry_t *next; // points to the next entry (possibly NULL)
};*/

typedef struct orderamnt orderamnt_t;


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

db_t *ioopm_db_create()
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

    ioopm_list_t *locs = ioopm_linked_list_create(string_eq);
    merch->locs = locs;

    return merch;
}


void free_cart_merch(elem_t key, elem_t *value, void *x)
{
    nametuple_t *freeptr = x;
    char *nameofmerch = freeptr->oldname;
    if (strcmp(key.p, nameofmerch) == 0)
    {
        freeptr->newname = key.p;
    }
}

void destroy_shelf(shelf_t *shelf)
{
    free(shelf->shelf);
    free(shelf);
}

static void destroylocslist(elem_t *value, void *x)
{
    destroy_shelf((*value).p);
}

void destroy_merch(merch_t *merch)
{
    ioopm_linked_list_apply_to_all(merch->locs, destroylocslist, NULL);
    ioopm_linked_list_destroy(merch->locs);
    
    free(merch->name);
    free(merch->description);
    free(merch);
}

static void destroyhtnamemerch(elem_t key, elem_t *value, void *x)
{
    destroy_merch((*value).p);
}

void free_all_cart_merch(elem_t key, elem_t *value, void *x)
{
    free(key.p);
}


void destroy_cart(ioopm_hash_table_t *ht)
{
    ioopm_list_t *keys = ioopm_hash_table_keys(ht);
    ioopm_hash_table_destroy(ht);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(keys);
    size_t size = ioopm_linked_list_size(keys);
    for (int i = 0; i < size; i++)
    {
        char *tofree = ioopm_iterator_current(iter).p;
        free(tofree);
        ioopm_iterator_next(iter);
    }
    ioopm_iterator_destroy(iter);
    ioopm_linked_list_destroy(keys);
}

void destroy_smaller_cartht(elem_t key, elem_t *value, void *x)
{
    destroy_cart((*value).p);
}

void free_name_shelftoname(elem_t key, elem_t *value, void *x)
{
    free((*value).p);
}

void ioopm_db_destroy(db_t *db)
{
    ioopm_hash_table_apply_to_all(db->namemerch, destroyhtnamemerch, NULL);
    ioopm_hash_table_apply_to_all(db->shelftoname, free_name_shelftoname, NULL);
    ioopm_hash_table_destroy(db->shelftoname); //vi freear inte name-strduppen i denna hashtable
    ioopm_hash_table_apply_to_all(db->carts, destroy_smaller_cartht, NULL);
    ioopm_hash_table_destroy(db->carts);
    ioopm_hash_table_destroy(db->namemerch);
    free(db);
}

bool ioopm_add_merchandise(db_t *db, char *name, char *description, int price)
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t hasname = ioopm_hash_table_lookup(ht, ptr_elem(name));
    if (hasname.success == true)
    {
        free(name);
        free(description);
        return false;
    }
    merch_t *merch = create_merch(name, description, price);
    ioopm_hash_table_insert(ht, ptr_elem(name), ptr_elem(merch));
    return true; 
}

//helper funktion till vår remove.. vet att det finns många funktioner här uppe men det 
//är för att db_destroy är ganska så svår
void destroyingmerch(ioopm_hash_table_t *ht, merch_t *merch)
{
    ioopm_list_t *list = merch->locs;
    if (list != NULL)
    {
    size_t size = ioopm_linked_list_size(list);
    if (size != 0)
    {
        ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
        shelf_t *shelf = ioopm_iterator_current(iter).p;
        free(shelf);
        while (ioopm_iterator_has_next(iter))
        {
            shelf = ioopm_iterator_next(iter).p;
            free(shelf);
        }
        ioopm_iterator_destroy(iter);
    }
    ioopm_linked_list_destroy(list);
    }
    ioopm_hash_table_remove(ht, ptr_elem(merch->name));
    free(merch->name);
    free(merch->description);
    free(merch);
}

void remove_smallhtc_edit(ioopm_hash_table_t *ht, char *name)
{
    ioopm_hash_table_remove(ht, ptr_elem(name));
}


void remove_smallhtc(ioopm_hash_table_t *ht, char *name)
{
    nametuple_t tofree;
    (&tofree)->oldname = name;
    (&tofree)->newname = "";
    ioopm_hash_table_apply_to_all(ht, free_cart_merch, &tofree);
    ioopm_hash_table_remove(ht, ptr_elem(name));
    free(tofree.newname);
}

void remove_bightc_edit(elem_t key, elem_t *value, void *x)
{
    remove_smallhtc_edit((*value).p, x);
}

void remove_bightc(elem_t key, elem_t *value, void *x)
{
    remove_smallhtc((*value).p, x);
}


bool ioopm_remove_merchandise(db_t *db, char *name, bool edit)
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t lookup = ioopm_hash_table_lookup(ht, ptr_elem(name));
    if (lookup.success == true)
    {
        //tar bort från name-merch ht
        destroyingmerch(ht, lookup.value.p);
        //bort från carts-ht
        ioopm_hash_table_t *htc = db->carts;
        if (edit == true)
        {
            ioopm_hash_table_apply_to_all(htc, remove_bightc_edit, name);
        }
        else 
        {
            ioopm_hash_table_apply_to_all(htc, remove_bightc, name);
        }
        //bort från shelf-name-ht
        ioopm_hash_table_t *shelfname = db->shelftoname;
        ioopm_list_t *keys = ioopm_hash_table_keys(shelfname);
        ioopm_list_iterator_t *iter = ioopm_list_iterator(keys);
        size_t size = ioopm_linked_list_size(keys);
        for (int i = 0; i < size; i++)
        {
            elem_t currentkey = ioopm_iterator_current(iter);
            option_t value_option = ioopm_hash_table_lookup(shelfname, currentkey);
            if (value_option.success)
            {
                char *value = value_option.value.p;
            
                if (strcmp(value, name) == 0)
                {
                    ioopm_hash_table_remove(shelfname, currentkey);
                    free(value);
                    free(currentkey.p);
                }
            }
            ioopm_iterator_next(iter);
        }
        ioopm_iterator_destroy(iter);
        ioopm_linked_list_destroy(keys);
        return true;
    }
    else
    {
        return false;
    }
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

listtype_t *ioopm_get_merchandise(db_t *db, bool *is_empty)
{
    ioopm_hash_table_t *ht = db->namemerch;
    int size = ioopm_hash_table_size(ht);
    ioopm_list_t *listofkeys = ioopm_hash_table_keys(ht);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(listofkeys);

    *is_empty = (size == 0);

    char **keys_arr = calloc(size, sizeof(char *));
    for (int i = 0; i < size; i++)
    {
        keys_arr[i] = ioopm_iterator_current(iter).p;
        ioopm_iterator_next(iter);
    }

    ioopm_iterator_destroy(iter);
    ioopm_linked_list_destroy(listofkeys);
    sort_keys(keys_arr, size); //return keys_arr
    listtype_t *result = makelisttype(keys_arr, size);
    return result;
}

void change_name_shelfht(elem_t key, elem_t *value, void *x)
{
    nametuple_t *nametuple = x;
    if (strcmp(nametuple->oldname, (*value).p) == 0)
    {
        free((*value).p);
        (*value).p = strdup(nametuple->newname);
    }
}

void change_name_cartht(elem_t key, elem_t *value, void *x)
{
    nametuple_t *nametuple = x; //skickar med båda namnen så vi kan jämföra genom carten och byta ut
    ioopm_hash_table_t *cart = (*value).p;
    option_t lookup = ioopm_hash_table_lookup(cart, ptr_elem(nametuple->oldname));
    if (lookup.success == false)
    {
        return;
    }
    
    nametuple_t tofree;
    (&tofree)->oldname = nametuple->oldname;
    int quantity = lookup.value.i;
    ioopm_hash_table_apply_to_all(cart, free_cart_merch, &tofree);
    ioopm_hash_table_remove(cart, ptr_elem(nametuple->oldname));
    free(tofree.newname);
    ioopm_hash_table_insert(cart, ptr_elem(strdup(nametuple->newname)), int_elem(quantity));

}

bool ioopm_edit_merchandise_name(db_t *db, char *name, char *newname)
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t lookup = ioopm_hash_table_lookup(ht, ptr_elem(name));
    bool success = lookup.success;
    if (success == false)
    {
        return false;
    }

    merch_t *merch = lookup.value.p;
    merch_t *edited = create_merch(newname, strdup(merch->description), merch->price);
    ioopm_linked_list_destroy(edited->locs);
    edited->locs = merch->locs;
    merch->locs = NULL;
    ioopm_hash_table_insert(ht, ptr_elem(newname), ptr_elem(edited));
    //apply to all på shelf-to-name ht
    //ändrar namnet även i shelf-to-name ht'et

    nametuple_t nametuple;
    (&nametuple)->oldname = name;
    (&nametuple)->newname = newname;
    ioopm_hash_table_apply_to_all(db->shelftoname, change_name_shelfht, &nametuple);
    //apply to all på alla carts
    //ändrar namnet i cartsen


    ioopm_hash_table_apply_to_all(db->carts, change_name_cartht, &nametuple);
    ioopm_remove_merchandise(db, name, true);
    return true;
}

bool ioopm_edit_merchandise_description(db_t *db, char *name, char *newdescription)
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t lookup = ioopm_hash_table_lookup(ht, ptr_elem(name));
    bool success = lookup.success;
    if (success == false)
    {
        return false;
    }
    merch_t *merch = lookup.value.p;
    char *desc = merch->description;
    merch->description = newdescription;
    free(desc);
    return true;
}

bool ioopm_edit_merchandise_price(db_t *db, char *name, int newprice)
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

ioopm_list_t *ioopm_show_stock(db_t *db, char *name) //bygg om så den blir som get-funktionen o returnar en array så att vi kan keys_sort-a den också
{

    ioopm_hash_table_t *ht = db->namemerch;
    option_t success = ioopm_hash_table_lookup(ht, ptr_elem(name));
    if (success.success == false)
    {
        return NULL;
    }
    else
    {
        merch_t *merch = success.value.p;
        ioopm_list_t *shelflist = merch->locs;
        return shelflist;
    }
}


    /*
    ioopm_hash_table_t *ht = db->namemerch;
    option_t lookup = ioopm_hash_table_lookup(ht, ptr_elem(name));
    bool success = lookup.success;
    if (success == false)
    {
        return ioopm_linked_list_create(string_eq); // EMPTY LIST RETURNED IF LOOKUP FAILS
    }

    merch_t *merch = lookup.value.p;
    ioopm_list_t *listoflocations = merch->locs;
    ioopm_list_iterator_t *iter = ioopm_list_iterator(listoflocations);
    ioopm_list_t *result = ioopm_linked_list_create(string_eq);
    while (ioopm_iterator_has_next(iter)) //TODO!!! NU MISSAR DEN SISTA GREJEN // GÖR DEN VERKLIGEN DET? V (2022-11-02) //
    {
        elem_t shelf_elem = ioopm_iterator_current(iter);
        //shelf_t *shelf = shelf_elem.p; // COMMENTED

        ioopm_linked_list_append(result, shelf_elem);

        //printf("%s: %d\n", shelf->shelf, shelf->quantity); // USED TO PRINT HERE, NO MORE
        ioopm_iterator_next(iter);
        elem_t shelf_elem = ioopm_iterator_next(iter); //har en dummy i början, osäker om vår linked list har det??
        shelf_t *shelf = shelf_elem.p;
        printf("%s: %d\n", shelf->shelf, shelf->quanitity); 
    }
    return result; */

shelf_t *create_shelf(char *newshelf, int newquantity)
{
    shelf_t *sh = calloc(1, sizeof(shelf_t));
    newshelf[0] = toupper(newshelf[0]);
    sh->shelf = newshelf;
    sh->quantity = newquantity;
    return sh;
}

bool ioopm_replenish_stock(db_t *db, char *name, char *shelftoreplenish, int amount) //for-loop med i=0, i++, i < size så vi når sista grejen
{
    ioopm_show_stock(db, name);

    bool isshelf = is_shelf(shelftoreplenish); //kollar att tar rätt input
    if (isshelf == false) return false;

    ioopm_hash_table_t *shelftoname = db->shelftoname;
    option_t shelf_lookup = ioopm_hash_table_lookup(shelftoname, ptr_elem(shelftoreplenish));
    if (shelf_lookup.success == true)
    {
        if (strcmp(shelf_lookup.value.p, name) != 0)
        {
            printf("Shelf already has other merch\n");
            return false;
        }
        //se till att det är samma namn, annars return false
    }
    option_t name_lookup = ioopm_hash_table_lookup(db->namemerch, ptr_elem(name));
    if (!name_lookup.success) return false;
    merch_t *merch = name_lookup.value.p;

    option_t lookup = ioopm_hash_table_lookup(db->shelftoname, ptr_elem(shelftoreplenish));
    if (!lookup.success)
    {
        shelf_t *shelf = create_shelf(shelftoreplenish, amount);
        ioopm_linked_list_append(merch->locs, ptr_elem(shelf));
        ioopm_hash_table_insert(db->shelftoname, ptr_elem(shelftoreplenish), ptr_elem(name)); //leak?? name freeas aldrig
        return true;
    }
    else if (strcmp(lookup.value.p, name) == 0)
    {
        ioopm_list_t *listoflocations = merch->locs;
        ioopm_list_iterator_t *iter = ioopm_list_iterator(listoflocations);
        size_t size = ioopm_linked_list_size(listoflocations);
        for (int i = 0; i < size; i++)
        {
            elem_t shelf_elem = ioopm_iterator_current(iter);
            shelf_t *shelf = shelf_elem.p;
            if (strcmp(shelftoreplenish, shelf->shelf) == 0)
            {
                shelf->quantity += amount;
                free(name);
                free(shelftoreplenish);
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

int ioopm_cart_create(db_t *db)
{
    ioopm_hash_table_t *ht = db->carts; //outer hashtable. int (vilket cart) till lilla hashtablet
    ioopm_hash_table_t *cart = ioopm_hash_table_create(string_eq, string_sum_hash); //inner hashtable. name of merch till amount to order
    db->carts_amnt++;
    ioopm_hash_table_insert(ht, int_elem(db->carts_amnt), ptr_elem(cart));
    return db->carts_amnt;
}

//REMOVE
//ta in carts_amnt vilken du vill ta bort
bool ioopm_cart_remove (db_t *db, int carttoremove)
{
    //lookup carttoremove
    //om inte finns return false
    //annars, htdestroy det lilla och htremova entry't i stora ht'et.
    ioopm_hash_table_t *htc = db->carts;
    option_t exists = ioopm_hash_table_lookup(htc, int_elem(carttoremove));
    if (exists.success == true)
    {
        ioopm_hash_table_t *cart = exists.value.p;
        ioopm_hash_table_destroy(cart);
        ioopm_hash_table_remove(htc, int_elem(carttoremove));
        return true;
    }
    else
    {
        return false;
    }
}

int totalstockofmerch(merch_t *merch)
{
    //count up total stock number of merch across its stock locations
    ioopm_list_t *list = merch->locs;
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    size_t size = ioopm_linked_list_size(list);
    int totalstock = 0;
    for (int i = 0; i < size; i++)
    {
        elem_t shelf_elem = ioopm_iterator_current(iter);
        shelf_t *shelf = shelf_elem.p;
        totalstock += shelf->quantity;
        ioopm_iterator_next(iter);
    }
    ioopm_iterator_destroy(iter);
    return totalstock;
}

void totalcartorderofmerch(elem_t key, elem_t *value, void *orderamnt)
{
    orderamnt_t *ordr = orderamnt;
    char *nameofmerch = key.p;
    if (strcmp(nameofmerch, ordr->merchname) == 0)
    {
       *ordr->totalstock += (*value).i;
    }
}

void allcartorders(elem_t key, elem_t *value, void *orderamnt)
{
    ioopm_hash_table_t *cart = (*value).p;
    ioopm_hash_table_apply_to_all(cart, totalcartorderofmerch, &orderamnt);
}

int totalordersofmerch(db_t *db, char *nameofmerch)
{
    //count up how many in the carts currently
    //void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg);
    //typedef void (*ioopm_apply_function)(elem_t key, elem_t *value, void *extra)

    ioopm_hash_table_t *htc = db->carts;
    int totalorders = 0;
    orderamnt_t orderamnt;
    (&orderamnt)->totalstock = &totalorders;
    (&orderamnt)->merchname = nameofmerch;
    ioopm_hash_table_apply_to_all(htc, allcartorders, &orderamnt);
    return totalorders;
}

bool ioopm_add_to_cart(db_t *db, int carttoaddto, char *nameofmerch, int quantity)
{
    ioopm_hash_table_t *ht = db->namemerch;
    ioopm_hash_table_t *carts = db->carts;
    option_t merchlookup = ioopm_hash_table_lookup(ht, ptr_elem(nameofmerch));
    option_t cartlookup = ioopm_hash_table_lookup(carts, int_elem(carttoaddto));
    if (merchlookup.success == false || cartlookup.success == false)
    {
        return false;
    }
    merch_t *merch = merchlookup.value.p;
    int totalstock = totalstockofmerch(merch);
    int totalorders = totalordersofmerch(db, nameofmerch);
    int result = totalstock - totalorders - quantity;
    ioopm_hash_table_t *cart = cartlookup.value.p;
    if (result >= 0)
    {
        ioopm_hash_table_insert(cart, ptr_elem(nameofmerch), int_elem(quantity));
        return true;
    }
    return false;
    //if total stock - total order - quantity >= 0, då får vi lägga till till carten
    //vi har tillräckligt med stocks med tanke på orders att lägga till den quantity'n vi vill ha i en cart
    //annars fail
}

bool ioopm_remove_from_cart(db_t *db, int cartnmr, char *nameofmerch, int quantity)
{
    //lookup i lilla hashtable på hur många orders du har på said vara i din cart
    //om mängden orders - quantity > 0, så behlver vi bara ändra quantityn i lilla ht (eller ny ht-insert med samma key (denna kommer replacas - det är så vi gjorde ht-insert))
    //annars gör ht remove i lilla 
    ioopm_hash_table_t *htc = db->carts;
    option_t lookup = ioopm_hash_table_lookup(htc, int_elem(cartnmr));
    ioopm_hash_table_t *cart = lookup.value.p;
    option_t lookupincart = ioopm_hash_table_lookup(cart, ptr_elem(nameofmerch));
    if (lookupincart.success == false)
    {
        return false;
    }
    int orders = lookupincart.value.i;
    if (orders - quantity > 0)
    {
        ioopm_hash_table_insert(cart, ptr_elem(nameofmerch), int_elem(orders-quantity));
        return true;
    }
    if (orders-quantity == 0)
    {
        nametuple_t freeptr;
        (&freeptr)->oldname = nameofmerch;
        ioopm_hash_table_apply_to_all(cart, free_cart_merch, &freeptr);
        ioopm_hash_table_remove(cart, ptr_elem(nameofmerch));
        free(freeptr.newname);
        return true;
    }
    if (orders-quantity > 0)
    {
        return false;
    }
    return false;
}

int calc_costofmerch(ioopm_hash_table_t *ht, char *nameofmerch, int quantity)
{
    //lookup på namnet och hitta dess pris
    //returnera pris x quantity
    option_t success = ioopm_hash_table_lookup(ht, ptr_elem(nameofmerch));
    if (success.success == false)
    {
        return 0; //TODO? är 0 bäst
    }
    merch_t *merch = success.value.p;
    int price = merch->price;
    int costofmerch = price * quantity;
    return costofmerch;
}

int ioopm_calculate_cost(db_t *db, int cartnmr)
{
    //gå igenom allt i carten
    //för varje merch calculate cost of merch
    //apply to all eller hämta ut keys and values och flr varje par calc cost of merch
    //summa och returnera summa
    ioopm_hash_table_t *htc = db->carts;
    ioopm_hash_table_t *ht = db->namemerch;
    option_t lookup = ioopm_hash_table_lookup(htc, int_elem(cartnmr));
    ioopm_hash_table_t *cart = lookup.value.p; //the cart of which we want to calculate the cost
    //ioopm_hash_table_apply_to_all_acc(cart, calc_costofmerch, );
    int acc = 0;
    for (int i = 0; i < 17; i++)
    {
        entry_t *entry = &cart->buckets[i]; // pekare till början av varje bucket
        entry = entry->next;              // för att skippa dummy entryt
        while (entry != NULL)
        {
            char *nameofmerch = entry->key.p;
            int quantity = entry->value.i;
            int price = calc_costofmerch(ht, nameofmerch, quantity);
            acc += price;
            entry = entry->next;
        }
    }
return acc;
}

void removestock(db_t *db, char *name, int removequantity)
{
    //gör en lookup på namnet, hämta ut listan av shelves, och gå igenom listan 
    //och ta ut från de olika stocken tills det adds upp till hur mycket du vill ta bort
    ioopm_hash_table_t *ht = db->namemerch;
    option_t success = ioopm_hash_table_lookup(ht, ptr_elem(name));
    merch_t *merch = success.value.p;
    ioopm_list_t *list = merch->locs;
    //gå igenom listan och kolla quantity och ta ut från varje elem tills vi tagit ut quantity
    //if stock quantity > quantity = update stock till stock-quantity
    //if stock quantity == quantity = remove this stock
    //if stock quantity < quantity = remove this stock, update removequantity to quantity-stockquantity och move to next stock place
    //iterate through the linked list
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    size_t size = ioopm_linked_list_size(list);
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        elem_t shelf_elem = ioopm_iterator_current(iter);
        shelf_t *shelf = shelf_elem.p;
        int thisstockquantity = shelf->quantity;
        if (thisstockquantity == removequantity)
        {
            ioopm_linked_list_remove(list, index);
            ioopm_iterator_destroy(iter);
            return;
        }
        if (thisstockquantity > removequantity)
        {
            shelf->quantity = thisstockquantity - removequantity;
            ioopm_iterator_destroy(iter);
            return;
        }
        if (thisstockquantity < removequantity)
        {
            removequantity = removequantity - thisstockquantity;
            ioopm_linked_list_remove(list, index);
            ioopm_iterator_next(iter);
        }
    }
    ioopm_iterator_destroy(iter);
}

bool ioopm_checkout(db_t *db, int cartnmr)
{
    ioopm_hash_table_t *htc = db->carts;
    option_t lookup = ioopm_hash_table_lookup(htc, int_elem(cartnmr));
    if (lookup.success == false)
    {
        return false;
    }
    ioopm_hash_table_t *cart = lookup.value.p;
    for (int i = 0; i < 17; i++)
    {
        entry_t *entry = &cart->buckets[i]; // pekare till början av varje bucket
        entry = entry->next;              // för att skippa dummy entryt
        while (entry != NULL)
        {
            char *nameofmerch = entry->key.p;
            int quantity = entry->value.i;
            removestock(db, nameofmerch, quantity);
            entry = entry->next;
        }
    }
    destroy_cart(cart);
    ioopm_hash_table_remove(htc, int_elem(cartnmr));
    return true;
    //gå igenom allt i den carten vi har valt att checka ut
}




//------------------------------------------- helper functions for frontend testing

merch_t *ioopm_get_merch_info(db_t *db, char *name)
{
    ioopm_hash_table_t *ht = db->namemerch;
    option_t success = ioopm_hash_table_lookup(ht, ptr_elem(name));
    if (success.success == false)
    {
        return NULL;
    }
    else
    {
        merch_t *merch = success.value.p;
        return merch;
    }
}