#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "linked_list.h"
#include "common.h"
/**
 * @file hash_table.h
 * @author Alexandra Dahlberg & Anthony Melinder
 * @date 06 October 2022
 * @brief Simple hash table that maps integer keys to string values.
 *
This header-file lists and defines all functions that are written for and used to make our hash table structure. 
 */
typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;
typedef struct entry entry_t;
typedef union elem elem_t;

typedef void (*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);
typedef int (*ioopm_hash_function)(elem_t key); 
typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra, ioopm_hash_function hash_func);

struct option
{
    bool success;
    elem_t value;
};

struct entry
{
    elem_t key;       // holds the key (int)
    elem_t value;   // holds the value (char *)
    entry_t *next; // points to the next entry (possibly NULL)
};

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_eq_function ins_value_eq_fn, ioopm_hash_function ins_hash_func);

/// @brief map elem_t (expect integer) key as an integer
/// @param key key value operated upon
/// @return key as an int
int hash_map_func_int(elem_t key); //Hash mapping function when elem_t is an integer.

/// @brief map elem_t (expect char *) key as an integer
/// @param key key value operated upon
/// @return key as an int
int hash_map_func_string(elem_t key); //Hash mapping function when elem_t is a string.

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);

/// @brief return the keys for all entries in a hash map (in no particular order, but same as ioopm_hash_table_values)
/// @param h hash table operated upon
/// @return an array of keys for hash table h
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht);

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param h hash table operated upon
/// @return an array of values for hash table h
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht);

/// @brief clear all the entries in a hash table
/// @param h hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);

/// @brief returns the number of key => value entries in the hash table
/// @param h hash table operated upon
/// @return the number of key => value entries in the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);

/// @brief checks if the hash table is empty
/// @param h hash table operated upon
/// @return true is size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief check if a hash table has an entry with a given key
/// @param h hash table operated upon
/// @param key the key sought
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if a hash table has an entry with a given value
/// @param h hash table operated upon
/// @param value the value sought
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

//// @brief apply a function to all entries in a hash table
/// @param h hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg);

/// @brief check if all ht entry values are equal to value.
/// @param ht hash table operated upon
/// @param value the value that all value entries should equal
/// @return boolean true or false.
bool hash_table_has_all_values(ioopm_hash_table_t *ht, elem_t value);
