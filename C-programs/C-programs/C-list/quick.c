/* �N�C�b�N�\�[�g�̃v���O������ */

#include <stdio.h>
#include <stdlib.h>
#define N 500             /* �z��A�̍ő�T�C�Y */
/* �֐��̐錾 */
void quicksort(int i, int j, int *A);
int partition(int i, int j, int a, int *A);
int pivot(int i, int j, int *A);
void swap(int i, int j, int *A);

main()
/* �N�C�b�N�\�[�g�̃e�X�g�v���O���� */
{
 int A[N];
 int n, i;
 FILE *file;

 file=fopen("sortdata", "r");            /* �f�[�^�̓Ǎ��� */
 fscanf(file, "%d", &n);
 if(n>N) 
   {
    printf("Illegal array size n = %d for N = %d\n", n, N); 
    exit(1);
   }
 printf("n = %d\nA = ", n);
 for(i=0; i<n; i++) fscanf(file, "%d", &A[i]);
 for(i=0; i<n; i++) printf("%d ", A[i]);
 printf("\nA = ");
 quicksort(0, n-1, A);   /* �N�C�b�N�\�[�g�ɂ��z��A�̐��� */
 for(i=0; i<n; i++) printf("%d ",A[i]);
 printf("\n");
 return(0);
}

void quicksort(int i, int j, int *A)
/* �z��A[i],...,A[j]���N�C�b�N�\�[�g�ɂ�萮�� */
{
 int a, pv, k;

 pv=pivot(i, j, A);
 if(pv!=-1)                    /* ���v�f�����������ꍇ */
   {
    a=A[pv];                   /* ���v�f */
    k=partition(i, j, a, A);   /* ���v�fA[pv]�ɂ�蕪�� */
    quicksort(i, k-1, A);      /* �O���̐��� */
    quicksort(k, j, A);        /* �㔼�̐��� */
   }
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
    if(l<=r) {swap(l, r, A); l=l+1; r=r-1;}    /* A[l]��A[r]�̌��� */
    else break;                                 /* �I�� */
   }
 k=l;
 return(k);
}

int pivot(int i, int j, int *A)
/* A[i],...,A[j]���玲�v�fA[pv]��I��pv���o�� */
/* A[pv]��A[i]�ƍŏ��ɈقȂ�A[k]�̑傫�����G���ׂē����Ȃ�pv=-1 */
{
 int pv, k;

 k=i+1;
 while(k<=j && A[i]==A[k]) k=k+1;
 if(k>j) pv=-1;
 else if(A[i]>=A[k]) pv=i;
 else pv=k;
 return(pv);
}

void swap(int i, int j, int *A)
/* Swap A[i] and A[j]. */
{
 int temp;
 temp=A[i]; A[i]=A[j]; A[j]=temp;
 return;
}
