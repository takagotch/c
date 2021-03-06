/*********************************************************/
/*                      cnn.c　                          */
/* 畳み込み演算を伴うニューラルネット                    */
/* 使い方　                                              */
/*  \Users\odaka\ch3>cnn < data.txt > result.txt         */
/*　誤差の推移や，学習結果となる結合係数などを出力します */
/*********************************************************/

/*Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

/* ヘッダファイルのインクルード*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*記号定数の定義*/
#define VOCSIZE 12  /*1-of-N表現の語彙数（次数）*/ 
#define WORDLEN 7   /*1-of-N表現の単語の連鎖数*/
#define FILTERSIZE 3 /*フィルタの大きさ*/
#define POOLSIZE 3 /*プーリングサイズ*/
#define FILTERNO 2 /*フィルタの個数*/

#define INPUTNO 48 /*入力層のセル数*/
  /*語彙数と単語連鎖数から決定（(12-2-2)*(7-2-2))*FILTERNO*/ 
#define HIDDENNO 2  /*中間層のセル数*/ 
#define ALPHA  10  /*学習係数*/ 
#define SEED 7    /*乱数のシード*/ 
#define MAXINPUTNO 100    /*学習データの最大個数*/ 
#define BIGNUM 100    /*誤差の初期値*/ 
#define LIMIT 0.01    /*誤差の上限値*/ 

/*関数のプロトタイプの宣言*/
void convpool(double s[WORDLEN][VOCSIZE],
              double mfilter[FILTERNO][FILTERSIZE][FILTERSIZE],
              double se[INPUTNO+1],
              double teacher) ;/*畳み込みとプーリング*/
void conv(double filter[][FILTERSIZE]
   ,double sentence[][VOCSIZE]
   ,double convout[][VOCSIZE]) ; /*畳み込みの計算*/
double calcconv(double filter[][FILTERSIZE]
               ,double sentence[][VOCSIZE],int i,int j) ;
                               /*  フィルタの適用  */
void convres(double convout[][VOCSIZE]) ;
              /*畳み込みの結果出力*/
int getdata(double sentence[MAXINPUTNO][WORDLEN][VOCSIZE],
            double teacher[MAXINPUTNO]);/*データ読み込み*/ 
void poolres(double poolout[][VOCSIZE]) ;/*プーリング出力*/
void pool(double convout[][VOCSIZE]
         ,double poolout[][VOCSIZE]) ; 
             /*プーリングの計算*/           
double maxpooling(double convout[][VOCSIZE]
                 ,int i,int j) ;/* 最大値プーリング */
         
double f(double u) ; /*伝達関数（シグモイド関数）*/
void initwh(double wh[HIDDENNO][INPUTNO+1]) ;
                         /*中間層の重みの初期化*/
void initwo(double wo[HIDDENNO+1]) ;/*出力層の重みの初期化*/
double drnd(void) ;/* 乱数の生成     */
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[HIDDENNO+1]) ; /*結果の出力*/
double forward(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO+1]) ; /*順方向の計算*/
void olearn(double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO+1],double o) ; /*出力層の重みの調整*/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO+1],double o) ; /*中間層の重みの調整*/

/*******************/ 
/*    main()関数   */ 
/*******************/ 
int main()
{
 double mfilter[FILTERNO][FILTERSIZE][FILTERSIZE]
      ={
        {{1,0,0},{0,1,0},{0,0,1}} ,
        {{1,0,0},{1,0,0},{1,0,0}} 
       };/*フィルタ群*/
 double sentence[MAXINPUTNO][WORDLEN][VOCSIZE] ;/*入力データ*/
 double convout[WORDLEN][VOCSIZE]={0} ;/*畳み込み出力*/
 double poolout[WORDLEN][VOCSIZE]={0} ;/*出力データ*/

 double teacher[MAXINPUTNO] ;/*教師データ*/
 double wh[HIDDENNO][INPUTNO+1] ;/*中間層の重み*/
 double wo[HIDDENNO+1] ;/*出力層の重み*/
 double e[MAXINPUTNO][INPUTNO+1] ;/*学習データセット*/
 double hi[HIDDENNO+1] ;/*中間層の出力*/
 double o ;/*出力*/
 double err=BIGNUM ;/*誤差の評価*/
 int i,j ;/*繰り返しの制御*/
 int n_of_e ;/*学習データの個数*/
 int count=0 ;/*繰り返し回数のカウンタ*/

 /*乱数の初期化*/
 srand(SEED) ;

 /*重みの初期化*/
 initwh(wh) ;/*中間層の重みの初期化*/
 initwo(wo) ;/*出力層の重みの初期化*/
 print(wh,wo) ; /*結果の出力*/

 /*学習データの読み込み*/
 n_of_e=getdata(sentence,teacher) ;
 printf("学習データの個数:%d\n",n_of_e) ;

 /*畳み込みとプーリングの計算*/
 for(i=0;i<n_of_e;++i){
  convpool(sentence[i],mfilter,e[i],teacher[i]) ;
 }

 /*学習*/
 while(err>LIMIT){
  err=0.0 ;
  for(j=0;j<n_of_e;++j){
   /*順方向の計算*/
   o=forward(wh,wo,hi,e[j]) ;
   /*出力層の重みの調整*/
   olearn(wo,hi,e[j],o) ;
   /*中間層の重みの調整*/
   hlearn(wh,wo,hi,e[j],o) ;
   /*誤差の積算*/
   err+=(o-e[j][INPUTNO])*(o-e[j][INPUTNO]) ;
  }
  ++count ;
  /*誤差の出力*/
  fprintf(stderr,"%d\t%lf\n",count,err) ;
 }/*学習終了*/

 /*結合荷重の出力*/
 print(wh,wo) ; 

 /*学習データに対する出力*/
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
/*  poolres()関数     */
/* 　結果出力         */
/**********************/
void poolres(double poolout[][VOCSIZE]) 
{
 int i,j ;/*繰り返しの制御*/
 int startpoint=FILTERSIZE/2+POOLSIZE/2 ;
               /*プーリング計算範囲の下限*/

 for(i=startpoint;i<WORDLEN-startpoint;++i){
  for(j=startpoint;j<VOCSIZE-startpoint;++j)
   printf("%.3lf ",poolout[i][j]) ;  
  printf("\n") ;
 }
 printf("\n") ;	
} 

/**********************/
/*  pool()関数        */
/* プーリングの計算   */
/**********************/
void pool(double convout[][VOCSIZE]
         ,double poolout[][VOCSIZE]) 
{
 int i,j ;/*繰り返しの制御*/
 int startpoint=FILTERSIZE/2+POOLSIZE/2 ;
                /*プーリング計算範囲の下限*/

 for(i=startpoint;i<WORDLEN-startpoint;++i)
  for(j=startpoint;j<VOCSIZE-startpoint;++j)
   poolout[i][j]=maxpooling(convout,i,j) ;
}

/**********************/
/* maxpooling()関数   */
/* 最大値プーリング   */
/**********************/
double maxpooling(double convout[][VOCSIZE]
                 ,int i,int j)
{
 int m,n ;/*繰り返しの制御用*/
 double max ;/*最大値*/
 
 max
 =convout[i+POOLSIZE/2][j+POOLSIZE/2];
 for(m=i-POOLSIZE/2;m<=i+POOLSIZE/2;++m)
  for(n=j-POOLSIZE/2;n<=j+POOLSIZE/2;++n)
   if(max<convout[m][n]) max=convout[m][n] ;

 return max ;
}
 

/**********************/
/*  convres()関数     */
/* 畳み込みの結果出力 */
/**********************/
void convres(double convout[][VOCSIZE]) 
{
 int i,j ;/*繰り返しの制御*/
 int startpoint=FILTERSIZE/2 ;/*出力範囲の下限*/
 
 for(i=startpoint;i<WORDLEN-1;++i){
  for(j=startpoint;j<VOCSIZE-1;++j){
   printf("%.3lf ",convout[i][j]) ;
  }
  printf("\n") ;
 }
 printf("\n") ;	
} 

/**********************/
/*  conv()関数        */
/*  畳み込みの計算    */
/**********************/
void conv(double filter[][FILTERSIZE]
         ,double sentence[][VOCSIZE],double convout[][VOCSIZE])
{
 int i=0,j=0 ;/*繰り返しの制御用*/
 int startpoint=FILTERSIZE/2 ;/*畳み込み範囲の下限*/

 for(i=startpoint;i<WORDLEN-startpoint;++i)
  for(j=startpoint;j<VOCSIZE-startpoint;++j)
   convout[i][j]=calcconv(filter,sentence,i,j) ;
}

/**********************/
/*  calcconv()関数    */
/*  フィルタの適用    */
/**********************/
double calcconv(double filter[][FILTERSIZE]
             ,double sentence[][VOCSIZE],int i,int j)
{
 int m,n ;/*繰り返しの制御用*/
 double sum=0 ;/*和の値*/
 
 for(m=0;m<FILTERSIZE;++m)
  for(n=0;n<FILTERSIZE;++n)
   sum+=sentence[i-FILTERSIZE/2+m][j-FILTERSIZE/2+n]*filter[m][n];
   
 return sum ;
}

/************************/
/*  convpool()関数      */
/*  畳み込みとプーリング*/
/************************/
void convpool(double s[WORDLEN][VOCSIZE],
              double mfilter[FILTERNO][FILTERSIZE][FILTERSIZE],
              double se[INPUTNO+1],
              double teacher)
{
 int i,j,k;
 int startpoint=FILTERSIZE/2+POOLSIZE/2 ;
               /*プーリング計算範囲の下限*/
 /*各フィルタを用いて畳み込みとプーリングを実行*/
 for(i=0;i<FILTERNO;++i){ 
  double convout[WORDLEN][VOCSIZE]={0} ;/*畳み込み出力*/
  double poolout[WORDLEN][VOCSIZE]={0} ;/*出力データ*/
  /*畳み込みの計算*/
  conv(mfilter[i],s,convout) ;

  /*畳み込み演算の結果出力*/
  convres(convout) ;

  /*プーリングの計算*/
  pool(convout,poolout) ;

  /*結果の出力*/
  poolres(poolout) ;

  /*畳み込み計算の結果を、全結合部への入力として代入*/
  for(j=startpoint;j<WORDLEN-startpoint;++j){
   for(k=startpoint;k<VOCSIZE-startpoint;++k)
    se[i*INPUTNO/FILTERNO+(j-startpoint)*(VOCSIZE-startpoint*2)+(k-startpoint)]
      =poolout[j][k];    
  }
 }  /*教師データの代入*/
 se[i*INPUTNO/FILTERNO]=teacher ;

}



/**********************/
/*  hlearn()関数      */
/*  中間層の重み学習  */
/**********************/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
    ,double wo[HIDDENNO+1]
    ,double hi[],double e[INPUTNO+1],double o)
{
 int i,j ;/*繰り返しの制御*/
 double dj ;/*中間層の重み計算に利用*/

 for(j=0;j<HIDDENNO;++j){/*中間層の各セルjを対象*/
  dj=hi[j]*(1-hi[j])*wo[j]*(e[INPUTNO]-o)*o*(1-o) ;
  for(i=0;i<INPUTNO;++i)/*i番目の重みを処理*/
   wh[j][i]+=ALPHA*e[i]*dj ;
  wh[j][i]+=ALPHA*(-1.0)*dj ;/*しきい値の学習*/
 }
}


/**********************/
/*  getdata()関数     */
/*学習データの読み込み*/
/**********************/
int getdata(double sentence[MAXINPUTNO][WORDLEN][VOCSIZE],
            double teacher[MAXINPUTNO])
{
 int i=0,j=0,k=0 ;/*繰り返しの制御用*/

 /*データの入力*/
 while(scanf("%lf",&teacher[i])!=EOF){/*教師データの読み込み*/
  /*単語列データの読み込み*/
  while(scanf("%lf",&sentence[i][j][k])!=EOF){
   ++ k ;
   if(k>=VOCSIZE){/*次のデータ*/
    k=0 ;
    ++j ;
    if(j>=WORDLEN) break ;/*入力終了*/
   }
  }
  j=0; k=0 ;
  ++i ; 
  if(i>MAXINPUTNO) break ;/*入力終了*/
 }
 return i ;

}

/**********************/
/*  olearn()関数      */
/*  出力層の重み学習  */
/**********************/
void olearn(double wo[HIDDENNO+1]
    ,double hi[],double e[INPUTNO+1],double o)
{
 int i ;/*繰り返しの制御*/
 double d ;/*重み計算に利用*/

 d=(e[INPUTNO]-o)*o*(1-o) ;/*誤差の計算*/
 for(i=0;i<HIDDENNO;++i){
  wo[i]+=ALPHA*hi[i]*d ;/*重みの学習*/
 }
 wo[i]+=ALPHA*(-1.0)*d ;/*しきい値の学習*/
 
} 


/**********************/
/*  forward()関数     */
/*  順方向の計算      */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO+1]
 ,double wo[HIDDENNO+1],double hi[],double e[INPUTNO+1])
{
 int i,j ;/*繰り返しの制御*/
 double u ;/*重み付き和の計算*/
 double o ;/*出力の計算*/

 /*hiの計算*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*重み付き和を求める*/
  for(j=0;j<INPUTNO;++j)
   u+=e[j]*wh[i][j] ; 
  u-=wh[i][j] ;/*しきい値の処理*/
  hi[i]=f(u) ;
 }
 /*出力oの計算*/
 o=0 ;
 for(i=0;i<HIDDENNO;++i)
  o+=hi[i]*wo[i] ;
 o-=wo[i] ;/*しきい値の処理*/
 
 return f(o) ;
} 

/**********************/
/*   print()関数      */
/*   結果の出力       */
/**********************/
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[HIDDENNO+1])
{
 int i,j ;/*繰り返しの制御*/

 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<INPUTNO+1;++j)
   printf("%lf ",wh[i][j]) ;
 printf("\n") ;
 for(i=0;i<HIDDENNO+1;++i)
  printf("%lf ",wo[i]) ;
 printf("\n") ;
} 

/**********************/
/*    initwh()関数    */
/*中間層の重みの初期化*/
/**********************/
void initwh(double wh[HIDDENNO][INPUTNO+1])
{
 int i,j ;/*繰り返しの制御*/

 /*乱数による重みの決定*/ 
 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<INPUTNO+1;++j)
   wh[i][j]=drnd() ;
} 

/**********************/
/*    initwo()関数    */
/*出力層の重みの初期化*/
/**********************/
void initwo(double wo[HIDDENNO+1])
{
 int i ;/*繰り返しの制御*/

 /*乱数による重みの決定*/
 for(i=0;i<HIDDENNO+1;++i)
   wo[i]=drnd() ;
} 

/*******************/
/* drnd()関数      */
/* 乱数の生成      */
/*******************/
double drnd(void)
{
 double rndno ;/*生成した乱数*/

 while((rndno=(double)rand()/RAND_MAX)==1.0) ;
 rndno=rndno*2-1 ;/*-1から1の間の乱数を生成*/
 return rndno; 
}

/*******************/
/* f()関数         */
/* 伝達関数        */
/*(シグモイド関数) */
/*******************/
double f(double u)
{
 return 1.0/(1.0+exp(-u)) ;
}



