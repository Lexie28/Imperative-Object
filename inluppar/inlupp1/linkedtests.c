

#include "linked_list.h"
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

// TEST CASES BELOW

void test_create_destroy() // Testing to create and destroy a linked list.
{
    ioopm_list_t *linklist = ioopm_linked_list_create(elem_equality_func_int); // Create a linked list.
    CU_ASSERT_PTR_NOT_NULL(linklist);                    // Check that we now have a pointer to where the linked structure is.
    ioopm_linked_list_destroy(linklist);                 // Destroy our linked structure.
}

void test_append() // Testing to insert element to the end of linked list.
{
    ioopm_list_t *linklist = ioopm_linked_list_create(elem_equality_func_int);          // Create a linked list.
    ioopm_linked_list_append(linklist, int_elem(1));                        // Append a first element into the linked structure.
    ioopm_linked_list_append(linklist, int_elem(2));                        // Append a second element into the linked structure.
    ioopm_linked_list_append(linklist, int_elem(150));                      // Append a third (and last) element into the linked structure..
    size_t lSize = ioopm_linked_list_size(linklist);              // Get the size of the linked structure.
    int lastElement = ioopm_linked_list_get(linklist, lSize-1).i; // Get the last element in the linked structure.
    CU_ASSERT_EQUAL(lastElement, 150);                            // Check if the last element is equal to last i in loop (133).
    ioopm_linked_list_destroy(linklist);                          // Free up memory used by linked structure.
}

void test_prepend() // Testing to insert an element to the start of a linked list.
{
    ioopm_list_t *linklist = ioopm_linked_list_create(elem_equality_func_int);       // Create a linked list.
    ioopm_linked_list_prepend(linklist, int_elem(1));                    // Prepend 1 to beginning of linked structure.
    ioopm_linked_list_prepend(linklist, int_elem(2));                    // Prepend 2 to beginning of linked structure.
    ioopm_linked_list_prepend(linklist, int_elem(100));                  // Prepend 100 to beginning of linked structure.
    CU_ASSERT_TRUE(ioopm_linked_list_get(linklist, 0).i == 100); // Check if first element is equal to what we
    ioopm_linked_list_destroy(linklist);                       // Free up memory used by linked structure.
}

void test_insert() // Testing to insert an element into random places in linked structure.
{
    ioopm_list_t *linklist = ioopm_linked_list_create(elem_equality_func_int); // Create a linked list.
    for (int i = 0; i <= 10; i++)
    {
        ioopm_linked_list_append(linklist, int_elem(i)); // Create a medium sized linked list.
    }

    ioopm_linked_list_insert(linklist, 0, int_elem(25));                // Insert 25 to beginning of linked structure.
    CU_ASSERT_TRUE(ioopm_linked_list_get(linklist, 0).i == 25); // Check if first element is equal to what we inserted.
    size_t lSize = ioopm_linked_list_size(linklist);          // Get the size of the linked structure.

    ioopm_linked_list_insert(linklist, lSize - 1, int_elem(50));                // Insert 50 to end of linked structure
    CU_ASSERT_TRUE(ioopm_linked_list_get(linklist, lSize - 1).i == 50); // Check if last element is 50.

    ioopm_linked_list_insert(linklist, 5, int_elem(75));                // Insert 75 into middle of linked structure.
    CU_ASSERT_TRUE(ioopm_linked_list_get(linklist, 5).i == 75); // Check if middle element (spot 4)  is 75.
    ioopm_linked_list_destroy(linklist);                      // Free up memory used by linked structure.
}

void test_remove() // Testing to remove an element from random places in the linked structure.
{
    ioopm_list_t *linklist = ioopm_linked_list_create(elem_equality_func_int); // Create a linked list.
    for (int i = 0; i <= 10; i++)
    {
        ioopm_linked_list_append(linklist, int_elem(i)); // Create a medium sized linked list.
    }
    int removeVal = ioopm_linked_list_remove(linklist, 0).i;   // Remove the first element from linked structrue (0)
    CU_ASSERT_EQUAL(removeVal, 0);                           // Check if removed element is the right one..
    CU_ASSERT_TRUE(ioopm_linked_list_get(linklist, 0).i == 1); // Check if first element is now 1 (which was second before).

    size_t lSize = ioopm_linked_list_size(linklist);                 // Get the size of the linked structure.
    removeVal = ioopm_linked_list_remove(linklist, lSize - 1).i;       // Remove 10 from the linked structure.
    CU_ASSERT_EQUAL(removeVal, 10);                                  // Check if we removed correct value.
    lSize = ioopm_linked_list_size(linklist);                        // Get the updated list size.
    CU_ASSERT_TRUE(ioopm_linked_list_get(linklist, lSize - 1).i == 9); // Check if last element is now 9.

    removeVal = ioopm_linked_list_remove(linklist, 5).i;       // Remove a entry from middle of linked list.
    CU_ASSERT_EQUAL(removeVal, 6);                           // Check if we removed correct value (should be 6 now cause indexes are different.)
    CU_ASSERT_TRUE(ioopm_linked_list_get(linklist, 5).i == 7); // Check if new index 5 is the number after 6.
    ioopm_linked_list_destroy(linklist);                     // Free up memory used by linked structure.
}

void test_get() // Testing to get elements of different indexes in the linked structure.
{
    ioopm_list_t *linklist = ioopm_linked_list_create(elem_equality_func_int); // Create a linked list.
    for (int i = 0; i <= 10; i++)
    {
        ioopm_linked_list_append(linklist, int_elem(i)); // Create a medium sized linked list.
    }
    CU_ASSERT_TRUE(ioopm_linked_list_get(linklist, 0).i == 0); // Check if first element is -5 which it should be.

    size_t lSize = ioopm_linked_list_size(linklist);                  // Get the size of the linked structure.
    CU_ASSERT_TRUE(ioopm_linked_list_get(linklist, lSize - 1).i == 10); // Check if last element is 133 which it should be..

    CU_ASSERT_TRUE(ioopm_linked_list_get(linklist, 5).i == 5); // Check if index 5 (middle of structure) is equal to which it should be.
    ioopm_linked_list_destroy(linklist);                     // Free up memory used by linked structure.
}

void test_contain() // Test if an element is in a linked structure.
{
    ioopm_list_t *linklist = ioopm_linked_list_create(elem_equality_func_int);      // Create a linked list.
    CU_ASSERT_FALSE(ioopm_linked_list_contains(linklist, int_elem(8))); // Test if we can find an random number in an empty list.
    for (int i = 0; i <= 10; i++)
    {
        ioopm_linked_list_append(linklist, int_elem(i)); // Create a medium sized linked list.
    }
    CU_ASSERT_TRUE(ioopm_linked_list_contains(linklist, int_elem(7)));   // Test if we can find a value that is in the linked list.
    CU_ASSERT_FALSE(ioopm_linked_list_contains(linklist, int_elem(11))); // Test if we can find a number that is not in the list..
    ioopm_linked_list_destroy(linklist);                       // Destroy our linked structure.
}

void test_size_of_list() // Test the size of a linked structure.
{
    ioopm_list_t *linklist = ioopm_linked_list_create(elem_equality_func_int); // Create a linked list.
    size_t a = ioopm_linked_list_size(linklist);         // Get size of an empty linked list.
    CU_ASSERT_EQUAL(a, 0);                               // Check if the size of the empty list is correct.
    for (int i = 0; i <= 10; i++)
    {
        ioopm_linked_list_append(linklist, int_elem(i)); // Fill the empty list with entries.
    }
    a = ioopm_linked_list_size(linklist); // Get the new size of the linked list.
    CU_ASSERT_EQUAL(a, 11);               // See if the updated size value is now correct.
    ioopm_linked_list_destroy(linklist);  // Free memory used by linked list.
}

void test_is_empty() // Test if a linked structure is empty or not.
{
    ioopm_list_t *linklist = ioopm_linked_list_create(elem_equality_func_int); // Create a linked list.
    bool a = ioopm_linked_list_is_empty(linklist);
    CU_ASSERT_TRUE(a); // Check if the linked list is empty.
    for (int i = 0; i <= 10; i++)
    {
        ioopm_linked_list_append(linklist, int_elem(i)); // Fill the empty list with entries.
    }
    a = ioopm_linked_list_is_empty(linklist);
    CU_ASSERT_FALSE(a);                  // Check if the linked list is still empty.
    ioopm_linked_list_destroy(linklist); // Destroy our linked structure.
}

void test_clear() // Testing to clear a linked structure.
{
    ioopm_list_t *linklist = ioopm_linked_list_create(elem_equality_func_int); // Create a linked list.
    bool a = ioopm_linked_list_is_empty(linklist);
    CU_ASSERT_TRUE(a); // Check if the linked list is empty.
    for (int i = 0; i <= 10; i++)
    {
        ioopm_linked_list_append(linklist, int_elem(i)); // Fill the empty list with entries.
    }
    a = ioopm_linked_list_is_empty(linklist);
    CU_ASSERT_FALSE(a);                // Check if the linked list is still empty.
    ioopm_linked_list_clear(linklist); // Empty the linked list.
    a = ioopm_linked_list_is_empty(linklist);
    CU_ASSERT_TRUE(a);                   // Check if the list is now empty.
    ioopm_linked_list_destroy(linklist); // Destroy our linked structure.
}

void test_all() // Test that checks if something holds for all values of linked structure.
{
    ioopm_list_t *linklist = ioopm_linked_list_create(elem_equality_func_int); // Create a linked list.
    int value = 7;                                       // Set a value for our extra.
    bool a = hasallvalues(linklist, int_elem(value));              // Check if it holds for all on empty list.
    CU_ASSERT_FALSE(a);                                  // See if function returned correct value.
    for (int i = 0; i <= 10; i++)
    {
        ioopm_linked_list_append(linklist, int_elem(i)); // Fill the empty list with entries.
    }
    a = hasallvalues(linklist,int_elem(value));                    // Check if it holds for all when it should not.
    CU_ASSERT_FALSE(a);                                   // See if function returns correct value.
    ioopm_linked_list_clear(linklist);                    // Empty the linked list.
    CU_ASSERT_TRUE(ioopm_linked_list_is_empty(linklist)); // Check if linked list is now empty.
    for (int i = 0; i <= 10; i++)
    {
        ioopm_linked_list_append(linklist, int_elem(7)); // Fill the empty list with entries that should return true.
    }
    a = hasallvalues(linklist, int_elem(value)); // Check if it holdes for all entries.
    CU_ASSERT_TRUE(a);                 // See if function returns correct value.
    ioopm_linked_list_destroy(linklist);
    // Free memory used by linked list.
}

void test_any()
{
    ioopm_list_t *list = ioopm_linked_list_create(elem_equality_func_int);
    ioopm_linked_list_prepend(list, int_elem(7));
    ioopm_linked_list_prepend(list, int_elem(5));
    ioopm_linked_list_prepend(list, int_elem(10));
    int v = 7;
    bool a = has_any_value(list, int_elem(v));
    CU_ASSERT_TRUE(a);
    ioopm_linked_list_remove(list, 2); // Remove the 7
    a = has_any_value(list, int_elem(v));
    CU_ASSERT_FALSE(a);
    ioopm_linked_list_destroy(list);
}

void test_apply_to_all()
{
    ioopm_list_t *linklist = ioopm_linked_list_create(elem_equality_func_int); // Create a linked list.
    int x = 7;                                           // Set the value we want to change to.
    for (int i = 0; i <= 10; i++)
    {
        ioopm_linked_list_append(linklist, int_elem(i)); // Fill the empty list with entries.
    }
    bool a = hasallvalues(linklist, int_elem(7));
    CU_ASSERT_FALSE(a);                                                 // Check if all entries have value 7 (false).
    ioopm_linked_list_apply_to_all(linklist, changeallvaluestoarg, &x); // Change all entries values to 7.
    a = hasallvalues(linklist, int_elem(7));
    CU_ASSERT_TRUE(a);                   // Check if all entries have value 7 now (true)
    ioopm_linked_list_destroy(linklist); // Free memory used by linked list.
}
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
        (CU_add_test(my_test_suite, "Test that creates and destroys a linked structure.", test_create_destroy) == NULL) ||
        (CU_add_test(my_test_suite, "Test that appends an entry to end of linked structure..", test_append) == NULL) ||
        (CU_add_test(my_test_suite, "Test that prepends an entry to beginning of linked structure.", test_prepend) == NULL) ||
        (CU_add_test(my_test_suite, "Test that inserts entries into linked structure.", test_insert) == NULL) ||
        (CU_add_test(my_test_suite, "Test that removes entries from linked structure.", test_remove) == NULL) ||
        (CU_add_test(my_test_suite, "Test that gets entries from a linked structure", test_get) == NULL) ||
        (CU_add_test(my_test_suite, "Test that checks if entries are in a linked structure", test_contain) == NULL) ||
        (CU_add_test(my_test_suite, "Test that checks size of linked structure.", test_size_of_list) == NULL) ||
        (CU_add_test(my_test_suite, "Test that checks if a linked structure is empty.", test_is_empty) == NULL) ||
        (CU_add_test(my_test_suite, "Test that clears a linked structure.", test_clear) == NULL) ||
        (CU_add_test(my_test_suite, "Test that checks if something holds for all entries in linked structure.", test_all) == NULL) ||
        (CU_add_test(my_test_suite, "Test that checks if something holds for atleast one entry in linked structure.", test_any) == NULL) ||
        (CU_add_test(my_test_suite, "Test that applies a change to all entries in the linked structure.", test_apply_to_all) == NULL) ||
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
