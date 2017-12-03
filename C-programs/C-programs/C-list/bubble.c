/* バブルソートのプログラム例 */

#include <stdio.h>
#include <stdlib.h>
#define N 500   /* The max size of array. */
void bubblesort(int h, int k, int *A);
void swap(int i, int j, int *A);

main()
/* バブルソートのテストプログラム */
{
 int A[N];
 int n, i;
 FILE *file;

 file=fopen("sortdata", "r");  /* データの読込み */
 fscanf(file, "%d", &n);
 if(n>N) 
   {
    printf("Illegal array size n = %d for N = %d\n", n, N); 
    exit(1);
   }
 printf("n = %d\nA = ", n);
 for(i=0; i<n; i++) fscanf(file, "%d", &A[i]);
 for(i=0; i<n; i++) printf("%d ", A[i]);
 printf("\nA = ");
 bubblesort(0, n-1, A);      /* 配列A[0]からA[n-1]の整列 */
 for(i=0; i<n; i++) printf("%d ",A[i]);
 printf("\n");
 return(0);
}

void bubblesort(int h, int k, int *A)
/* A[k],...,A[h]の要素をバブルソートによって整列 */
{
 int i, j;
 int test;                   /* test==1; すでに整列済み */

 for(i=h; i<k; i++)          /* バブル操作の反復 */
   {
    test=1;
    for(j=k; j>=i+1; j--) 
      if(A[j]<A[j-1]) {swap(j, j-1, A); test=0;}
    if(test==1) return;
   }
 return;
}

void swap(int i, int j, int *A)
/* Swap A[i] and A[j]. */
{
 int temp;
 temp=A[i]; A[i]=A[j]; A[j]=temp;
 return;
}
