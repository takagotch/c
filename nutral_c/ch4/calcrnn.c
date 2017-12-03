/*********************************************************/
/*                   calcrnn.c　                         */
/*　リカレントニューラルネットワーク                     */
/*　学習済みのネットワークを計算します                   */
/* 使い方　                                              */
/*  \Users\odaka\ch4>calcrnn 2 < data.txt 　             */
/*　コマンドライン引数として、開始単語の番号を与えます   */
/*********************************************************/

/*Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

/* ヘッダファイルのインクルード*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*記号定数の定義*/
#define INPUTNO 5  /*入力の要素数*/
#define HIDDENNO 5  /*中間層のセル数*/
#define OUTPUTNO 5  /*出力層のセル数*/
#define WORDLEN 50 /*単語連鎖数*/

/*関数のプロトタイプの宣言*/
double f(double u) ; /*伝達関数（シグモイド関数）*/
void print(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
          ,double wo[OUTPUTNO][HIDDENNO+1]) ; /*結果の出力*/
double forward(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[]) ; /*順方向の計算*/
void readwh(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]) ;
                         /*中間層の重みの読み込み*/
void readwo(double wo[OUTPUTNO][HIDDENNO+1]) ;
                         /*出力層の重みの読み込み*/
void  putword(double inputdata[]) ;
       /*単語部分のみを1-of-N表現で表示*/


/*******************/
/*    main()関数   */
/*******************/
int main(int argc,char *argv[])
{
 double wh[HIDDENNO][INPUTNO+1+HIDDENNO] ;/*中間層の重み*/
 double wo[OUTPUTNO][HIDDENNO+1] ;/*出力層の重み*/
 double hi[HIDDENNO+1]={0} ;/*中間層の出力*/
 double o[OUTPUTNO] ;/*出力*/
 double inputdata[INPUTNO+HIDDENNO]={0} ;/*入力*/
 int i,j ;/*繰り返しの制御*/
 int startno ; /*開始単語の番号*/

 /*開始単語の指定*/
 if(argc<2){
  startno=0 ;/*指定が無い場合は0番から開始*/
 }
 else{
  startno=atoi(argv[1]) ;
  if((startno<0) || (startno>=INPUTNO)){
   /*開始単語指定のエラー*/
   fprintf(stderr,"開始単語の指定値(%d)が間違っています\n",startno) ;
   exit(1) ;
  }
 }   
 inputdata[startno]=1.0 ;

 /*重みの読み込み*/
 readwh(wh) ;/*中間層の重みの読み込み*/
 readwo(wo) ;/*出力層の重みの読み込み*/


 /*文生成*/
 for(i=0;i<WORDLEN;++i){
  /*入力データを表示*/
  /*必要ならば以下の3行のコメントを外す*/
//  for(j=0;j<INPUTNO+HIDDENNO;++j)
//   printf("%.3lf ",inputdata[j]) ;
//  printf("\n") ;
  /*単語部分のみを1-of-N表現で表示*/
  putword(inputdata) ;
  /*順方向の計算*/
  for(j=0;j<OUTPUTNO;++j)
   o[j]=forward(wh,wo[j],hi,inputdata) ;
  /*前回の出力を入力にセット*/
  for(j=0;j<HIDDENNO;++j)
    inputdata[j]=o[j] ;
  /*前回の中間層出力を入力に追加*/
  for(j=0;j<HIDDENNO;++j)
    inputdata[INPUTNO+j]=hi[j] ;
 }

 return 0 ;
}

/********************************/
/*   putword()関数              */
/*単語部分のみを1-of-N表現で表示*/
/********************************/
void  putword(double inputdata[])
{
 int i ;/*繰り返しの制御*/
 int maxindex=0 ;/*最大値要素の添え字番号*/
 double max=inputdata[0] ;/*最大値*/

 /*最大となる要素を調べる*/
 for(i=1;i<INPUTNO;++i)
  if(max<inputdata[i]){
   max=inputdata[i] ;
   maxindex=i ;
  }
 /*1-of-N表現で単語を出力*/
 for(i=0;i<INPUTNO;++i){
  if(i==maxindex) printf("1 ") ;
  else printf("0 ") ;
 }
 printf("\n") ;

}

/**********************/
/*  forward()関数     */
/*  順方向の計算      */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
 ,double wo[HIDDENNO+1],double hi[],double e[])
{
 int i,j ;/*繰り返しの制御*/
 double u ;/*重み付き和の計算*/
 double o ;/*出力の計算*/

 /*hiの計算*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*重み付き和を求める*/
  for(j=0;j<INPUTNO+HIDDENNO;++j)
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

/************************/
/*    readwh()関数      */
/*中間層の重みの読み込み*/
/************************/
void readwh(double wh[HIDDENNO][INPUTNO+1+HIDDENNO])
{
 int i,j ;/*繰り返しの制御*/

  for(i=0;i<HIDDENNO;++i){
  for(j=0;j<INPUTNO+1+HIDDENNO;++j)
   scanf("%lf",&(wh[i][j])) ;
 }
}

/************************/
/*    readwo()関数      */
/*出力層の重みの読み込み*/
/************************/
void readwo(double wo[OUTPUTNO][HIDDENNO+1])
{
 int i,j ;/*繰り返しの制御*/

 for(i=0;i<OUTPUTNO;++i){
  for(j=0;j<HIDDENNO+1;++j)
   scanf("%lf",&(wo[i][j])) ;
 }
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





