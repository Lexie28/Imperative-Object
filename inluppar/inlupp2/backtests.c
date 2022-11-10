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

// ------------------------------------------------------------------------

void test_db_create()
{
    db_t *db = ioopm_db_create();
    CU_ASSERT_PTR_NOT_NULL(db);
    ioopm_db_destroy(db);
}

void test_add_merchandise()
{
    db_t *db = ioopm_db_create();
    ioopm_hash_table_t *ht = db->namemerch;
    char *name = "Lexie";
    char *description = "Cool kid";
    int price = 55;
    ioopm_add_merchandise(db, strdup(name), strdup(description), price);
    option_t a = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_TRUE(a.success);
    merch_t *merch = a.value.p;
    CU_ASSERT_TRUE(strcmp(name, merch->name) == 0);
    ioopm_db_destroy(db);
}

void test_remove_merchandise()
{
    db_t *db = ioopm_db_create();
    ioopm_hash_table_t *ht = db->namemerch;
    char *name = "Lexie";
    char *description = "Cool kid";
    int price = 55;
    ioopm_add_merchandise(db, strdup(name), strdup(description), price);
    option_t a = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_TRUE(a.success);
    ioopm_remove_merchandise(db, name, false);
    option_t b = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_FALSE(b.success);
    ioopm_db_destroy(db);
}

void test_edit_name_merchandise()
{
    db_t *db = ioopm_db_create();
    ioopm_hash_table_t *ht = db->namemerch;
    char *name = "Lexie";
    char *description = "Cool kid";
    int price = 55;

    ioopm_add_merchandise(db, strdup(name), strdup(description), price);
    option_t a = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_TRUE(a.success);
    char *newname = "Vincent";
    ioopm_edit_merchandise_name(db, name, strdup(newname));
    option_t b = ioopm_hash_table_lookup(ht, ptr_elem(newname));
    CU_ASSERT_TRUE(b.success);
    option_t c = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_FALSE(c.success);
    ioopm_db_destroy(db);
}

void test_edit_description_merchandise()
{
    db_t *db = ioopm_db_create();
    ioopm_hash_table_t *ht = db->namemerch;
    char *name = "Lexie";
    char *description = "Cool kid";
    int price = 55;

    ioopm_add_merchandise(db, strdup(name), strdup(description), price);
    option_t a = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_TRUE(a.success);
    merch_t *merch = a.value.p;
    CU_ASSERT_STRING_EQUAL(merch->description, description);
    char *newdescription = "Not cool";
    ioopm_edit_merchandise_description(db, name, strdup(newdescription)); // FREE CRASHES
    option_t b = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_TRUE(b.success);
    merch_t *merchupdated = b.value.p;
    CU_ASSERT_STRING_EQUAL(merchupdated->description, newdescription);
    ioopm_db_destroy(db);
}

void test_edit_price_merchandise()
{
    db_t *db = ioopm_db_create();
    ioopm_hash_table_t *ht = db->namemerch;
    char *name = "Lexie";
    char *description = "Cool kid";
    int price = 55;

    ioopm_add_merchandise(db, strdup(name), strdup(description), price);
    option_t a = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_TRUE(a.success);
    merch_t *merch = a.value.p;
    CU_ASSERT_EQUAL(merch->price, price);
    int newprice = 10;
    ioopm_edit_merchandise_price(db, name, newprice);
    option_t b = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_TRUE(b.success);
    merch_t *merchupdated = b.value.p;
    CU_ASSERT_EQUAL(merchupdated->price, newprice);
    ioopm_db_destroy(db);
}

void test_replenish_stock()
{
    db_t *db = ioopm_db_create();
    ioopm_hash_table_t *ht = db->namemerch;
    char *name = "Lexie";
    char *description = "Cool kid";
    int price = 55;

    ioopm_add_merchandise(db, strdup(name), strdup(description), price);
    option_t a = ioopm_hash_table_lookup(ht, ptr_elem(name));
    CU_ASSERT_TRUE(a.success);
    char *shelftoreplenish = "J44";
    int amount = 10;
    ioopm_replenish_stock(db, strdup(name), strdup(shelftoreplenish), amount);
    merch_t *merch = a.value.p;
    ioopm_list_t *locs = merch->locs;
    CU_ASSERT_TRUE(strcmp(name, (char *)(ioopm_linked_list_remove(locs, 0)).p));
    ioopm_db_destroy(db);
}

void test_add_remove_cart()
{
    db_t *db = ioopm_db_create();
    char *name = strdup("Lexie");
    char *description = strdup("Cool kid");
    int price = 55;

    ioopm_add_merchandise(db, name, description, price);
    ioopm_replenish_stock(db, name, strdup("A27"), 20);

    ioopm_cart_create(db); //Automagically asigns a cart 1 since not other carts exist.
    ioopm_add_to_cart(db, 1, name, 10);

    ioopm_hash_table_t *htc = db->carts;
    option_t lookup = ioopm_hash_table_lookup(htc, int_elem(1));
    ioopm_hash_table_t *cart = lookup.value.p;
    option_t lookupincart = ioopm_hash_table_lookup(cart, ptr_elem(name));
    CU_ASSERT_TRUE(lookupincart.success);

    ioopm_db_destroy(db);
}

void test_add_remove_multiple_cart()
{
    db_t *db = ioopm_db_create();
    char *name = strdup("Lexie");
    char *description = strdup("Cool kid");
    int   price = 55;

    char *name2 = strdup("Vincent");
    char *description2 = strdup("meh");
    int   price2 = 52;

    ioopm_add_merchandise(db, name, description, price); 
    ioopm_add_merchandise(db, name2, description2, price2); 

    ioopm_replenish_stock(db, name, strdup("A27"), 20);
    ioopm_replenish_stock(db, name2, strdup("B27"), 20);

    ioopm_cart_create(db); //Automagically asigns a cart 1 since not other carts exist.
    ioopm_add_to_cart(db, 1, name, 10);
    ioopm_add_to_cart(db, 1, name2, 10);

    ioopm_hash_table_t *htc = db->carts;
    option_t lookup = ioopm_hash_table_lookup(htc, int_elem(1));
    ioopm_hash_table_t *cart = lookup.value.p;
    option_t lookupincart = ioopm_hash_table_lookup(cart, ptr_elem(name));
    option_t lookupincart2 = ioopm_hash_table_lookup(cart, ptr_elem(name2));

    CU_ASSERT_TRUE(lookupincart.success);
    CU_ASSERT_TRUE(lookupincart2.success);

    ioopm_db_destroy(db);
}

void test_calculate_costs()
{
    db_t *db = ioopm_db_create();
    char *name = strdup("Lexie");
    char *description = strdup("Cool kid");
    int price = 55;

    char *name2 = strdup("Vincent");
    char *description2 = strdup("meh");
    int price2 = 52;

    ioopm_add_merchandise(db, name, description, price); 
    ioopm_add_merchandise(db, name2, description2, price2); 

    ioopm_replenish_stock(db, name, strdup("A27"), 20);
    ioopm_replenish_stock(db, name2, strdup("B27"), 20);

    ioopm_cart_create(db); //Automagically asigns a cart 1 since not other carts exist.
    ioopm_add_to_cart(db, 1, name, 10);
    ioopm_add_to_cart(db, 1, name2, 10);

    CU_ASSERT_TRUE(ioopm_calculate_cost(db, 1)==1070);
    ioopm_db_destroy(db);
}

void test_checkout()
{
    db_t *db = ioopm_db_create();
    char *name = strdup("Lexie");
    char *description = strdup("Cool kid");
    int price = 55;

    char *name2 = strdup("Vincent");
    char *description2 = strdup("meh");
    int price2 = 52;

    ioopm_add_merchandise(db, name, description, price); 
    ioopm_add_merchandise(db, name2, description2, price2); 

    ioopm_replenish_stock(db, name, strdup("A27"), 10);
    ioopm_replenish_stock(db, name2, strdup("B27"), 10);

    ioopm_cart_create(db); //Automagically asigns a cart 1 since not other carts exist.
    ioopm_add_to_cart(db, 1, name, 10);
    ioopm_add_to_cart(db, 1, name2, 10);

    ioopm_checkout(db, 1);

    CU_ASSERT_TRUE(ioopm_hash_table_size(db->namemerch)==0);
    CU_ASSERT_TRUE(ioopm_hash_table_size(db->carts)==0);


    ioopm_db_destroy(db);
}

// ------------------------------------------------------------------------

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
    // copy a line below and change the information test_merch_create
    if (
        (CU_add_test(my_test_suite, "Test creating a database", test_db_create) == NULL) ||
        (CU_add_test(my_test_suite, "Test adding merchandise to database", test_add_merchandise) == NULL) ||
        (CU_add_test(my_test_suite, "Test removing merchandise to database", test_remove_merchandise) == NULL) ||
        (CU_add_test(my_test_suite, "Test changing name of merchandise", test_edit_name_merchandise) == NULL) ||
        (CU_add_test(my_test_suite, "Test changing description", test_edit_description_merchandise) == NULL) ||
        (CU_add_test(my_test_suite, "Test changing price", test_edit_price_merchandise) == NULL) ||
        (CU_add_test(my_test_suite, "Test replenishing stock", test_replenish_stock) == NULL) ||
        (CU_add_test(my_test_suite, "Test adding and removing to a cart", test_add_remove_cart) == NULL) ||
        (CU_add_test(my_test_suite, "Test adding and removing multiple items to a cart", test_add_remove_multiple_cart) == NULL) ||
        (CU_add_test(my_test_suite, "Test calculating the cost of a cart", test_calculate_costs) == NULL) ||
        (CU_add_test(my_test_suite, "Test checking out carts works", test_checkout) == NULL) ||
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
