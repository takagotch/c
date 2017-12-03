/* �����z�����ɑ΂��鑝���@�̃v���O������ */

#include <stdio.h>
#include <math.h>
#define M 100         /* �z��A�̍ő�T�C�Y */
struct value          /* �\����value�̒�` */
{
 float d;
 int j;
};
/* �֐��̐錾 */
void resource(int n, int N);
float fn(float x, int j);
struct value deletemin(struct value *A, int n);
void downmin(int i, struct value *A, int n);
void insert(struct value dj, struct value *A, int n);
void upmin(int i, struct value *A, int n);
void heapify(struct value *A, int n);
void swap(int i, int j, struct value *A);

main()
/* �����z�����̃e�X�g�v���O���� */
{
 int n, N;

 n=5; N=6;      /* �ϐ��̐�n�ƉE�ӂ̒lN�̐ݒ� */
 resource(n, N);
 return(0);
}

void resource(int n, int N)
/* �����@��p���Ď����z����������. �ϐ��̌�n, �E�ӂ̒lN. */
{
 struct value dj, min, inc[M];  /* inc�͑����ʂ𒙂���q�[�v */
 int j, i, x[M];                /* x�͉� */
 float sum, fjx, fjx1;

 sum=0.0;
 for(j=0; j<n; j++)             /* ������ */
   {
    x[j]=0;                     /* ������ */
    fjx=fn(0.0, j); fjx1=fn(1.0, j);
    sum=sum+fjx;
    inc[j].d=fjx1-fjx; inc[j].j=j;
   }
 heapify(inc, n);               /* �����q�[�v */
 for(i=1; i<=N; i++)            /* �����@�̔��� */
   {
    min=deletemin(inc, n);
    x[min.j]=x[min.j]+1;        /* �����ʍŏ���xj��1���� */
    sum=sum+min.d;
    fjx=fn(x[min.j], min.j);    
    fjx1=fn(x[min.j]+1.0, min.j);
    dj.d=fjx1-fjx; dj.j=min.j;
    insert(dj, inc, n-1);       /* �q�[�v�̍X�V */
   }
 printf("Solution x =");        /* �œK���̏o�� */
 for(j=0; j<n; j++) printf("%d ", x[j]);
 printf("\n");
 printf("Objective value = %f\n", sum);
 return;
}

float fn(float x, int j)
/* �ړI�֐��lfj(x)��^����v���O������ */
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
/* �q�[�vA[0],...,A[n-1]�֐V�����v�fx�̑}��; n=n+1 */
{
 A[n]=dj;
 upmin(n, A, n+1);
}

struct value deletemin(struct value *A, int n)
/* �q�[�vA[0],...,A[n-1]����ŏ��v�fA[0]�̏o�͂Ə���; n=n-1 */
{
 struct value min;

 min=A[0]; A[0]=A[n-1];
 if(n>1) downmin(0, A, n-1);
 return(min);
}

void upmin(int i, struct value *A, int n)
/* A[i]�������ցA�q�[�v�����񕜂̂���swap�����K�p */
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
/* A[i]���牺���ցA�q�[�v�����񕜂̂��߂�swap�����K�p�G
�Ō�̗v�f��A[n-1] */
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
/* A[0],...,A[n-1]���q�[�v�� */
{
 int i;

 for(i=n/2-1; i>=0; i--) downmin(i, A, n);
 return;
}

void swap(int i, int j, struct value *A)
/* �\����A[i]��A[j]�̌��� */
{
 struct value temp;
 temp=A[i]; A[i]=A[j]; A[j]=temp;
 return;
}

