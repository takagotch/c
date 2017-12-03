/* 最小木問題に対するクラスカル法のプログラム例 */

#include <stdio.h>
#include <math.h>
#define N 100        /* 節点数の上限 */
#define M 500        /* 枝数の上限 */
#define ZERO 0.0001  /* 丸め誤差の許容値 */
struct edge          /* 構造体edgeの定義 */
{
 float d;            /* 枝長 */
 int end1, end2;     /* 両端点 */
};
struct set           /* 構造体setの定義 */
{
 int size[N];
 int root[N];
 int parent[N];
};

/* 関数の宣言 */
void kruskal(struct edge *E, struct edge *T, int n, int m);
void quicksort(int i, int j, struct edge *A);
int partition(int i, int j, float a, struct edge *A);
int pivot(int i, int j, struct edge *A);
void swap(int i, int j, struct edge *A);
void treemerge(int i, int k, struct set *S);
int treefind(int j, struct set *S);

main()
/* 最小木のアルゴリズムのテストプログラム */
{
 struct edge E[M], T[N-1];    /* 枝集合E, 最小木T */
 int i, k, n, m;
 FILE *file;

 file=fopen("edgedata", "r");
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
 kruskal(E, T, n, m);
 printf("MST edges\n");
 for(k=0; k<n-1; k++) 
   printf("%f, %d, %d\n", T[k].d, T[k].end1, T[k].end2);
 return(0);
}

void kruskal(struct edge *E, struct edge *T, int n, int m)
/* 節点数n, 枝数m, 枝集合Eをもつグラフの最小木を求める
クラスカルのアルゴリズム; 結果をTに入れる */
{
 struct set comp;           /* 計算に必要な集合族（森による表現） */
 int i, j, k, s1, s2;

 for(j=0; j<n; j++)         /* compの初期化 */
   {
    comp.size[j]=1; comp.root[j]=j; comp.parent[j]=-j-1;
   }
 quicksort(0, m-1, E);      /* 枝集合Eの整列 */
 k=0; i=0;                  /* クラスカルのアルゴリズムの反復 */
 while(k<n-1)
   {
    s1=treefind(E[i].end1, &comp);  /* 枝E[i]の両端点の集合s1とs2 */
    s2=treefind(E[i].end2, &comp);
    if(s1!=s2)              /* s1とs2の併合 */
      {
       treemerge(s1, s2, &comp);
       T[k]=E[i];
       k=k+1;
      }
    i=i+1;
   }
/* printf("final sets comp\n");
 for(i=0; i<n; i++) printf("%d, %d, %d\n", i, comp.size[i], comp.root[i]);
 printf("parents\n");
 for(j=0; j<n; j++) printf("%d, %d\n", j, comp.parent[j]); */
 return;
}

void quicksort(int i, int j, struct edge *A)
/* 配列A[i],...,A[j]をクイックソートにより整列 */
{
 int a, pv, k;

 pv=pivot(i, j, A);
 if(pv!=-1)
   {
    a=A[pv].d;
    k=partition(i, j, a, A);
    quicksort(i, k-1, A);
    quicksort(k, j, A);
   }
 return;
}

int partition(int i, int j, float a, struct edge *A)
/* A[i],...,A[j]を軸要素aによって分割 */
/* 前半はA[i],...,A[k-1]<a, 後半はA[k],...,A[j]>=aを満たす */
{
 int l, r, k;
 l=i; r=j;

 while(A[l].d < a-ZERO) l=l+1; while(A[r].d+ZERO >= a) r=r-1;
 while(l<=r)
   {
    swap(l, r, A); l=l+1; r=r-1;
    while(A[l].d < a-ZERO) l=l+1; while(A[r].d+ZERO >= a) r=r-1;
   }
 k=l;
 return(k);
}

int pivot(int i, int j, struct edge *A)
/* A[i],...,A[j]から軸要素A[pv]を選びpvを出力 */
/* A[pv]はA[i]と最初に異なるA[k]の大きい方；すべて同じならpv=-1 */
{
 int pv, k;

 k=i+1;
 while(fabs(A[i].d-A[k].d)<=ZERO && k<=j) k=k+1;
 if(k>j) pv=-1;
 else if(A[i].d >= A[k].d) pv=i;
 else pv=k;
 return(pv);
}


void swap(int i, int j, struct edge *A)
/* 構造体A[i]とA[j]の交換 */
{
 struct edge temp;

 temp=A[i]; A[i]=A[j]; A[j]=temp;
 return;
}


void treemerge(int i, int k, struct set *S)
/* 集合iとkの２つの木の併合 */
{
 int j, large, small;

 if(S->size[i] <= S->size[k]) {small=i; large=k;}
 else {small=k; large=i;}
 j=S->root[small];
 if(S->size[small] == 0) return;
 S->parent[j] = S->root[large];
 S->size[large] = S->size[large]+S->size[small];
 S->size[small] = 0;
 S->root[small] = -1;
 return;
}

int treefind(int j, struct set *S)
/* jを要素とする集合iの出力と路の圧縮 */
{
 int i, k, temp;
 k=j;

 while(k>=0) k = S->parent[k];
 i = -k-1;
 k=j;
 while(k>=0) 
   {
    temp = S->parent[k];
    if(temp>=0) S->parent[k] = S->root[i];
    k=temp;
   }
 return(i);
}
