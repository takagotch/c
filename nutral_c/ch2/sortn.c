/*********************************************/
/*           sortn.c                          /
/*  �s���̐��l�ɂ��s�𐮗񂵂܂�           */
/* �g����                                    */
/*C:\Users\odaka\ch2>sortn < text.txt        */
/*********************************************/

/*Visual Studio�Ƃ̌݊����m�� */
#define _CRT_SECURE_NO_WARNINGS

/*�w�b�_�t�@�C���̃C���N���[�h*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* �L���萔�̒�`             */
#define LINESIZE 256 /*�@��s�̃o�C�g���̏�� */
#define MAX 65536*3 /* �s���̏�� */ 


/* �֐��̃v���g�^�C�v�̐錾   */
int cmpdata(const char *a,const char *b) ;
      /*��r�֐�*/

/* �O���ϐ��@*/
char lines[MAX][LINESIZE] ; /*�����Ώۃe�L�X�g*/

/****************/
/*  main()�֐�  */
/****************/
int main()
{
 char buffer[LINESIZE] ;/*�ǂݍ��݃o�b�t�@*/
 int pos=0 ;/*�ǂݍ��ݍs���̃J�E���^*/
 int i ;
 
 /*�e�L�X�g��ǂݍ���*/
 while(fgets(buffer,LINESIZE,stdin)!=NULL){
   strcpy(lines[pos],buffer) ;
   if((++pos)>=MAX){ 
    fprintf(stderr,
      "�t�@�C���T�C�Y�̏���𒴂��܂���\n") ;
    exit(1);
   }
  }
 /*����*/
 qsort(lines,pos,LINESIZE,
   (int (*)(const void *,const void *))cmpdata) ;
 /*�o��*/
 for(i=0;i<pos;++i)
  printf("%s",lines[i]) ;
  
 return 0;
}


/*******************************/
/*  cmpdata()�֐�              */
/*�@��r�֐�                   */
/*******************************/
int cmpdata(const char *a,const char *b)
{
 int inta,intb ;

 inta=atoi(a) ;
 intb=atoi(b) ;
 if(inta>intb) return -1;/*���������傫��*/
 else if(inta<intb) return 1 ;/*���������傫��*/

 return 0 ;/*����ȊO*/
}

