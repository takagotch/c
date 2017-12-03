/*********************************************************/
/*                   conv.c                              */
/*�@��ݍ��ݏ���                                         */
/*�@1-of-N�f�[�^��ǂݎ��A��ݍ��݂��{���܂��@�@�@�@�@*/
/* �g�����@                                              */
/*  \Users\odaka\ch3>conv  < data1.txt                   */
/*********************************************************/

/*Visual Studio�Ƃ̌݊����m�� */
#define _CRT_SECURE_NO_WARNINGS

/* �w�b�_�t�@�C���̃C���N���[�h*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*�L���萔�̒�`*/
#define VOCSIZE 12  /*1-of-N�\���̌�b���i�����j*/ 
#define WORDLEN 5   /*1-of-N�\���̒P��̘A����*/
#define FILTERSIZE 3 /*�t�B���^�̑傫��*/

/*�֐��̃v���g�^�C�v�̐錾*/
void conv(double filter[][FILTERSIZE]
   ,double sentence[][VOCSIZE]
   ,double convout[][VOCSIZE]) ; /*��ݍ��݂̌v�Z*/
double calcconv(double filter[][FILTERSIZE]
               ,double sentence[][VOCSIZE],int i,int j) ;
                               /*  �t�B���^�̓K�p  */
void convres(double convout[][VOCSIZE]) ;
              /*��ݍ��݂̌��ʏo��*/
void getdata(double sentence[][VOCSIZE]) ;/*�f�[�^�ǂݍ���*/ 
         
/*******************/ 
/*    main()�֐�   */ 
/*******************/ 
int main()
{
 double filter[FILTERSIZE][FILTERSIZE]
//      ={{1,0,0},{0,1,0},{0,0,1}} ;/*���ڃt�B���^*/
      ={{1,0,0},{1,0,0},{1,0,0}} ;/*�A���t�B���^*/
 double sentence[WORDLEN][VOCSIZE] ;/*���̓f�[�^*/
 double convout[WORDLEN][VOCSIZE]={0} ;/*��ݍ��ݏo��*/
 
 
 /*���̓f�[�^�̓ǂݍ���*/
 getdata(sentence) ;
 
 /*��ݍ��݂̌v�Z*/
 conv(filter,sentence,convout) ;

 /*���ʂ̏o��*/
 convres(convout) ;
 
 return 0 ;
}

/**********************/
/*  convres()�֐�     */
/* ��ݍ��݂̌��ʏo�� */
/**********************/
void convres(double convout[][VOCSIZE]) 
{
 int i,j ;/*�J��Ԃ��̐���*/
 int startpoint=FILTERSIZE/2 ;/*�o�͔͈͂̉���*/
 
 for(i=startpoint;i<WORDLEN-1;++i){
  for(j=startpoint;j<VOCSIZE-1;++j){
   printf("%.3lf ",convout[i][j]) ;
  }
  printf("\n") ;
 }
 printf("\n") ;	
} 
              
/**********************/
/*  getdata()�֐�     */
/*���̓f�[�^�̓ǂݍ���*/
/**********************/
void getdata(double e[][VOCSIZE])
{
 int i=0,j=0 ;/*�J��Ԃ��̐���p*/

 /*�f�[�^�̓���*/
 while(scanf("%lf",&e[i][j])!=EOF){
  ++ j ;
  if(j>=VOCSIZE){/*���̃f�[�^*/
   j=0 ;
   ++i ;
   if(i>=WORDLEN) break ;/*���͏I��*/
  }
 }
}

/**********************/
/*  conv()�֐�        */
/*  ��ݍ��݂̌v�Z    */
/**********************/
void conv(double filter[][FILTERSIZE]
         ,double sentence[][VOCSIZE],double convout[][VOCSIZE])
{
 int i=0,j=0 ;/*�J��Ԃ��̐���p*/
 int startpoint=FILTERSIZE/2 ;/*��ݍ��ݔ͈͂̉���*/

 for(i=startpoint;i<WORDLEN-startpoint;++i)
  for(j=startpoint;j<VOCSIZE-startpoint;++j)
   convout[i][j]=calcconv(filter,sentence,i,j) ;
}

/**********************/
/*  calcconv()�֐�    */
/*  �t�B���^�̓K�p    */
/**********************/
double calcconv(double filter[][FILTERSIZE]
             ,double sentence[][VOCSIZE],int i,int j)
{
 int m,n ;/*�J��Ԃ��̐���p*/
 double sum=0 ;/*�a�̒l*/
 
 for(m=0;m<FILTERSIZE;++m)
  for(n=0;n<FILTERSIZE;++n)
   sum+=sentence[i-FILTERSIZE/2+m][j-FILTERSIZE/2+n]*filter[m][n];
   
 return sum ;
}

