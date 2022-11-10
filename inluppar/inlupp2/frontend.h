#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"
#include "backend.h"

/**
 * @file frontend.h
 * @author Alexandra Dahlberg & Vincent Andersson
 * @date ---
 * @brief Frontend functions for a functioning database (e.g. to be used by a store)
 *
This header-file lists and defines all frontend functions that are written for and used to make our database.
 */


/// @brief adding a merchandise to our database
/// @param db the database we add our merchandise to
void ui_add_merchandise(db_t *db);

/// @brief listing all of the merchandise in our database
/// @param db the database from which we list our merchandise
void ui_list_merchandise(db_t *db);

/// @brief removing a merchandise from our database
/// @param db the database we want to remove our database from
void ui_remove_merchandise(db_t *db);

/// @brief editing the name, description or price of a merchandise in our database
/// @param db the database from which we want to edit a merchandise
void ui_edit_merchanidse(db_t *db);

/// @brief showing the stock of a merchandise in our database
/// @param db the database containing the merchandise for which we want to show its stock
void ui_show_stock(db_t *db);

/// @brief replenishing the stock of a merchandise in our database
/// @param db the database containing the merchandise for which we want to replenish its stock
void ui_replenish_stock(db_t *db);

/// @brief creating a new cart in our database
/// @param db the database in which we want to create a cart
void ui_cart_create(db_t *db);

/// @brief removing a cart from out database
/// @param db the database from which we want to remove a cart
void ui_cart_remove(db_t *db);

/// @brief adding a merchandise to a cart
/// @param db the database we want to add a merchandise from into a cart
void ui_add_to_cart(db_t *db);

/// @brief removing a merchandise from a cart
/// @param db the database in which we want to remove a merchandise from a cart
void ui_remove_from_cart(db_t *db);

/// @brief calculating the cost of a cart
/// @param db the database containing the cart and the merchandise the cart contains
void ui_calculate_cost(db_t *db);

/// @brief checking out a cart, removing the cart and the merchandise it contains from our database
/// @param db the database containing the cart and its merchandise
void ui_checkout(db_t *db);

/// @brief displaying all of the features for a specific merchandise
/// @param db the database containing the merchandise
void ui_show_merch(db_t *db);

/// @brief displaying the contains of a cart (merchandise name and quantity in cart)
/// @param db the database containing the cart and its merchandise
void ui_show_cart(db_t *db);

/// @brief a menu of all of the options possible to do to our database
/// @return a string menu
char *print_menu();
