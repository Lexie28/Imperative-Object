#include <CUnit/Basic.h>
#include <stdlib.h>
#include "linked_list.h"
//#include "hash_table.c"
#define _XOPEN_SOURCE 700

#include <string.h>

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

void test_create_destroy() // Testing to create and destroy a linked table.
{
  ioopm_list_t *list = ioopm_linked_list_create();
  CU_ASSERT_PTR_NOT_NULL(list);    // Check that we now have a pointer to where the linked structure is.
  ioopm_linked_list_destroy(list); // Destroy our linked structure.
}
/*
void test_append() // Testing to insert element at the end of linked list.
{
 ioopm_list_t *list = ioopm_linked_list_create();
 ioopm_linked_list_prepend(list, 100);
 ioopm_linked_list_prepend(list, 50);
 ioopm_linked_list_append(list, 7);
 CU_ASSERT_TRUE(ioopm_linked_list_get(list, 2) == 7);
 ioopm_linked_list_destroy(list); // Destroy our linked structure
} */
// TODO???????

void test_prepend() // Testing to insert an element at the start of a linked list.
{
  ioopm_list_t *linklist = ioopm_linked_list_create();       // Create a linked list.
  ioopm_linked_list_prepend(linklist, 100);                  // We add 100 to beginning of list.
  CU_ASSERT_TRUE(ioopm_linked_list_get(linklist, 0) == 100); // Check if first element is equal to what we
  ioopm_linked_list_destroy(linklist);                       // Free up memory used by linked structure.
}

void test_insertzero() // Testing to insert an element into random places in linked structure.
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 7);
  ioopm_linked_list_prepend(list, 4);
  ioopm_linked_list_prepend(list, 10);
  ioopm_linked_list_insert(list, 0, 9);
  CU_ASSERT_TRUE(ioopm_linked_list_get(list, 0) == 9);
  ioopm_linked_list_destroy(list);
}

void test_insertmiddle() // test to insert in the middle
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 7);
  ioopm_linked_list_prepend(list, 4);
  ioopm_linked_list_prepend(list, 10);
  ioopm_linked_list_insert(list, 2, 9);
  CU_ASSERT_TRUE(ioopm_linked_list_get(list, 2) == 9);
  ioopm_linked_list_destroy(list);
}

void test_remove()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 7);  // i2
  ioopm_linked_list_prepend(list, 4);  // i1
  ioopm_linked_list_prepend(list, 10); // i0
  ioopm_linked_list_remove(list, 1);
  int a = ioopm_linked_list_get(list, 1);
  CU_ASSERT_NOT_EQUAL(a, 4);
  CU_ASSERT_EQUAL(a, 7);
  ioopm_linked_list_destroy(list);
}

void test_get()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 7);
  ioopm_linked_list_prepend(list, 4);
  ioopm_linked_list_prepend(list, 10);
  CU_ASSERT_TRUE(ioopm_linked_list_get(list, 0) == 10);
  ioopm_linked_list_destroy(list);
}

void test_getmiddle()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 7);
  ioopm_linked_list_prepend(list, 4);
  ioopm_linked_list_prepend(list, 10);
  CU_ASSERT_TRUE(ioopm_linked_list_get(list, 1) == 4);
  ioopm_linked_list_destroy(list);
}

void test_containstrue()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 7);
  ioopm_linked_list_prepend(list, 4);
  ioopm_linked_list_prepend(list, 10);
  bool a = ioopm_linked_list_contains(list, 7);
  CU_ASSERT_TRUE(a);
  ioopm_linked_list_destroy(list); // Destroy our linked structure.
}

void test_containsempty()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  bool a = ioopm_linked_list_contains(list, 8);
  CU_ASSERT_FALSE(a);
  ioopm_linked_list_destroy(list); // Destroy our linked structure.
}

void test_containsnot()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 7);
  ioopm_linked_list_prepend(list, 4);
  ioopm_linked_list_prepend(list, 10);
  bool a = ioopm_linked_list_contains(list, 8);
  CU_ASSERT_FALSE(a);
  ioopm_linked_list_destroy(list); // Destroy our linked structure.
}

void test_sizeoflist()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 7);
  ioopm_linked_list_prepend(list, 4);
  ioopm_linked_list_prepend(list, 10);
  int a = ioopm_linked_list_size(list);
  CU_ASSERT_EQUAL(a, 3);
  ioopm_linked_list_destroy(list); // Destroy our linked structure.
}

void test_emptysizeoflist()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  int a = ioopm_linked_list_size(list);
  CU_ASSERT_EQUAL(a, 0);
  ioopm_linked_list_destroy(list); // Destroy our linked structure.
}

void test_isemptytrue()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  bool a = ioopm_linked_list_is_empty(list);
  CU_ASSERT_TRUE(a);
  ioopm_linked_list_destroy(list); // Destroy our linked structure.
}

void test_isemptyfalse()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 7);
  bool a = ioopm_linked_list_is_empty(list);
  CU_ASSERT_FALSE(a);
  ioopm_linked_list_destroy(list); // Destroy our linked structure.
}

void test_clear()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 7);
  ioopm_linked_list_prepend(list, 4);
  ioopm_linked_list_prepend(list, 10);
  ioopm_linked_list_clear(list);
  bool a = ioopm_linked_list_is_empty(list);
  CU_ASSERT_TRUE(a);
  ioopm_linked_list_destroy(list); // Destroy our linked structure.
}

void test_all()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 7);
  ioopm_linked_list_prepend(list, 7);
  ioopm_linked_list_prepend(list, 7);
  int v = 7;
  bool a = hasallvalues(list, v);
  CU_ASSERT_TRUE(a);
  ioopm_linked_list_destroy(list);
}

void test_anytrue()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 7);
  ioopm_linked_list_prepend(list, 5);
  ioopm_linked_list_prepend(list, 10);
  int v = 7;
  bool a = has_any_value(list, v);
  CU_ASSERT_TRUE(a);
  ioopm_linked_list_destroy(list);
}

void test_anyfalse()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(list, 6);
  ioopm_linked_list_prepend(list, 5);
  ioopm_linked_list_prepend(list, 10);
  int v = 7;
  bool a = has_any_value(list, v);
  CU_ASSERT_FALSE(a);
  ioopm_linked_list_destroy(list);
}
/*
void changeallvaluestoarg(int value, void *arg) // arg = "7"
{
 value = arg;
}

void test_applytoall()
{
 ioopm_list_t *list = ioopm_linked_list_create();
 ioopm_linked_list_prepend(list, 6);
 ioopm_linked_list_prepend(list, 5);
 ioopm_linked_list_prepend(list, 10);
 ioopm_linked_list_apply_to_all(list, changeallvaluestoarg, 7);
 bool a = hasallvalues(list, 7);
 CU_ASSERT_TRUE(a);
 ioopm_linked_list_destroy(list);
} */

int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
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
      //(CU_add_test(my_test_suite, "Test recursive count size of list", test_recsizeoflist) == NULL) ||
      (CU_add_test(my_test_suite, "Test create/destroy list", test_create_destroy) == NULL) ||
      //(CU_add_test(my_test_suite, "Test append", test_append) == NULL) || TODO!!!??????
      (CU_add_test(my_test_suite, "Test prepend", test_prepend) == NULL) ||
      (CU_add_test(my_test_suite, "Test insert", test_insertzero) == NULL) ||
      (CU_add_test(my_test_suite, "Test insert middle", test_insertmiddle) == NULL) ||
      (CU_add_test(my_test_suite, "Test remove", test_remove) == NULL) || // TODO??!!!????
      (CU_add_test(my_test_suite, "Test get", test_get) == NULL) ||
      (CU_add_test(my_test_suite, "Test get middle", test_getmiddle) == NULL) ||
      //
      (CU_add_test(my_test_suite, "Test contains in empty list", test_containsempty) == NULL) ||
      (CU_add_test(my_test_suite, "Test contains true in list", test_containstrue) == NULL) ||
      (CU_add_test(my_test_suite, "Test contains not true", test_containsnot) == NULL) ||
      (CU_add_test(my_test_suite, "Test to count size of list", test_sizeoflist) == NULL) ||
      (CU_add_test(my_test_suite, "Test to empty size of list", test_emptysizeoflist) == NULL) ||
      (CU_add_test(my_test_suite, "Test is empty true", test_isemptytrue) == NULL) ||
      (CU_add_test(my_test_suite, "Test is empty false", test_isemptyfalse) == NULL) ||
      (CU_add_test(my_test_suite, "Test clearing a linked list", test_clear) == NULL) ||
      (CU_add_test(my_test_suite, "Test all", test_all) == NULL) ||
      (CU_add_test(my_test_suite, "Test any true", test_anytrue) == NULL) ||
      (CU_add_test(my_test_suite, "Test any false", test_anyfalse) == NULL) ||
      //(CU_add_test(my_test_suite, "Test change all values to seven", test_applytoall) == NULL) ||
      //(CU_add_test(my_test_suite, "T...",) == NULL) ||
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