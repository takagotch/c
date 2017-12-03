/* 階乗n!の計算のプログラム例 */

#include <stdio.h>   /* 標準入出力のヘッダファイルの読込み */
int fact(int n);     /* 関数の宣言 */

main()
/* 階乗の計算のテストプログラム */
{
 int n;

 n=5;                /* nの設定 */
 printf("factorial of n = %d is %d\n", n, fact(n)); /* n!の計算と出力 */
}

int fact(int n)
/* 階乗n!の計算 */
{
 if(n<=0) {printf("Illegal input n = %d\n", n); exit(1);}
 else 
   {
    if(n==1) return(1);         /* n==1の場合 */
    else return(n*fact(n-1));   /* factの再帰呼び出し */
   }
 return;
}
