/*********************************************/
/*           extraction.c                    */
/*  Shift_JIS漢字コード用全角文字抽出器      */
/*　Shift_JISで記述されたファイルから        */
/*  全角データのみ抽出します                 */
/* 使い方                                    */
/*C:\Users\odaka\ch2>extraction < text1.txt  */
/*********************************************/

/*Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

/*ヘッダファイルのインクルード*/
#include <stdio.h>
#include <stdlib.h>

/* 記号定数の定義             */
#define TRUE 1 
#define FALSE 0

/* 関数のプロトタイプの宣言   */
int is2byte(int chr) ;/*全角文字の1バイト目かどうかの判定*/

/****************/
/*  main()関数  */
/****************/
int main()
{
 int chr ;/*入力文字*/

 /*データを読み込んで1文字ずつ出力する*/
 while((chr=getchar())!=EOF){
  if(is2byte(chr)==TRUE){
   /*全角（２バイト）出力*/
   putchar(chr) ;
   putchar(getchar()) ;
  }
 }

 return 0 ;
}

/***********************************/
/*  is2byte()関数                  */
/*全角文字の1バイト目かどうかの判定*/
/***********************************/
int is2byte(int c)
{
 if(((c>=0x81)&&(c<=0x9F))||(c>=0xe0)&&(c<=0xef))
  return TRUE ;/*2バイト文字*/
 return FALSE ;/*1バイト文字*/
}

