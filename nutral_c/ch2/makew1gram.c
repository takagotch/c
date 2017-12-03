/*************************************************/
/*           makew1gram.c                        */
/*  Shift_JIS�����R�[�h�p�P��1-gram������ �@     */
/*�@Shift_JIS�ŋL�q���ꂽ�t�@�C������            */
/*  �S�p�f�[�^�̂ݒ��o���ĒP��1-gram�𐶐����܂� */
/* �g����                                        */
/*C:\Users\odaka\ch2>makew1gram < text1.txt      */
/*************************************************/

/*Visual Studio�Ƃ̌݊����m�� */
#define _CRT_SECURE_NO_WARNINGS

/*�w�b�_�t�@�C���̃C���N���[�h*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* �L���萔�̒�`             */
#define TRUE 1 
#define FALSE 0
#define KANJI 0 /*����͊���*/
#define KATAKANA 1/*����̓J�^�J�i*/
#define KUTOUTEN 2/*����͋�Ǔ_*/
#define SONOTA 3 /*����͏�L�ȊO*/


/* �֐��̃v���g�^�C�v�̐錾   */
int is2byte(int chr) ;/*�S�p��1�o�C�g�ڂ��ǂ����̔���*/
int typep(int chr1,int chr2) ;/*����̔���*/

/****************/
/*  main()�֐�  */
/****************/
int main()
{
 int chr1,chr2 ;/*���͕���*/
 int now,last=-1 ;/*����̋L��*/

 /*�f�[�^��ǂݍ����1�������o�͂���*/
 while((chr1=getchar())!=EOF){
  if(is2byte(chr1)==TRUE){
   chr2=getchar() ;
   now=typep(chr1,chr2) ;

   /*�S�p�i�Q�o�C�g�j�o��*/
   if(now!=last){
    putchar('\n') ;/*1-gram�̋�؂�*/
    last=now ;
   }
   putchar(chr1) ;
   putchar(chr2) ;
 
  }
 }

 return 0 ;
}

/*******************************/
/*  typep()�֐�                */
/*�@����̔���                 */
/*******************************/
int typep(int chr1,int chr2)
{
 char chr[3]="�@" ;/*��Ǔ_����p*/

 chr[0]=chr1 ; chr[1]=chr2 ; /*�����̐ݒ�*/
 /*����̔���*/
 if(chr1>=0x88)
  return KANJI ;/*����*/
 else if((chr1==0x83)&&(chr2>=0x40)&&(chr2<=0x96))  
  return KATAKANA ;/*�J�^�J�i*/
 else if((strncmp(chr,"�B",2) ==0) ||
         (strncmp(chr,"�D",2) ==0) ||
         (strncmp(chr,"�A",2) ==0) ||
         (strncmp(chr,"�C",2) ==0))
  return KUTOUTEN ;/*��Ǔ_*/
 return SONOTA ;/*���̑�*/
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

