/*************************************************/
/*           makes.c                             */
/* 1-of-N�\������,���𐶐����܂� �@�@�@�@        */
/* �g����                                        */
/*C:\Users\odaka\ch2>makes  (�����j              */
/*�����ł͓��̓t�@�C�����w�肵�܂�               */
/* �������@�P���b���i�[����t�@�C��          */
/* �����̎w�肪�����ꍇ��voc.txt�t�@�C�����w��   */
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
#define LENGTH 64 /*�P��̒����̏��*/
#define N 10000/*�P��̎�ނ̏��*/
#define VOCFILE "voc.txt"/*�f�t�H���g�P���b�t�@�C��*/

/****************/
/*  main()�֐�  */
/****************/
int main(int argc,char *argv[])
{
 char word[LENGTH*10] ;/*�P��̓ǂݍ��ݗp*/
 char dictionary[N][LENGTH] ;/*�P���o�^���鎫��*/
 int n=0 ;/*�P��̎�ސ�*/
 FILE *fpvoc,*fpi ;/*�t�@�C���|�C���^*/
 char inputfile[LENGTH] ;/*���̓t�@�C����*/
 char vocfile[LENGTH]=VOCFILE ;/*�P���b�t�@�C����*/
 int e ;/*���̓x�N�g���̗v�f�̒l*/
 int i ;/*�J�Ԃ��̐���*/

 /*���̓t�@�C�����̐ݒ�*/
 fpi=stdin ;
 if(argc>=2) strncpy(vocfile,argv[1],LENGTH) ;
 if(argc>=3) strncpy(inputfile,argv[2],LENGTH) ;

 /*��b�t�@�C���̃I�[�v��*/
 if((fpvoc=fopen(vocfile,"r"))==NULL){
  /*�t�@�C���I�[�v�����s*/
  fprintf(stderr,"%s:�t�@�C���I�[�v�����s\n",vocfile) ;
  exit(1);
 }

 /*���̓t�@�C���̃I�[�v��*/
 if((argc>=3)&&(fpi=fopen(inputfile,"r"))==NULL){
  /*�t�@�C���I�[�v�����s*/
  fprintf(stderr,"%s:�t�@�C���I�[�v�����s\n",inputfile) ;
  exit(1);
 }

 /*�P���b�f�[�^��ǂݍ���Ŏ����ɓo�^����*/
 while(fscanf(fpvoc,"%s",word)!=EOF){
  strncpy(dictionary[n],word,LENGTH) ;/*�P��o�^*/
  ++n ;/*�P�ꐔ���J�E���g�A�b�v*/
 }
 printf("�P�ꐔ %d\n",n) ;

 /* ���̏o��*/
 i=0 ;
 while(fscanf(fpi,"%d",&e)!=EOF){
  if(e==1) printf("%s",dictionary[i]) ;
  ++i ;
  if(i>=n) i=0 ;
 }
 
 return 0 ;
}



