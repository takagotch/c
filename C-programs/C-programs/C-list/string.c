/* ������ƍ����s��BM�@�̃v���O������ */

#include <stdio.h>
#define N 1000       /* �e�L�X�g�̍ő咷 */
#define M 100        /* �p�^�[���̍ő咷 */ 
#define A 128        /* �A���t�@�x�b�g�̕����� */

/* �֐��̐錾 */
int bm(char *t, char *p, int n, int m);
void fd(char *p, int *d, int m);
void fe(char *p, int *e, int m);

main()
/* ������ƍ��̃e�X�g�v���O���� */
{
 char t[N], p[M];                   /* �e�L�X�gt, �p�^�[��p */
 int h, n, m;
 FILE *file;                        /* �t�@�C���̏��� */

 n=0; m=0;
 file=fopen("textdata", "r");       /* �e�L�X�g�f�[�^�̓Ǎ��� */
 printf("text:\n");
 while (fscanf(file, "%c", &t[n]) != EOF)   /* �e�L�X�g�̏o�� */
   {
    printf("%c", t[n]);
    n=n+1;
   }
 printf("\n");
 file=fopen("patterndata", "r");    /* �p�^�[���f�[�^�̓Ǎ��� */
 printf("pattern:\n");
 while (fscanf(file, "%c", &p[m]) != EOF)   /* �p�^�[���̏o�� */
   {
    printf("%c", p[m]);
    m=m+1;
   }
 n=n-1; m=m-1;
 printf("\nn= %d, m = %d\n", n, m);
 h=bm(t, p, n, m);                  /* BM�@�̎��s */
 printf("first location: %d\n", h); /* ���ʂ̏o�� */
 return(0);
}

int bm(char *t, char *p, int n, int m)
/* ����n�̃e�L�X�gt�ƒ���m�̃p�^�[��p��BM�@��K�p���Ap��
�ŏ��̈ʒu���o�́ip���Ȃ����-1�j */
{
 int h, j, s;
 int d[A], e[M];

 fd(p, d, m);                /* �p�^�[��p�ɑ΂�d(a)�̌v�Z */
 fe(p, e, m);                /* �p�^�[��p�ɑ΂�e(j)�̌v�Z */
 h=0;  
 while(h+m-1 < n)            /* �ʒuh�̃p�^�[��p��t�̏ƍ� */
   {
    j=m-1;
    while(j>=0 && t[h+j]==p[j]) j=j-1;
    if(j==-1) return(h);     /* �p�^�[��p�𔭌� */
    else                     /* p�����̈ʒu�ֈړ� */
      {
       s=j-d[(int)t[h+j]]; 
       if(e[j] > s) s=e[j];
       h=h+s;
      }
   }
 return(-1);                 /* �p�^�[��p�͑��݂��Ȃ� */
}


void fd(char *p, int *d, int m)
/* ����m�̃p�^�[��p�ɑ΂��֐�d�̌v�Z */
{
 int i, k;

 for(i=0; i<A; i++) d[i]=-1;
 for(k=0; k<m; k++) d[(int)p[k]]=k;
 return;
}


void fe(char *p, int *e, int m)
/* ����m�̃p�^�[��p�ɑ΂��֐�g��e�̌v�Z */
/* g(k), k=-1,0,...,m-1��g[0],g[1],...,g[m]�Ɋi�[ */
{
 int i, j, k, l;
 int g[M+1];                 /* g���i�[����z�� */

 j=m; k=m-1;
 while(k >= 0)               /* g�̌v�Z */
   {
    g[k+1]=j;
    while(j<=m-1 && p[k]!=p[j]) j=g[j+1];
    j=j-1; k=k-1;
   }
 g[0]=j;
 for(k=0; k<m; k++) e[k]=m;  /* e�̌v�Z */
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