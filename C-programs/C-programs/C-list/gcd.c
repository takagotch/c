#include <stdio.h>        /* 標準入出力のヘッダファイルの読込み */
#include <stdlib.h>       /* 標準ライブラリのヘッダファイルの読込み */
int gcd(int a0, int a1);  /* 関数の宣言 */

main()                   
/* メインプログラム：最大公約数計算のためのデータの入出力 */
{
 int a0, a1, temp;                    /* 変数の宣言 */

 printf("Type in the first integer.\n");  /* a0の入力を指示 */
 scanf("%d", &a0);                    /* キーボードからa0の入力 */
 printf("a0 = %d\n", a0);             /* a0の出力 */
 printf("Type in the second integer.\n"); /* a1の入力を指示 */
 scanf("%d", &a1);                    /* キーボードからa1の入力 */
 printf("a1 = %d\n", a1);             /* a1の出力 */
 if(a0<=0 || a1<=0)                   /* 正性のチェック */
   {printf("Illegal input number\n"); exit(1);}
 if(a0<a1) {temp=a0; a0=a1; a1=temp;} /* a0>=a1に正規化 */
 printf("GCD = %d\n", gcd(a0,a1));    /* 最大公約数の計算と出力 */
 return(0);
}

int gcd(int a0, int a1)          /* ユークリッドの互除法 */
/* ユークリッドの互除法: a0とa1の最大公約数の計算 */
{
 int a, b, temp;                      /* 変数の宣言 */

 a=a0; b=a1;                          /* 初期設定 */
 while(b!=0) {temp=a%b; a=b; b=temp;} /* 互除法の反復 */
 return(a);                           /* 計算結果を返す */
}
