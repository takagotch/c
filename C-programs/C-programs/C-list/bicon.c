/* �[���D��T���ɂ���ăO���t�̊֐ߓ_�����߂�A���S���Y���̃v���O������ */

#include <stdio.h>
#include <stdlib.h>
#define N 100         /* �ߓ_���̏�� */
#define M 500         /* �}���̏�� */
struct edge           /* �\����edge�̒�` */
{
 int end1, end2;
};
struct cell           /* �\����cell�̒�` */
{  
 int adj;
 int edge;
 struct cell *next;
};
struct number         /* �\����number�̒�` */
{
 int v, e, lowpt;
};

/* �֐��̐錾 */
void artic(struct edge *E, int *art, int n, int m);
struct number dfs(int v, struct number data, struct cell **adjlist, 
              int *num, int *pre, int *lowpt, int *escan);

main()
/* �O���tG =(V, E)�̊֐ߓ_�����߂�e�X�g�v���O���� */
{
 struct edge E[M];    /* �O���t�̎}�W�� */
 int art[N];          /* j���֐ߓ_�Ȃ�art[j]==1, �����Ȃ����0 */
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
/* �ߓ_��n, �}��m, �}�W��E�����O���t�̂��ׂĂ̊֐ߓ_�����߂� */
/* ���ʂ͔z��art�ɏo�� */
{
 int i, j, u, v, v1, v2, ucount;
 int num[N], pre[N], lowpt[N]; 
 int escan[M];               /* �}i�̑����ԍ�; �������Ȃ�-1 */
 struct number data;
 struct cell  *r, *q, *adjlist[N];

 for(i=0; i<m; i++) escan[i]=-1;    /* ������ */
 for(j=0; j<n; j++) {num[j]=pre[j]=-1; art[j]=0; adjlist[j]=NULL;}
 ucount=0;               /* �n�_0����o��T(G)�̎}�̖{�� */
 for(i=0; i<m; i++)      /* �אڃ��X�gadjlist�̍\�� */
   {
    v1=E[i].end1;
    v2=E[i].end2;    
    r=(struct cell *)malloc(sizeof(struct cell));
    r->adj=v2; r->edge=i; r->next=adjlist[v1]; adjlist[v1]=r;
    q=(struct cell *)malloc(sizeof(struct cell));
    q->adj=v1; q->edge=i; q->next=adjlist[v2]; adjlist[v2]=q;
   }
 u=0;                    /* �n�_0����[���D��T�� */
 num[u]=0; lowpt[u]=num[u];
 data.v=1; data.e=0; 
 data=dfs(u, data, adjlist, num, pre, lowpt, escan);
 for(v=0; v<n; v++)      /* �֐ߓ_�̏����i�藝6.4�j�`�F�b�N */
   { 
    u=pre[v];
    if(u==0) ucount=ucount+1;
    if(u>0 && lowpt[v]>=num[u]) art[u]=1; /* u�͊֐ߓ_ */
   }
 if(ucount>1) art[0]=1;  /* �ߓ_0�̏����`�F�b�N */
 printf("num, pre, lowpt, art\n");
 for(j=0; j<n; j++)
    printf("j = %d: %d, %d, %d, %d\n", j, num[j], pre[j], lowpt[j], art[j]); 
 return;
 }


struct number dfs(int u, struct number data, struct cell **adjlist, 
                  int *num, int *pre, int *lowpt, int *escan)
/* �אڃ��X�gadjlist��p����u����[���D��T��; u�Ɋւ���f�[�^���o�� */
{
 int i, uadj;
 struct cell *p;

 p=adjlist[u];           /* �ߓ_u�̗אڃ��X�g�̒T�� */
 while(p!=NULL) 
   {
    i=p->edge;
    if(escan[i]==-1)     /* �}i�͖����� */
      {
       escan[i]=data.e;
       data.e=data.e+1;
       uadj=p->adj;
       if(num[uadj]==-1)      /* �}i�̐�̐ߓ_uadj�͖��T�� */
         {
          num[uadj]=data.v;   /* T(G)��uadj��ǉ� */
          pre[uadj]=u; lowpt[uadj]=num[uadj];
          data.v=data.v+1;
          /* uadj����[���D��T���̍ċA�ďo�� */
          data=dfs(uadj, data, adjlist, num, pre, lowpt, escan);
          if(data.lowpt<lowpt[u]) lowpt[u]=data.lowpt;
         }
       else if(num[uadj]<lowpt[u]) lowpt[u]=num[uadj]; /* uadj�͒T���� */ 
      }
    p=p->next;           /* �אڃ��X�g�̎��̎} */
   }
 data.lowpt=lowpt[u];    /* lowpt�̍X�V */
 return(data);
}
