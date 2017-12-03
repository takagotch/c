/*********************************************/
/*           sortn.c                          /
/*  行頭の数値により行を整列します           */
/* 使い方                                    */
/*C:\Users\odaka\ch2>sortn < text.txt        */
/*********************************************/

/*Visual Studioとの互換性確保 */
#define _CRT_SECURE_NO_WARNINGS

/*ヘッダファイルのインクルード*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 記号定数の定義             */
#define LINESIZE 256 /*　一行のバイト数の上限 */
#define MAX 65536*3 /* 行数の上限 */ 


/* 関数のプロトタイプの宣言   */
int cmpdata(const char *a,const char *b) ;
      /*比較関数*/

/* 外部変数　*/
char lines[MAX][LINESIZE] ; /*処理対象テキスト*/

/****************/
/*  main()関数  */
/****************/
int main()
{
 char buffer[LINESIZE] ;/*読み込みバッファ*/
 int pos=0 ;/*読み込み行数のカウンタ*/
 int i ;
 
 /*テキストを読み込む*/
 while(fgets(buffer,LINESIZE,stdin)!=NULL){
   strcpy(lines[pos],buffer) ;
   if((++pos)>=MAX){ 
    fprintf(stderr,
      "ファイルサイズの上限を超えました\n") ;
    exit(1);
   }
  }
 /*整列*/
 qsort(lines,pos,LINESIZE,
   (int (*)(const void *,const void *))cmpdata) ;
 /*出力*/
 for(i=0;i<pos;++i)
  printf("%s",lines[i]) ;
  
 return 0;
}


/*******************************/
/*  cmpdata()関数              */
/*　比較関数                   */
/*******************************/
int cmpdata(const char *a,const char *b)
{
 int inta,intb ;

 inta=atoi(a) ;
 intb=atoi(b) ;
 if(inta>intb) return -1;/*第一引数が大きい*/
 else if(inta<intb) return 1 ;/*第二引数が大きい*/

 return 0 ;/*それ以外*/
}

