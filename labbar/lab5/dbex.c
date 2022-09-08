#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"



struct item
{
    char *namn;
    char *beskrivning;
    int pris;
    char *hylla;
};

typedef struct item item_t;

void print_item(item_t *p)
{
    printf("Name: %s \n", p->namn);
    printf("Desc: %s \n", p->beskrivning);
    printf("Price: %d.%d SEK\n", p->pris/100, p->pris % 100);
    printf("Shelf: %s \n", p->hylla);

}

item_t make_item(char *n, char *b, int p, char *h)
{
    item_t item = {.namn = n, .beskrivning = b, .pris = p, .hylla = h};
    return item;
    /*item_t *item = calloc(1, sizeof(item_t));
    item->namn = n;
    item->beskrivning = b;
    item->pris = p;
    item->hylla = h;
    return item; */

}


bool is_shelf(char *shelf)
{
    if (strlen(shelf) >= 2 && isalpha(shelf[0]))
    {
        for (int i = 1; i < strlen(shelf); i++)
        {
            if (isdigit(shelf[i]) == false)
            {
                return false;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

char* ask_question_shelf(char *question)
{
    return ask_question(question, is_shelf, (convert_func) strdup).string_value;
}

item_t input_item()
{
    char *a = ask_question_string("The item name:");
    char *b = ask_question_string("The item description:");
    int c = ask_question_int("The price:");
    char *d = ask_question_shelf("The shelf:");
    item_t i1 = make_item(a,b,c,d);
    return i1;
    //print_item(&i1);
}

char *magick(char **arr1, char **arr2, char **arr3, int n) 
{
  char buf[255];
  char *ord1 = arr1[rand() % n];
  char *ord2 = arr2[rand() % n];
  char *ord3 = arr3[rand() % n];

  int m = 0;

  for (int j = 0; j < strlen(ord1); j++)
  {
    buf[m] = ord1[j];
    m++;
  }

  buf[m] = '-';
  m++;

  for (int j = 0; j < strlen(ord2); j++)
  {
    buf[m] = ord2[j];
    m++;
  }

  buf[m] = ' ';
  m++;

  for (int j = 0; j < strlen(ord3); j++)
  {
    buf[m] = ord3[j];
    m++;
  }

  buf[m] = '\0';
  
  return strdup(buf);

}

void list_db(item_t *items, int no_items) //number of items = "no items"
{
    for (int i=0; i < no_items; i++)
    {
        item_t item = items[i];
        printf("%d. %s \n",(i+1), item.namn); //. för -> funkar bara för pekare
    }

}

void edit_db(item_t *items, int itemsize)
{
    int i = ask_question_int("Which item would you like to edit:") -1;
    while (i >= itemsize || i < 0) {
        i = ask_question_int("Which item would you like to edit:") -1;
    }
    item_t item = items[i];
    print_item(&item);

    item_t newitem = input_item();
    items[i] = newitem;

}


char *print_menu()
{
    return(
        "[L]ägg till en vara \n"
        "[T]a bort en vara \n"
        "[R]edigera en vara \n"
        "Ån[g]ra senaste ändringen \n"
        "Lista [h]ela varukatalogen \n"
        "[A]vsluta\n"
    );
}

bool is_menu_answer(char *menuans)
{

    if (strlen(menuans) > 1) 
    {
        return false;
    }
    else 
    {
        char newans = toupper(menuans[0]);
        char *correctanswers = "LTRGHA";

        for (int i = 0; i < strlen(correctanswers); i++)
        {
            if (correctanswers[i] == newans) return true;
        }
    }
    return false;
}


char ask_question_menu(char *question)
{
    return ask_question(question, is_menu_answer, (convert_func) strdup).string_value[0];
}



int add_item_to_db(item_t *db, int db_siz)
{
    item_t newitem = input_item();
    db[db_siz] = newitem;
    db_siz ++;
    return db_siz;

}

int remove_item_from_db(item_t *db, int db_siz)
{
    list_db(db, db_siz);

    int i = ask_question_int("Which item would you like to remove:") -1;
    while (i >= db_siz || i < 0) {
        i = ask_question_int("Which item would you like to remove:") -1;
    }

    for (int m = i; m < db_siz - 1; m++)
    {
        db[m] = db[m+1];
    }
    db_siz--;
    
    return db_siz; //RETURN db size
}




void event_loop(item_t *db, int db_siz)
{
    char ans = toupper(ask_question_menu(print_menu()));
    while (ans != 'A')
    {
        if (ans == 'L') 
        {
            db_siz = add_item_to_db(db, db_siz);
        }
        if (ans == 'T') 
        {
            db_siz = remove_item_from_db(db, db_siz);
        }
        if (ans == 'R') edit_db(db, db_siz); 
        if (ans == 'G') printf("Not yet implemented!\n");
        if (ans == 'H') list_db(db, db_siz);
        ans = toupper(ask_question_menu(print_menu()));
    }
}




int main(int argc, char *argv[])
{
    char *array1[] = { "Laser",        "Polka",    "Extra" };
    char *array2[] = { "förnicklad",   "smakande", "ordinär" };
    char *array3[] = { "skruvdragare", "kola", "glass" };

  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0; // Antalet varor i arrayen just nu

    int items = atoi(argv[1]); // Antalet varor som skall skapas

    for (int i = db_siz; i < items; ++i)
      {
        char *name = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        char *desc = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, shelf);

        db[db_siz] = item;
        ++db_siz;
      }

     // Skriv ut innehållet
     list_db(db, db_siz);

     event_loop(db, db_siz);

  }
  return 0;
}
