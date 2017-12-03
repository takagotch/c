/* 深さ優先探索によってグラフの関節点を求めるアルゴリズムのプログラム例 */

#include <stdio.h>
#include <stdlib.h>
#define N 100         /* 節点数の上限 */
#define M 500         /* 枝数の上限 */
struct edge           /* 構造体edgeの定義 */
{
 int end1, end2;
};
struct cell           /* 構造体cellの定義 */
{  
 int adj;
 int edge;
 struct cell *next;
};
struct number         /* 構造体numberの定義 */
{
 int v, e, lowpt;
};

/* 関数の宣言 */
void artic(struct edge *E, int *art, int n, int m);
struct number dfs(int v, struct number data, struct cell **adjlist, 
              int *num, int *pre, int *lowpt, int *escan);

main()
/* グラフG =(V, E)の関節点を求めるテストプログラム */
{
 struct edge E[M];    /* グラフの枝集合 */
 int art[N];          /* jが関節点ならart[j]==1, さもなければ0 */
 int i, n, m;
 FILE *file;

 file=fopen("graphdata", "r");
    {
     fscanf(file, "%d", &n);
     fscanf(file, "%d", &m);
    }
 for(i=0; i<m; i++)
   {
    fscanf(file, "%d", &E[i].end1);
    fscanf(file, "%d", &E[i].end2);
   }
 printf("n = %d, m = %d\n", n, m);
 printf("edges i: end1, end2 \n");
 for(i=0; i<m; i++) 
    printf("%d: %d, %d\n", i, E[i].end1, E[i].end2);
 artic(E, art, n, m);
 printf("articulation vertices (= those with 1) \n");
 for(i=0; i<n; i++)
    printf("art[%d] = %d\n", i, art[i]);
 return(0);
}

void artic(struct edge *E, int *art, int n, int m)
/* 節点数n, 枝数m, 枝集合Eをもつグラフのすべての関節点を求める */
/* 結果は配列artに出力 */
{
 int i, j, u, v, v1, v2, ucount;
 int num[N], pre[N], lowpt[N]; 
 int escan[M];               /* 枝iの走査番号; 未走査なら-1 */
 struct number data;
 struct cell  *r, *q, *adjlist[N];

 for(i=0; i<m; i++) escan[i]=-1;    /* 初期化 */
 for(j=0; j<n; j++) {num[j]=pre[j]=-1; art[j]=0; adjlist[j]=NULL;}
 ucount=0;               /* 始点0から出るT(G)の枝の本数 */
 for(i=0; i<m; i++)      /* 隣接リストadjlistの構成 */
   {
    v1=E[i].end1;
    v2=E[i].end2;    
    r=(struct cell *)malloc(sizeof(struct cell));
    r->adj=v2; r->edge=i; r->next=adjlist[v1]; adjlist[v1]=r;
    q=(struct cell *)malloc(sizeof(struct cell));
    q->adj=v1; q->edge=i; q->next=adjlist[v2]; adjlist[v2]=q;
   }
 u=0;                    /* 始点0から深さ優先探索 */
 num[u]=0; lowpt[u]=num[u];
 data.v=1; data.e=0; 
 data=dfs(u, data, adjlist, num, pre, lowpt, escan);
 for(v=0; v<n; v++)      /* 関節点の条件（定理6.4）チェック */
   { 
    u=pre[v];
    if(u==0) ucount=ucount+1;
    if(u>0 && lowpt[v]>=num[u]) art[u]=1; /* uは関節点 */
   }
 if(ucount>1) art[0]=1;  /* 節点0の条件チェック */
 printf("num, pre, lowpt, art\n");
 for(j=0; j<n; j++)
    printf("j = %d: %d, %d, %d, %d\n", j, num[j], pre[j], lowpt[j], art[j]); 
 return;
 }


struct number dfs(int u, struct number data, struct cell **adjlist, 
                  int *num, int *pre, int *lowpt, int *escan)
/* 隣接リストadjlistを用いてuから深さ優先探索; uに関するデータを出力 */
{
 int i, uadj;
 struct cell *p;

 p=adjlist[u];           /* 節点uの隣接リストの探索 */
 while(p!=NULL) 
   {
    i=p->edge;
    if(escan[i]==-1)     /* 枝iは未走査 */
      {
       escan[i]=data.e;
       data.e=data.e+1;
       uadj=p->adj;
       if(num[uadj]==-1)      /* 枝iの先の節点uadjは未探索 */
         {
          num[uadj]=data.v;   /* T(G)にuadjを追加 */
          pre[uadj]=u; lowpt[uadj]=num[uadj];
          data.v=data.v+1;
          /* uadjから深さ優先探索の再帰呼出し */
          data=dfs(uadj, data, adjlist, num, pre, lowpt, escan);
          if(data.lowpt<lowpt[u]) lowpt[u]=data.lowpt;
         }
       else if(num[uadj]<lowpt[u]) lowpt[u]=num[uadj]; /* uadjは探索済 */ 
      }
    p=p->next;           /* 隣接リストの次の枝 */
   }
 data.lowpt=lowpt[u];    /* lowptの更新 */
 return(data);
}
