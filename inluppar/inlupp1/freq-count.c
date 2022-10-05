#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "iterator.h"
#include "common.h"
#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

static int cmpstringp(const void *p1, const void *p2)
{
    return strcmp(*(char *const *)p1, *(char *const *)p2);
}

void sort_keys(char *keys[], size_t no_keys)
{
    qsort(keys, no_keys, sizeof(char *), cmpstringp);
}

void process_word(char *word, ioopm_hash_table_t *ht)
{
    option_t a = ioopm_hash_table_lookup(ht, ptr_elem(word));
    if (a.success == true)
    {
        //printf("WORD: %s FREQ: %d \n", word, a.value.i+1);
        ioopm_hash_table_insert(ht, ptr_elem(word), (elem_t) {.i = a.value.i + 1});
    }
    else
    {
        //printf("WORD: %s FREQ: %d \n", word, 1);
        ioopm_hash_table_insert(ht, ptr_elem(strdup(word)), (elem_t) {.i = 1});
    }
}

void process_file(char *filename, ioopm_hash_table_t *ht)
{
    FILE *f = fopen(filename, "r");
    while (true)
    {
        char *buf = NULL;
        size_t len = 0;
        getline(&buf, &len, f);
        if (feof(f))
        {
            free(buf);
            break;
        }
        for (char *word = strtok(buf, Delimiters);
             word && *word;
             word = strtok(NULL, Delimiters))
        {
            /*if (strcmp(word, "vel")== 1)
            {
            printf("%d", strcmp(word, "vel")== 1);
            } */
            process_word(word, ht);
        }
        free(buf);
    }
    fclose(f);
}

int string_sum_hash(elem_t e) // tar en sträng och ger den ett hash-värde. värde som sen bestämmer vilken bucket vi lägger in varje ord i
{
    char *str = e.p;
    int result = 0;
    // printf("%s, ", str);
    do
    {
        if (*str < 0)
        {
            result += -*str;
        }
        else
        {
        result += *str;
        }
    } while (*++str != '\0');
    // printf("%d \n", result);
    return result;
}

bool string_eq(elem_t e1, elem_t e2)
{
    //printf("%d", strcmp(e1.p, "vel"));
    return (strcmp((char *)e1.p, (char *)e2.p) == 0);
}

int main(int argc, char *argv[])
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_eq, string_sum_hash);
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            process_file(argv[i], ht);
        }
        //print_ht(ht);
        //printf("HT SIZE: %ld \n", ioopm_hash_table_size(ht));
        // FIXME: If the keys are returned as a list, transfer them into
        // an array to use `sort_keys` (perhaps using an iterator?)
        ioopm_list_t *keys_list = ioopm_hash_table_keys(ht);
        int size = ioopm_linked_list_size(keys_list);
        ioopm_list_iterator_t *iter = ioopm_list_iterator(keys_list);
        // char **keys_arr = calloc(size, sizeof(char));
        char *keys_arr[size];
        for (int i = 0; i < size; i++)
        {
            keys_arr[i] = ioopm_iterator_current(iter).p;
            ioopm_iterator_next(iter);
        }
        ioopm_iterator_destroy(iter);
        sort_keys(keys_arr, size);
        //int totalSum = 0;
        for (int i = 0; i < size; ++i)
        {
            // FIXME: Update to match your own interface, error handling, etc.
            option_t freqopt = ioopm_hash_table_lookup(ht, ptr_elem(keys_arr[i]));
            int freq = freqopt.value.i;
            printf("%s: %d\n", keys_arr[i], freq);
            //totalSum = totalSum + freq;
        }
        //printf("Total number of words: %d\n", totalSum);
        //print_ht(ht);
        for (int a = 0; a < size; a++)
        {
            free(keys_arr[a]);
        }
        ioopm_linked_list_destroy(keys_list); 
    }
    else
    {
        puts("Usage: freq-count file1 ... filen");
    }
    // FIXME: Leaks memory! Use valgrind to find out where that memory is
    // being allocated, and then insert code here to free it.
    ioopm_hash_table_destroy(ht);
}