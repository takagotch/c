/*********************************************/
/*           dupline.c                       */
/*  2�s�ڈȍ~�̓��͍s�𕡐����܂�            */
/* �g����                                    */
/*C:\Users\odaka\ch4>dupline < text1.txt   */
/*********************************************/

/*Visual Studio�Ƃ̌݊����m�� */
#define _CRT_SECURE_NO_WARNINGS

/* �L���萔�̒�`             */
#define MAXSIZE 4096 /*1�s�̍ő�T�C�Y*/ 

/*�w�b�_�t�@�C���̃C���N���[�h*/
#include <stdio.h>
#include <stdlib.h>

/****************/
/*  main()�֐�  */
/****************/
int main()
{
 char line[MAXSIZE] ;/*���͍s*/

 /*�ŏ��̍s��ǂݍ���ł��̂܂܏o�͂���*/
 fgets(line,MAXSIZE,stdin) ;
 printf("%s",line) ;

 /*2�s�ڈȍ~�𕡐�����*/
 while(fgets(line,MAXSIZE,stdin)!=NULL){
  printf("%s",line) ;
  printf("%s",line) ;
 }

 return 0 ;
}
