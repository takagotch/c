/* ヒープソートのプログラム例 */

#include <stdio.h>
#include <stdlib.h>
#define N 500        /* The max size of array A. */
void heapsort(int *A, int n);
void heapify(int *A, int n);
void downmax(int i, int *A, int n);
int deletemax(int *A, int n);
void swap(int i, int j, int *A);

main()
/* ヒープソートのテストプログラム */
{
 int A[N];
 int n, i;
 FILE *file;

 file=fopen("sortdata", "r");   /* データの読込み */
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
 heapsort(A, n);                /* ヒープソートによる配列Aの整列 */
 for(i=0; i<n; i++) printf("%d ",A[i]);
 printf("\n");
 return(0);
}

void heapsort(int *A, int n)
/* 配列A[0],...,A[n-1]をヒープソートにより整列 */
{
 int i;

 heapify(A, n);         /* ヒープ化; ただし根は最大要素をもつ */
 for(i=n-1; i>0; i--) A[i]=deletemax(A, i+1);  /* 最大要素を末尾へ */
}

void heapify(int *A, int n)
/* A[0],...,A[n-1]をヒープ化 */
{
 int i;
 for(i=n/2-1; i>=0; i--) downmax(i, A, n);
}

void downmax(int i, int *A, int n)
/* A[i]から下方へ、ヒープの性質を回復するためのswap操作を適用 */
{
 int j;

 j=2*i+1;               /* iの左の子 */ 
 if(j>=n) return;
 if(j+1<n && A[j]<A[j+1]) j=j+1;   /* j: iの子で大きな値を持つ方 */
 if(A[j]>A[i])          /* iとjの交換 */
   {
    swap(i, j, A);
    downmax(j, A, n);   /* jの下方へ再帰的実行 */
   }
 return;
}

int deletemax(int *A, int n)
/* ヒープA[0],...,A[n-1]から最大要素A[0]の出力と除去 */
{
 int max;

 max=A[0]; A[0]=A[n-1]; /* A[0]の出力とA[n-1]の移動 */
 downmax(0, A, n-1);    /* ヒープ条件の回復のため下へ */
 return(max);
}

void swap(int i, int j, int *A)
/* Swap A[i] and A[j]. */
{
 int temp;
 temp=A[i]; A[i]=A[j]; A[j]=temp;
 return;
}
