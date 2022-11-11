#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include <stdbool.h>
#include <string.h>
#define Success(v) (option_t){.success = true, .value = v};
#define Failure() (option_t){.success = false};
#define Successful(o) (o.success == true)
#define Unsuccessful(o) (o.success == false)
#define No_Buckets 17

typedef struct entry entry_t;
typedef struct option option_t;

struct hash_table
{
    entry_t buckets[No_Buckets];       // The buckets
    ioopm_eq_function key_eq_fn;       // Function for checking if keys are equal.
    ioopm_hash_function hash_function; // Function for determining the keys of inputs elem_t.
};

// FUNCTIONS BELOW //

static bool key_equiv(elem_t key, elem_t value_ignored, void *x, ioopm_hash_function hash_func)
{
    int *other_key_ptr = x;
    int other_key = *other_key_ptr;
    return hash_func(key) == other_key;
}

static bool value_equiv(elem_t key_ignored, elem_t value, void *x, ioopm_hash_function hash_func)
{
    char **other_value_ptr = x;
    char *other_value = *other_value_ptr;
    if (strcmp(value.p, other_value) == 0)
    {
        return true;
    }
    return false;
}

int hash_map_func_int(elem_t key) // Hash mapping function when elem_t is an integer.
{
    int int_key = key.i;
    return int_key;
    /*if (key.i < 0)
    {
        int int_key = key.i; // If key is negative we will return the positive variant of it.
        return int_key;
    }
    else // Otherwise (it is positive) we will return simply it's value.
    {
    }
    */
}

static entry_t *find_previous_entry_for_key(entry_t *entry, elem_t key, ioopm_eq_function key_eq_fun)
{
    while (entry->next != NULL)
    {
        if (key_eq_fun(entry->next->key, key))
        {
            return entry;
        }
        else
        {
            entry = entry->next;
        }
    }
    return entry;
}

static entry_t *entry_create(elem_t insertedKey, elem_t v, entry_t *next)
{
    entry_t *new_entry = calloc(1, sizeof(entry_t));
    new_entry->key = insertedKey; // The key value.
    new_entry->value = v;
    new_entry->next = next;
    return new_entry;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) // the hash table only owns (and thus needs to manage)
// the memory it has allocated itself (meaning only the buckets array and all entries). Thus, if destroying a hash table creates memory leaks it is the fault of the programmer.
{
    ioopm_hash_table_clear(ht);
    free(ht);
}

void ioopm_hash_table_destroy_key(ioopm_hash_table_t *ht) // the hash table only owns (and thus needs to manage)
// the memory it has allocated itself (meaning only the buckets array and all entries). Thus, if destroying a hash table creates memory leaks it is the fault of the programmer.
{
    ioopm_hash_table_clear_key(ht);
    free(ht);
}

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_eq_function ins_key_eq_fn, ioopm_hash_function ins_hash_func)
{
    ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
    result->hash_function = ins_hash_func;
    result->key_eq_fn = ins_key_eq_fn;
    return result;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t insertedKey, elem_t value)
{
    int mappedKey = ht->hash_function(insertedKey);
    // assert(mappedkey > 0 && return); //mappedkey måste vara större än noll, annars return
    if (mappedKey < 0)
    {
        return;
        
    }
    /// Calculate the bucket for this entry
    int bucket = mappedKey % No_Buckets;
    /// Search for an existing entry for a key
    entry_t *previousentry = find_previous_entry_for_key(&ht->buckets[bucket], insertedKey, ht->key_eq_fn); // This passes in the address to the entry in the
    // bucket rather than passes in a copy of the entire entry
    // pekare till hela entryt innan det vi vill sätta in
    entry_t *next = previousentry->next; // previousentry is the previous key
    // next är pekare till gamla vad som den pekade till

    /// Check if the next entry should be updated or not
    if (next != NULL && ht->key_eq_fn(next->key, insertedKey)) // vi är inte på slutet och vi vill
    // sätta in nytt entry med samma key som existerande, byter vi bara ut valuet till det nya
    {
        next->value = value;
    }
    else
    {
        previousentry->next = entry_create(insertedKey, value, next); // entrycreate returnerar pekaren till det nya entryt.
                                                                      // previousentry pekar till lådan med elementet innan där vi vill sätta in
                                                                      // previousentry->next = pekaren i sista lådan som vi ändrar till att peka på vårt nya element
    }
}

option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t insertedKey)
{
    int mappedKey = ht->hash_function(insertedKey);
    //assert(mappedKey > 0 && "You want to look-up an invalid key");
    if (mappedKey < 0)
    {
        return Failure();
    }
    int bucket = mappedKey % No_Buckets;
    entry_t *tmp = find_previous_entry_for_key(&ht->buckets[bucket], insertedKey, ht->key_eq_fn);
    entry_t *next = tmp->next;

    if (next && ht->key_eq_fn(next->key, insertedKey)) // kolla både att vi fick ut en pekare, men också att dom är samma!! så next->key faktiskt är samma som insertedKey som vi vill kolla
    {
        return Success(next->value);
    }
    else
    {
        return Failure();
    }
}

option_t ioopm_hash_table_lookup_key(ioopm_hash_table_t *ht, elem_t insertedKey)
{
    int mappedKey = ht->hash_function(insertedKey);
    //assert(mappedKey > 0 && "You want to look-up an invalid key");
    if (mappedKey < 0)
    {
        return Failure();
    }
    int bucket = mappedKey % No_Buckets;
    entry_t *tmp = find_previous_entry_for_key(&ht->buckets[bucket], insertedKey, ht->key_eq_fn);
    entry_t *next = tmp->next;

    if (next && ht->key_eq_fn(next->key, insertedKey)) // kolla både att vi fick ut en pekare, men också att dom är samma!! så next->key faktiskt är samma som insertedKey som vi vill kolla
    {
        return Success(next->key);
    }
    else
    {
        return Failure();
    }
}

elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t insertedKey)
{

    int mapped_key = ht->hash_function(insertedKey);
    int bucket = mapped_key % No_Buckets;
    entry_t *prev_entry = find_previous_entry_for_key(&ht->buckets[bucket], insertedKey, ht->key_eq_fn); // finds previous entry to the entry we want to remove
    entry_t *entry_remove = prev_entry->next;                                                            // entry_remove is pointer to entry we wish to remove (the one after our previous entry)
    option_t entry_exist = ioopm_hash_table_lookup(ht, insertedKey);                                     // we look if our entry exists in our hashtable
    if (entry_exist.success == true)                                                                     // if our entry that we want to remove does exist
    {

        prev_entry->next = entry_remove->next; // we make the previous entry next pointer point to the adress of the entry AFTER the one we want to remove
        free(entry_remove);                    // we free the entry we want to remove
        elem_t returnVal = entry_exist.value;
        return returnVal; // we return the value belonging together with the key in the entry we removed (as requested on studium)
    }

    return ptr_elem(NULL); // if the entry we wanted to remove didn't even exist in our hashtable we return NULL
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
    size_t acc = 0;
    for (int i = 0; i < No_Buckets; i++)
    {
        entry_t *entry = &ht->buckets[i]; // pekare till början av varje bucket
        entry = entry->next;              // we skip dummy entry and go into
        while (entry != NULL)             // går igenom next-pekarna tills vi kommer till slutet
        {
            entry_t *a = entry->next;
            entry = a;
            acc++;
        }
    }
    return acc;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
    // entry = entry->next;              // we skip dummy entry and go into
    for (int i = 0; i < No_Buckets; i++)
    {
        entry_t *entry = &ht->buckets[i];
        if (entry->next != NULL) // If dummy entry pointer is not equal to NULL we can return false.
        {
            return false;
        }
    }
    return true; // If we go through all buckets and this is not true we return true.
}

void ioopm_hash_table_clear_key(ioopm_hash_table_t *ht)
{
    // Iterate over the different buckets.
    for (int i = 0; i < No_Buckets; i++)
    {
        entry_t *entry = &ht->buckets[i]; // pekare till början av varje bucket
        entry = entry->next;              // we skip dummy entry and go into
        while (entry != NULL)             // går igenom next-pekarna tills vi kommer till slutet
        {
            entry_t *a = entry->next;
            free((entry->key).p);
            free(entry);
            entry = a;
        }
        entry_t *dummyEntry = &ht->buckets[i];
        dummyEntry->next = NULL;
    }

    // for each bucket, iterate over its entries and deallocate them
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
    // Iterate over the different buckets.
    for (int i = 0; i < No_Buckets; i++)
    {
        entry_t *entry = &ht->buckets[i]; // pekare till början av varje bucket
        entry = entry->next;              // we skip dummy entry and go into
        while (entry != NULL)             // går igenom next-pekarna tills vi kommer till slutet
        {
            entry_t *a = entry->next;
            free(entry);
            entry = a;
        }
        entry_t *dummyEntry = &ht->buckets[i];
        dummyEntry->next = NULL;
    }

    // for each bucket, iterate over its entries and deallocate them
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
    // calloc = number of elements followed by each element size
    // Problem is that calloc overwrites the memory we are already using.
    ioopm_list_t *keylist = ioopm_linked_list_create(elem_equality_func_int);

    for (int i = 0; i < No_Buckets; i++) // We go through entire table;
    {
        entry_t *entry = &ht->buckets[i]; // Pointer to start of each bucket.
        while (entry->next != NULL)       // går igenom next-pekarna tills vi kommer till slutet
        {
            entry = entry->next; // We skip the dummy entry.
            ioopm_linked_list_append(keylist, entry->key);
        }
    }
    return keylist;
}

ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
    ioopm_list_t *keylist = ioopm_linked_list_create(elem_equality_func_str); // We create the linked list and use elem equality function for strings since the values should be string format.
    // int acc = 0;                                        // We set accumulator to 0,
    for (int i = 0; i < No_Buckets; i++) // We go through entire table;
    {
        // We are unable to access ht, why?
        entry_t *entry = &ht->buckets[i]; // Pointer to start of each bucket.
        while (entry->next != NULL)       // går igenom next-pekarna tills vi kommer till slutet
        {
            entry = entry->next;                             // We skip the dummy entry.
            ioopm_linked_list_append(keylist, entry->value); // We add the value to the end of the list.
            // foundValues[acc] = entry->value.p; // We set current position in int array to current entry's key.
            // acc++;                             // We increase accumulator to go to next position in our int array.
        }
    }
    return keylist;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
    size_t size = ioopm_hash_table_size(ht);
    ioopm_list_t *keys = ioopm_hash_table_keys(ht);
    ioopm_list_t *values = ioopm_hash_table_values(ht);
    for (int i = 0; i < size; ++i)
    {
        if (pred(ioopm_linked_list_get(keys, i), ioopm_linked_list_get(values, i), arg, ht->hash_function) == true)
        {
            ioopm_linked_list_destroy(keys);   // Free space used by keys.
            ioopm_linked_list_destroy(values); // Free space used by values.
            return true;
        }
    }
    ioopm_linked_list_destroy(keys);   // In-case we never enter the if-statement, free memory.
    ioopm_linked_list_destroy(values); // In-case we never enter the if-statement, free memory.
    return false;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *x)
{
    size_t size = ioopm_hash_table_size(ht);
    ioopm_list_t *keys = ioopm_hash_table_keys(ht);
    ioopm_list_t *values = ioopm_hash_table_values(ht);
    if (size == 0)
    {
        ioopm_linked_list_destroy(keys);
        free(values);
        return false;
    }
    for (int i = 0; i < size; ++i)
    {
        if (pred(ioopm_linked_list_get(keys, i), ioopm_linked_list_get(values, i), x, ht->hash_function) == false)
        {
            ioopm_linked_list_destroy(keys);
            ioopm_linked_list_destroy(values);
            return false;
        }
    }
    ioopm_linked_list_destroy(keys);
    ioopm_linked_list_destroy(values);
    return true;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
    return ioopm_hash_table_any(ht, key_equiv, &key);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
    return ioopm_hash_table_any(ht, value_equiv, &value);
}

bool hash_table_has_all_values(ioopm_hash_table_t *ht, elem_t value)
{
    return ioopm_hash_table_all(ht, value_equiv, &value);
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg) // tar in ht, funktion, och om det ska ta argument till funktionen
{
    for (int i = 0; i < No_Buckets; i++)
    {
        entry_t *entry = &ht->buckets[i]; // pekare till början av varje bucket
        entry = entry->next;              // för att skippa dummy entryt
        while (entry != NULL)
        {
            apply_fun(entry->key, &entry->value, arg);
            entry = entry->next;
        }
    }
}

void ioopm_hash_table_apply_to_all_acc(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg, void *acc) // tar in ht, funktion, och om det ska ta argument till funktionen
{
    for (int i = 0; i < No_Buckets; i++)
    {
        entry_t *entry = &ht->buckets[i]; // pekare till början av varje bucket
        entry = entry->next;              // för att skippa dummy entryt
        while (entry != NULL)
        {
            apply_fun(entry->key, &entry->value, arg);
            entry = entry->next;
        }
    }
}
