/*********************************************/
/*           extraction.c                    */
/*  Shift_JIS�����R�[�h�p�S�p�������o��      */
/*�@Shift_JIS�ŋL�q���ꂽ�t�@�C������        */
/*  �S�p�f�[�^�̂ݒ��o���܂�                 */
/* �g����                                    */
/*C:\Users\odaka\ch2>extraction < text1.txt  */
/*********************************************/

/*Visual Studio�Ƃ̌݊����m�� */
#define _CRT_SECURE_NO_WARNINGS

/*�w�b�_�t�@�C���̃C���N���[�h*/
#include <stdio.h>
#include <stdlib.h>

/* �L���萔�̒�`             */
#define TRUE 1 
#define FALSE 0

/* �֐��̃v���g�^�C�v�̐錾   */
int is2byte(int chr) ;/*�S�p������1�o�C�g�ڂ��ǂ����̔���*/

/****************/
/*  main()�֐�  */
/****************/
int main()
{
 int chr ;/*���͕���*/

 /*�f�[�^��ǂݍ����1�������o�͂���*/
 while((chr=getchar())!=EOF){
  if(is2byte(chr)==TRUE){
   /*�S�p�i�Q�o�C�g�j�o��*/
   putchar(chr) ;
   putchar(getchar()) ;
  }
 }

 return 0 ;
}

/***********************************/
/*  is2byte()�֐�                  */
/*�S�p������1�o�C�g�ڂ��ǂ����̔���*/
/***********************************/
int is2byte(int c)
{
 if(((c>=0x81)&&(c<=0x9F))||(c>=0xe0)&&(c<=0xef))
  return TRUE ;/*2�o�C�g����*/
 return FALSE ;/*1�o�C�g����*/
}

