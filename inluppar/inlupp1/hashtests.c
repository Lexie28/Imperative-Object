#include <CUnit/Basic.h>
#include "hash_table.h"
//#include "hash_table.c"

#include <string.h>


int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// These are example test functions. You should replace them with
// functions of your own.
void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht); //	Check that ht is not equal to NULL
   ioopm_hash_table_destroy(ht);
}

void test_insert_freshkey()
{
  int k = 1;
  char *v = "John";
  ioopm_hash_table_t *ht = ioopm_hash_table_create(); //create a new empty hash table ht
  option_t first = ioopm_hash_table_lookup(ht, k); //verify that key k is not in h using lookup
  char *a = first.value;
  CU_ASSERT_PTR_NULL(a); //make sure a is null aka that there is no value to key k in ht
  ioopm_hash_table_insert(ht, k, v); //insert (k, v) into the hashtable
  option_t second = ioopm_hash_table_lookup(ht, k);
  char *b = second.value;
  CU_ASSERT_STRING_EQUAL(b, v); //make sure value b in ht (paired with k), is the same as value v we inserted together in beginning
  ioopm_hash_table_destroy(ht); //destroy ht 
}

void test_insert_alreadythere ()
{
  int k = 2;
  char *v1 = "Lexie";
  ioopm_hash_table_t *ht = ioopm_hash_table_create(); //create a new empty hash table ht
  ioopm_hash_table_insert(ht, k, v1);
  option_t first= ioopm_hash_table_lookup(ht, k); //verify that key k IS ht using lookup. return value mapped to this k
  char *a = first.value;
  char *v2 = "Nyacool";
  ioopm_hash_table_insert(ht, k, v2); //insert (k, v) into the hashtable
  option_t second= ioopm_hash_table_lookup(ht, k); //looking up new value mapped to k
  char *b = second.value; 
  CU_ASSERT_STRING_NOT_EQUAL(a, b); //make sure current value paired with k (b) is NOT the same as initial value a
  CU_ASSERT_STRING_EQUAL(b, v2);
  ioopm_hash_table_destroy(ht); //destroy ht
}

void test_insert_invalidkey()
{
  int k = -67;
  char *v = "Lexie";
  ioopm_hash_table_t *ht = ioopm_hash_table_create(); //create a new empty hash table ht
  ioopm_hash_table_insert(ht, k, v);
  option_t first= ioopm_hash_table_lookup(ht,k);
  char *a = first.value;
  CU_ASSERT_PTR_NULL(a);
  ioopm_hash_table_destroy(ht); 
  
  //CU_ASSERT_STRING_EQUAL(v,a); //TODO?? SKA VI KUNNA TA INVALIDS? VAD ÄR INVALIDS
  //test andra invalids också
}

void test_lookup_empty()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   for (int i = 0; i < 18; ++i) /// 18 is a bit magical. 18 because 17 wraps around to 0.
     {
       option_t first = ioopm_hash_table_lookup(ht, i);
       CU_ASSERT_PTR_NULL(first.value);
     }
   option_t second = ioopm_hash_table_lookup(ht,-1);
   CU_ASSERT_PTR_NULL(second.value);
   ioopm_hash_table_destroy(ht);
}


//test different combinations of 1,2 and 3. look first half of inlup1.

int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
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
    (CU_add_test(my_test_suite, "Test that create != destroy hash table", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "Test that inserts a fresh key in hash table", test_insert_freshkey) == NULL) ||
    (CU_add_test(my_test_suite, "Test that inserts already existing key in hash table", test_insert_alreadythere) == NULL) ||
    (CU_add_test(my_test_suite, "Test that is trying to look up a key that is not in the table", test_insert_invalidkey) == NULL) ||
    (CU_add_test(my_test_suite, "Test lookup empty", test_lookup_empty) == NULL) ||
    0
  )
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