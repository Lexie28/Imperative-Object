#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

struct point
{
  int x;
  int y;
};

typedef struct point point_t;

void translate(point_t *p1, point_t *p2)
{
  p1->x += p2->x;
  p1->y += p2->y;
}

int main(int argc, char const *argv[])
{
    
point_t p = { .x = 10, .y = 7 };
translate(&p, &p);

}


