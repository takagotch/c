/*********************************************/
/*           make3gram.c                     */
/*  Shift_JIS�����R�[�h�p����3-gram������    */
/*�@Shift_JIS�ŋL�q���ꂽ�t�@�C������        */
/*  �S�p�f�[�^�̂ݒ��o����3-gram�𐶐����܂� */
/* �g����                                    */
/*C:\Users\odaka\ch2>make3gram <text1.txt    */
/*********************************************/

/*Visual Studio�Ƃ̌݊����m�� */
#define _CRT_SECURE_NO_WARNINGS

/*�w�b�_�t�@�C���̃C���N���[�h*/
#include <stdio.h>
#include <stdlib.h>

/* �L���萔�̒�`             */
#define TRUE 1 
#define FALSE 0
#define N 6 /*n-gram��n�̂Q�{*/

/* �֐��̃v���g�^�C�v�̐錾   */
int is2byte(int chr) ;/*�S�p������1�o�C�g�ڂ��ǂ����̔���*/
void put3gram(int chr) ;/*3-gram�̏o��*/
int invert(int flag) ;/*�t���O�̔��]*/

/****************/
/*  main()�֐�  */
/****************/
int main()
{
 int chr ;/*���͕���*/

 /*�f�[�^��ǂݍ����1�������o�͂���*/
 while((chr=getchar())!=EOF){
  if(is2byte(chr)==TRUE){
   /*put3gram()�֐��ɂ��o��*/
   put3gram(chr) ;
   put3gram(getchar()) ;
  }
 }

 return 0 ;
}

/*******************************/
/*  invett()�֐�               */
/*�@flag�̔��]                 */
/*******************************/
int invert(int flag)
{
 if(flag==FALSE)
  return TRUE ;
 return FALSE ;
}


/*******************************/
/*  put3gram()�֐�             */
/*  3-gram�̏o��               */
/*******************************/
void put3gram(int c)
{
 static char queue[N]="�@�@�@" ;/*�o�͗p�̃L���[*/
 static int flag=FALSE ;/*�o�͂̃^�C�~���O����*/
 int i;/*�J�Ԃ��̐���*/

 /*�L���[�Ƀf�[�^��ǉ�*/
 for(i=0;i<N-1;++i)
  queue[i]=queue[i+1] ;
 queue[N-1]=c ;/*�f�[�^�ǉ�*/ 

 /*2�o�C�g�̋�؂�Ȃ�o��*/
 if(flag==TRUE){
  for(i=0;i<N;++i)
   putchar(queue[i]) ; 
  putchar('\n') ;
 }
 /*�t���O���]*/
 flag=invert(flag) ;
}


/*******************************/
/*  is2byte()�֐�              */
/*�S�p��1�o�C�g�ڂ��ǂ����̔���*/
/*******************************/
int is2byte(int c)
{
 if(((c>0x80)&&(c<0xA0))||(c>0xDF)&&(c<0xF0))
  return TRUE ;/*2�o�C�g����*/
 return FALSE ;/*1�o�C�g����*/
}

