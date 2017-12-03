/*********************************************/
/*           dupline.c                       */
/*  2行目以降の入力行を複製します            */
/* 使い方                                    */
/*C:\Users\odaka\ch4>dupline < text1.txt   */
/*********************************************/

/*Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

/* 記号定数の定義             */
#define MAXSIZE 4096 /*1行の最大サイズ*/ 

/*ヘッダファイルのインクルード*/
#include <stdio.h>
#include <stdlib.h>

/****************/
/*  main()関数  */
/****************/
int main()
{
 char line[MAXSIZE] ;/*入力行*/

 /*最初の行を読み込んでそのまま出力する*/
 fgets(line,MAXSIZE,stdin) ;
 printf("%s",line) ;

 /*2行目以降を複製する*/
 while(fgets(line,MAXSIZE,stdin)!=NULL){
  printf("%s",line) ;
  printf("%s",line) ;
 }

 return 0 ;
}
