/* �K��n!�̌v�Z�̃v���O������ */

#include <stdio.h>   /* �W�����o�͂̃w�b�_�t�@�C���̓Ǎ��� */
int fact(int n);     /* �֐��̐錾 */

main()
/* �K��̌v�Z�̃e�X�g�v���O���� */
{
 int n;

 n=5;                /* n�̐ݒ� */
 printf("factorial of n = %d is %d\n", n, fact(n)); /* n!�̌v�Z�Əo�� */
}

int fact(int n)
/* �K��n!�̌v�Z */
{
 if(n<=0) {printf("Illegal input n = %d\n", n); exit(1);}
 else 
   {
    if(n==1) return(1);         /* n==1�̏ꍇ */
    else return(n*fact(n-1));   /* fact�̍ċA�Ăяo�� */
   }
 return;
}
