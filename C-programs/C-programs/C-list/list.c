/* 連結リストに対するINSERTとDELETEのプログラム例 */

#include <stdio.h>    /* 標準入出力のヘッダファイルの読込み */
#include <stdlib.h>   /* 標準ライブラリのヘッダファイル */
struct cell           /* 構造体cellの定義 */
{
 int element;
 struct cell *next;
};
/* 関数の宣言 */
struct cell *insert(int x, struct cell *p, struct cell *init); 
struct cell *delete(struct cell *p, struct cell *init);

main()  
/* Manipulation of a linked list of cells. */
{
 struct cell *init;
 struct cell *p, *q;
 int i;

 init=NULL;
 p=NULL;
 for(i=0; i<10; i++) {init=insert(i+1, p, init); p=NULL;} 
 printf("init = %p\n", init);
 q=init;
 while(q!=NULL)
   {
    printf("cell = %d, %p\n", q->element, q->next);
    q=q->next;
   }  
 p=init->next->next;
 for(i=0; i<6; i++) init=delete(p, init);
 printf("init = %p\n", init);
 q=init;
 while(q!=NULL)
   {
    printf("cell = %d, %p\n", q->element, q->next);
    q=q->next;
   }
 return(0);
}

struct cell *insert(int x, struct cell *p, struct cell *init)
/* ポインタpが指すセルの次にxのセルを挿入; p==NULLなら先頭へ挿入 */
/* 連結リストはポインタinitから始まる */
{
 struct cell *q, *r;

 r=(struct cell *)malloc(sizeof(struct cell)); /* 新しいポインタの獲得 */
 if(p==NULL) {q=init; init=r;}       /* 先頭への挿入 */
 else {q=p->next; p->next=r;}        /* 途中への挿入 */
 r->element=x; r->next=q;
 return(init);
}

struct cell *delete(struct cell *p, struct cell *init)
/* initからの連結リストにおいてポインタpが指すセルの次のセルを除去 */
{
 struct cell *q;

 if(init==NULL) {printf("Error: List is empty.\n"); exit(1);}
 if(p==NULL)                         /* 先頭のセルの除去 */
   {q=init; init=init->next; free(q);}
 else                                /* その他の場合 */
   {
    if(p->next == NULL)              /* 次のセルは存在しない（誤り）*/
      {printf("Error: No element to remove.\n"); exit(1);}
    else                             /* 次のセルの除去 */
      {q=p->next; p->next=q->next; free(q);}
   }
 return(init);
}
