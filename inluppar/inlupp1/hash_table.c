

#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define Success(v) (option_t){.success = true, .value = v};
#define Failure() (option_t){.success = false}; // valuet blir NULL
#define Successful(o) (o.success == true)
#define Unsuccessful(o) (o.success == false)

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
  // utan * så säger vi att varje låda innehåller en entry_t och då kommer den skapas (dummy)
};

// typedef struct option option_t;

static entry_t *find_previous_entry_for_key(entry_t *entry, int key)
{
  // ctr + F to search for things

  while (entry->next != NULL && entry->next->key < key)
  {
    entry = entry->next;
  }
  return entry;
}

char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
  
  
  entry_t *prev_entry = find_previous_entry_for_key(&ht->buckets[key % 17], key);
  entry_t *entry_remove = prev_entry->next;
  option_t entry_exist = ioopm_hash_table_lookup(ht, key);
  if(entry_exist.success)
  {
    
    prev_entry->next = entry_remove->next;
    free(entry_remove);
    return(entry_exist.value);
  }
  
  return NULL;
  
}

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  return result;
}

void entry_destroy(entry_t *entry)
{
  free(entry);
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) // the hash table only owns (and thus needs to manage)
// the memory it has allocated itself (meaning only the buckets array and all entries). Thus, if destroying a hash table creates memory leaks it is the fault of the programmer.
{
  // destroy_entry(entries in ht)
  // iterate over the buckets in the buckets array
  for (int i = 0; i < 17; i++)
  {
    entry_t *entry = &ht->buckets[i]; // pekare till början av varje bucket
    entry = entry->next;              // för att skippa dummy entryt

    while (entry != NULL) // går igenom next-pekarna tills vi kommer till slutet
    {
      entry_t *a = entry->next;
      free(entry);
      entry = a;
    }
  }
  // for each bucket, iterate over its entries and deallocate them
  free(ht); // destroying the ht structure
}

static entry_t *entry_create(int k, char *v, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  new_entry->key = k;
  new_entry->value = v;
  new_entry->next = next;
  return new_entry;
}



void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  if (key < 0)
  {
    printf("Invalid key!");
    return;
  }
  /// Calculate the bucket for this entry
  int bucket = key % 17;
  /// Search for an existing entry for a key
  entry_t *previousentry = find_previous_entry_for_key(&ht->buckets[bucket], key); // This passes in the address to the entry in the
  // bucket rather than passes in a copy of the entire entry
  // pekare till hela entryt innan det vi vill sätta in
  entry_t *next = previousentry->next; // previousentry is the previous key
  // next är pekare till gamla vad som den pekade till

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key) // vi är inte på slutet och vi vill
  // sätta in nytt entry med samma key som existerande, byter vi bara ut valuet till det nya
  {
    next->value = value;
  }
  else
  {
    previousentry->next = entry_create(key, value, next); // entrycreate returnerar pekaren till det nya entryt.
    // previousentry pekar till lådan med elementet innan där vi vill sätta in
    // previousentry->next = pekaren i sista lådan som vi ändrar till att peka på vårt nya element
  }
}

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key (FIXME: incomplete)
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  /// Find the previous entry for key
  if (key < 0)
  {
    return Failure();
  }
  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[key % 17], key);
  entry_t *next = tmp->next;

  if (next && next->value)
  {
    return Success(next->value);
  }
  else
  {
    return Failure();
  }
}

/*
int main(int argc, char const *argv[])
{
  return 0;
}
*/