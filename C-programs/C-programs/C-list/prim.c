/* �ŏ��ؖ��ɑ΂���v�����@�̃v���O������ */

#include <stdio.h>
#include <stdlib.h>
#define N 100         /* �ߓ_���̏�� */
#define M 100         /* �}���̏�� */ 
#define ZERO 0.0001   /* �ۂߌ덷�̋��e�l */

struct edge           /* �\����edge�̒�` */
{
 float d;
 int end1, end2;
};
struct value          /* �\����value�̒�` */
{
 float d;
 int node;
};
struct cell           /* �\����cell�̒�` */
{
 int adj;
 int edge;
 struct cell *next;
};

/* �֐��̐錾 */
void prim(struct edge *E, struct edge *T, int n, int m);
void insert(struct value dj, struct value *A, int *loc, int n);
struct value deletemin(struct value *A, int *loc, int n);
void upmin(int i, struct value *A, int *loc, int n);
void downmin(int i, struct value *A, int *loc, int n);
void swap(int i, int j, struct value *A, int *loc);

main()
/* �ŏ��ؖ��ɑ΂���v�����@�̃e�X�g�v���O���� */
{
 struct edge E[M], T[N-1];
 int i, k, n, m;
 FILE *file;

 file=fopen("edgedata", "r");       /* �f�[�^�̓Ǎ��� */
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
 prim(E, T, n, m);                  /* �ŏ��؂̌v�Z */
 printf("MST edges\n");
 for(k=0; k<n-1; k++) 
   printf("%f, %d, %d\n", T[k].d, T[k].end1, T[k].end2);
 return(0);
}

void prim(struct edge *E, struct edge *T, int n, int m)
/*  �ߓ_��n, �}��m, �}�W��E�����O���t�̍ŏ��؂����߂�v�����@; 
���ʂ�T�ɓ���� */
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
          if(loc[vadj] == -1)  /* vadj���q�[�v�ɓ���� */
            {
             vh.d=E[p->edge].d; vh.node=vadj;
             edge[vadj]=p->edge;
             insert(vh, heap, loc, nh);
             nh=nh+1;
            }
          else                 /* ���łɃq�[�v�ɂ���vadj�̍X�V */
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
/* �q�[�vA[0],...,A[n-1]�֐V�����v�fx�̑}��; n=n+1 */
{
 A[n].d=vh.d;
 A[n].node=vh.node;
 loc[A[n].node]=n;
 upmin(n, A, loc, n+1);
}

struct value deletemin(struct value *A, int *loc, int n)
/* �q�[�vA[0],...,A[n-1]����ŏ��v�fA[0]�̏o�͂Ə���; n=n-1 */
{
 struct value min;

 min.d=A[0].d; A[0].d=A[n-1].d;
 min.node=A[0].node; A[0].node=A[n-1].node;
 loc[A[0].node]=0;
 if(n>1) downmin(0, A, loc, n-1);
 return(min);
}

void upmin(int i, struct value *A, int *loc, int n)
/* A[i]�������ցA�q�[�v�����񕜂̂���swap�����K�p */
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
/* A[i]���牺���ցA�q�[�v�����񕜂̂��߂�swap�����K�p */
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
/* �q�[�vA�ɂ�����\����A[i]��A[j]�̌��� */
{
 struct value temp;

 temp=A[i]; A[i]=A[j]; A[j]=temp;
 loc[A[i].node]=i; loc[A[j].node]=j;           /* loc�̍X�V */
 return;
}

