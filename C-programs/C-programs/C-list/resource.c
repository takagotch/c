/* 資源配分問題に対する増分法のプログラム例 */

#include <stdio.h>
#include <math.h>
#define M 100         /* 配列Aの最大サイズ */
struct value          /* 構造体valueの定義 */
{
 float d;
 int j;
};
/* 関数の宣言 */
void resource(int n, int N);
float fn(float x, int j);
struct value deletemin(struct value *A, int n);
void downmin(int i, struct value *A, int n);
void insert(struct value dj, struct value *A, int n);
void upmin(int i, struct value *A, int n);
void heapify(struct value *A, int n);
void swap(int i, int j, struct value *A);

main()
/* 資源配分問題のテストプログラム */
{
 int n, N;

 n=5; N=6;      /* 変数の数nと右辺の値Nの設定 */
 resource(n, N);
 return(0);
}

void resource(int n, int N)
/* 増分法を用いて資源配分問題を解く. 変数の個数n, 右辺の値N. */
{
 struct value dj, min, inc[M];  /* incは増分量を貯えるヒープ */
 int j, i, x[M];                /* xは解 */
 float sum, fjx, fjx1;

 sum=0.0;
 for(j=0; j<n; j++)             /* 初期化 */
   {
    x[j]=0;                     /* 初期解 */
    fjx=fn(0.0, j); fjx1=fn(1.0, j);
    sum=sum+fjx;
    inc[j].d=fjx1-fjx; inc[j].j=j;
   }
 heapify(inc, n);               /* 初期ヒープ */
 for(i=1; i<=N; i++)            /* 増分法の反復 */
   {
    min=deletemin(inc, n);
    x[min.j]=x[min.j]+1;        /* 増分量最小のxjを1増加 */
    sum=sum+min.d;
    fjx=fn(x[min.j], min.j);    
    fjx1=fn(x[min.j]+1.0, min.j);
    dj.d=fjx1-fjx; dj.j=min.j;
    insert(dj, inc, n-1);       /* ヒープの更新 */
   }
 printf("Solution x =");        /* 最適解の出力 */
 for(j=0; j<n; j++) printf("%d ", x[j]);
 printf("\n");
 printf("Objective value = %f\n", sum);
 return;
}

float fn(float x, int j)
/* 目的関数値fj(x)を与えるプログラム例 */
{
 float f;

 switch(j)
   {
    case 0: f=1.0/(x+1.0); break;
    case 1: f=(x-2.5)*(x-2.5); break;
    case 2: f=1.0+0.1*x*x*x; break;
    case 3: f=-1.0+(x-2.0)*(x-2.0); break;
    case 4: f=3.0-sqrt(x); break;    
    default: {printf("Error: j = %d is out of the range.", j); exit(1);}
   }
 return(f);
}

void insert(struct value dj, struct value *A, int n)
/* ヒープA[0],...,A[n-1]へ新しい要素xの挿入; n=n+1 */
{
 A[n]=dj;
 upmin(n, A, n+1);
}

struct value deletemin(struct value *A, int n)
/* ヒープA[0],...,A[n-1]から最小要素A[0]の出力と除去; n=n-1 */
{
 struct value min;

 min=A[0]; A[0]=A[n-1];
 if(n>1) downmin(0, A, n-1);
 return(min);
}

void upmin(int i, struct value *A, int n)
/* A[i]から上方へ、ヒープ条件回復のためswap操作を適用 */
{
 int j;
 if(i<0 || i>=n)
   { 
    printf("Illegal element i = %d for n = %d\n", i, n); 
    exit();
   }
 if(i==0) return;
 j=(i+1)/2-1; 
 if(A[j].d>A[i].d)
   {
    swap(i, j, A); 
    upmin(j, A, n);
   }
 return;
}


void downmin(int i, struct value *A, int n)
/* A[i]から下方へ、ヒープ条件回復のためのswap操作を適用；
最後の要素はA[n-1] */
{
 int j;

 if(i<0 || i>=n) 
   { 
    printf("Illegal element i = %d for n = %d\n", i, n); 
    exit();
   }
 j=2*i+1;
 if(j>=n) return;
 if(j+1<n && A[j].d>A[j+1].d) j=j+1; 
 if(A[j].d<A[i].d) 
   {
    swap(i, j, A);
    downmin(j, A, n);
   }
 return;
}

void heapify(struct value *A, int n)
/* A[0],...,A[n-1]をヒープ化 */
{
 int i;

 for(i=n/2-1; i>=0; i--) downmin(i, A, n);
 return;
}

void swap(int i, int j, struct value *A)
/* 構造体A[i]とA[j]の交換 */
{
 struct value temp;
 temp=A[i]; A[i]=A[j]; A[j]=temp;
 return;
}

