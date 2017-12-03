/* ��p�v�f��I��SELECT�̃v���O������ */

#include <stdio.h>
#include <stdlib.h>
#define N 500  /* The size of array. */
int select(int i, int j, int p, int *A);
void bubblesort(int i, int j, int *A);
void swap(int i, int j, int *A);
int partition(int i, int j, int a, int *A);

main()
/* p�Ԗڂ̑傫���̗v�f�̑I���̃e�X�g�v���O���� */
{
 int A[N];
 int n, i, p, ap;
 FILE *file;
 file=fopen("selectdata", "r");        /* �f�[�^�t�@�C���̓Ǎ� */
 fscanf(file, "%d", &n);
 fscanf(file, "%d", &p); 
 if(n>N)                               /* �z��T�C�Y�̃`�F�b�N */
   {
    printf("Illegal array size n = %d for N = %d\n", n, N); 
    exit(1);
   }
 for(i=0; i<n; i++) fscanf(file, "%d", &A[i]); 
 printf("n = %d\nA = ", n);            /* A�̏o�� */
 for(i=0; i<n; i++) printf("%d ", A[i]);
 printf("\n"); 
 ap=select(0, n-1, p, A);              /* SELECT�̎��s */
 printf("%d-th smallest element = %d\n", p, ap); /* ���ʂ̏o�� */
 return(0);
}

int select(int i, int j, int p, int *A)
/* �z��A[i],...,A[j]����p�Ԗڂ̑傫���̗v�f���o�� */
{
 int m, a, h, k;

 if(j-i+1 < 50)      /* A�̃T�C�Y���̏ꍇ */
   {
    bubblesort(i, j, A);
    return(A[i+p-1]);
   }
 else                /* A�̃T�C�Y��̏ꍇ */
   {
    m=(j-i+1)/5;
    for(h=0; h<m; h++)                  /* 5�v�f����m�O���[�v�ɕ��� */
      {
       bubblesort(i+5*h, i+5*h+4, A);   /* �e�O���[�v�Ƀo�u���\�[�g */
       swap(i+h, i+5*h+2, A);           /* �e�O���[�v�̒����l��擪�� */
      }
    a=select(i, i+m-1, (j-i+6)/10, A);  /* a: m�̒����l�̒����l */
    k=partition(i, j, a, A);            /* a�ɂ���ĕ��� */
    if(p<=k-i) return(select(i, k-1, p, A)); /* �����������֍ċA�I�K�p */
    else return(select(k, j, p-k+i, A));
   }
}

void bubblesort(int h, int k, int *A)
/* A[k],...,A[h]�̗v�f���o�u���\�[�g�ɂ���Đ��� */
{
 int i, j;
 int test;                   /* test==1; ���łɐ���ς� */

 for(i=h; i<k; i++)          /* �o�u������̔��� */
   {
    test=1;
    for(j=k; j>=i+1; j--) 
      if(A[j]<A[j-1]) {swap(j, j-1, A); test=0;}
    if(test==1) return;
   }
 return;
}

void swap(int i, int j, int *A)
/* Swap A[i] and A[j]. */
{
 int temp;
 temp=A[i]; A[i]=A[j]; A[j]=temp;
 return;
}

int partition(int i, int j, int a, int *A)
/* A[i],...,A[j]�����v�fa�ɂ���ĕ��� */
/* �O����A[i],...,A[k-1]<a, �㔼��A[k],...,A[j]>=a�𖞂��� */
{
 int l, r, k;

 l=i; r=j;                     /* l�͍�����Ar�͉E���� */
 while(1)    
   {
    while(A[l]<a) l=l+1; while(A[r]>=a) r=r-1;  /* l��r�̈ړ� */
    if(l<=r) {swap(l, r, A); l=l+1; r=r-1;}     /* A[l]��A[r]�̌��� */
    else break;                                 /* �I�� */
   }
 k=l;
 return(k);
}
