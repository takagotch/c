/*********************************************************/
/*                      cnn.c�@                          */
/* ��ݍ��݉��Z�𔺂��j���[�����l�b�g                    */
/* �g�����@                                              */
/*  \Users\odaka\ch3>cnn < data.txt > result.txt         */
/*�@�덷�̐��ڂ�C�w�K���ʂƂȂ錋���W���Ȃǂ��o�͂��܂� */
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
#define FILTERNO 2 /*�t�B���^�̌�*/

#define INPUTNO 48 /*���͑w�̃Z����*/
  /*��b���ƒP��A�������猈��i(12-2-2)*(7-2-2))*FILTERNO*/ 
#define HIDDENNO 2  /*���ԑw�̃Z����*/ 
#define ALPHA  10  /*�w�K�W��*/ 
#define SEED 7    /*�����̃V�[�h*/ 
#define MAXINPUTNO 100    /*�w�K�f�[�^�̍ő��*/ 
#define BIGNUM 100    /*�덷�̏����l*/ 
#define LIMIT 0.01    /*�덷�̏���l*/ 

/*�֐��̃v���g�^�C�v�̐錾*/
void convpool(double s[WORDLEN][VOCSIZE],
              double mfilter[FILTERNO][FILTERSIZE][FILTERSIZE],
              double se[INPUTNO+1],
              double teacher) ;/*��ݍ��݂ƃv�[�����O*/
void conv(double filter[][FILTERSIZE]
   ,double sentence[][VOCSIZE]
   ,double convout[][VOCSIZE]) ; /*��ݍ��݂̌v�Z*/
double calcconv(double filter[][FILTERSIZE]
               ,double sentence[][VOCSIZE],int i,int j) ;
                               /*  �t�B���^�̓K�p  */
void convres(double convout[][VOCSIZE]) ;
              /*��ݍ��݂̌��ʏo��*/
int getdata(double sentence[MAXINPUTNO][WORDLEN][VOCSIZE],
            double teacher[MAXINPUTNO]);/*�f�[�^�ǂݍ���*/ 
void poolres(double poolout[][VOCSIZE]) ;/*�v�[�����O�o��*/
void pool(double convout[][VOCSIZE]
         ,double poolout[][VOCSIZE]) ; 
             /*�v�[�����O�̌v�Z*/           
double maxpooling(double convout[][VOCSIZE]
                 ,int i,int j) ;/* �ő�l�v�[�����O */
         
double f(double u) ; /*�`�B�֐��i�V�O���C�h�֐��j*/
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
void hlearn(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO+1],double o) ; /*���ԑw�̏d�݂̒���*/

/*******************/ 
/*    main()�֐�   */ 
/*******************/ 
int main()
{
 double mfilter[FILTERNO][FILTERSIZE][FILTERSIZE]
      ={
        {{1,0,0},{0,1,0},{0,0,1}} ,
        {{1,0,0},{1,0,0},{1,0,0}} 
       };/*�t�B���^�Q*/
 double sentence[MAXINPUTNO][WORDLEN][VOCSIZE] ;/*���̓f�[�^*/
 double convout[WORDLEN][VOCSIZE]={0} ;/*��ݍ��ݏo��*/
 double poolout[WORDLEN][VOCSIZE]={0} ;/*�o�̓f�[�^*/

 double teacher[MAXINPUTNO] ;/*���t�f�[�^*/
 double wh[HIDDENNO][INPUTNO+1] ;/*���ԑw�̏d��*/
 double wo[HIDDENNO+1] ;/*�o�͑w�̏d��*/
 double e[MAXINPUTNO][INPUTNO+1] ;/*�w�K�f�[�^�Z�b�g*/
 double hi[HIDDENNO+1] ;/*���ԑw�̏o��*/
 double o ;/*�o��*/
 double err=BIGNUM ;/*�덷�̕]��*/
 int i,j ;/*�J��Ԃ��̐���*/
 int n_of_e ;/*�w�K�f�[�^�̌�*/
 int count=0 ;/*�J��Ԃ��񐔂̃J�E���^*/

 /*�����̏�����*/
 srand(SEED) ;

 /*�d�݂̏�����*/
 initwh(wh) ;/*���ԑw�̏d�݂̏�����*/
 initwo(wo) ;/*�o�͑w�̏d�݂̏�����*/
 print(wh,wo) ; /*���ʂ̏o��*/

 /*�w�K�f�[�^�̓ǂݍ���*/
 n_of_e=getdata(sentence,teacher) ;
 printf("�w�K�f�[�^�̌�:%d\n",n_of_e) ;

 /*��ݍ��݂ƃv�[�����O�̌v�Z*/
 for(i=0;i<n_of_e;++i){
  convpool(sentence[i],mfilter,e[i],teacher[i]) ;
 }

 /*�w�K*/
 while(err>LIMIT){
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
  printf("%d\n",i) ;
  for(j=0;j<INPUTNO+1;++j)
   printf("%lf ",e[i][j]) ;
  printf("\n") ;
  o=forward(wh,wo,hi,e[i]) ;
  printf("%lf\n\n",o) ;
 }

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

/************************/
/*  convpool()�֐�      */
/*  ��ݍ��݂ƃv�[�����O*/
/************************/
void convpool(double s[WORDLEN][VOCSIZE],
              double mfilter[FILTERNO][FILTERSIZE][FILTERSIZE],
              double se[INPUTNO+1],
              double teacher)
{
 int i,j,k;
 int startpoint=FILTERSIZE/2+POOLSIZE/2 ;
               /*�v�[�����O�v�Z�͈͂̉���*/
 /*�e�t�B���^��p���ď�ݍ��݂ƃv�[�����O�����s*/
 for(i=0;i<FILTERNO;++i){ 
  double convout[WORDLEN][VOCSIZE]={0} ;/*��ݍ��ݏo��*/
  double poolout[WORDLEN][VOCSIZE]={0} ;/*�o�̓f�[�^*/
  /*��ݍ��݂̌v�Z*/
  conv(mfilter[i],s,convout) ;

  /*��ݍ��݉��Z�̌��ʏo��*/
  convres(convout) ;

  /*�v�[�����O�̌v�Z*/
  pool(convout,poolout) ;

  /*���ʂ̏o��*/
  poolres(poolout) ;

  /*��ݍ��݌v�Z�̌��ʂ��A�S�������ւ̓��͂Ƃ��đ��*/
  for(j=startpoint;j<WORDLEN-startpoint;++j){
   for(k=startpoint;k<VOCSIZE-startpoint;++k)
    se[i*INPUTNO/FILTERNO+(j-startpoint)*(VOCSIZE-startpoint*2)+(k-startpoint)]
      =poolout[j][k];    
  }
 }  /*���t�f�[�^�̑��*/
 se[i*INPUTNO/FILTERNO]=teacher ;

}



/**********************/
/*  hlearn()�֐�      */
/*  ���ԑw�̏d�݊w�K  */
/**********************/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
    ,double wo[HIDDENNO+1]
    ,double hi[],double e[INPUTNO+1],double o)
{
 int i,j ;/*�J��Ԃ��̐���*/
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
int getdata(double sentence[MAXINPUTNO][WORDLEN][VOCSIZE],
            double teacher[MAXINPUTNO])
{
 int i=0,j=0,k=0 ;/*�J��Ԃ��̐���p*/

 /*�f�[�^�̓���*/
 while(scanf("%lf",&teacher[i])!=EOF){/*���t�f�[�^�̓ǂݍ���*/
  /*�P���f�[�^�̓ǂݍ���*/
  while(scanf("%lf",&sentence[i][j][k])!=EOF){
   ++ k ;
   if(k>=VOCSIZE){/*���̃f�[�^*/
    k=0 ;
    ++j ;
    if(j>=WORDLEN) break ;/*���͏I��*/
   }
  }
  j=0; k=0 ;
  ++i ; 
  if(i>MAXINPUTNO) break ;/*���͏I��*/
 }
 return i ;

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
  hi[i]=f(u) ;
 }
 /*�o��o�̌v�Z*/
 o=0 ;
 for(i=0;i<HIDDENNO;++i)
  o+=hi[i]*wo[i] ;
 o-=wo[i] ;/*�������l�̏���*/
 
 return f(o) ;
} 

/**********************/
/*   print()�֐�      */
/*   ���ʂ̏o��       */
/**********************/
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[HIDDENNO+1])
{
 int i,j ;/*�J��Ԃ��̐���*/

 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<INPUTNO+1;++j)
   printf("%lf ",wh[i][j]) ;
 printf("\n") ;
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
/* f()�֐�         */
/* �`�B�֐�        */
/*(�V�O���C�h�֐�) */
/*******************/
double f(double u)
{
 return 1.0/(1.0+exp(-u)) ;
}



