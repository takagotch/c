/*************************************************/
/*           makevec.c                           */
/* 単語1-gramから,1-of-N表現を生成します         */
/* 使い方                                        */
/*C:\Users\odaka\ch2>makevec  (引数）            */
/*引数では入出力ファイルを指定します             */
/* 第一引数　入力ファイル （単語1-gram）         */
/* 引数の指定が無い場合はw1gram.txtファイルを指定*/
/* 第二引数　単語語彙を格納するファイル          */
/* 引数の指定が無い場合はvoc.txtファイルを指定   */
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
#define N 5000/*単語の種類の上限*/
#define INPUTFILE "w1gram.txt"/*デフォルト入力ファイル*/
#define OUTPUTFILE "voc.txt"/*デフォルト出力ファイル*/


/* 関数のプロトタイプの宣言   */
int isnew(char word[],
      char dictionary[][LENGTH],int n)  ;/*新規単語判別*/
void putvec(char word[],
      char dictionary[][LENGTH],int n)  ;/*1-of-N出力*/

/****************/
/*  main()関数  */
/****************/
int main(int argc,char *argv[])
{
 char word[LENGTH*10] ;/*単語の読み込み用*/
 char dictionary[N][LENGTH] ;/*単語を登録する辞書*/
 int n=0 ;/*単語の種類数*/
 FILE *fpi,*fpo ;/*ファイルポインタ*/
 char inputfile[LENGTH]=INPUTFILE ;/*入力ファイル名*/
 char outputfile[LENGTH]=OUTPUTFILE ;/*出力ファイル名*/

 /*入力ファイル名の設定*/
 if(argc>=2) strncpy(inputfile,argv[1],LENGTH) ;
 if(argc>=3) strncpy(outputfile,argv[2],LENGTH) ;

 /*入力ファイルのオープン*/
 if((fpi=fopen(inputfile,"r"))==NULL){
  /*ファイルオープン失敗*/
  fprintf(stderr,"%s:ファイルオープン失敗\n",inputfile) ;
  exit(1);
 }

 /*出力ファイルのオープン*/
 if((fpo=fopen(outputfile,"w"))==NULL){
  /*ファイルオープン失敗*/
  fprintf(stderr,"%s:ファイルオープン失敗\n",outputfile) ;
  exit(1);
 }
 /*データを読み込んで辞書に登録する*/
 while(fscanf(fpi,"%s",word)!=EOF){
  if(isnew(word,dictionary,n)==TRUE){/*新しい単語なら*/
    strncpy(dictionary[n],word,LENGTH) ;/*単語登録*/
    ++n ;/*単語数をカウントアップ*/
  }
 }
 fprintf(stderr,"単語数 %d\n",n) ;
 rewind(fpi) ;/*ファイル先頭に巻き戻す*/

 /* 1-of-N表現の出力*/
 while(fscanf(fpi,"%s",word)!=EOF){
  putvec(word,dictionary,n) ;/*出力*/
 }
 
 /*語彙のファイル出力*/
 {
  int i ;
  for(i=0;i<n;++i) fprintf(fpo,"%s\n",dictionary[i]) ;
 }


 return 0 ;
}

/*******************************/
/*  putvec()関数               */
/* 1-of-N表現の出力            */
/*******************************/
void putvec(char word[],
      char dictionary[][LENGTH],int n)  
{
 int i ;/*ループ制御用変数*/

 for(i=0;i<n;++i){
  if((strncmp(word,dictionary[i],LENGTH)==0)
       && (strlen(word)==strlen(dictionary[i]))) /*一致*/
   printf("1") ;
  else printf("0") ;
  printf(" ") ;
 }
 printf("\n") ;/*ベクトルの区切り*/
}

/*******************************/
/*  isnew()関数                */
/*新規単語かどうかの判定       */
/*******************************/
int isnew(char word[],
      char dictionary[][LENGTH],int n)  
{
 int i ;/*ループ制御用変数*/

 for(i=0;i<n;++i){
  if((strncmp(word,dictionary[i],LENGTH)==0)
       && (strlen(word)==strlen(dictionary[i]))) break ;/*既登録*/
 }
 if(i<n) return FALSE ;
 
 return TRUE ;
}

