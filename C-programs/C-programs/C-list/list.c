/* �A�����X�g�ɑ΂���INSERT��DELETE�̃v���O������ */

#include <stdio.h>    /* �W�����o�͂̃w�b�_�t�@�C���̓Ǎ��� */
#include <stdlib.h>   /* �W�����C�u�����̃w�b�_�t�@�C�� */
struct cell           /* �\����cell�̒�` */
{
 int element;
 struct cell *next;
};
/* �֐��̐錾 */
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
/* �|�C���^p���w���Z���̎���x�̃Z����}��; p==NULL�Ȃ�擪�֑}�� */
/* �A�����X�g�̓|�C���^init����n�܂� */
{
 struct cell *q, *r;

 r=(struct cell *)malloc(sizeof(struct cell)); /* �V�����|�C���^�̊l�� */
 if(p==NULL) {q=init; init=r;}       /* �擪�ւ̑}�� */
 else {q=p->next; p->next=r;}        /* �r���ւ̑}�� */
 r->element=x; r->next=q;
 return(init);
}

struct cell *delete(struct cell *p, struct cell *init)
/* init����̘A�����X�g�ɂ����ă|�C���^p���w���Z���̎��̃Z�������� */
{
 struct cell *q;

 if(init==NULL) {printf("Error: List is empty.\n"); exit(1);}
 if(p==NULL)                         /* �擪�̃Z���̏��� */
   {q=init; init=init->next; free(q);}
 else                                /* ���̑��̏ꍇ */
   {
    if(p->next == NULL)              /* ���̃Z���͑��݂��Ȃ��i���j*/
      {printf("Error: No element to remove.\n"); exit(1);}
    else                             /* ���̃Z���̏��� */
      {q=p->next; p->next=q->next; free(q);}
   }
 return(init);
}
