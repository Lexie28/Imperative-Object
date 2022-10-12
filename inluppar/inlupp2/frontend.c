#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"
#include "frontend.h"
#include "backend.h"

//namet på merch, location etc måste freeas. applytoall-free

void ui_add_merchandise(db_t *db) // typ alla ui/frontend-funktioner ska se ut så här
{
    char *name = ask_question_string("The item name:");
    char *description = ask_question_string("The item description:");
    int price = ask_question_int("The price:");
    if (add_merchandise(db, name, description, price) == true)
    {
        printf("Item successfully added! \n");
    }
    else
    {
        printf("Item with that name already exists! \n");
    }
}

void ui_list_merchandise(db_t *db) //TODO?? FUNKAR INTE ATT SE MER ÄN 20!!
{
    listtype_t *merch = get_merchandise(db); //option-type med char ** (array av strängar) och en size
    int j = 0;
    int i = 0;
    while (merch->arr[j] != NULL)
    {
        for (i = 0; i < 20 && j < merch->size; i++) // antingen mindre än 20, eller om listan är kortare, tills vi läser av något som är NULL aka slutet av arrayen
        {
            if (merch->arr[j+i] != NULL)
            {
            char *name = merch->arr[j + i];
            printf("%d. %s \n", j + i + 1, name);
            }
            else
            {
                break;
            }
        }
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
            break;
        }

        // printf("BOOL: %d", merch->arr[j] != NULL); // 0 betyder att det är false
    }
    free(merch->arr);
}

void ui_remove_merchandise(db_t *db)
{
    ui_list_merchandise(db);
    char *name = ask_question_string("The item name:");
    if (remove_merchandise(db, name) == true)
    {
        printf("Item successfully removed! \n");
    }
    else
    {
        printf("Item could not be removed! \n");
    }
}

void ui_edit_merchanidse(db_t *db)
{
    ui_list_merchandise(db);
    char *name = ask_question_string("Which item would you like to edit?");
    if (edit_merchandise(db, name) == true)
    {
        printf("Item successfully edited! \n");
    }
    else
    {
        printf("Item would not be edited! \n");
    }
}


void ui_show_stock(db_t *db)
{
    ui_list_merchandise(db);
    char *name = ask_question_string("For which item would you like to see the stock?");
    return show_stock(db, name);   
}

void ui_replenish_stock(db_t *db)
{
    ui_list_merchandise(db);
    char *name = ask_question_string("Which item would you like to replenish?");
    if (replenish_stock(db, name) == true)
    {
        printf("Stock successfully replenished!");
    }
    else
    {
        printf("Stock could not be replenished!");
    }
}


char *print_menu()
{
    return(
        "[A]dd merchandise \n"
        "[L]ist merchandise \n"
        "[R]emove merchandise \n"
        "[E]dit merchandise \n"
    );
}

int main()
{
    db_t *db = db_create();
    
    add_merchandise(db, "hej", "cool", 1);
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
    add_merchandise(db, "t", "co", 3);

    char ans = toupper(ask_question_menu(print_menu())); //remember to change askquestionmenu when you add options

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
            ui_edit_merchanidse(db);
        }
        ans = toupper(ask_question_menu(print_menu()));
    }
    return 0;
}