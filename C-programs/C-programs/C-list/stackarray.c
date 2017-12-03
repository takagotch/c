/* �z��ɂ��X�^�b�N����̃v���O������ */

#include <stdio.h>
#define N 100    /* �X�^�b�N�z��̍ő�T�C�Y */
struct stack     /* �\����stack�̒�` */
{
 int top;
 int element[N];
};
/* �֐��̐錾 */
void push(int x, struct stack *S);
void pop(struct stack *S);

main()  
/* Implementation of a stack by an array. */
{
 struct stack S;
 int i;
 S.top=N;
 for(i=0; i<10; i++) push(i+1, &S); 
 printf("S.top = %d, N = %d\n", S.top, N);
 i=S.top;
 while(i<N)
   {
    printf("i = %d, x = %d\n", i, S.element[i]);
    i=i+1;
   }  
 for(i=0; i<8; i++) pop(&S);
 printf("S.top = %d\n", S.top);
 i=S.top;
 while(i<N)
   {
    printf("i = %d, x = %d\n", i, S.element[i]);
    i=i+1;
   }
 return(0);
}

void push(int x, struct stack *S)
/* �X�^�b�NS�̐擪��x��}�� */
{
 if(S->top>=N || S->top<0) S->top=N;                /* S����̏ꍇ */
 if(S->top==0)                                      /* S�͖��t */
   {printf("Error: Stack is full.\n"); exit(1);}      
 else {S->top=S->top-1; S->element[S->top]=x;}      /* ���̑��̏ꍇ */
 return;
}

void pop(struct stack *S)
/* �X�^�b�NS�̐擪�̗v�f������ */
{
 if(S->top<N) {S->top=S->top+1;}                     /* �ʏ�̏ꍇ */
 else {printf("Error: Stack is empty.\n"); exit(1);} /* ��̏ꍇ */
 return;
}
