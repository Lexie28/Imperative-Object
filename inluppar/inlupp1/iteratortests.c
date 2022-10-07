#include <stdlib.h>
#include "linked_list.h"
#include "iterator.h"
#include <CUnit/Basic.h>
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

void itest_create_destroy()
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_equality_func_int);
    ioopm_list_iterator_t *it = ioopm_list_iterator(list);
    CU_ASSERT_PTR_NOT_NULL(it);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(it);
}

void itest_hasnexttrue()
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_equality_func_int);
    ioopm_linked_list_prepend(list, int_elem(7));
    ioopm_linked_list_prepend(list, int_elem(4));
    ioopm_linked_list_prepend(list, int_elem(10));
    ioopm_list_iterator_t *it = ioopm_list_iterator(list);
    bool a = ioopm_iterator_has_next(it);
    CU_ASSERT_TRUE(a);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(it);   
}

void itest_hasnextfalse()
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_equality_func_int);
    ioopm_linked_list_prepend(list, int_elem(7));
    ioopm_list_iterator_t *it = ioopm_list_iterator(list);
    bool a = ioopm_iterator_has_next(it);
    CU_ASSERT_FALSE(a);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(it);   
}

void itest_hasnextempty()
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_equality_func_int);
    ioopm_list_iterator_t *it = ioopm_list_iterator(list);
    bool a = ioopm_iterator_has_next(it);
    CU_ASSERT_FALSE(a);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(it);  
}

void itest_nextexists()
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_equality_func_int);

    ioopm_linked_list_prepend(list, int_elem(7));
    ioopm_linked_list_prepend(list, int_elem(4));
    ioopm_linked_list_prepend(list, int_elem(10));
    ioopm_list_iterator_t *it = ioopm_list_iterator(list);
    int a = ioopm_iterator_next(it).i;
    CU_ASSERT_EQUAL(a,4);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(it);  
}

void itest_iteratorreset()
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_equality_func_int);
    ioopm_linked_list_prepend(list, int_elem(7));
    ioopm_linked_list_prepend(list, int_elem(4));
    ioopm_linked_list_prepend(list, int_elem(10));
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    ioopm_iterator_next(iter);
    int a = ioopm_iterator_current(iter).i;
    CU_ASSERT_EQUAL(a,4);
    ioopm_iterator_reset(iter);
    int b = ioopm_iterator_current(iter).i;
    CU_ASSERT_EQUAL(b,10);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);
}

void itest_currentfirst()
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_equality_func_int);
    ioopm_linked_list_prepend(list, int_elem(7));
    ioopm_linked_list_prepend(list, int_elem(4));
    ioopm_linked_list_prepend(list, int_elem(10));
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    int a = ioopm_iterator_current(iter).i;
    CU_ASSERT_EQUAL(a,10);
    ioopm_iterator_next(iter);
    int b = ioopm_iterator_current(iter).i;
    CU_ASSERT_EQUAL(b,4);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(iter);  
}
void itest_next_empty()
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_equality_func_int);
    ioopm_list_iterator_t *it = ioopm_list_iterator(list);
    elem_t a = ioopm_iterator_next(it);
    CU_ASSERT_PTR_NULL(a.p);
    ioopm_linked_list_destroy(list);
    ioopm_iterator_destroy(it);   
}

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
        (CU_add_test(my_test_suite, "Test create/destroy iterator", itest_create_destroy) == NULL) ||
        (CU_add_test(my_test_suite, "Test has next true", itest_hasnexttrue) == NULL) ||
        (CU_add_test(my_test_suite, "Test has next false", itest_hasnextfalse) == NULL) ||
        (CU_add_test(my_test_suite, "Test has next empty", itest_hasnextempty) == NULL) ||
        (CU_add_test(my_test_suite, "Test next exists", itest_nextexists) == NULL) ||
        (CU_add_test(my_test_suite, "Test reset iterator", itest_iteratorreset) == NULL) ||
        (CU_add_test(my_test_suite, "Test current first", itest_currentfirst) == NULL) ||
        (CU_add_test(my_test_suite, "Test next if next is empty", itest_next_empty) == NULL) ||
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