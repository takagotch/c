#include <stdio.h>
#define N 100        /* 配列Aの最大サイズ */
enum yn {yes, no};   /* 列挙型データynの定義 */
/* 関数の宣言 */
enum yn bsearch(int x, int *A, int n); 

main()
/* 配列上の２分探索のテストプログラム */
{
 int A[N];
 int i, x, nA;
 enum yn ans;
 nA=15; 
 for(i=0; i<nA; i++)
   {
    A[i]=5+2*i;
   }
 printf("A = ");
 for(i=0; i<nA; i++) printf("%d ", A[i]); 
 printf("\n");
 x=7;
 printf("x = %d\n", x);
 ans=bsearch(x, A, nA);
 if(ans==yes) printf("Answer = yes\n");
 else printf("Answer = no\n"); 
 return(0);
}

enum yn bsearch(int x, int *A, int n)
/* 整列配列A[0],...,A[n-1]上でxの２分探索；yesあるいはnoの出力 */
{
 int iL, iR, iM;     /* iLは左、iRは右、iMは中央のインデックス */
 iL=0; iR=n-1;
 if(A[iL]==x || A[iR]==x) return(yes);  /* 初期条件でのチェック */
 if(x<A[iL] || x>A[iR]) return(no);
 while(iR-iL>1)               /* 2分探索 */
   {
    iM=(iL+iR)/2;             /* 中央値 */
    if(A[iM]==x) return(yes);
    if(A[iM]<x) iL=iM;        /* 新しいインデックスの設定 */
    else iR=iM;
   }
 return(no);
}

