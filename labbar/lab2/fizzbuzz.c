#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <ctype.h>

void print_number(int j)
{
    if (j%3 == 0 && j%5 == 0)
    {
        printf("Fizz Buzz");
    }
    
    else if (j%3 == 0) 
    {
        printf("Fizz");
    }

    else if (j%5 == 0)
    {

        printf("Buzz");
    }

    else
    {
        printf("%d", j);
    }
}



int main(int argc, char *argv[])
{
    int T = atoi(argv[1]);

    for (int i=1; i<=T; i++)
    {
        print_number(i);
        if (i != T) printf(", ");
        
    }

}

