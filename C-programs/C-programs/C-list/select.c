/* 第p要素を選ぶSELECTのプログラム例 */

#include <stdio.h>
#include <stdlib.h>
#define N 500  /* The size of array. */
int select(int i, int j, int p, int *A);
void bubblesort(int i, int j, int *A);
void swap(int i, int j, int *A);
int partition(int i, int j, int a, int *A);

main()
/* p番目の大きさの要素の選択のテストプログラム */
{
 int A[N];
 int n, i, p, ap;
 FILE *file;
 file=fopen("selectdata", "r");        /* データファイルの読込 */
 fscanf(file, "%d", &n);
 fscanf(file, "%d", &p); 
 if(n>N)                               /* 配列サイズのチェック */
   {
    printf("Illegal array size n = %d for N = %d\n", n, N); 
    exit(1);
   }
 for(i=0; i<n; i++) fscanf(file, "%d", &A[i]); 
 printf("n = %d\nA = ", n);            /* Aの出力 */
 for(i=0; i<n; i++) printf("%d ", A[i]);
 printf("\n"); 
 ap=select(0, n-1, p, A);              /* SELECTの実行 */
 printf("%d-th smallest element = %d\n", p, ap); /* 結果の出力 */
 return(0);
}

int select(int i, int j, int p, int *A)
/* 配列A[i],...,A[j]からp番目の大きさの要素を出力 */
{
 int m, a, h, k;

 if(j-i+1 < 50)      /* Aのサイズ小の場合 */
   {
    bubblesort(i, j, A);
    return(A[i+p-1]);
   }
 else                /* Aのサイズ大の場合 */
   {
    m=(j-i+1)/5;
    for(h=0; h<m; h++)                  /* 5要素ずつmグループに分割 */
      {
       bubblesort(i+5*h, i+5*h+4, A);   /* 各グループにバブルソート */
       swap(i+h, i+5*h+2, A);           /* 各グループの中央値を先頭へ */
      }
    a=select(i, i+m-1, (j-i+6)/10, A);  /* a: m個の中央値の中央値 */
    k=partition(i, j, a, A);            /* aによって分割 */
    if(p<=k-i) return(select(i, k-1, p, A)); /* 正しい部分へ再帰的適用 */
    else return(select(k, j, p-k+i, A));
   }
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

int partition(int i, int j, int a, int *A)
/* A[i],...,A[j]を軸要素aによって分割 */
/* 前半はA[i],...,A[k-1]<a, 後半はA[k],...,A[j]>=aを満たす */
{
 int l, r, k;

 l=i; r=j;                     /* lは左から、rは右から */
 while(1)    
   {
    while(A[l]<a) l=l+1; while(A[r]>=a) r=r-1;  /* lとrの移動 */
    if(l<=r) {swap(l, r, A); l=l+1; r=r-1;}     /* A[l]とA[r]の交換 */
    else break;                                 /* 終了 */
   }
 k=l;
 return(k);
}
