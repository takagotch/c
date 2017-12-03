/*************************************************/
/*           makebagofw.c                        */
/* bag-of-words�𐶐����܂�                      */
/* �g����                                        */
/*C:\Users\odaka\ch2>makebagofw  (�����j         */
/* �������@�P���b�� n                        */
/* �������@ ���̓t�@�C�� �i1-on-N�\���j        */
/* �����̎w�肪�����ꍇ�͕W�����͂��w��          */
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
#define N 1000/*��b(�P��j�̎�ނ̏��*/
#define LENGTH 64 /*�t�@�C�����̒����̏��*/

/****************/
/*  main()�֐�  */
/****************/
int main(int argc,char *argv[])
{
 int n ;/*�P��̎�ސ�*/
 FILE *fpi ;/*�t�@�C���|�C���^*/
 char inputfile[LENGTH] ;/*���̓t�@�C����*/
 int e ;/*�x�N�g���̗v�f�̒l*/
 int i=0 ;/*�J�Ԃ��̐���*/
 int bagofwords[N]={0} ;/*bag-of-words�\��*/

 /*��������̏����l�̐ݒ�*/
 if(argc<2){
  /*����������Ȃ�*/
  fprintf(stderr,"�g����\n >makenewvec "
          "�P���ސ�n  (�t�@�C����)\n") ;
  exit(1);
 }
 fpi=stdin ;/*�f�t�H���g�͕W������*/
 n=atoi(argv[1]) ;/*��b�����Z�b�g*/
 if(argc>2){/*���̓t�@�C���̃I�[�v��*/
  strncpy(inputfile,argv[2],LENGTH) ;/*���̓t�@�C��*/
  if((fpi=fopen(inputfile,"r"))==NULL){
   /*�t�@�C���I�[�v�����s*/
   fprintf(stderr,"%s:�t�@�C���I�[�v�����s\n",inputfile) ;
   exit(1);
  }
 }
  
 /*1-of-N�\���Ɋ�Â��P��̕��т̓ǂݍ���*/
 while(fscanf(fpi,"%d",&e)!=EOF){
  bagofwords[i]+=e ;
  ++i ;
  if(i>=n) i=0 ;
 }

 /*bag-of-words�\���̏o��*/
 for(i=0;i<n;++i)
  printf("%d ", bagofwords[i]);
 printf("\n") ;

 return 0 ;
}
