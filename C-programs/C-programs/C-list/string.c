/* 文字列照合を行うBM法のプログラム例 */

#include <stdio.h>
#define N 1000       /* テキストの最大長 */
#define M 100        /* パターンの最大長 */ 
#define A 128        /* アルファベットの文字数 */

/* 関数の宣言 */
int bm(char *t, char *p, int n, int m);
void fd(char *p, int *d, int m);
void fe(char *p, int *e, int m);

main()
/* 文字列照合のテストプログラム */
{
 char t[N], p[M];                   /* テキストt, パターンp */
 int h, n, m;
 FILE *file;                        /* ファイルの準備 */

 n=0; m=0;
 file=fopen("textdata", "r");       /* テキストデータの読込み */
 printf("text:\n");
 while (fscanf(file, "%c", &t[n]) != EOF)   /* テキストの出力 */
   {
    printf("%c", t[n]);
    n=n+1;
   }
 printf("\n");
 file=fopen("patterndata", "r");    /* パターンデータの読込み */
 printf("pattern:\n");
 while (fscanf(file, "%c", &p[m]) != EOF)   /* パターンの出力 */
   {
    printf("%c", p[m]);
    m=m+1;
   }
 n=n-1; m=m-1;
 printf("\nn= %d, m = %d\n", n, m);
 h=bm(t, p, n, m);                  /* BM法の実行 */
 printf("first location: %d\n", h); /* 結果の出力 */
 return(0);
}

int bm(char *t, char *p, int n, int m)
/* 長さnのテキストtと長さmのパターンpにBM法を適用し、pの
最初の位置を出力（pがなければ-1） */
{
 int h, j, s;
 int d[A], e[M];

 fd(p, d, m);                /* パターンpに対しd(a)の計算 */
 fe(p, e, m);                /* パターンpに対しe(j)の計算 */
 h=0;  
 while(h+m-1 < n)            /* 位置hのパターンpとtの照合 */
   {
    j=m-1;
    while(j>=0 && t[h+j]==p[j]) j=j-1;
    if(j==-1) return(h);     /* パターンpを発見 */
    else                     /* pを次の位置へ移動 */
      {
       s=j-d[(int)t[h+j]]; 
       if(e[j] > s) s=e[j];
       h=h+s;
      }
   }
 return(-1);                 /* パターンpは存在しない */
}


void fd(char *p, int *d, int m)
/* 長さmのパターンpに対し関数dの計算 */
{
 int i, k;

 for(i=0; i<A; i++) d[i]=-1;
 for(k=0; k<m; k++) d[(int)p[k]]=k;
 return;
}


void fe(char *p, int *e, int m)
/* 長さmのパターンpに対し関数gとeの計算 */
/* g(k), k=-1,0,...,m-1をg[0],g[1],...,g[m]に格納 */
{
 int i, j, k, l;
 int g[M+1];                 /* gを格納する配列 */

 j=m; k=m-1;
 while(k >= 0)               /* gの計算 */
   {
    g[k+1]=j;
    while(j<=m-1 && p[k]!=p[j]) j=g[j+1];
    j=j-1; k=k-1;
   }
 g[0]=j;
 for(k=0; k<m; k++) e[k]=m;  /* eの計算 */
 for(k=0; k<m; k++) if(p[g[k+1]]!=p[k]) e[g[k+1]]=g[k+1]-k;
 j=0; l=-1;
 while(l<m)
   {
    l=g[l+1];
    for(i=j; i<=l; i++) if(l+1<e[i]) e[i]=l+1;
    j=l+1;
   }
 return;
}
