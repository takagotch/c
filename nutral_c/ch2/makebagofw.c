/*************************************************/
/*           makebagofw.c                        */
/* bag-of-wordsを生成します                      */
/* 使い方                                        */
/*C:\Users\odaka\ch2>makebagofw  (引数）         */
/* 第一引数　単語語彙数 n                        */
/* 第二引数　 入力ファイル （1-on-N表現）        */
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
#define LENGTH 64 /*ファイル名の長さの上限*/

/****************/
/*  main()関数  */
/****************/
int main(int argc,char *argv[])
{
 int n ;/*単語の種類数*/
 FILE *fpi ;/*ファイルポインタ*/
 char inputfile[LENGTH] ;/*入力ファイル名*/
 int e ;/*ベクトルの要素の値*/
 int i=0 ;/*繰返しの制御*/
 int bagofwords[N]={0} ;/*bag-of-words表現*/

 /*引数からの初期値の設定*/
 if(argc<2){
  /*引数が足りない*/
  fprintf(stderr,"使い方\n >makenewvec "
          "単語種類数n  (ファイル名)\n") ;
  exit(1);
 }
 fpi=stdin ;/*デフォルトは標準入力*/
 n=atoi(argv[1]) ;/*語彙数をセット*/
 if(argc>2){/*入力ファイルのオープン*/
  strncpy(inputfile,argv[2],LENGTH) ;/*入力ファイル*/
  if((fpi=fopen(inputfile,"r"))==NULL){
   /*ファイルオープン失敗*/
   fprintf(stderr,"%s:ファイルオープン失敗\n",inputfile) ;
   exit(1);
  }
 }
  
 /*1-of-N表現に基づく単語の並びの読み込み*/
 while(fscanf(fpi,"%d",&e)!=EOF){
  bagofwords[i]+=e ;
  ++i ;
  if(i>=n) i=0 ;
 }

 /*bag-of-words表現の出力*/
 for(i=0;i<n;++i)
  printf("%d ", bagofwords[i]);
 printf("\n") ;

 return 0 ;
}
