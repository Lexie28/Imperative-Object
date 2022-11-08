#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "hash_table.h"
#include "linked_list.h"


/**
 * @file backend.h
 * @author Alexandra Dahlberg & Vincent Andersson
 * @date 18 Oktober 2022
 * @brief Backend functions for a functioning database (e.g. to be used by a store)
 *
This header-file lists and defines all backend functions that are written for and used to make our database.
Our database contains three hashtables:
-1. mapping the name of merchandise to the merchandise struct
-2. one mapping the shelf (key) to the name of merchandise
-3. one mapping the number (index) of a cart to a cart (which itself is another hashtable containing the merchandise and quantity of that cart)
Using these structures we define the backend functions supporting basic functionality of a database.
 */

struct merch
{
    char *name;
    char *description;
    ioopm_list_t *locs;
    int price;
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
    int carts_amnt; // mängden carts i systemet
};

typedef struct db db_t;

struct listtype
{
    char **arr;
    int size;
};

typedef struct listtype listtype_t;

/// @brief create an empty database
/// @return database
db_t *ioopm_db_create();

/// @brief add a merchandise to our hash table
/// @param db is the database we enter into to find our hash table
/// @param name a string forming the name of our merchandise
/// @param description a string forming the description of our merchandise
/// @param price an int forming the price of our merchandise
/// @return a bool indicating whether we managed to add the new merchandise
bool ioopm_add_merchandise(db_t *db, char *name, char *description, int price);

/// @brief remove a merchandise from our hash table
/// @param db is the database we enter into to find our hash table
/// @param name a string forming the name of our merchandise
/// @return a bool indicating whether we managed to remove the chosen merchandise
bool ioopm_remove_merchandise(db_t *db, char *name);

/// @brief get an array of the keys (merchandise names) and size of said array from our hash table
/// @param db is the database we enter into to find our hash table
/// @return a listtype_t containing an array of the hash table's keys and its size
listtype_t *ioopm_get_merchandise(db_t *db, bool *is_empty);

/// @brief edit the name of a chosen merchandise
/// @param db is the database we enter into to find our hash table
/// @param name is a string being the name of our merchandise
/// @param newname is the new name of our merchandise
/// @return a bool indicating whether we could successfully change the name of the merchandise
bool ioopm_edit_merchandise_name(db_t *db, char *name, char *newname);

/// @brief edit the description of a chosen merchandise
/// @param db is the database we enter into to find our hash table
/// @param name is a string being the name of our merchandise
/// @param newdescription is the new description of our merchandise
/// @return a bool indicating whether we could successfully change the description of the merchandise
bool ioopm_edit_merchandise_description(db_t *db, char *name, char *newdescription);

/// @brief edit the price of a chosen merchandise
/// @param db is the database we enter into to find our hash table
/// @param name is a string being the name of our merchandise
/// @param newprice is the new price of our merchandise
/// @return a bool indicating whether we could successfully change the price of the merchandise
bool ioopm_edit_merchandise_price(db_t *db, char *name, int newprice);

/// @brief show all of the stock locations for a specific merchandise
/// @param db is the database we enter into to find the relevant hash table
/// @param name is the name of our merchandise for which we want to list all of its storage locations
/// @return List of all obejcts to print
ioopm_list_t *ioopm_show_stock(db_t *db, char *name);

/// @brief replenish the stock of a certain merchandise in our database
/// @param db is the database we enter into to find the relevant hash table
/// @param name is the name of our merchandise
/// @param shelftoreplenish is the specific shelf belonging to our merchandise which we wish to replenish
/// @return a bool indicating whether we could replenish the shelf for our merchandise
bool ioopm_replenish_stock(db_t *db, char *name, char *shelftoreplenish, int amount);

/// @brief destroying the whole database structure
/// @param db the entire database which we wish to destroy
void ioopm_db_destroy(db_t *db);

/// @brief creating an empty cart for the shopper
/// @param db the database in which the cart exists
int ioopm_cart_create(db_t *db);

/// @brief removing a cart from our database
/// @param db the database in which the cart exists
bool ioopm_cart_remove (db_t *db, int carttoremove);

/// @brief adding a merchandise of a certain quantity to a cart
/// @param db the database in which our merchandise and our cart exists
/// @param carttoaddto the number of the cart in our cart hashtable to add the merchandise (and quantity) to
/// @param nameofmerch the name of the merchandise you wish to add to your cart
/// @param quantity the quantity of merchandise you wish to add to your cart
/// @return a bool indicating whether you were able to add the merchandise (of specified quantity) to your cart
bool ioopm_add_to_cart(db_t *db, int carttoaddto, char *nameofmerch, int quantity);

/// @brief removing a merchandise of a certain quantity to a cart
/// @param db the database in which our merchandise and our cart exists
/// @param cart the number of the cart in our cart hashtable to remove our merchandise from
/// @param nameofmerch the name of the merchandise we wish to remove
/// @param quantity the quantity of said merchandise we wish to remove
/// @return a bool indicating whether you were able to remove the merchandise (of specified quantity) from your cart
bool ioopm_remove_from_cart(db_t *db, int cart, char *nameofmerch, int quantity);

/// @brief calculating the cost of a certain cart
/// @param db the database in which our cart exists
/// @param cart the number of the cart in our cart hashtable we wish to calculate the cost of
/// @return an integer representing the final cost of our cart
int ioopm_calculate_cost(db_t *db, int cart);

/// @brief checking out a specific cart. it removes the shopping cart from the system and decreases the stock for the merchandise in the cart
/// @param db the database in which our cart and the merchandise it contains exists
/// @param cart the number of the cart in our cart hashtable we wish to check out
bool ioopm_checkout(db_t *db, int cart);

/// @brief get all of the information related to a certain merchandise
/// @param db the database in which this information is located
/// @param name the name of the merchandise for which you request its information
/// @return information belongning to this merchandise in the struct of merch_t.
merch_t *ioopm_get_merch_info(db_t *db, char *name);