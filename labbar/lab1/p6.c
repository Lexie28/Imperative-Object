#include <stdio.h> 
#include <stdlib.h>
#include <math.h>   

int main(int argc, char *argv[]) 
{ 
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    while (a > 0 && b > 0)
    {
        if (a==b)
    {
        printf ("%d", a);
        return 0;
    }
    else if (a > b)
    {
        a = a-b;
    }                
    else
    {
        b = b - a;
    }
    }  

    printf("\n");
}