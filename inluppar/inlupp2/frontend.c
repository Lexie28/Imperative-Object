#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include "frontend.h"
#include "backend.h"
#include "iterator.h"


//namet på merch, location etc måste freeas. applytoall-free

void ui_add_merchandise(db_t *db) // typ alla ui/frontend-funktioner ska se ut så här
{
    char *name = ask_question_string("The item name:");
    char *description = ask_question_string("The item description:");
    int price = ask_question_int("The price:");
    if (ioopm_add_merchandise(db, name, description, price) == true)
    {
        printf("Item successfully added! \n");
    }
    else
    {
        printf("Item with that name already exists! \n");
    }
    //free(name);
    //free(description);
}

void ui_list_merchandise(db_t *db) //TODO?? SEGFAULT MED OJÄMNA TAL
{
    bool is_empty = false;
    listtype_t *merch = ioopm_get_merchandise(db, &is_empty); //option-type med char ** (array av strängar) och en size
    if (!is_empty) {
        int j = 0;
        int i = 0;
        while (merch->arr[j] != NULL)
        {
            for (i = 0; i < 20 && j < merch->size; i++) // antingen mindre än 20, eller om listan är kortare, tills vi läser av något som är NULL aka slutet av arrayen
            {
                //printf("i = %d, j = %d, i+j = %d \n", i, j, i+j); 
                if (merch->size == i+j)
                {
                    //printf("i+j = %d + %d | size = %d", i,j,merch->size); 
                    break;
                }
                
                if (merch->arr[j+i] != NULL)
                {
                char *name = merch->arr[j + i];
                printf("%d. %s \n", j + i + 1, name);
                }
                else
                {
                    //printf("j2 = %d", j);
                    break;
                }
            }
            //printf("Test 2 | i = %d, j = %d, i+j = %d \n", i, j, i+j);

            j += i;
            //printf("j = %d", j);
            if (i < 20)
            {
                break;
            }
            char *answer = ask_question_string("Would you like to see more merchandise? y/n");
            char ans = toupper(answer[0]);
            if (ans != 'Y') // (strcmp(answer, "y") != 0 || strcmp(answer, "Y") != 0)
            {
                //printf("jag är här!");
                free(answer);
                break;
            }
            //printf("Going to access march->array value %d \n", j);
            free(answer);
            // printf("BOOL: %d", merch->arr[j] != NULL); // 0 betyder att det är false
        }
    }
    else
    {
        printf("No merch in store.\n");
    }
    free(merch->arr);
    free(merch);
}

void ui_remove_merchandise(db_t *db)
{
    ui_list_merchandise(db);
    char *name = ask_question_string("The item name:");
    char *sure = ask_question_string("Are you sure you want to remove this merchandise? y/n");
    if (strcmp(sure, "y") == 0 || strcmp(sure, "Y") == 0)
    {
        if (ioopm_remove_merchandise(db, name, false) == true)
        {
            printf("Item successfully removed! \n");
        }
        else
        {
            printf("Item could not be removed! \n");
        }
    }
    else
    {
        return;
    }
    free(name);
    free(sure);
}

void ui_edit_merchandise(db_t *db)
{
    ui_list_merchandise(db);
    char *name = ask_question_string("Which item would you like to edit?");
    char choice = toupper(ask_question_char("Would you like to edit this merchandise's [N]ame, [D]escription or [P]rice? \n"));
    if (choice == 'N')
    {
        char *newname = ask_question_string("Edit name: \n"); //allocd
        if (ioopm_edit_merchandise_name(db, name, newname) == true)
        {
            printf("Item successfully edited! \n");
        }
        else
        {
            free(newname);
            printf("Item could not be edited! \n");
        }
    }
    else if (choice == 'D')
    {
        char *newdescription = ask_question_string("Edit description: \n");
        if (ioopm_edit_merchandise_description(db, name, newdescription) == true)
        {
            printf("Item successfully edited! \n");
        }
        else
        {
            free(newdescription);
            printf("Item could not be edited! \n");
        }
    }
    else if (choice == 'P')
    {
        int newprice = ask_question_int("Edit price: \n");
        if (ioopm_edit_merchandise_price(db, name, newprice) == true)
        {
            printf("Item successfully edited! \n");
        }
        else
        {
            printf("Item could not be edited! \n");
        }
    }
    else
    {
        printf("You did not pick a valid option to edit the merchandise! \n"); 
        free(name);
        return;
    }
    free(name);
    //free(choice);

}

void ui_show_stock(db_t *db)
{
    ui_list_merchandise(db);
    char *name = ask_question_string("For which item would you like to see the stock?");
    //ioopm_list_t *shelf_list = show_stock(db, name);
    //merch_t *merch = get_merch_info(db, name);
    ioopm_list_t *shelf_list = ioopm_show_stock(db, name);
    if (shelf_list == NULL)
    {
        printf("Invalid item");
        return;
    }
    ioopm_list_iterator_t *iter = ioopm_list_iterator(shelf_list);
    size_t size = ioopm_linked_list_size(shelf_list);
    for (int i = 0; i < size; i++)
    //while (ioopm_iterator_has_next(iter)) //TODO!!! NU MISSAR DEN SISTA GREJEN // GÖR DEN VERKLIGEN DET? V (2022-11-02) //
    {
        shelf_t *shelf = ioopm_iterator_current(iter).p;
        printf("%s:%d, \n", shelf->shelf, shelf->quantity);
        ioopm_iterator_next(iter);
    }
    free(name);
    ioopm_iterator_destroy(iter);
}

void ui_replenish_stock(db_t *db)
{
    ui_list_merchandise(db);
    char *name = ask_question_string("Which item would you like to replenish?");
    ioopm_show_stock(db, name);
    char *shelftoreplenish = ask_question_string("Which stock would you like to replenish, if new, write new shelf number");
    int amount = ask_question_int("How much would you like to replenish it by?");
    if (ioopm_replenish_stock(db, name, shelftoreplenish, amount) == true)
    {
        printf("Stock successfully replenished!\n");
    }
    else
    {  
        free(shelftoreplenish);   
        free(name);
        printf("Stock could not be replenished!\n");
    }
}


void ui_cart_create(db_t *db)
{
    int cartnmr = ioopm_cart_create(db);
    printf("You have created a new cart, number %d \n", cartnmr);
}

void ui_cart_remove(db_t *db)
{
    int carttoremove = ask_question_int("Which cart would you like to remove?");
    if (ioopm_cart_remove(db, carttoremove) == true)
    {
        printf("Cart nr.%d was successfully removed! \n", carttoremove);
    }
    else
    {
        printf("Cart nr.%d could not be removed \n", carttoremove);
    }
}

void ui_add_to_cart(db_t *db)
{
    int carttoaddto = ask_question_int("Which cart nr. would you like to add merchandise to? \n");
    //list all merchandise i databasen
    ui_list_merchandise(db);
    char *nameofmerch = ask_question_string("Which merchandise would you like to add to this cart? \n");
    int quantity = ask_question_int("How much (/quantity) of this merchandise would you like to add?");
    if (ioopm_add_to_cart(db, carttoaddto, nameofmerch, quantity) == true)
    {
        printf("Item was successfully added to cart! \n");
    }
    else
    {
        free(nameofmerch);
        printf("Item could not be added to cart \n");
    }
    //
}


void ui_remove_from_cart(db_t *db)
{
    int cartnmr = ask_question_int("Which cart nr. would you like to remove from? \n");
    //list allt i denna cart
    char *nameofmerch = ask_question_string("Which merchandise would you like to remove from this cart? \n");
    int quantity = ask_question_int("How much (/quantity) of this merchandise would you like to remove? \n");

    if (ioopm_remove_from_cart(db, cartnmr, nameofmerch, quantity) == true)
    {
        printf("Merchandise successfully removed from this cart!");
    }
    else
    {
        printf("Removal could not be done");
    }
    free(nameofmerch);
}

void ui_calculate_cost(db_t *db)
{
    int cartnmr = ask_question_int("For which cart number would you like to calculate the cost? \n");
    int cartcost = ioopm_calculate_cost(db, cartnmr);
    printf("The cost of cart %d is: %d \n", cartnmr, cartcost);
}

void ui_checkout(db_t *db)
{
    int cartnmr = ask_question_int("Which cart would you like to check out?");
    if (ioopm_checkout(db, cartnmr) == true)
    {
        printf("Your cart has been checked out! \n");
    }
    else
    {
        printf("Your cart could not be checked out! \n");
    }
}

void ui_show_merch(db_t *db) 
{
    ui_list_merchandise(db);
    char *name = ask_question_string("The item name:");
    merch_t *merch = ioopm_get_merch_info(db, name);
    if (merch == NULL) {
        printf("No merch with that name found\n");
        return;
    }
    printf(
        "Name: %s\n" 
        "Description: %s\n"
        "Price: %d\n"
    , merch->name, merch->description, merch->price);
    ioopm_list_t *locs = merch->locs;
    size_t size = ioopm_linked_list_size(locs);
    if (size > 0) {
        printf("Locations: ");
        ioopm_list_iterator_t *iter = ioopm_list_iterator(locs);
        for (int i = 0; i < size; i++) {
            shelf_t *shelf = ioopm_iterator_current(iter).p;
            printf("%s:%d, ", shelf->shelf, shelf->quantity);
            ioopm_iterator_next(iter);
        }
        printf("\n");
        ioopm_iterator_destroy(iter);
    } else {
        printf("No stock for selected merch\n");
    }
    free(name);
}

void print_cart(elem_t key, elem_t *value, void *x)
{
    printf("Merch:%s, Quantity:%d \n", (char *) key.p, (*value).i);
}

void ui_show_cart(db_t *db)
{
    ioopm_hash_table_t *carts = db->carts;
    int cartnmr = ask_question_int("Which cart would you like to view?");
    option_t lookup = ioopm_hash_table_lookup(carts, int_elem(cartnmr));
    if (lookup.success == false)
    {
        printf("This cart does not exist");
        return;
    }
    ioopm_hash_table_t *cart = lookup.value.p;
    ioopm_hash_table_apply_to_all(cart, print_cart, NULL);
}

char *print_menu()
{
    return(
        "[A]dd merchandise \n"
        "[L]ist merchandise \n"
        "[R]emove merchandise \n"
        "[E]dit merchandise \n"
        "[S]how merchandise features \n"
        "[F]ill / replenish merchandise stock\n"
        "[I]nspect stock \n"
        "[C]reate cart \n"
        "Re[M]ove cart \n"
        "A[D]d to cart \n"
        "Rem[O]ve from cart \n"
        "Calc[U]late cost of cart \n"
        "Dis[P]lay cart \n"
        "C[H]eckout \n"
        "[Q]uit \n"
    );
}

int main()
{
    db_t *db = ioopm_db_create();
    
    /*add_merchandise(db, "hej", "cool", 1);
    add_merchandise(db, "he", "coo", 2);
    add_merchandise(db, "h", "co", 3);
    add_merchandise(db, "nej", "cool", 1);
    add_merchandise(db, "ne", "coo", 2);
    add_merchandise(db, "n", "co", 3);
    add_merchandise(db, "aej", "cool", 1);
    add_merchandise(db, "ae", "coo", 2);
    add_merchandise(db, "a", "co", 3);
    add_merchandise(db, "bej", "cool", 1);
    add_merchandise(db, "be", "coo", 2);
    add_merchandise(db, "b", "co", 3);
    add_merchandise(db, "cej", "cool", 1);
    add_merchandise(db, "ce", "coo", 2);
    add_merchandise(db, "c", "co", 3);
    add_merchandise(db, "dej", "cool", 1);
    add_merchandise(db, "de", "coo", 2);
    add_merchandise(db, "d", "co", 3);
    add_merchandise(db, "eej", "cool", 1);
    add_merchandise(db, "ee", "coo", 2);
    add_merchandise(db, "e", "co", 3);
    add_merchandise(db, "fej", "cool", 1);
    add_merchandise(db, "fe", "coo", 2);
    add_merchandise(db, "f", "co", 3);
    add_merchandise(db, "gej", "cool", 1);
    add_merchandise(db, "ge", "coo", 2);
    add_merchandise(db, "g", "co", 3);
    add_merchandise(db, "tej", "cool", 1);
    add_merchandise(db, "te", "coo", 2);
    add_merchandise(db, "t", "co", 3);*/

    //printf("ADDINGF");
    //ui_list_merchandise(db);

    char ans = toupper(ask_question_char(print_menu()));
    //char ans = toupper(to_free[0]); //remember to change askquestionmenu when you add options

    while (ans != 'Q')
    {
        if (ans == 'A')
        {
            ui_add_merchandise(db);
        }
        if (ans == 'L')
        {
            ui_list_merchandise(db);
        }
        if (ans == 'R')
        {
            ui_remove_merchandise(db);
        }
        if (ans == 'E')
        {
            ui_edit_merchandise(db);
        }
        if (ans == 'S')
        {
            ui_show_merch(db);
        }
        if (ans == 'F')
        {
            ui_replenish_stock(db);            
        }
        if (ans == 'I')
        {
            ui_show_stock(db);
        }
        if (ans == 'C')
        {
            ui_cart_create(db);
        }
        if (ans == 'M')
        {
            ui_cart_remove(db);
        }
        if (ans == 'D')
        {
            ui_add_to_cart(db);
        }
        if (ans == 'O')
        {
            ui_remove_from_cart(db);
        }
        if (ans == 'U')
        {
            ui_calculate_cost(db);
        }
        if (ans == 'H')
        {
            ui_checkout(db);
        }
        if (ans == 'P')
        {
            ui_show_cart(db);
        }
        ans = toupper(ask_question_char(print_menu()));
        /*free(to_free);
        to_free = ask_question_menu(print_menu());
        ans = toupper(to_free[0]);*/
    }
    //free(to_free);
    ioopm_db_destroy(db);
    return 0;
}
