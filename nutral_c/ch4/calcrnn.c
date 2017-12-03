/*********************************************************/
/*                   calcrnn.c�@                         */
/*�@���J�����g�j���[�����l�b�g���[�N                     */
/*�@�w�K�ς݂̃l�b�g���[�N���v�Z���܂�                   */
/* �g�����@                                              */
/*  \Users\odaka\ch4>calcrnn 2 < data.txt �@             */
/*�@�R�}���h���C�������Ƃ��āA�J�n�P��̔ԍ���^���܂�   */
/*********************************************************/

/*Visual Studio�Ƃ̌݊����m�� */
#define _CRT_SECURE_NO_WARNINGS

/* �w�b�_�t�@�C���̃C���N���[�h*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*�L���萔�̒�`*/
#define INPUTNO 5  /*���̗͂v�f��*/
#define HIDDENNO 5  /*���ԑw�̃Z����*/
#define OUTPUTNO 5  /*�o�͑w�̃Z����*/
#define WORDLEN 50 /*�P��A����*/

/*�֐��̃v���g�^�C�v�̐錾*/
double f(double u) ; /*�`�B�֐��i�V�O���C�h�֐��j*/
void print(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
          ,double wo[OUTPUTNO][HIDDENNO+1]) ; /*���ʂ̏o��*/
double forward(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[]) ; /*�������̌v�Z*/
void readwh(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]) ;
                         /*���ԑw�̏d�݂̓ǂݍ���*/
void readwo(double wo[OUTPUTNO][HIDDENNO+1]) ;
                         /*�o�͑w�̏d�݂̓ǂݍ���*/
void  putword(double inputdata[]) ;
       /*�P�ꕔ���݂̂�1-of-N�\���ŕ\��*/


/*******************/
/*    main()�֐�   */
/*******************/
int main(int argc,char *argv[])
{
 double wh[HIDDENNO][INPUTNO+1+HIDDENNO] ;/*���ԑw�̏d��*/
 double wo[OUTPUTNO][HIDDENNO+1] ;/*�o�͑w�̏d��*/
 double hi[HIDDENNO+1]={0} ;/*���ԑw�̏o��*/
 double o[OUTPUTNO] ;/*�o��*/
 double inputdata[INPUTNO+HIDDENNO]={0} ;/*����*/
 int i,j ;/*�J��Ԃ��̐���*/
 int startno ; /*�J�n�P��̔ԍ�*/

 /*�J�n�P��̎w��*/
 if(argc<2){
  startno=0 ;/*�w�肪�����ꍇ��0�Ԃ���J�n*/
 }
 else{
  startno=atoi(argv[1]) ;
  if((startno<0) || (startno>=INPUTNO)){
   /*�J�n�P��w��̃G���[*/
   fprintf(stderr,"�J�n�P��̎w��l(%d)���Ԉ���Ă��܂�\n",startno) ;
   exit(1) ;
  }
 }   
 inputdata[startno]=1.0 ;

 /*�d�݂̓ǂݍ���*/
 readwh(wh) ;/*���ԑw�̏d�݂̓ǂݍ���*/
 readwo(wo) ;/*�o�͑w�̏d�݂̓ǂݍ���*/


 /*������*/
 for(i=0;i<WORDLEN;++i){
  /*���̓f�[�^��\��*/
  /*�K�v�Ȃ�Έȉ���3�s�̃R�����g���O��*/
//  for(j=0;j<INPUTNO+HIDDENNO;++j)
//   printf("%.3lf ",inputdata[j]) ;
//  printf("\n") ;
  /*�P�ꕔ���݂̂�1-of-N�\���ŕ\��*/
  putword(inputdata) ;
  /*�������̌v�Z*/
  for(j=0;j<OUTPUTNO;++j)
   o[j]=forward(wh,wo[j],hi,inputdata) ;
  /*�O��̏o�͂���͂ɃZ�b�g*/
  for(j=0;j<HIDDENNO;++j)
    inputdata[j]=o[j] ;
  /*�O��̒��ԑw�o�͂���͂ɒǉ�*/
  for(j=0;j<HIDDENNO;++j)
    inputdata[INPUTNO+j]=hi[j] ;
 }

 return 0 ;
}

/********************************/
/*   putword()�֐�              */
/*�P�ꕔ���݂̂�1-of-N�\���ŕ\��*/
/********************************/
void  putword(double inputdata[])
{
 int i ;/*�J��Ԃ��̐���*/
 int maxindex=0 ;/*�ő�l�v�f�̓Y�����ԍ�*/
 double max=inputdata[0] ;/*�ő�l*/

 /*�ő�ƂȂ�v�f�𒲂ׂ�*/
 for(i=1;i<INPUTNO;++i)
  if(max<inputdata[i]){
   max=inputdata[i] ;
   maxindex=i ;
  }
 /*1-of-N�\���ŒP����o��*/
 for(i=0;i<INPUTNO;++i){
  if(i==maxindex) printf("1 ") ;
  else printf("0 ") ;
 }
 printf("\n") ;

}

/**********************/
/*  forward()�֐�     */
/*  �������̌v�Z      */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
 ,double wo[HIDDENNO+1],double hi[],double e[])
{
 int i,j ;/*�J��Ԃ��̐���*/
 double u ;/*�d�ݕt���a�̌v�Z*/
 double o ;/*�o�͂̌v�Z*/

 /*hi�̌v�Z*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*�d�ݕt���a�����߂�*/
  for(j=0;j<INPUTNO+HIDDENNO;++j)
   u+=e[j]*wh[i][j] ;
  u-=wh[i][j] ;/*�������l�̏���*/
  hi[i]=f(u) ;
 }
 /*�o��o�̌v�Z*/
 o=0 ;
 for(i=0;i<HIDDENNO;++i)
  o+=hi[i]*wo[i] ;
 o-=wo[i] ;/*�������l�̏���*/
 
 return f(o) ;
}

/************************/
/*    readwh()�֐�      */
/*���ԑw�̏d�݂̓ǂݍ���*/
/************************/
void readwh(double wh[HIDDENNO][INPUTNO+1+HIDDENNO])
{
 int i,j ;/*�J��Ԃ��̐���*/

  for(i=0;i<HIDDENNO;++i){
  for(j=0;j<INPUTNO+1+HIDDENNO;++j)
   scanf("%lf",&(wh[i][j])) ;
 }
}

/************************/
/*    readwo()�֐�      */
/*�o�͑w�̏d�݂̓ǂݍ���*/
/************************/
void readwo(double wo[OUTPUTNO][HIDDENNO+1])
{
 int i,j ;/*�J��Ԃ��̐���*/

 for(i=0;i<OUTPUTNO;++i){
  for(j=0;j<HIDDENNO+1;++j)
   scanf("%lf",&(wo[i][j])) ;
 }
}

/*******************/
/* f()�֐�         */
/* �`�B�֐�        */
/*(�V�O���C�h�֐�) */
/*******************/
double f(double u)
{
 return 1.0/(1.0+exp(-u)) ;
}





