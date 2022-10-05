#include "hash_table.h"
#include <CUnit/Basic.h>
#include <string.h>
#include <stdlib.h>

int init_suite(void)
{
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void)
{
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// These are example test functions. You should replace them with
// functions of your own.

void test_create_destroy()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int);
  CU_ASSERT_PTR_NOT_NULL(ht); //    Check that ht is not equal to NULL
  ioopm_hash_table_destroy(ht);
}

void test_insert_freshkey()                                  // ELEM_T ADAPTED
{                                                            // stacken inom funktionen freshkey
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int);        // create a new empty hash table ht. pekaren sparas i stacken. tablecreate allokerar minne i heapen (som vi pekar på med en variabel från stacken)
  option_t first = ioopm_hash_table_lookup(ht, int_elem(1)); // verify that key k is not in h using lookup //skapa en ny stack för lookup med ht och k. look-up stacken försvinner (man "poppar stacken")
  // och ger vårt returvärde som vi sparar i variabeln first (som ligger freshkey-stacken). lookup-stacken finns inte längre
  char *a = first.value.p;
  CU_ASSERT_PTR_NULL(a);                                      // make sure a is null aka that there is no value to key k in ht //jämför vår stack-variabel a
  ioopm_hash_table_insert(ht, int_elem(1), ptr_elem("John")); // insert (k, v) into the hashtable //samma som i look-up (ny stack för insert - kopierar ht, k, v) - försvinner när vi når return i insert
  option_t second = ioopm_hash_table_lookup(ht, int_elem(1)); // samma som ovan
  char *b = second.value.p;
  CU_ASSERT_STRING_EQUAL(b, "John"); // make sure value b in ht (paired with k), is the same as value v we inserted together in beginning
  // jämför variablar från vår stack
  ioopm_hash_table_destroy(ht); // ny destroy-stack med kopia av ht. en till stack för clear. sista raden i destroy - freear heap-minnet för vårt hashtable
}

void test_insert_alreadythere() // ELEM_T ADAPTED
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int); // create a new empty hash table ht
  ioopm_hash_table_insert(ht, int_elem(2), ptr_elem("Lexie"));
  option_t a_tmp = ioopm_hash_table_lookup(ht, int_elem(2));
  char *a = a_tmp.value.p;                                       // verify that key k IS ht using lookup. return value mapped to this k
  ioopm_hash_table_insert(ht, int_elem(2), ptr_elem("Nyacool")); // insert (k, v) into the hashtable
  option_t b_tmp = ioopm_hash_table_lookup(ht, int_elem(2));
  char *b = b_tmp.value.p;          // looking up new value mapped to k
  CU_ASSERT_STRING_NOT_EQUAL(a, b); // make sure current value paired with k (b) is NOT the same as initial value a
  ioopm_hash_table_destroy(ht);     // destroy ht
}

void test_insert_invalidkey() // ELEM_T ADAPTED
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int); // create a new empty hash table ht
  ioopm_hash_table_insert(ht, int_elem(-67), ptr_elem("Lexie"));
  option_t a_tmp = ioopm_hash_table_lookup(ht, int_elem(-67));
  char *a = a_tmp.value.p;
  CU_ASSERT_PTR_NULL(a);
  ioopm_hash_table_destroy(ht);
  // test andra invalids också
}

/*
void insert_same_bucketfirst() //insert in the same bucket 1 18 35
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int); // create a new empty hash table ht
  ioopm_hash_table_insert(ht, int_elem(2), ptr_elem("Lexie"));
} n*/

void test_lookup_empty() // ELEM_T ADAPTED
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int);
  for (int i = 0; i < 18; ++i) /// 18 is a bit magical
  {
    option_t a_tmp = ioopm_hash_table_lookup(ht, int_elem(i));
    char *a = a_tmp.value.p;
    CU_ASSERT_PTR_NULL(a);
  }
  option_t a_tmp = ioopm_hash_table_lookup(ht, int_elem(-1));
  CU_ASSERT_PTR_NULL(a_tmp.value.p);
  ioopm_hash_table_destroy(ht);
}

void test_remove_entry() // ELEM_T ADAPTED
{
  int k = 12;                                                    // Creating key
  char *v = "Anthony";                                           // Creating value
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int);            // Creating hash table.
  ioopm_hash_table_insert(ht, int_elem(k), ptr_elem(v));         // Inserting key-value into hash table.
  char *removedVal = ioopm_hash_table_remove(ht, int_elem(k)).p; // Remove entry from hash table
  CU_ASSERT_STRING_EQUAL(removedVal, v);                         // Check that string val of entry removed = initial string value.
  option_t a_tmp = ioopm_hash_table_lookup(ht, int_elem(k));     // We look to see if we can find the key-value.
  CU_ASSERT_PTR_NULL(a_tmp.value.p);                             // We check if return value is NULL which it should be if we couldn't find it.
  ioopm_hash_table_destroy(ht);                                  // Free memory used by hash table.
}

void test_ht_size() // ELEM_T ADAPTED
// Test that takes the size of empty hash table, hash table with one entry, and hash table with several entries.
{
  ioopm_hash_table_t *emptyht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int); // Create an empty hash table.
  size_t sizOfEmptyHT = ioopm_hash_table_size(emptyht);    // Find the size of emptyht.
  CU_ASSERT_TRUE(sizOfEmptyHT == 0);                       // Check if return value from size of empty hash table = 0.
  ioopm_hash_table_destroy(emptyht);                       // Free memory used by emptyht.

  ioopm_hash_table_t *size1ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int);      // Create a hash table which we will set to size 1.
  int k1 = 12;                                                  // Creating key 1
  char *v1 = "Anthony";                                         // Creating value 1
  ioopm_hash_table_insert(size1ht, int_elem(k1), ptr_elem(v1)); // Inserting one entry into hash table of size 1.
  size_t sizOf1HT = ioopm_hash_table_size(size1ht);             // Find the size of size1ht.
  CU_ASSERT_TRUE(sizOf1HT == 1);                                // Check if return value from size of hash table with size 1 = 1.
  ioopm_hash_table_destroy(size1ht);                            // Free memory used by size 1 hash table.

  ioopm_hash_table_t *size3ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int);      // Create a hash table which we will set to size 3 (multiple entries).
  ioopm_hash_table_insert(size3ht, int_elem(k1), ptr_elem(v1)); // Inserting one entry into hash table of size 3.
  int k2 = 15;                                                  // Creating key 2
  char *v2 = "Marcus";                                          // Creating value 2
  ioopm_hash_table_insert(size3ht, int_elem(k2), ptr_elem(v2)); // Inserting the second entry into hash table of size 3.
  int k3 = 2;                                                   // Creating key 3
  char *v3 = "Samuel";                                          // Creating value 3
  ioopm_hash_table_insert(size3ht, int_elem(k3), ptr_elem(v3)); // Inserting the third entry into hash table of size 3.
  size_t sizOfMultipleHT = ioopm_hash_table_size(size3ht);      // Find the size of size3ht.
  CU_ASSERT_TRUE(sizOfMultipleHT == 3);                         // Check if return value from size of hash table with size 3 (multiple entries) = 3.
  ioopm_hash_table_destroy(size3ht);                            // Free memory used by hash table with multiple entries (3).
}

void test_is_ht_empty() // ELEM_T ADAPTED
{
  ioopm_hash_table_t *emptyht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int); // Create an empty hash table.
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(emptyht));      // Check if hash table is empty or not (should be empty).
  ioopm_hash_table_destroy(emptyht);                       // Free memory used by hash table.

  ioopm_hash_table_t *size3ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int);      // Create a hash table which we will set to size 3 (multiple entries).
  int k1 = 12;                                                  // Creating key 1
  char *v1 = "Anthony";                                         // Creating value 1
  ioopm_hash_table_insert(size3ht, int_elem(k1), ptr_elem(v1)); // Inserting one entry into hash table of size 3.
  int k2 = 15;                                                  // Creating key 2
  char *v2 = "Marcus";                                          // Creating value 2
  ioopm_hash_table_insert(size3ht, int_elem(k2), ptr_elem(v2)); // Inserting the second entry into hash table of size 3.
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(size3ht));          // Check if hash table is empty (should not be).
  ioopm_hash_table_destroy(size3ht);                            // Free memory used by hash table.
}

void test_clear_ht() // ELEM_T ADAPTED
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int);      // Create an hash table.
  int k1 = 12;                                             // Creating key 1
  char *v1 = "Anthony";                                    // Creating value 1
  ioopm_hash_table_insert(ht, int_elem(k1), ptr_elem(v1)); // Inserting one entry into the hash table.
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));          // See if hash table is empty (should not be).
  ioopm_hash_table_clear(ht);                              // Clear the hash table.
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));           // See if the hash table is now empty.
  ioopm_hash_table_destroy(ht);                            // Free memory used by hash table.
}

void test_get_all_keys() // ELEM_T ADAPTED
{
  int keys[5] = {0, 10, 42, 3, 99};                                 // Creating an array of k to be inserted into hash table.
  char *values[5] = {"Anthony", "Lexie", "Marcus", "Anik", "Lowe"}; // Creating an array of v to be inserted into hash table.
  bool found[5] = {false};
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int); // Create an hash table.
  for (int i = 0; i < 5; i++)                         // Iterate over k, v arrays and insert their values into the hash table.
  {
    ioopm_hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
  }
  size_t htSize = ioopm_hash_table_size(ht);           // We find the hash table size.
  ioopm_list_t *foundKeys = ioopm_hash_table_keys(ht); // We set an array to all keys in the hash table.
  for (int i = 0; i < htSize; i++)                     // Iterate over the resulting array
  {
    for (int j = 0; j < htSize; j++)
    {
      if (ioopm_linked_list_get(foundKeys, j).i == keys[i]) // If they are equal, we set corresponding found position to true.
      {
        found[i] = true;
      }
    }
    if (found[i] == false)
    {

      CU_FAIL("Found a key that was never inserted!");
    }
    // If the list entries are not equal we register fail.
  }
  for (int i = 0; i < htSize; i++)
  {
    CU_ASSERT_TRUE(found[i]);
  }
  ioopm_linked_list_destroy(foundKeys); // Free memory used by foundKeys.
  ioopm_hash_table_destroy(ht);         // Free memory used by hash table.
}

void test_get_all_values() // ELEM_T ADAPTED -- ADAPTED FOR LINKED LIST ALL VALUES
{
  int keys[5] = {0, 10, 42, 3, 99};                                 // Creating an array of k to be inserted into hash table.
  char *values[5] = {"Anthony", "Lexie", "Marcus", "Anik", "Lowe"}; // Creating an array of v to be inserted into hash table.
  bool found[5] = {false};
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_str, hash_map_func_int); // Create an hash table.
  for (int i = 0; i < 5; i++)                         // Iterate over k, v arrays and insert their values into the hash table.
  {
    ioopm_hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
  }
  size_t htSize = ioopm_hash_table_size(ht); // We find the hash table size.
  ioopm_list_t *foundValues = ioopm_hash_table_values(ht); // We set an array to all keys in the hash table.
  for (int i = 0; i < htSize; i++)                  // Iterate over the resulting array
  {
    for (int j = 0; j < htSize; j++)
    {
      if (ioopm_linked_list_get(foundValues, j).p == values[i]) // If they are equal, we set corresponding found position to true.
      {
        found[i] = true;
      }
    }
    if (found[i] == false) // If we find a value that was never inserted.
    {
      CU_FAIL("Found a value that was never inserted!");
    }
    // If the list entries are not equal we register fail.
  }
  for (int i = 0; i < htSize; i++)
  {
    CU_ASSERT_TRUE(found[i]);
  }
  ioopm_linked_list_destroy(foundValues);            // Free memory used by foundKeys.
  ioopm_hash_table_destroy(ht); // Free memory used by hash table.
}

void test_has_key() // ELEM_T ADAPTED
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int);         // Create an hash table.
  int k1 = 12;                                                // Creating a key
  char *v1 = "Anthony";                                       // Creating a value
  ioopm_hash_table_insert(ht, int_elem(k1), ptr_elem(v1));    // Inserting an entry into the hash table.
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, int_elem(k1))); // Check that we are able to find the key.
  ioopm_hash_table_clear(ht);                                 // Clear the hash table
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht,int_elem(k1)));  // Check now that we are not able to find the key.
  ioopm_hash_table_destroy(ht);                       // Free memory used by it.
}
void test_has_value() // ELEM_T ADAPTED
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int);
  int k = 2;
  char *v = "Lexie";
  ioopm_hash_table_insert(ht, int_elem(k), ptr_elem(v));
  char *copy = strdup(v);                                         // TODO???? VARFÖR FUNKAR INTE STRING COPY?????????????
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, ptr_elem(v)));    // Kollar ekvivalens med og value.
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, ptr_elem(copy))); // Kollar ekvivalens med kopia av
  ioopm_hash_table_clear(ht);
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, ptr_elem(v)));
  free(copy);
  ioopm_hash_table_destroy(ht);
}

void test_all_values()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(elem_equality_func_int, hash_map_func_int);
  char *v = "Lexie";           // Our key to insert across hash table.
  for (int i = 1; i < 11; i++) // Insert value across many hash tables.
  {
    ioopm_hash_table_insert(ht, int_elem(i), ptr_elem(v));
  }
  CU_ASSERT_TRUE(hash_table_has_all_values(ht, ptr_elem(v))); // See if all values are equal to it (should pass).
  ioopm_hash_table_clear(ht);                                 // Clear the hash table.
  CU_ASSERT_FALSE(hash_table_has_all_values(ht, ptr_elem(v))); // See if all values are equal to it (should fail).
  ioopm_hash_table_destroy(ht);
}

// END OF TEST CASES //
// MAIN //

int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("Testing border cases of hash table functions", init_suite, clean_suite);
  if (my_test_suite == NULL)
  {
    // If the test suite could not be added, tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
      (CU_add_test(my_test_suite, "Test that create != destroy hash table.", test_create_destroy) == NULL) ||
      (CU_add_test(my_test_suite, "Trying to insert a key not already in the hash table.", test_insert_freshkey) == NULL) ||
      (CU_add_test(my_test_suite, "Trying to insert a key already in the hash table.", test_insert_alreadythere) == NULL) ||
      (CU_add_test(my_test_suite, "Trying to lookup a key that is not in the hash table.", test_lookup_empty) == NULL) ||
      (CU_add_test(my_test_suite, "Trying to insert an invalid key.", test_insert_invalidkey) == NULL) ||
      (CU_add_test(my_test_suite, "Removing a key from the hash table.", test_remove_entry) == NULL) ||
      (CU_add_test(my_test_suite, "Checking the size of different hash tables.", test_ht_size) == NULL) ||
      (CU_add_test(my_test_suite, "Checking if the hash table is empty.", test_is_ht_empty) == NULL) ||
      (CU_add_test(my_test_suite, "Trying to clear an hash table", test_clear_ht) == NULL) ||
      (CU_add_test(my_test_suite, "Getting all the keys from a hash table.", test_get_all_keys) == NULL) ||
      (CU_add_test(my_test_suite, "Getting all the values from a hash table.", test_get_all_values) == NULL) ||
      //Tests below are leaking for unknown reason.
      (CU_add_test(my_test_suite, "Testing if a key exists in a hash table.", test_has_key) == NULL) ||
      (CU_add_test(my_test_suite, "Testing if a value exists in a hash table.", test_has_value) == NULL) ||
      (CU_add_test(my_test_suite, "Testing if a value is equal to all values in a hash table.", test_all_values) == NULL) ||
      0)
  {
    // If adding any of the tests fails, we tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}