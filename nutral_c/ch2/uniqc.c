/*********************************************/
/*           uniqc.c                         */
/*  �d���s�̐����グ                         */
/*�@�s�̌J��Ԃ����폜��,�d���񐔂������܂�  */
/* �g����                                    */
/*C:\Users\odaka\ch2>uniqc < text.txt        */
/*********************************************/

/*Visual Studio�Ƃ̌݊����m�� */
#define _CRT_SECURE_NO_WARNINGS

/*�w�b�_�t�@�C���̃C���N���[�h*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/* �L���萔�̒�`             */
#define MAXLINE 65535 

/****************/
/*  main()�֐�  */
/****************/
int main()
{
 char newline[MAXLINE] ;/*���͍s*/
 char oldline[MAXLINE] ;/*�O�̍s*/
 int count=1 ;/*�d����*/

 /*�e�L�X�g��ǂݍ���*/
 fgets(oldline,MAXLINE,stdin) ;
 while(fgets(newline,MAXLINE,stdin)!=NULL){
  if(strcmp(newline,oldline)==0) ++count ;/*�����s*/
  else{/*�قȂ�s*/
   printf("%d\t%s",count,oldline);
   count=1 ;
   strcpy(oldline,newline) ;
  }
 }
 printf("%d\t%s",count,oldline);

 return 0 ;
}
