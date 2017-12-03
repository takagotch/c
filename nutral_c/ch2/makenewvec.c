/*************************************************/
/*           makenewvec.c                        */
/* ランダムに新しい文(1-of-N表現）を生成します   */
/* 使い方                                        */
/*C:\Users\odaka\ch2>makenewvec  (引数）         */
/*引数では入力ファイルを指定します               */
/* 第一引数　単語語彙数 n                        */
/* 第二引数　開始単語番号  s (ただし0<=s<n)      */
/* 引数の指定が無い場合は0を指定                 */
/* 第三引数　 入力ファイル （1-on-N表現）        */
/* 引数の指定が無い場合は標準入力を指定          */
/*************************************************/

/*Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

/*ヘッダファイルのインクルード*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 記号定数の定義             */
#define TRUE 1 
#define FALSE 0
#define N 1000/*語彙(単語）の種類の上限*/
#define WN 5000/*単語の個数の上限*/
#define WLIMIT 50/*出力単語数*/
#define LENGTH 64 /*文字列の長さの上限*/
#define SEED 65535    /*乱数のシード*/
#define ULIMIT 5 /*単語をランダムに探索する上限回数*/

/* 関数のプロトタイプの宣言   */
int read1ofn(FILE *fpi,int n) ;
   /*1-of-N表現に基づく単語の並びの読み込み*/
void putvec(int nextn,int n) ;
   /*1-of-N表現に基づく単語の出力*/
int searchs(int s,int n,int wn) ;
   /*sに対応する単語を探す*/
int matchptn(int i,int s,int n) ;
  /*単語の一致を検査する　              */
int rndn(int n) ;
  /*引数以下の整数乱数を返す*/

/*外部変数*/
char ngram[WN][N] ;/*1-of-N表現の入力データを格納*/

/****************/
/*  main()関数  */
/****************/
int main(int argc,char *argv[])
{
 int n ;/*単語の種類数*/
 int wn ;/*入力された単語の総数*/
 int s=0 ;/*開始単語番号*/
 FILE *fpi ;/*ファイルポインタ*/
 char inputfile[LENGTH] ;/*入力ファイル名*/
 int i,j ;/*繰返しの制御*/
 int loopmax ;/*繰り返し回数*/

 /*乱数の初期化*/
 srand(SEED) ;
 
 /*引数からの初期値の設定*/
 if(argc<2){
  /*引数が足りない*/
  fprintf(stderr,"使い方\n >makenewvec "
          "単語種類数n (開始単語番号s) (ファイル名)\n") ;
  exit(1);
 }
 fpi=stdin ;/*デフォルトは標準入力*/
 n=atoi(argv[1]) ;/*語彙数をセット*/
 if(argc>2) s=atoi(argv[2]) ;/*開始単語番号*/
 if(argc>3){/*入力ファイルのオープン*/
  strncpy(inputfile,argv[3],LENGTH) ;/*入力ファイル*/
  if((fpi=fopen(inputfile,"r"))==NULL){
   /*ファイルオープン失敗*/
   fprintf(stderr,"%s:ファイルオープン失敗\n",inputfile) ;
   exit(1);
  }
 }
  
 fprintf(stderr,"単語数 %d,開始単語番号 %d\n",n,s) ;
 if((s>=n)||(s<0)){/*sが不適当*/
   fprintf(stderr,"s=%d,sは1以上ｎ未満にしてください\n",s) ;
   exit(1);
 }
 /*1-of-N表現に基づく単語の並びの読み込み*/
 wn= read1ofn(fpi,n) ;/*読み込みと入力単語総数wnのセット*/

 /*単語連鎖（文）の生成*/
 putvec(s,n) ;/*開始記号*/

 for(i=0;i<WLIMIT;++i){
  /*sに対応する単語を探す*/
  loopmax=rndn(ULIMIT) ;/*最大ULIMIT回繰り返す*/
  for(j=0;j<loopmax;++j)/*ランダムに複数回繰り返す*/
   s=searchs(s,n,wn) ;
  /*隣接する次の単語を出力*/
  ++ s ;
  if(s>=wn) s=0 ;/*最初に戻る*/
  putvec(s,n) ;
 }

 return 0 ;
}

/**************************************/
/*   rndn()関数                       */
/*引数以下の整数乱数を返す            */
/**************************************/
int rndn(int n)
{
 double rndno ;/*生成した乱数*/

 while((rndno=(double)rand()/RAND_MAX)==1.0) ;
 return rndno*n ;
}

/**************************************/
/*   searcha()関数                    */
/*sに対応する単語を探す               */
/**************************************/
int searchs(int s,int n,int wn) 
{
 int i ;/*繰返しの制御*/

 for(i=s+1;i<wn;++i)
  if(matchptn(i,s,n)==TRUE) return i ;
 for(i=0;i<=s;++i)
  if(matchptn(i,s,n)==TRUE) return i ;
 /*いずれも合致しない*/
 fprintf(stderr,"内部エラー　searchs()関数\n") ;
 exit(1) ;
}

/**************************************/
/*   matchptn()関数                   */
/*単語の一致を検査する　              */
/**************************************/
int matchptn(int i,int s,int n) 
{
 int result=TRUE ;
 int index ;

 for(index=0;index<n;++index)
  if(ngram[i][index]!=ngram[s][index])
   result=FALSE ;/*不一致*/
 return result ;
}


/**************************************/
/*   putvec()関数                     */
/*1-of-N表現に基づく単語の出力        */
/**************************************/
void putvec(int nextn,int n) 
{
 int j=0 ;/*繰返しの制御*/

 for(j=0;j<n;++j)
  printf("%1d ",ngram[nextn][j]);
 printf("\n") ;

}

/****************************************/
/*   read1ofn()関数                     */
/*1-of-N表現に基づく単語の並びの読み込み*/
/****************************************/
int read1ofn(FILE *fpi,int n) 
{
 int e ;/*入力ベクトルの要素の値*/
 int i=0,j=0 ;/*繰返しの制御*/

 while((fscanf(fpi,"%d",&e)!=EOF)&&(i<WN)){
  ngram[i][j]=e ;
  ++j ;
  if(j>=n){
   j=0 ; ++i ;
  }
 } 
 return i ;
}