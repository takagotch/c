/*********************************************/
/*           uniqc.c                         */
/*  重複行の数え上げ                         */
/*　行の繰り返しを削除し,重複回数を示します  */
/* 使い方                                    */
/*C:\Users\odaka\ch2>uniqc < text.txt        */
/*********************************************/

/*Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

/*ヘッダファイルのインクルード*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/* 記号定数の定義             */
#define MAXLINE 65535 

/****************/
/*  main()関数  */
/****************/
int main()
{
 char newline[MAXLINE] ;/*入力行*/
 char oldline[MAXLINE] ;/*前の行*/
 int count=1 ;/*重複回数*/

 /*テキストを読み込む*/
 fgets(oldline,MAXLINE,stdin) ;
 while(fgets(newline,MAXLINE,stdin)!=NULL){
  if(strcmp(newline,oldline)==0) ++count ;/*同じ行*/
  else{/*異なる行*/
   printf("%d\t%s",count,oldline);
   count=1 ;
   strcpy(oldline,newline) ;
  }
 }
 printf("%d\t%s",count,oldline);

 return 0 ;
}
