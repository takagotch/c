/*************************************************/
/*           tow2gram.c                          */
/*  makew1gram.c�v���O�����̏o�͌��ʂ���         */
/*  �P���2-gram�𐶐����܂�                     */
/* �g����                                        */
/*C:\Users\odaka\ch2>makew1gram<t.txt|tow2gram   */
/*************************************************/

/*Visual Studio�Ƃ̌݊����m�� */
#define _CRT_SECURE_NO_WARNINGS

/*�w�b�_�t�@�C���̃C���N���[�h*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* �L���萔�̒�`             */
#define N 256 /*�P��1-gram�̃o�C�g��*/


/****************/
/*  main()�֐�  */
/****************/
int main()
{
 char w1[N]="",w2[N]="" ;/*���͂��ꂽ�P��(1-gram)*/

 /*�f�[�^��ǂݍ���ŒP��2-gram���o�͂���*/
 while(scanf("%s",w2)!=EOF){
  printf("%s->%s\n",w1,w2) ;
  strncpy(w1,w2,N) ;/*���͂��ꂽ�P���ۑ�*/
 }

 return 0 ;
}

