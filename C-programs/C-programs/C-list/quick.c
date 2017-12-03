/* クイックソートのプログラム例 */

#include <stdio.h>
#include <stdlib.h>
#define N 500             /* 配列Aの最大サイズ */
/* 関数の宣言 */
void quicksort(int i, int j, int *A);
int partition(int i, int j, int a, int *A);
int pivot(int i, int j, int *A);
void swap(int i, int j, int *A);

main()
/* クイックソートのテストプログラム */
{
 int A[N];
 int n, i;
 FILE *file;

 file=fopen("sortdata", "r");            /* データの読込み */
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
 quicksort(0, n-1, A);   /* クイックソートによる配列Aの整列 */
 for(i=0; i<n; i++) printf("%d ",A[i]);
 printf("\n");
 return(0);
}

void quicksort(int i, int j, int *A)
/* 配列A[i],...,A[j]をクイックソートにより整列 */
{
 int a, pv, k;

 pv=pivot(i, j, A);
 if(pv!=-1)                    /* 軸要素が見つかった場合 */
   {
    a=A[pv];                   /* 軸要素 */
    k=partition(i, j, a, A);   /* 軸要素A[pv]により分割 */
    quicksort(i, k-1, A);      /* 前半の整列 */
    quicksort(k, j, A);        /* 後半の整列 */
   }
 return;
}

int partition(int i, int j, int a, int *A)
/* A[i],...,A[j]を軸要素aによって分割 */
/* 前半はA[i],...,A[k-1]<a, 後半はA[k],...,A[j]>=aを満たす */
{
 int l, r, k;

 l=i; r=j;                     /* lは左から、rは右から */
 while(1)    
   {
    while(A[l]<a) l=l+1; while(A[r]>=a) r=r-1;  /* lとrの移動 */
    if(l<=r) {swap(l, r, A); l=l+1; r=r-1;}    /* A[l]とA[r]の交換 */
    else break;                                 /* 終了 */
   }
 k=l;
 return(k);
}

int pivot(int i, int j, int *A)
/* A[i],...,A[j]から軸要素A[pv]を選びpvを出力 */
/* A[pv]はA[i]と最初に異なるA[k]の大きい方；すべて同じならpv=-1 */
{
 int pv, k;

 k=i+1;
 while(k<=j && A[i]==A[k]) k=k+1;
 if(k>j) pv=-1;
 else if(A[i]>=A[k]) pv=i;
 else pv=k;
 return(pv);
}

void swap(int i, int j, int *A)
/* Swap A[i] and A[j]. */
{
 int temp;
 temp=A[i]; A[i]=A[j]; A[j]=temp;
 return;
}
