/*************************************************/
/*           makevec.c                           */
/* �P��1-gram����,1-of-N�\���𐶐����܂�         */
/* �g����                                        */
/*C:\Users\odaka\ch2>makevec  (�����j            */
/*�����ł͓��o�̓t�@�C�����w�肵�܂�             */
/* �������@���̓t�@�C�� �i�P��1-gram�j         */
/* �����̎w�肪�����ꍇ��w1gram.txt�t�@�C�����w��*/
/* �������@�P���b���i�[����t�@�C��          */
/* �����̎w�肪�����ꍇ��voc.txt�t�@�C�����w��   */
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
#define N 5000/*�P��̎�ނ̏��*/
#define INPUTFILE "w1gram.txt"/*�f�t�H���g���̓t�@�C��*/
#define OUTPUTFILE "voc.txt"/*�f�t�H���g�o�̓t�@�C��*/


/* �֐��̃v���g�^�C�v�̐錾   */
int isnew(char word[],
      char dictionary[][LENGTH],int n)  ;/*�V�K�P�ꔻ��*/
void putvec(char word[],
      char dictionary[][LENGTH],int n)  ;/*1-of-N�o��*/

/****************/
/*  main()�֐�  */
/****************/
int main(int argc,char *argv[])
{
 char word[LENGTH*10] ;/*�P��̓ǂݍ��ݗp*/
 char dictionary[N][LENGTH] ;/*�P���o�^���鎫��*/
 int n=0 ;/*�P��̎�ސ�*/
 FILE *fpi,*fpo ;/*�t�@�C���|�C���^*/
 char inputfile[LENGTH]=INPUTFILE ;/*���̓t�@�C����*/
 char outputfile[LENGTH]=OUTPUTFILE ;/*�o�̓t�@�C����*/

 /*���̓t�@�C�����̐ݒ�*/
 if(argc>=2) strncpy(inputfile,argv[1],LENGTH) ;
 if(argc>=3) strncpy(outputfile,argv[2],LENGTH) ;

 /*���̓t�@�C���̃I�[�v��*/
 if((fpi=fopen(inputfile,"r"))==NULL){
  /*�t�@�C���I�[�v�����s*/
  fprintf(stderr,"%s:�t�@�C���I�[�v�����s\n",inputfile) ;
  exit(1);
 }

 /*�o�̓t�@�C���̃I�[�v��*/
 if((fpo=fopen(outputfile,"w"))==NULL){
  /*�t�@�C���I�[�v�����s*/
  fprintf(stderr,"%s:�t�@�C���I�[�v�����s\n",outputfile) ;
  exit(1);
 }
 /*�f�[�^��ǂݍ���Ŏ����ɓo�^����*/
 while(fscanf(fpi,"%s",word)!=EOF){
  if(isnew(word,dictionary,n)==TRUE){/*�V�����P��Ȃ�*/
    strncpy(dictionary[n],word,LENGTH) ;/*�P��o�^*/
    ++n ;/*�P�ꐔ���J�E���g�A�b�v*/
  }
 }
 fprintf(stderr,"�P�ꐔ %d\n",n) ;
 rewind(fpi) ;/*�t�@�C���擪�Ɋ����߂�*/

 /* 1-of-N�\���̏o��*/
 while(fscanf(fpi,"%s",word)!=EOF){
  putvec(word,dictionary,n) ;/*�o��*/
 }
 
 /*��b�̃t�@�C���o��*/
 {
  int i ;
  for(i=0;i<n;++i) fprintf(fpo,"%s\n",dictionary[i]) ;
 }


 return 0 ;
}

/*******************************/
/*  putvec()�֐�               */
/* 1-of-N�\���̏o��            */
/*******************************/
void putvec(char word[],
      char dictionary[][LENGTH],int n)  
{
 int i ;/*���[�v����p�ϐ�*/

 for(i=0;i<n;++i){
  if((strncmp(word,dictionary[i],LENGTH)==0)
       && (strlen(word)==strlen(dictionary[i]))) /*��v*/
   printf("1") ;
  else printf("0") ;
  printf(" ") ;
 }
 printf("\n") ;/*�x�N�g���̋�؂�*/
}

/*******************************/
/*  isnew()�֐�                */
/*�V�K�P�ꂩ�ǂ����̔���       */
/*******************************/
int isnew(char word[],
      char dictionary[][LENGTH],int n)  
{
 int i ;/*���[�v����p�ϐ�*/

 for(i=0;i<n;++i){
  if((strncmp(word,dictionary[i],LENGTH)==0)
       && (strlen(word)==strlen(dictionary[i]))) break ;/*���o�^*/
 }
 if(i<n) return FALSE ;
 
 return TRUE ;
}

