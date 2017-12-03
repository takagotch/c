/* �|�C���^�ɂ��X�^�b�N����̃v���O������ */

#include <stdio.h>    /* �W�����o�͂̃w�b�_�t�@�C���̓Ǎ��� */
#include <stdlib.h>   /* �W�����C�u�����̃w�b�_�t�@�C�� */
struct cell           /* �\����cell�̒�` */
{
 int element;
 struct cell *next;
};
/* �֐��̐錾 */
struct cell *push(int x, struct cell *init);
struct cell *pop(struct cell *init);

main()  
/* �A�����X�g�ɂ��X�^�b�N����̃e�X�g�v���O���� */
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
/* �X�^�b�Ninit�̐擪��x�����Z����}�� */
{
 struct cell *q, *r;

 r=(struct cell *)malloc(sizeof(struct cell)); /* �V�����|�C���^�̊l�� */
 q=init;                 /* �Z���̑}�� */
 init=r;
 r->element=x; r->next=q;
 return(init);
}

struct cell *pop(struct cell *init)
/* �X�^�b�Ninit�̐擪�Z�������� */
{
 struct cell *q;

 if(init!=NULL) 
   {
    q=init; init=init->next; free(q); return(init);
   }
 else {printf("Error: Stack is empty.\n"); exit(1);}
}
