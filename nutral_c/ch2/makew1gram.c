/*************************************************/
/*           makew1gram.c                        */
/*  Shift_JIS漢字コード用単語1-gram生成器 　     */
/*　Shift_JISで記述されたファイルから            */
/*  全角データのみ抽出して単語1-gramを生成します */
/* 使い方                                        */
/*C:\Users\odaka\ch2>makew1gram < text1.txt      */
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
#define KANJI 0 /*字種は漢字*/
#define KATAKANA 1/*字種はカタカナ*/
#define KUTOUTEN 2/*字種は句読点*/
#define SONOTA 3 /*字種は上記以外*/


/* 関数のプロトタイプの宣言   */
int is2byte(int chr) ;/*全角の1バイト目かどうかの判定*/
int typep(int chr1,int chr2) ;/*字種の判定*/

/****************/
/*  main()関数  */
/****************/
int main()
{
 int chr1,chr2 ;/*入力文字*/
 int now,last=-1 ;/*字種の記憶*/

 /*データを読み込んで1文字ずつ出力する*/
 while((chr1=getchar())!=EOF){
  if(is2byte(chr1)==TRUE){
   chr2=getchar() ;
   now=typep(chr1,chr2) ;

   /*全角（２バイト）出力*/
   if(now!=last){
    putchar('\n') ;/*1-gramの区切り*/
    last=now ;
   }
   putchar(chr1) ;
   putchar(chr2) ;
 
  }
 }

 return 0 ;
}

/*******************************/
/*  typep()関数                */
/*　字種の判定                 */
/*******************************/
int typep(int chr1,int chr2)
{
 char chr[3]="　" ;/*句読点判定用*/

 chr[0]=chr1 ; chr[1]=chr2 ; /*文字の設定*/
 /*字種の判定*/
 if(chr1>=0x88)
  return KANJI ;/*漢字*/
 else if((chr1==0x83)&&(chr2>=0x40)&&(chr2<=0x96))  
  return KATAKANA ;/*カタカナ*/
 else if((strncmp(chr,"。",2) ==0) ||
         (strncmp(chr,"．",2) ==0) ||
         (strncmp(chr,"、",2) ==0) ||
         (strncmp(chr,"，",2) ==0))
  return KUTOUTEN ;/*句読点*/
 return SONOTA ;/*その他*/
}

/*******************************/
/*  is2byte()関数              */
/*全角の1バイト目かどうかの判定*/
/*******************************/
int is2byte(int c)
{
 if(((c>0x80)&&(c<0xA0))||(c>0xDF)&&(c<0xF0))
  return TRUE ;/*2バイト文字*/
 return FALSE ;/*1バイト文字*/
}

