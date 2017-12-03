/* 2分探索による零点の計算のプログラム例 */

#include <stdio.h>
#include <math.h>
float epsilon=0.0001;    /* 外部変数; xの許容誤差 */
float delta=0.0001;      /* 外部変数; fの許容誤差 */
/* 関数の宣言 */
float findzero(float a, float b);
float f(float x);

main()
/* 2分探索により f(x)=0.0 を解くテストプログラム */
{
 float a, b, x;

 a=0.0; b=10.0;
 x=findzero(a, b);
 printf("a = %f, b = %f, epsilon = %f, delta = %f\n", a, b, epsilon, delta);
 printf("zero x* = %f, f(x*) = %f\n", x, f(x));
 return(0);
}

float findzero(float a, float b)
/* 非減少連続関数f()の零点を区間[a, b]内で２分探索により求める */
{
 float xL, xR, xM, fx;               /* xLは左、xRは右、xMは中央値 */

 xL=a; xR=b;                         /* 初期設定 */
 if(f(a)>delta || f(b)<-delta) {printf("There is no zero f(x)=0.\n"); exit(1);}
 while(xR-xL>epsilon)
   {
    xM=(xL+xR)/2.0;                  /* 中点 */
    fx=f(xM);
    if(fabs(fx)<=delta) return(xM);  /* 関数値十分小; 零点発見 */
    if(fx<=0.0) xL=xM; else xR=xM;   /* 新しい区間の設定 */
   }
 return(xL);                         /* 零点を返す */
}

float f(float x)
/* 関数値f(x)を与えるプログラム */
{
 float fx;

 fx=x*x*x-10.0;
 return(fx);
}

