/* �|�C���^�ɂ��҂��s��̑���̃v���O������ */

#include <stdio.h>     /* �W�����o�͂̃w�b�_�t�@�C���̓Ǎ��� */
#include <stdlib.h>    /* �W�����C�u�����̃w�b�_�t�@�C�� */
struct cell            /* �\����cell�̒�` */
{
 int element;
 struct cell *next;
};
struct queue           /* �\����queue�̒�` */
{
 struct cell *front;   /* queue�̐擪 */
 struct cell *rear;    /* queue�̖��� */
};
/* �֐��̐錾 */
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
/* �҂��s��Q�̖����ɗv�fx��}�� */
{
 struct cell *p;

 p=(struct cell *)malloc(sizeof(struct cell)); /* �V�����|�C���^�̊l�� */
 if(Q->rear != NULL) Q->rear->next = p;        /* Q����łȂ��ꍇ */
 Q->rear = p;
 if(Q->front == NULL) Q->front = p;            /* Q����̏ꍇ */
 Q->rear->element = x; Q->rear->next = NULL;
 return;
}

void dequeue(struct queue *Q)
/* �҂��s��Q�̐擪�̃Z�������� */
{
 struct cell *q;

 if(Q->front == NULL) {printf("Error: Queue is empty.\n"); exit(1);} 
                                                        /* ��: Q�͋� */
 else {q=Q->front; Q->front = Q->front->next; free(q);} /* ��ʂ̏ꍇ */
 if(Q->front == NULL) Q->rear = NULL;
 return;
}

