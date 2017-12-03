/* バケットによる基数ソートのプログラム例 */

#include <stdio.h>
#include <stdlib.h>
#define N 100     /* 配列Aの最大サイズ */
#define m 10      /* 値の範囲は[0,1,...,m-1] */
#define K 3       /* 語長 */
struct word       /* 構造体wordの宣言 */
{
 int letter[K];
};
struct cell       /* 構造体cellの宣言 */
{
 int index;
 struct cell *next;
};
/* 関数の宣言 */
void radixsort(struct word *A, int *idx, int n);
void bucketsort(struct word *A, int *idx, int n, int k);
void insert(struct word *A, int idx, struct cell **B, int k);

main()  
/* 連結リストによる基数ソートのテストプログラム */
{
 struct word A[N];
 int idx[N];
 int i, h, n;

 n=15;
 for(i=0; i<n; i++)    /* データの生成 */
   {
    idx[i]=i;
    for(h=0; h<K; h++) A[i].letter[h]=(765-i*i+3*h*i)%10;
   }
 printf("n = %d\n", n);
 for(i=0; i<n; i++) 
   {
    for(h=0; h<K; h++) printf("%d", A[idx[i]].letter[h]);
    printf(" ");
   }
 printf("\n");
 radixsort(A, idx, n);    /* 基数ソートによる整列 */
 for(i=0; i<n; i++) 
   {
    for(h=0; h<K; h++) printf("%d", A[idx[i]].letter[h]);
    printf(" ");
   }
 printf("\n"); 
 return(0);
}

void radixsort(struct word *A, int *idx, int n)
/* 配列A[0],...,A[n-1]の基数ソートによる整列。*/
/* 整列は配列idx[0],...,idx[n-1]を用いて間接的に行う */
{
 int k;
                                       /* 桁ごとにバケットソート */
 for(k=K-1; k>=0; k--) bucketsort(A, idx, n, k); 
 return;
}

void bucketsort(struct word *A, int *idx, int n, int k)
/* A[0],...,A[n-1]をk桁目の値にしたがってバケットソート */
/* 整列は配列idx上で間接的に行う */
{
 struct cell *B[m];               /* バケット0,...,m-1 */
 struct cell *p, *q;
 int i, j;

 for(j=0; j<m; j++) B[j]=NULL;                /* バケットの初期化 */
 for(i=0; i<n; i++) insert(A, idx[i], B, k);  /* idx[i]をバケットへ */
 i=n-1;
 for(j=m-1; j>=0; j--)            /* バケットからidxへ戻す */
   {
    p=B[j];
    while(p != NULL) 
      {idx[i] = p->index; i=i-1; q = p->next; free(p); p=q;}
   }
 return;
}

void insert(struct word *A, int ix, struct cell **B, int k)
/* ixをk桁目の値A[ix].letter[k]のバケットBに挿入 */
{
 struct cell *p;

 p=(struct cell *)malloc(sizeof(struct cell));  /* 新しいポインタの獲得 */
 p->index = ix;                                 /* バケットへの挿入 */
 p->next = B[A[ix].letter[k]];
 B[A[ix].letter[k]] = p;
 return;
}

