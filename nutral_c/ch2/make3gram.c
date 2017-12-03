/*********************************************/
/*           make3gram.c                     */
/*  Shift_JIS漢字コード用文字3-gram生成器    */
/*　Shift_JISで記述されたファイルから        */
/*  全角データのみ抽出して3-gramを生成します */
/* 使い方                                    */
/*C:\Users\odaka\ch2>make3gram <text1.txt    */
/*********************************************/

/*Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

/*ヘッダファイルのインクルード*/
#include <stdio.h>
#include <stdlib.h>

/* 記号定数の定義             */
#define TRUE 1 
#define FALSE 0
#define N 6 /*n-gramのnの２倍*/

/* 関数のプロトタイプの宣言   */
int is2byte(int chr) ;/*全角文字の1バイト目かどうかの判定*/
void put3gram(int chr) ;/*3-gramの出力*/
int invert(int flag) ;/*フラグの反転*/

/****************/
/*  main()関数  */
/****************/
int main()
{
 int chr ;/*入力文字*/

 /*データを読み込んで1文字ずつ出力する*/
 while((chr=getchar())!=EOF){
  if(is2byte(chr)==TRUE){
   /*put3gram()関数による出力*/
   put3gram(chr) ;
   put3gram(getchar()) ;
  }
 }

 return 0 ;
}

/*******************************/
/*  invett()関数               */
/*　flagの反転                 */
/*******************************/
int invert(int flag)
{
 if(flag==FALSE)
  return TRUE ;
 return FALSE ;
}


/*******************************/
/*  put3gram()関数             */
/*  3-gramの出力               */
/*******************************/
void put3gram(int c)
{
 static char queue[N]="　　　" ;/*出力用のキュー*/
 static int flag=FALSE ;/*出力のタイミング制御*/
 int i;/*繰返しの制御*/

 /*キューにデータを追加*/
 for(i=0;i<N-1;++i)
  queue[i]=queue[i+1] ;
 queue[N-1]=c ;/*データ追加*/ 

 /*2バイトの区切りなら出力*/
 if(flag==TRUE){
  for(i=0;i<N;++i)
   putchar(queue[i]) ; 
  putchar('\n') ;
 }
 /*フラグ反転*/
 flag=invert(flag) ;
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

