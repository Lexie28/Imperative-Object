#include <stdio.h> 
#include <stdlib.h>
#include <math.h>   

int main(int argc, char *argv[]) 
{   
    if (argc < 1 || argc > 2)
{
  printf("Error! Ge 1 argument");
}
else
{
    int n = atoi(argv[1]); 
    int limit = floor(sqrt(n)) + 1;
    for (int i = 2; i <= n; i++) 
    {      for (int j = 2; j <= n; j++)     
            {      
              if ( i*j == n)
              {
                printf("%d is not a prime number\n", n);
                return 0;
              }           
            }  
    }
    printf("%d is a prime number\n", n); 
    return 0; 
    }  
}

