/* ポインタによる待ち行列の操作のプログラム例 */

#include <stdio.h>     /* 標準入出力のヘッダファイルの読込み */
#include <stdlib.h>    /* 標準ライブラリのヘッダファイル */
struct cell            /* 構造体cellの定義 */
{
 int element;
 struct cell *next;
};
struct queue           /* 構造体queueの定義 */
{
 struct cell *front;   /* queueの先頭 */
 struct cell *rear;    /* queueの末尾 */
};
/* 関数の宣言 */
void enqueue(int x, struct queue *Q);
void dequeue(struct queue *Q);

main()  
/* Manipulation of a linked queue of cells. */
{
 struct queue Q;
 struct cell *q;
 int i;

 Q.front=Q.rear=NULL;
 for(i=0; i<8; i++) {enqueue(i+1, &Q);} 
 printf("Q.front = %p,  Q.rear = %p\n", Q.front, Q.rear);
 q=Q.front;
 while(q!=NULL)
   {
    printf("cell = %d, %p\n", q->element, q->next);
    q=q->next;
   }  
 for(i=0; i<10; i++) dequeue(&Q);
 printf("Q.front = %p,  Q.rear = %p\n", Q.front, Q.rear);
 q=Q.front;
 while(q!=NULL)
   {
    printf("cell = %d, %p\n", q->element, q->next);
    q=q->next;
   } 
 return(0);
}

void enqueue(int x, struct queue *Q)
/* 待ち行列Qの末尾に要素xを挿入 */
{
 struct cell *p;

 p=(struct cell *)malloc(sizeof(struct cell)); /* 新しいポインタの獲得 */
 if(Q->rear != NULL) Q->rear->next = p;        /* Qが空でない場合 */
 Q->rear = p;
 if(Q->front == NULL) Q->front = p;            /* Qが空の場合 */
 Q->rear->element = x; Q->rear->next = NULL;
 return;
}

void dequeue(struct queue *Q)
/* 待ち行列Qの先頭のセルを除去 */
{
 struct cell *q;

 if(Q->front == NULL) {printf("Error: Queue is empty.\n"); exit(1);} 
                                                        /* 誤: Qは空 */
 else {q=Q->front; Q->front = Q->front->next; free(q);} /* 一般の場合 */
 if(Q->front == NULL) Q->rear = NULL;
 return;
}

