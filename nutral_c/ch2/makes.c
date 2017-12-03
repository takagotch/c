/*************************************************/
/*           makes.c                             */
/* 1-of-N表現から,文を生成します 　　　　        */
/* 使い方                                        */
/*C:\Users\odaka\ch2>makes  (引数）              */
/*引数では入力ファイルを指定します               */
/* 第一引数　単語語彙を格納するファイル          */
/* 引数の指定が無い場合はvoc.txtファイルを指定   */
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
#define LENGTH 64 /*単語の長さの上限*/
#define N 10000/*単語の種類の上限*/
#define VOCFILE "voc.txt"/*デフォルト単語語彙ファイル*/

/****************/
/*  main()関数  */
/****************/
int main(int argc,char *argv[])
{
 char word[LENGTH*10] ;/*単語の読み込み用*/
 char dictionary[N][LENGTH] ;/*単語を登録する辞書*/
 int n=0 ;/*単語の種類数*/
 FILE *fpvoc,*fpi ;/*ファイルポインタ*/
 char inputfile[LENGTH] ;/*入力ファイル名*/
 char vocfile[LENGTH]=VOCFILE ;/*単語語彙ファイル名*/
 int e ;/*入力ベクトルの要素の値*/
 int i ;/*繰返しの制御*/

 /*入力ファイル名の設定*/
 fpi=stdin ;
 if(argc>=2) strncpy(vocfile,argv[1],LENGTH) ;
 if(argc>=3) strncpy(inputfile,argv[2],LENGTH) ;

 /*語彙ファイルのオープン*/
 if((fpvoc=fopen(vocfile,"r"))==NULL){
  /*ファイルオープン失敗*/
  fprintf(stderr,"%s:ファイルオープン失敗\n",vocfile) ;
  exit(1);
 }

 /*入力ファイルのオープン*/
 if((argc>=3)&&(fpi=fopen(inputfile,"r"))==NULL){
  /*ファイルオープン失敗*/
  fprintf(stderr,"%s:ファイルオープン失敗\n",inputfile) ;
  exit(1);
 }

 /*単語語彙データを読み込んで辞書に登録する*/
 while(fscanf(fpvoc,"%s",word)!=EOF){
  strncpy(dictionary[n],word,LENGTH) ;/*単語登録*/
  ++n ;/*単語数をカウントアップ*/
 }
 printf("単語数 %d\n",n) ;

 /* 文の出力*/
 i=0 ;
 while(fscanf(fpi,"%d",&e)!=EOF){
  if(e==1) printf("%s",dictionary[i]) ;
  ++i ;
  if(i>=n) i=0 ;
 }
 
 return 0 ;
}



