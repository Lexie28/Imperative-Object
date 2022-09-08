#include <stdio.h>


int main(void)
{
int count = 0;
for (int i = 1; i <= 10; i++)
{ 
    for (int m=0; m < i; m++)
    {
        printf("*");
        count++;
    }
    printf("\n"); 

}
printf("Total %d", count);
printf("\n");
return 0;
}

