#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

struct ex
{
 int x;
 int y;
};


void main(int argc, char *argv[])
{
  /*int i, *a; */
  int i, b, a[10];/**/
  struct ex pair;
  void sub1();
  void sub2();
  void sub3();
  /*a = (int *) malloc( 10 * sizeof(int) ); */

  b=100;
  pair.x=10;
  pair.y=20;

  for(i=0; i<10; i++) a[i] = i+1;
  printf("a in main (before):\n");
  printf(" b = %d\n", b);
  printf("pair x= %d, y = %d\n", pair.x, pair.y);
  for(i=0; i<10; i++) printf(" %2d", a[i]);
  printf("\n");
  sub1(a, &b, &pair);
  printf("a in main  (after):\n");
  printf(" b = %d\n", b);
  printf("pair x= %d, y = %d\n", pair.x, pair.y);
  for(i=0; i<10; i++) printf(" %2d", a[i]);
  printf("\n");

  b=100;
  pair.x=10;
  pair.y=20;
  for(i=0; i<10; i++) a[i] = i+1;
  printf("a in main (before):\n");
  printf(" b = %d\n", b);
  printf("pair x= %d, y = %d\n", pair.x, pair.y);
  for(i=0; i<10; i++) printf(" %2d", a[i]);
  printf("\n");
  sub2(a, b, pair);
  printf("a in main  (after):\n");
  printf(" b = %d\n", b);
  printf("pair x= %d, y = %d\n", pair.x, pair.y);
  for(i=0; i<10; i++) printf(" %2d", a[i]);
  printf("\n");
  return;
}

void sub1(int *a, int *b,  struct ex *pair)
{
  int i;

  printf("a in sub1 (before):\n");
  printf(" b = %d\n", *b);
  printf("pair x= %d, y = %d\n", pair->x, pair->y);
  for(i=0; i<10; i++) printf(" %2d", a[i]);
  printf("\n");

  *b *= 2;
  pair->x *= 2;
  pair->y *= 2;
  for(i=0; i<10; i++) a[i] *= 2;

  printf("a in sub1  (after):\n");
  printf(" b = %d\n", *b);
  printf("pair x= %d, y = %d\n", pair->x, pair->y);
  for(i=0; i<10; i++) printf(" %2d", a[i]);
  printf("\n");
}

void sub2(int a[], int b, struct ex pair)
{
  int i;

  printf("a in sub2 (before):\n");
  printf(" b = %d\n", b);
  printf("pair x= %d, y = %d\n", pair.x, pair.y);
  for(i=0; i<10; i++) printf(" %2d", a[i]);
  printf("\n");

  b *= 2;
  pair.x *= 2;
  pair.y *= 2;
  for(i=0; i<10; i++) a[i] *= 2;

  printf("a in sub2  (after):\n");
  printf(" b = %d\n", b);
  printf("pair x= %d, y = %d\n", pair.x, pair.y);
  for(i=0; i<10; i++) printf(" %2d", a[i]);
  printf("\n");
}

