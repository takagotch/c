/* ポインタによるスタック操作のプログラム例 */

#include <stdio.h>    /* 標準入出力のヘッダファイルの読込み */
#include <stdlib.h>   /* 標準ライブラリのヘッダファイル */
struct cell           /* 構造体cellの定義 */
{
 int element;
 struct cell *next;
};
/* 関数の宣言 */
struct cell *push(int x, struct cell *init);
struct cell *pop(struct cell *init);

main()  
/* 連結リストによるスタック操作のテストプログラム */
{
 struct cell *init;
 struct cell *q;
 int i;

 init=NULL;
 for(i=0; i<10; i++) init=push(i+1, init); 
 printf("init = %p\n", init);
 q=init;
 while(q!=NULL)
   {
    printf("cell = %d, %p\n", q->element, q->next);
    q=q->next;
   }  
 for(i=0; i<7; i++) init=pop(init);
 printf("init = %p\n", init);
 q=init;
 while(q!=NULL)
   {
    printf("cell = %d, %p\n", q->element, q->next);
    q=q->next;
   }
 return(0);
}

struct cell *push(int x, struct cell *init)
/* スタックinitの先頭へxを持つセルを挿入 */
{
 struct cell *q, *r;

 r=(struct cell *)malloc(sizeof(struct cell)); /* 新しいポインタの獲得 */
 q=init;                 /* セルの挿入 */
 init=r;
 r->element=x; r->next=q;
 return(init);
}

struct cell *pop(struct cell *init)
/* スタックinitの先頭セルを除去 */
{
 struct cell *q;

 if(init!=NULL) 
   {
    q=init; init=init->next; free(q); return(init);
   }
 else {printf("Error: Stack is empty.\n"); exit(1);}
}
