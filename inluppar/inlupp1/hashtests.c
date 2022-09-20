#include <CUnit/Basic.h>
#include <stdlib.h>
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
{ //pekaren/adressen till vårt hash table (som är i heapen) ligger i en stack - pekaren ht är i stacken och ioopmhashtablecreate är minne i heapen
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht); //	Check that ht is not equal to NULL
   ioopm_hash_table_destroy(ht);
}

void test_insert_freshkey()
{
  int k = 1; //stacken inom funktionen freshkey
  char *v = "John"; //s
  ioopm_hash_table_t *ht = ioopm_hash_table_create(); //create a new empty hash table ht. pekaren sparas i stacken. tablecreate allokerar minne i heapen (som vi pekar på med en variabel från stacken)
  option_t first = ioopm_hash_table_lookup(ht, k); //verify that key k is not in h using lookup //skapa en ny stack för lookup med ht och k. look-up stacken försvinner (man "poppar stacken")
  //och ger vårt returvärde som vi sparar i variabeln first (som ligger freshkey-stacken). lookup-stacken finns inte längre
  char *a = first.value; //en till stack-variabel a
  CU_ASSERT_PTR_NULL(a); //make sure a is null aka that there is no value to key k in ht //jämför vår stack-variabel a
  ioopm_hash_table_insert(ht, k, v); //insert (k, v) into the hashtable //samma som i look-up (ny stack för insert - kopierar ht, k, v) - försvinner när vi når return i insert
  option_t second = ioopm_hash_table_lookup(ht, k); //samma som ovan
  char *b = second.value;
  CU_ASSERT_STRING_EQUAL(b, v); //make sure value b in ht (paired with k), is the same as value v we inserted together in beginning
  //jämför variablar från vår stack
  ioopm_hash_table_destroy(ht); //ny destroy-stack med kopia av ht. en till stack för clear. sista raden i destroy - freear heap-minnet för vårt hashtable
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
  
  //TODO?? SKA VI KUNNA TA INVALIDS? VAD ÄR INVALIDS
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

void test_remove_existingkey()
{
  int k = 6;
  char *v = "Lexie";
  ioopm_hash_table_t *ht = ioopm_hash_table_create(); //create a new hashtable
  ioopm_hash_table_insert(ht, k, v);
  ioopm_hash_table_remove(ht,k);
  option_t second = ioopm_hash_table_lookup(ht,k);
  char *b = second.value;
  CU_ASSERT_PTR_NULL(b); //checks that b is NULL (since we should have removed this entry)
  ioopm_hash_table_destroy(ht);
}

void test_remove_nonexistingkey()
{
  int k = 6;
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_remove (ht, k);
  option_t first = ioopm_hash_table_lookup(ht,k);
  char *a = first.value;
  CU_ASSERT_PTR_NULL(a); //checks that a = NULL since if we try to remove something that isn't there it remains NULL
  ioopm_hash_table_destroy(ht);
}

void test_countingemptyht()
{//testing ioopm_hash_table_size for case where hash table is empty
  ioopm_hash_table_t *ht = ioopm_hash_table_create(); //creates a new empty hashtable
  int a = ioopm_hash_table_size(ht); //gets size of current hashtable
  CU_ASSERT_EQUAL(a,0);//checks that size = 0 if ht is empty
  ioopm_hash_table_destroy(ht); //destroys and frees hashtable
}

void test_countingsingleht()
{//testing ioopm_hash_table_size for case where hash table has a single entry
  int k = 7; //creating variable k = 7
  char *v = "Lexie"; //creating variable v = "Lexie"
  ioopm_hash_table_t *ht = ioopm_hash_table_create(); //create a new empty hash table ht
  ioopm_hash_table_insert(ht, k, v); //inserting (k,v) into hashtable ht
  int a = ioopm_hash_table_size(ht); //get size of our current hash table
  CU_ASSERT_EQUAL(a,1);//checks that size of hashtable is 1 if it has one entry
  ioopm_hash_table_destroy(ht); //destroys and frees hashtable
}

void test_countingmanyht()
{//testing ioopm_hash_table_size for case where hash table has multiple entries; in this case three entries
  int k = 7; //creating variable k = 7
  char *v = "Lexie"; //creating variable v = "Lexie"
  ioopm_hash_table_t *ht = ioopm_hash_table_create(); //create a new empty hash table ht
  ioopm_hash_table_insert(ht, k, v); //inserting (k,v) into hashtable ht
  int k2 = 1; //creating variable k2 = 1
  char *v2 = "Hej"; //creating variable v2 = "Hej"
  ioopm_hash_table_insert(ht, k2, v2); //inserting (k2,v2) into hashtable ht
  int k3 = 3; //creating variable k3 = 3
  char *v3 = "Ja"; //creating variable v3 = "Ja"
  ioopm_hash_table_insert(ht, k3, v3); //inserting (k3,v3) into hashtable ht
  int a = ioopm_hash_table_size(ht); //gets size of our current hashtable
  CU_ASSERT_EQUAL(a,3);//checks that size of hashtable is 3 if it has three entries
  ioopm_hash_table_destroy(ht); //destroys and frees hashtable
}

void test_clearingaht()
{
  int k = 18;
  char *v = "Lexie";
  ioopm_hash_table_t *ht = ioopm_hash_table_create(); //create a new empty hash table ht
  ioopm_hash_table_insert(ht, k, v);
  int k2 = 1;
  char *v2 = "Hej";
  ioopm_hash_table_insert(ht, k2, v2);
  int k3 = 35;
  char *v3 = "Ja";
  ioopm_hash_table_insert(ht, k3, v3);
  ioopm_hash_table_clear(ht);
  bool a = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(a);
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
    (CU_add_test(my_test_suite, "Test remove existing key", test_remove_existingkey) == NULL) ||
    (CU_add_test(my_test_suite, "Test remove non-existing key", test_remove_nonexistingkey) == NULL) ||
    (CU_add_test(my_test_suite, "Test counting entries in empty ht", test_countingemptyht) == NULL) ||
    (CU_add_test(my_test_suite, "Test counting entries in one-entry ht", test_countingsingleht) == NULL) ||
    (CU_add_test(my_test_suite, "Test counting entries in multiple-entry (3 entries) ht", test_countingmanyht) == NULL) ||
    (CU_add_test(my_test_suite, "Test clearing a hashtable", test_clearingaht) == NULL) ||
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