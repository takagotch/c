#include <stdio.h>        /* �W�����o�͂̃w�b�_�t�@�C���̓Ǎ��� */
#include <stdlib.h>       /* �W�����C�u�����̃w�b�_�t�@�C���̓Ǎ��� */
int gcd(int a0, int a1);  /* �֐��̐錾 */

main()                   
/* ���C���v���O�����F�ő���񐔌v�Z�̂��߂̃f�[�^�̓��o�� */
{
 int a0, a1, temp;                    /* �ϐ��̐錾 */

 printf("Type in the first integer.\n");  /* a0�̓��͂��w�� */
 scanf("%d", &a0);                    /* �L�[�{�[�h����a0�̓��� */
 printf("a0 = %d\n", a0);             /* a0�̏o�� */
 printf("Type in the second integer.\n"); /* a1�̓��͂��w�� */
 scanf("%d", &a1);                    /* �L�[�{�[�h����a1�̓��� */
 printf("a1 = %d\n", a1);             /* a1�̏o�� */
 if(a0<=0 || a1<=0)                   /* �����̃`�F�b�N */
   {printf("Illegal input number\n"); exit(1);}
 if(a0<a1) {temp=a0; a0=a1; a1=temp;} /* a0>=a1�ɐ��K�� */
 printf("GCD = %d\n", gcd(a0,a1));    /* �ő���񐔂̌v�Z�Əo�� */
 return(0);
}

int gcd(int a0, int a1)          /* ���[�N���b�h�̌ݏ��@ */
/* ���[�N���b�h�̌ݏ��@: a0��a1�̍ő���񐔂̌v�Z */
{
 int a, b, temp;                      /* �ϐ��̐錾 */

 a=a0; b=a1;                          /* �����ݒ� */
 while(b!=0) {temp=a%b; a=b; b=temp;} /* �ݏ��@�̔��� */
 return(a);                           /* �v�Z���ʂ�Ԃ� */
}
