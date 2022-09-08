#include <stdio.h> 
#include <stdlib.h>   

int main(int argc, char *argv[]) 
{   
    if (argc < 2 || argc > 3)
{
  printf("Error! Ge 2 argument");
}
else
{
    int n = atoi(argv[1]); 
    int m = atoi(argv[2]); 
    int count = 0; 
    for (int i = m; i <= n*m; i=i+m) 
    {      for (int m=0; m < i; m++)     
            {         printf("*");         
                      count++;     
            }     printf("\n");   
    } 
    printf("Total %d", count); 
    printf("\n"); 
    return 0; 
}  
} 

