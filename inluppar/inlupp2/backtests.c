#include <stdlib.h>
#include "linked_list.h"
#include "backend.h"
#include "frontend.h"
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

void test_add_merchandise()
{
    db_t *db = db_create();
    ioopm_hash_table_t *ht = db->namemerch;
    char *name = "Lexie";
    char *description = "Cool kid";
    int price = 55;
    add_merchandise(db, strdup(name), strdup(description), price);
    option_t a = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_TRUE(a.success);
    merch_t *merch = a.value.p;
    CU_ASSERT_TRUE(strcmp(name, merch->name) == 0);
    db_destroy(db);
}


void test_remove_merchandise()
{
    db_t *db = db_create();
    ioopm_hash_table_t *ht = db->namemerch;
    char *name = "Lexie";
    char *description = "Cool kid";
    int price = 55;
    add_merchandise(db, strdup(name), strdup(description), price);
    option_t a = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_TRUE(a.success);
    remove_merchandise(db, name);
    option_t b = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_FALSE(b.success);
    db_destroy(db);
}

void test_edit_name_merchandise()
{
    db_t *db = db_create();
    ioopm_hash_table_t *ht = db->namemerch;
    char *name = "Lexie";
    char *description = "Cool kid";
    int price = 55;
    add_merchandise(db, strdup(name), strdup(description), price);
    option_t a = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_TRUE(a.success);
    char *newname = "Vincent";
    edit_merchandise_name(db, name, strdup(newname));
    option_t b = ioopm_hash_table_lookup(ht, ptr_elem(newname));
    CU_ASSERT_TRUE(b.success);
    option_t c = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_FALSE(c.success);
    db_destroy(db);
}

/*
void test_edit_description_merchandise()
{
    db_t *db = db_create();
    ioopm_hash_table_t *ht = db->namemerch;
    char *name = "Lexie";
    char *description = "Cool kid";
    int price = 55;
    add_merchandise(db, name, description, price);
    option_t a = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_TRUE(a.success);
    char *newdescription = "Not cool";
    edit_merchandise_description(db, name, newdescription);

    //TODO?? HOW TO CHECK IF DESCRIPTION IS CHANGED
    db_destroy(db);
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
        (CU_add_test(my_test_suite, "Test adding merchandise to database", test_add_merchandise) == NULL) ||
        (CU_add_test(my_test_suite, "Test removing merchandise to database", test_remove_merchandise) == NULL) ||
        (CU_add_test(my_test_suite, "Test removing merchandise to database", test_edit_name_merchandise) == NULL) ||
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