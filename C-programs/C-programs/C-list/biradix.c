/* 2進数の基数ソートのプログラム例 */

#include <stdio.h>
#include <stdlib.h>
#define N 100         /* 配列Aの最大サイズ */
#define K 5           /* 語長 */
struct word           /* 構造体wordの定義 */
{
 int letter[K];
};

/* 関数の宣言 */
void biradixsort(struct word *A, int *iA, int n);

main()  
/* 2進数の基数ソートのテストプログラム */
{
 struct word A[N];    /* K桁の2進数wordの配列 */
 int iA[N];           /* 配列Aのインデックス */
 int i, h, n;
 FILE *file;

 file=fopen("bidata", "r");  /* データの読込み */
 fscanf(file, "%d", &n);
 if(n>N) 
   {
    printf("Illegal size n = %d for N = %d\n", n, N); 
    exit(1);
   }
 printf("n = %d, K = %d\nA = \n", n, K);
 for(i=0; i<n; i++) 
   {
    for(h=0; h<K; h++) fscanf(file, "%1d", &A[i].letter[h]);
   }
 for(i=0; i<n; i++) 
   {
    for(h=0; h<K; h++) printf("%1d", A[i].letter[h]);
    printf("\n");
   }
 biradixsort(A, iA, n);       /* 2進数の基数ソートの実行 */
 printf("Sorted A =\n");
 for(i=0; i<n; i++) 
   {
    for(h=0; h<K; h++) printf("%1d", A[iA[i]].letter[h]);
    printf("\n");
   }
 return(0);
}

void biradixsort(struct word *A, int *iA, int n)
/* 2進数（構造体word）の配列A[0],...,A[n-1]を基数ソートにより整列 */
{
 int i, k, count, i0, i1;
 int iB[N];                   /* 配列のインデックス */

 for(i=0; i<n; i++) iA[i]=i;         /* 初期化 */
 for(k=K-1; k>=0; k--)
   {
    count=0;                 /* k桁目の値が0である要素数を数える */
    for(i=0; i<n; i++) if(A[i].letter[k]==0) count=count+1;
    i0=0; i1=count;
    for(i=0; i<n; i++)       /* k桁目の値にしたがってAからBへ移動 */
      {
       if(A[iA[i]].letter[k]==0)     /* k桁目の値は0 */
         {  
          iB[i0]=iA[i];
          i0=i0+1;
         }
       else                          /* k桁目の値は1 */
         {  
          iB[i1]=iA[i];
          i1=i1+1;
         }
      }
    for(i=0; i<n; i++) iA[i]=iB[i];  /* iBをiAへ移動 */
   }
 return;
}


