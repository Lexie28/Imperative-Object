#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


struct point
{
  int x;
  int y;
};

typedef struct point point_t;

struct rectangle
{
   point_t upper_left;
   point_t lower_right;
};

typedef struct rectangle rectangle_t;

void translate(point_t *p1, point_t *p2)
{
  p1->x += p2->x;
  p1->y += p2->y;
}

void print_point(point_t *p)
{
    printf("(%d,%d)\n", p->x, p->y);
}


void print_rect(rectangle_t *p)
{
    printf("rectangle(upper_left=");
    print_point(&p->upper_left);
    printf(", lower_right=");
    print_point(&p->lower_right);

}


point_t make_point(int x, int y)
{
    point_t point = {.x = x, .y = y};
}

rectangle_t make_rect(int a, int b, int c, int d)
{
    point_t q1 = make_point(a,b);
    point_t q2 = make_point(c,d);
    rectangle_t r1 = {.upper_left = q1, .lower_right = q2};
    print_rect(&r1);
    return r1;
}

int area_rect(rectangle_t* r1)
{
    int basen = (&r1 -> lower_right.x)-(&r1 -> upper_left.x);
    int höjd = (&r1 -> upper_left.y)-(&r1 -> lower_right.y);
    int area = basen * höjd;
    printf("area: %d", area);
}

int main(int argc, char const *argv[])
{ 
    rectangle_t rectangle = {.upper_left.x=1, .upper_left.y=4, .lower_right.x=4, .lower_right.y=1};
    int u = area_rect(&rectangle);
    printf("%d", u);
    //print_rect(&rectangle);
    return 0;


    /* point_t point = {.x = 5, .y = 10};
    print_point(&point);
    return 0; */
}

