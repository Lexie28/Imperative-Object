#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "hash_table.h"
#include "linked_list.h"

struct merch
{
    char *name;
    char *description;
    int price;
    ioopm_list_t *locs;
};

typedef struct merch merch_t;

struct shelf
{
    char *shelf;
    int quantity;
};

typedef struct shelf shelf_t;


struct db
{
    ioopm_hash_table_t *namemerch;
    ioopm_hash_table_t *shelftoname; //we map shelf (key) to name of the merchandise at the shelf (value)
    ioopm_hash_table_t *carts;
};

typedef struct db db_t;

struct listtype
{
    char **arr;
    int size;
};

typedef struct listtype listtype_t;

db_t *db_create();

merch_t *create_merch(char *name, char *description, int price);

void destroy_merch(merch_t *merch);

bool add_merchandise(db_t *db, char *name, char *description, int price);

bool remove_merchandise(db_t *db, char *name);

listtype_t *get_merchandise(db_t *db);

bool edit_merchandise_name(db_t *db, char *name, char *newname);

bool edit_merchandise_description(db_t *db, char *name, char *newdescription);

bool edit_merchandise_price(db_t *db, char *name, int newprice);

void show_stock(db_t *db, char *name);

shelf_t *create_shelf(char *newshelf, int newquantity);

bool replenish_stock(db_t *db, char *name, char *shelftoreplenish);