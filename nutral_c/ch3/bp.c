/*********************************************************/
/*                      bp.c�@                            */
/*�@�o�b�N�v���p�Q�[�V�����ɂ��j���[�����l�b�g�̊w�K   */
/* �g�����@                                              */
/*  \Users\odaka\ch3>bp < data.txt > result.txt          */
/*�@�덷�̐��ڂ�C�w�K���ʂƂȂ錋���W���Ȃǂ��o�͂��܂� */
/*********************************************************/

/*Visual Studio�Ƃ̌݊����m�� */
#define _CRT_SECURE_NO_WARNINGS

/* �w�b�_�t�@�C���̃C���N���[�h*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*�L���萔�̒�`*/
#define INPUTNO 2  /*���͑w�̃Z����*/ 
#define HIDDENNO 2  /*���ԑw�̃Z����*/ 
#define ALPHA  10  /*�w�K�W��*/ 
#define SEED 65535    /*�����̃V�[�h*/ 
#define MAXINPUTNO 100    /*�w�K�f�[�^�̍ő��*/ 
#define BIGNUM 100    /*�덷�̏����l*/ 
#define LIMIT 0.001    /*�덷�̏���l*/ 

/*�֐��̃v���g�^�C�v�̐錾*/
double fs(double u) ; /*�`�B�֐��i�V�O���C�h�֐��j*/
void initwh(double wh[HIDDENNO][INPUTNO+1]) ;
                         /*���ԑw�̏d�݂̏�����*/
void initwo(double wo[HIDDENNO+1]) ;/*�o�͑w�̏d�݂̏�����*/
double drnd(void) ;/* �����̐���     */
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[HIDDENNO+1]) ; /*���ʂ̏o��*/
double forward(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO+1]) ; /*�������̌v�Z*/
void olearn(double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO+1],double o) ; /*�o�͑w�̏d�݂̒���*/
int getdata(double e[][INPUTNO+1]) ; /*�w�K�f�[�^�̓ǂݍ���*/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO+1],double o) ; /*���ԑw�̏d�݂̒���*/

/*******************/ 
/*    main()�֐�   */ 
/*******************/ 
int main()
{
 double wh[HIDDENNO][INPUTNO+1] ;/*���ԑw�̏d��*/
 double wo[HIDDENNO+1] ;/*�o�͑w�̏d��*/
 double e[MAXINPUTNO][INPUTNO+1] ;/*�w�K�f�[�^�Z�b�g*/
 double hi[HIDDENNO+1] ;/*���ԑw�̏o��*/
 double o ;/*�o��*/
 double err=BIGNUM ;/*�덷*/
 int i,j ;/*�J��Ԃ��̐���ϐ�*/
 int n_of_e ;/*�w�K�f�[�^�̌�*/
 int count=0 ;/*�J��Ԃ��񐔂̃J�E���^*/

 /*�����̏�����*/
 srand(SEED) ;

 /*�d�݂̏�����*/
 initwh(wh) ;/*���ԑw�̏d�݂̏�����*/
 initwo(wo) ;/*�o�͑w�̏d�݂̏�����*/
 print(wh,wo) ; /*�d�݂̏o��*/

 /*�w�K�f�[�^�̓ǂݍ���*/
 n_of_e=getdata(e) ;
 printf("�w�K�f�[�^�̌�:%d\n",n_of_e) ;

 /*�w�K*/
 while(err>LIMIT){/*�덷����������܂ŌJ��Ԃ�*/
  err=0.0 ;
  for(j=0;j<n_of_e;++j){
   /*�������̌v�Z*/
   o=forward(wh,wo,hi,e[j]) ;
   /*�o�͑w�̏d�݂̒���*/
   olearn(wo,hi,e[j],o) ;
   /*���ԑw�̏d�݂̒���*/
   hlearn(wh,wo,hi,e[j],o) ;
   /*�덷�̐ώZ*/
   err+=(o-e[j][INPUTNO])*(o-e[j][INPUTNO]) ;
  }
  ++count ;
  /*�덷�̏o��*/
  fprintf(stderr,"%d\t%lf\n",count,err) ;
 }/*�w�K�I��*/

 /*�����׏d�̏o��*/
 print(wh,wo) ; 

 /*�w�K�f�[�^�ɑ΂���o��*/
 for(i=0;i<n_of_e;++i){
  printf("%d ",i) ;
  for(j=0;j<INPUTNO+1;++j)
   printf("%lf ",e[i][j]) ;
  o=forward(wh,wo,hi,e[i]) ;
  printf("%lf\n",o) ;
 }

 return 0 ;
}

/**********************/
/*  hlearn()�֐�      */
/*  ���ԑw�̏d�݊w�K  */
/**********************/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
    ,double wo[HIDDENNO+1]
    ,double hi[],double e[INPUTNO+1],double o)
{
 int i,j ;/*�J��Ԃ��̐���ϐ�*/
 double dj ;/*���ԑw�̏d�݌v�Z�ɗ��p*/

 for(j=0;j<HIDDENNO;++j){/*���ԑw�̊e�Z��j��Ώ�*/
  dj=hi[j]*(1-hi[j])*wo[j]*(e[INPUTNO]-o)*o*(1-o) ;
  for(i=0;i<INPUTNO;++i)/*i�Ԗڂ̏d�݂�����*/
   wh[j][i]+=ALPHA*e[i]*dj ;
  wh[j][i]+=ALPHA*(-1.0)*dj ;/*�������l�̊w�K*/
 }
}


/**********************/
/*  getdata()�֐�     */
/*�w�K�f�[�^�̓ǂݍ���*/
/**********************/
int getdata(double e[][INPUTNO+1])
{
 int n_of_e=0 ;/*�f�[�^�Z�b�g�̌�*/
 int i=0 ;/*�J��Ԃ��̐���p�ϐ�*/

 /*�f�[�^�̓���*/
 while(scanf("%lf",&e[n_of_e][i])!=EOF){
  ++ i ;
  if(i>INPUTNO){/*���̃f�[�^*/
   i=0 ;
   ++n_of_e ;
  }
 }
 return n_of_e ;
}

/**********************/
/*  olearn()�֐�      */
/*  �o�͑w�̏d�݊w�K  */
/**********************/
void olearn(double wo[HIDDENNO+1]
    ,double hi[],double e[INPUTNO+1],double o)
{
 int i ;/*�J��Ԃ��̐���*/
 double d ;/*�d�݌v�Z�ɗ��p*/

 d=(e[INPUTNO]-o)*o*(1-o) ;/*�덷�̌v�Z*/
 for(i=0;i<HIDDENNO;++i){
  wo[i]+=ALPHA*hi[i]*d ;/*�d�݂̊w�K*/
 }
 wo[i]+=ALPHA*(-1.0)*d ;/*�������l�̊w�K*/
 
} 


/**********************/
/*  forward()�֐�     */
/*  �������̌v�Z      */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO+1]
 ,double wo[HIDDENNO+1],double hi[],double e[INPUTNO+1])
{
 int i,j ;/*�J��Ԃ��̐���*/
 double u ;/*�d�ݕt���a�̌v�Z*/
 double o ;/*�o�͂̌v�Z*/

 /*hi�̌v�Z*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*�d�ݕt���a�����߂�*/
  for(j=0;j<INPUTNO;++j)
   u+=e[j]*wh[i][j] ; 
  u-=wh[i][j] ;/*�������l�̏���*/
  hi[i]=fs(u) ;
 }
 /*�o��o�̌v�Z*/
 o=0 ;
 for(i=0;i<HIDDENNO;++i)
  o+=hi[i]*wo[i] ;
 o-=wo[i] ;/*�������l�̏���*/
 
 return fs(o) ;
} 

/**********************/
/*   print()�֐�      */
/*   ���ʂ̏o��       */
/**********************/
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[HIDDENNO+1])
{
 int i,j ;/*�J��Ԃ��̐���*/

 /*���ԑw�̏d�݂̏o��*/
 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<INPUTNO+1;++j)
   printf("%lf ",wh[i][j]) ;
 printf("\n") ;
 /*�o�͑w�̏d�݂̏o��*/
 for(i=0;i<HIDDENNO+1;++i)
  printf("%lf ",wo[i]) ;
 printf("\n") ;
} 

/**********************/
/*    initwh()�֐�    */
/*���ԑw�̏d�݂̏�����*/
/**********************/
void initwh(double wh[HIDDENNO][INPUTNO+1])
{
 int i,j ;/*�J��Ԃ��̐���*/

 /*�����ɂ��d�݂̌���*/ 
 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<INPUTNO+1;++j)
   wh[i][j]=drnd() ;
} 

/**********************/
/*    initwo()�֐�    */
/*�o�͑w�̏d�݂̏�����*/
/**********************/
void initwo(double wo[HIDDENNO+1])
{
 int i ;/*�J��Ԃ��̐���*/

 /*�����ɂ��d�݂̌���*/
 for(i=0;i<HIDDENNO+1;++i)
   wo[i]=drnd() ;
} 

/*******************/
/* drnd()�֐�      */
/* �����̐���      */
/*******************/
double drnd(void)
{
 double rndno ;/*������������*/

 while((rndno=(double)rand()/RAND_MAX)==1.0) ;
 rndno=rndno*2-1 ;/*-1����1�̊Ԃ̗����𐶐�*/
 return rndno; 
}

/*******************/
/* fs()�֐�        */
/* �`�B�֐�        */
/*(�V�O���C�h�֐�) */
/*******************/
double fs(double u)
{
 return 1.0/(1.0+exp(-u)) ;
}


