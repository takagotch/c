/* 最小木問題に対するプリム法のプログラム例 */

#include <stdio.h>
#include <stdlib.h>
#define N 100         /* 節点数の上限 */
#define M 100         /* 枝数の上限 */ 
#define ZERO 0.0001   /* 丸め誤差の許容値 */

struct edge           /* 構造体edgeの定義 */
{
 float d;
 int end1, end2;
};
struct value          /* 構造体valueの定義 */
{
 float d;
 int node;
};
struct cell           /* 構造体cellの定義 */
{
 int adj;
 int edge;
 struct cell *next;
};

/* 関数の宣言 */
void prim(struct edge *E, struct edge *T, int n, int m);
void insert(struct value dj, struct value *A, int *loc, int n);
struct value deletemin(struct value *A, int *loc, int n);
void upmin(int i, struct value *A, int *loc, int n);
void downmin(int i, struct value *A, int *loc, int n);
void swap(int i, int j, struct value *A, int *loc);

main()
/* 最小木問題に対するプリム法のテストプログラム */
{
 struct edge E[M], T[N-1];
 int i, k, n, m;
 FILE *file;

 file=fopen("edgedata", "r");       /* データの読込み */
    {
     fscanf(file, "%d", &n);
     fscanf(file, "%d", &m);
    }
 for(i=0; i<m; i++)
   {
    fscanf(file, "%f", &E[i].d);
    fscanf(file, "%d", &E[i].end1);
    fscanf(file, "%d", &E[i].end2);
   }
 printf("n = %d, m = %d\n", n, m);
 printf("edges; d  end1  end2 \n");
 for(i=0; i<m; i++) 
    printf("%f, %d, %d\n", E[i].d, E[i].end1, E[i].end2);
 prim(E, T, n, m);                  /* 最小木の計算 */
 printf("MST edges\n");
 for(k=0; k<n-1; k++) 
   printf("%f, %d, %d\n", T[k].d, T[k].end1, T[k].end2);
 return(0);
}

void prim(struct edge *E, struct edge *T, int n, int m)
/*  節点数n, 枝数m, 枝集合Eをもつグラフの最小木を求めるプリム法; 
結果をTに入れる */
{
 int i, j, k, u, v1, v2, vadj, nh;
 int P[N], loc[N], edge[N];
 struct cell *adjlist[N];
 struct cell *r, *q, *p;
 struct value vh, vmin; 
 struct value heap[N-1]; 

 P[0]=1;
 for(j=1; j<n; j++) P[j]=0;
 for(j=0; j<n; j++) {adjlist[j]=NULL; loc[j]=-1;}
 for(i=0; i<m; i++)
   {
    v1=E[i].end1;
    v2=E[i].end2;    
    r=(struct cell *)malloc(sizeof(struct cell));
    r->adj=v2; r->edge=i; r->next=adjlist[v1]; adjlist[v1]=r;
    q=(struct cell *)malloc(sizeof(struct cell));
    q->adj=v1; q->edge=i; q->next=adjlist[v2]; adjlist[v2]=q;
   }
 nh=0;
 u=0;
 for(k=0; k<n-1; k++)
   {
    p=adjlist[u];
    while(p!=NULL)
      {
       vadj=p->adj;
       if(P[vadj]==0) 
         {
          if(loc[vadj] == -1)  /* vadjをヒープに入れる */
            {
             vh.d=E[p->edge].d; vh.node=vadj;
             edge[vadj]=p->edge;
             insert(vh, heap, loc, nh);
             nh=nh+1;
            }
          else                 /* すでにヒープにあるvadjの更新 */
            {
             j=loc[vadj];
             if(heap[j].d > E[p->edge].d+ZERO) 
               {
                heap[j].d=E[p->edge].d;
                edge[vadj]=p->edge;
                upmin(j, heap, loc, nh);
               }
            }
         }
       p=p->next;
      }
    vmin=deletemin(heap, loc, nh);
    nh=nh-1;
    u=vmin.node;
    P[u]=1;
    T[k]=E[edge[u]];
   }
}

void insert(struct value vh, struct value *A, int *loc, int n)
/* ヒープA[0],...,A[n-1]へ新しい要素xの挿入; n=n+1 */
{
 A[n].d=vh.d;
 A[n].node=vh.node;
 loc[A[n].node]=n;
 upmin(n, A, loc, n+1);
}

struct value deletemin(struct value *A, int *loc, int n)
/* ヒープA[0],...,A[n-1]から最小要素A[0]の出力と除去; n=n-1 */
{
 struct value min;

 min.d=A[0].d; A[0].d=A[n-1].d;
 min.node=A[0].node; A[0].node=A[n-1].node;
 loc[A[0].node]=0;
 if(n>1) downmin(0, A, loc, n-1);
 return(min);
}

void upmin(int i, struct value *A, int *loc, int n)
/* A[i]から上方へ、ヒープ条件回復のためswap操作を適用 */
{
 int j;

 if(i<0 || i>=n)
   { 
    printf("Illegal element i = %d for n = %d\n", i, n); 
    exit(1);
   }
 if(i==0) return;
 j=(i+1)/2-1; 
 if(A[j].d>A[i].d)
   {
    swap(i, j, A, loc); 
    upmin(j, A, loc, n);
   }
 return;
}


void downmin(int i, struct value *A, int *loc, int n)
/* A[i]から下方へ、ヒープ条件回復のためのswap操作を適用 */
{
 int j;

 if(i<0 || i>=n) 
   { 
    printf("Illegal element i = %d for n = %d\n", i, n); 
    exit(1);
   }
 j=2*i+1;
 if(j>=n) return;
 if(j+1<n && A[j].d > A[j+1].d+ZERO) j=j+1; 
 if(A[j].d < A[i].d-ZERO) 
   {
    swap(i, j, A, loc);
    downmin(j, A, loc, n);
   }
 return;
}


void swap(int i, int j, struct value *A, int *loc)
/* ヒープAにおける構造体A[i]とA[j]の交換 */
{
 struct value temp;

 temp=A[i]; A[i]=A[j]; A[j]=temp;
 loc[A[i].node]=i; loc[A[j].node]=j;           /* locの更新 */
 return;
}

