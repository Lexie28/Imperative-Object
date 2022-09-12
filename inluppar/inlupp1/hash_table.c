#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


typedef struct entry entry_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[17]; // utan * för att add a dummy entre to the buckets' lists??
};


ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  return result;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  free(ht);
}

static entry_t *find_previous_entry_for_key(ioopm_hash_table_t *ht, int key)
{
  int bucket = key % 17;
  entry_t *first_entry = &ht->buckets[bucket];
  entry_t *a = first_entry;
  //pointer to first entry = a
  while (a != NULL)
  {
    if (a->key == key)
    {
      return a; //how to make it return previous entry??
    }
    a = a->next;
  }

}

static entry_t *entry_create(int k, char *v, entry_t *first_entry)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  new_entry->key = k;
  new_entry->value = v;
  new_entry -> next = first_entry;

  //make the new entry place

}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry
  int bucket = key % 17;
  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key); //This passes in the addressto the entry in the bucket rather than passes in a copy of the entire entry
  entry_t *next = entry->next; //entry is the previous key

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }
}

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key (FIXME: incomplete)
char *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  //TODO: Stud
  return NULL; //why return NULL here? difference from writing it where Void is??
}

