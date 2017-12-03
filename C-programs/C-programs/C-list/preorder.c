/* 前順による木のなぞりのプログラム例 */

#include <stdio.h>   /* 標準入出力のヘッダファイルの読込み */
#include <stdlib.h>  /* 標準ライブラリのヘッダファイル */
#define N 100        /* 配列Sの最大サイズ（節点数） */
struct cell          /* 構造体cellの定義 */
{
 int node;
 struct cell *next;
};
void preorder(int k, struct cell **S);  /* 関数の宣言 */

main()  
/* Traverse a tree S in preorder. */
{
 struct cell *S[N], *p, *q;
 int n, j, parent, child, root;
 FILE *file;
 file=fopen("treedata", "r");
 fscanf(file, "%d", &n);
 if(n>N) 
   {
    printf("Illegal array size n = %d for N = %d\n", n, N); 
    exit(1);
   }
 printf("n = %d\n", n);
 for(j=0; j<n; j++) S[j]=NULL;
 fscanf(file, "%d", &parent);
 while(parent >= 0)
   {
    fscanf(file, "%d", &child);
    if(child >= 0)
      {
       p=(struct cell *)malloc(sizeof(struct cell));
       S[parent]=q=p;
      } 
    while(child >= 0)
      {
       q->node=child;
       q->next=NULL;
       fscanf(file, "%d", &child);
       if(child >= 0)
         {
          p=(struct cell *)malloc(sizeof(struct cell));
          q->next=p;
          q=p;
         }
      }
    fscanf(file, "%d", &parent);
   }
 for(j=0; j<n; j++) 
   {
    printf("S[%d] = %p, ", j, S[j]);
    q=S[j];
    while(q != NULL) 
      {
       printf("node = %d, next = %p, ", q->node, q->next);
       q=q->next;
      }
    printf("\n");
   }
 root=0;
 printf("preorder =");
 preorder(root, S);
 printf("\n");
 return(0);
}

void preorder(int k, struct cell **S) 
/* S[k]を根とする部分木の前順によるなぞり */
{
 struct cell *q;

 printf(" %d", k);      /* 節点kの出力 */
 q=S[k];                /* kから前順のなぞり */
 while(q != NULL)
   {
    preorder(q->node, S);   /* 再帰呼び出し */
    q=q->next;
   }
 return;
}

