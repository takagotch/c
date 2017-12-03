/*********************************************************/
/*                   conv.c                              */
/*　畳み込み処理                                         */
/*　1-of-Nデータを読み取り、畳み込みを施します　　　　　*/
/* 使い方　                                              */
/*  \Users\odaka\ch3>conv  < data1.txt                   */
/*********************************************************/

/*Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

/* ヘッダファイルのインクルード*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*記号定数の定義*/
#define VOCSIZE 12  /*1-of-N表現の語彙数（次数）*/ 
#define WORDLEN 5   /*1-of-N表現の単語の連鎖数*/
#define FILTERSIZE 3 /*フィルタの大きさ*/

/*関数のプロトタイプの宣言*/
void conv(double filter[][FILTERSIZE]
   ,double sentence[][VOCSIZE]
   ,double convout[][VOCSIZE]) ; /*畳み込みの計算*/
double calcconv(double filter[][FILTERSIZE]
               ,double sentence[][VOCSIZE],int i,int j) ;
                               /*  フィルタの適用  */
void convres(double convout[][VOCSIZE]) ;
              /*畳み込みの結果出力*/
void getdata(double sentence[][VOCSIZE]) ;/*データ読み込み*/ 
         
/*******************/ 
/*    main()関数   */ 
/*******************/ 
int main()
{
 double filter[FILTERSIZE][FILTERSIZE]
//      ={{1,0,0},{0,1,0},{0,0,1}} ;/*順接フィルタ*/
      ={{1,0,0},{1,0,0},{1,0,0}} ;/*連続フィルタ*/
 double sentence[WORDLEN][VOCSIZE] ;/*入力データ*/
 double convout[WORDLEN][VOCSIZE]={0} ;/*畳み込み出力*/
 
 
 /*入力データの読み込み*/
 getdata(sentence) ;
 
 /*畳み込みの計算*/
 conv(filter,sentence,convout) ;

 /*結果の出力*/
 convres(convout) ;
 
 return 0 ;
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
/*  getdata()関数     */
/*入力データの読み込み*/
/**********************/
void getdata(double e[][VOCSIZE])
{
 int i=0,j=0 ;/*繰り返しの制御用*/

 /*データの入力*/
 while(scanf("%lf",&e[i][j])!=EOF){
  ++ j ;
  if(j>=VOCSIZE){/*次のデータ*/
   j=0 ;
   ++i ;
   if(i>=WORDLEN) break ;/*入力終了*/
  }
 }
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

