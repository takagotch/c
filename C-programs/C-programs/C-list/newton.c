/* ニュートン法による零点の計算のプログラム例 */

#include <stdio.h>
#include <math.h>
float zero=0.001;        /* 外部変数; 微係数>0の許容範囲 */
float delta=0.0001;      /* 外部変数; |f(x)|の許容範囲 */
/* 関数の宣言 */
float f(float x);
float df(float x);
float newton(float xinit);

main()
/* ニュートン法により f(x)=0.0 を解くテストプログラム */
{
 float xinit, x;

 xinit=5.0;
 x=newton(xinit);
 printf("xinit = %f, delta = %f\n", xinit, delta);
 printf("zero x* = %f, f(x*) = %f\n", x, f(x));
 return(0);
}

float newton(float xinit)
/* 微分可能増加関数f(x)の零点をx=xinitからニュートン法により求める */
/* 関数f(x)とその微係数df(x)はプログラムによって与える */
{
 float x, y, dy;

 x=xinit;
 y=f(x);
 while(fabs(y)>delta)    /* ニュートン法の反復 */
   {
    dy=df(x);
    if(fabs(dy)<zero)    /* 誤り（微係数＝0）のチェック */
      {printf("Error: derivative at x = %f is zero.\n", x); exit(1);}
    x=x-y/dy;            /* 次の反復解 */
    y=f(x);
   }
 return(x);              /* 結果を返す */
}

float f(float x)
/* 関数値f(x)を与えるプログラム */
{
 float fx;

 fx=x*x*x-10.0;
 return(fx);
}

float df(float x)
/* f(x)の微係数を与えるプログラム */
{
 float d;

 d=3*x*x;
 return(d);
}

