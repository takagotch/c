/*************************************************/
/*           makenewvec.c                        */
/* �����_���ɐV������(1-of-N�\���j�𐶐����܂�   */
/* �g����                                        */
/*C:\Users\odaka\ch2>makenewvec  (�����j         */
/*�����ł͓��̓t�@�C�����w�肵�܂�               */
/* �������@�P���b�� n                        */
/* �������@�J�n�P��ԍ�  s (������0<=s<n)      */
/* �����̎w�肪�����ꍇ��0���w��                 */
/* ��O�����@ ���̓t�@�C�� �i1-on-N�\���j        */
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
#define WN 5000/*�P��̌��̏��*/
#define WLIMIT 50/*�o�͒P�ꐔ*/
#define LENGTH 64 /*������̒����̏��*/
#define SEED 65535    /*�����̃V�[�h*/
#define ULIMIT 5 /*�P��������_���ɒT����������*/

/* �֐��̃v���g�^�C�v�̐錾   */
int read1ofn(FILE *fpi,int n) ;
   /*1-of-N�\���Ɋ�Â��P��̕��т̓ǂݍ���*/
void putvec(int nextn,int n) ;
   /*1-of-N�\���Ɋ�Â��P��̏o��*/
int searchs(int s,int n,int wn) ;
   /*s�ɑΉ�����P���T��*/
int matchptn(int i,int s,int n) ;
  /*�P��̈�v����������@              */
int rndn(int n) ;
  /*�����ȉ��̐���������Ԃ�*/

/*�O���ϐ�*/
char ngram[WN][N] ;/*1-of-N�\���̓��̓f�[�^���i�[*/

/****************/
/*  main()�֐�  */
/****************/
int main(int argc,char *argv[])
{
 int n ;/*�P��̎�ސ�*/
 int wn ;/*���͂��ꂽ�P��̑���*/
 int s=0 ;/*�J�n�P��ԍ�*/
 FILE *fpi ;/*�t�@�C���|�C���^*/
 char inputfile[LENGTH] ;/*���̓t�@�C����*/
 int i,j ;/*�J�Ԃ��̐���*/
 int loopmax ;/*�J��Ԃ���*/

 /*�����̏�����*/
 srand(SEED) ;
 
 /*��������̏����l�̐ݒ�*/
 if(argc<2){
  /*����������Ȃ�*/
  fprintf(stderr,"�g����\n >makenewvec "
          "�P���ސ�n (�J�n�P��ԍ�s) (�t�@�C����)\n") ;
  exit(1);
 }
 fpi=stdin ;/*�f�t�H���g�͕W������*/
 n=atoi(argv[1]) ;/*��b�����Z�b�g*/
 if(argc>2) s=atoi(argv[2]) ;/*�J�n�P��ԍ�*/
 if(argc>3){/*���̓t�@�C���̃I�[�v��*/
  strncpy(inputfile,argv[3],LENGTH) ;/*���̓t�@�C��*/
  if((fpi=fopen(inputfile,"r"))==NULL){
   /*�t�@�C���I�[�v�����s*/
   fprintf(stderr,"%s:�t�@�C���I�[�v�����s\n",inputfile) ;
   exit(1);
  }
 }
  
 fprintf(stderr,"�P�ꐔ %d,�J�n�P��ԍ� %d\n",n,s) ;
 if((s>=n)||(s<0)){/*s���s�K��*/
   fprintf(stderr,"s=%d,s��1�ȏゎ�����ɂ��Ă�������\n",s) ;
   exit(1);
 }
 /*1-of-N�\���Ɋ�Â��P��̕��т̓ǂݍ���*/
 wn= read1ofn(fpi,n) ;/*�ǂݍ��݂Ɠ��͒P�ꑍ��wn�̃Z�b�g*/

 /*�P��A���i���j�̐���*/
 putvec(s,n) ;/*�J�n�L��*/

 for(i=0;i<WLIMIT;++i){
  /*s�ɑΉ�����P���T��*/
  loopmax=rndn(ULIMIT) ;/*�ő�ULIMIT��J��Ԃ�*/
  for(j=0;j<loopmax;++j)/*�����_���ɕ�����J��Ԃ�*/
   s=searchs(s,n,wn) ;
  /*�אڂ��鎟�̒P����o��*/
  ++ s ;
  if(s>=wn) s=0 ;/*�ŏ��ɖ߂�*/
  putvec(s,n) ;
 }

 return 0 ;
}

/**************************************/
/*   rndn()�֐�                       */
/*�����ȉ��̐���������Ԃ�            */
/**************************************/
int rndn(int n)
{
 double rndno ;/*������������*/

 while((rndno=(double)rand()/RAND_MAX)==1.0) ;
 return rndno*n ;
}

/**************************************/
/*   searcha()�֐�                    */
/*s�ɑΉ�����P���T��               */
/**************************************/
int searchs(int s,int n,int wn) 
{
 int i ;/*�J�Ԃ��̐���*/

 for(i=s+1;i<wn;++i)
  if(matchptn(i,s,n)==TRUE) return i ;
 for(i=0;i<=s;++i)
  if(matchptn(i,s,n)==TRUE) return i ;
 /*����������v���Ȃ�*/
 fprintf(stderr,"�����G���[�@searchs()�֐�\n") ;
 exit(1) ;
}

/**************************************/
/*   matchptn()�֐�                   */
/*�P��̈�v����������@              */
/**************************************/
int matchptn(int i,int s,int n) 
{
 int result=TRUE ;
 int index ;

 for(index=0;index<n;++index)
  if(ngram[i][index]!=ngram[s][index])
   result=FALSE ;/*�s��v*/
 return result ;
}


/**************************************/
/*   putvec()�֐�                     */
/*1-of-N�\���Ɋ�Â��P��̏o��        */
/**************************************/
void putvec(int nextn,int n) 
{
 int j=0 ;/*�J�Ԃ��̐���*/

 for(j=0;j<n;++j)
  printf("%1d ",ngram[nextn][j]);
 printf("\n") ;

}

/****************************************/
/*   read1ofn()�֐�                     */
/*1-of-N�\���Ɋ�Â��P��̕��т̓ǂݍ���*/
/****************************************/
int read1ofn(FILE *fpi,int n) 
{
 int e ;/*���̓x�N�g���̗v�f�̒l*/
 int i=0,j=0 ;/*�J�Ԃ��̐���*/

 while((fscanf(fpi,"%d",&e)!=EOF)&&(i<WN)){
  ngram[i][j]=e ;
  ++j ;
  if(j>=n){
   j=0 ; ++i ;
  }
 } 
 return i ;
}