#include <stdio.h>
#include <stdlib.h>
#define N 100  /* The max size of array A. */
#define m 100  /* Range of values [0, ..., m-1]. */
struct cell
{
 int element;
 struct cell *next;
};
void bucketsort(int *A, int n);
void insert(int x, struct cell **B);

main()  
/* Bucketsort by using linked lists. */
{
 int A[N];
 int i, n;
 n=10;
 for(i=0; i<n; i++) A[i]=99-i; 
 printf("n = %d\n", n);
 for(i=0; i<n; i++) printf("%d ", A[i]);
 printf("\n");
 bucketsort(A, n);
 for(i=0; i<n; i++) printf("%d ", A[i]);
 printf("\n"); 
 return(0);
}

void bucketsort(int *A, int n)
/* Bucket sort the first n elements in A. */
{
 struct cell *B[m];
 struct cell *p;
 int i, j;
 for(j=0; j<m; j++) B[j]=NULL;
 for(i=0; i<n; i++) insert(A[i], B);
 i=n-1;
 for(j=m-1; j>=0; j--)
   {
    p=B[j];
    while(p != NULL)
      {
       A[i] = p->element;
       i=i-1;
       p = p->next;
      }
   }
 return;
}

void insert(int x, struct cell **B)
/* Insert x in the bucket B[x]. */
{
 struct cell *r;
 r=(struct cell *)malloc(sizeof(struct cell));
 r->element=x; r->next=B[x];
 B[x]=r;
 return;
}

