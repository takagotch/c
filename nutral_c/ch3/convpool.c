/*********************************************************/
/*                   convpool.c                          */
/*��ݍ��݂ƃv�[�����O�̏���                             */
/*1-of-N�f�[�^��ǂݎ��A��ݍ��݂ƃv�[�����O���{���܂� */
/* �g�����@                                              */
/*  \Users\odaka\ch3>convpool  < data1.txt               */
/*********************************************************/

/*Visual Studio�Ƃ̌݊����m�� */
#define _CRT_SECURE_NO_WARNINGS

/* �w�b�_�t�@�C���̃C���N���[�h*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*�L���萔�̒�`*/
#define VOCSIZE 12  /*1-of-N�\���̌�b���i�����j*/ 
#define WORDLEN 7   /*1-of-N�\���̒P��̘A����*/
#define FILTERSIZE 3 /*�t�B���^�̑傫��*/
#define POOLSIZE 3 /*�v�[�����O�T�C�Y*/


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
void poolres(double poolout[][VOCSIZE]) ;/*�v�[�����O�o��*/
void pool(double convout[][VOCSIZE]
         ,double poolout[][VOCSIZE]) ; 
             /*�v�[�����O�̌v�Z*/           
double maxpooling(double convout[][VOCSIZE]
                 ,int i,int j) ;/* �ő�l�v�[�����O */
         
/*******************/ 
/*    main()�֐�   */ 
/*******************/ 
int main()
{
 double filter[FILTERSIZE][FILTERSIZE]
      ={{1,0,0},{0,1,0},{0,0,1}} ;/*���ڃt�B���^*/
//      ={{1,0,0},{1,0,0},{1,0,0}} ;/*�A���t�B���^*/
 double sentence[WORDLEN][VOCSIZE] ;/*���̓f�[�^*/
 double convout[WORDLEN][VOCSIZE]={0} ;/*��ݍ��ݏo��*/
 double poolout[WORDLEN][VOCSIZE]={0} ;/*�o�̓f�[�^*/
 
 
 /*���̓f�[�^�̓ǂݍ���*/
 getdata(sentence) ;
 
 /*��ݍ��݂̌v�Z*/
 conv(filter,sentence,convout) ;

 /*��ݍ��݉��Z�̌��ʏo��*/
 convres(convout) ;

 /*�v�[�����O�̌v�Z*/
 pool(convout,poolout) ;

 /*���ʂ̏o��*/
 poolres(poolout) ;
 
 return 0 ;
}

/**********************/
/*  poolres()�֐�     */
/* �@���ʏo��         */
/**********************/
void poolres(double poolout[][VOCSIZE]) 
{
 int i,j ;/*�J��Ԃ��̐���*/
 int startpoint=FILTERSIZE/2+POOLSIZE/2 ;
               /*�v�[�����O�v�Z�͈͂̉���*/

 for(i=startpoint;i<WORDLEN-startpoint;++i){
  for(j=startpoint;j<VOCSIZE-startpoint;++j)
   printf("%.3lf ",poolout[i][j]) ;  
  printf("\n") ;
 }
 printf("\n") ;	
} 

/**********************/
/*  pool()�֐�        */
/* �v�[�����O�̌v�Z   */
/**********************/
void pool(double convout[][VOCSIZE]
         ,double poolout[][VOCSIZE]) 
{
 int i,j ;/*�J��Ԃ��̐���*/
 int startpoint=FILTERSIZE/2+POOLSIZE/2 ;
                /*�v�[�����O�v�Z�͈͂̉���*/

 for(i=startpoint;i<WORDLEN-startpoint;++i)
  for(j=startpoint;j<VOCSIZE-startpoint;++j)
   poolout[i][j]=maxpooling(convout,i,j) ;
}

/**********************/
/* maxpooling()�֐�   */
/* �ő�l�v�[�����O   */
/**********************/
double maxpooling(double convout[][VOCSIZE]
                 ,int i,int j)
{
 int m,n ;/*�J��Ԃ��̐���p*/
 double max ;/*�ő�l*/
 
 max
 =convout[i+POOLSIZE/2][j+POOLSIZE/2];
 for(m=i-POOLSIZE/2;m<=i+POOLSIZE/2;++m)
  for(n=j-POOLSIZE/2;n<=j+POOLSIZE/2;++n)
   if(max<convout[m][n]) max=convout[m][n] ;

 return max ;
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

