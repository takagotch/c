/* n�v�f�𐮗񂷂�N�C�b�N�\�[�g�̃v���O�����Ⴛ�̂Q
�i���v�f�̑I��@���قȂ�j */

#include <stdio.h>
#include <stdlib.h>
#define N 10000                 /* �z��A�̍ő�T�C�Y */
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
 while(A[l]<a) l=l+1; while(A[r]>=a) r=r-1;
 while(l<=r)                   /* A[l]>=a��A[r]<a������ */
   {
    swap(l, r, A); l=l+1; r=r-1;                /* A[l]��A[r]�̌��� */
    while(A[l]<a) l=l+1; while(A[r]>=a) r=r-1;  /* ����l��r���v�Z */
   }
 k=l;
 return(k);
}

int pivot(int i, int j, int *A)
/* A[i],...,A[j]���玲�v�fA[pv]��I��pv���o�� */
/* s1��s2�̌��݂̕��ōŏ��ɔ�������2�̒l�̑傫�������s�{�b�g�Ƃ��� */
{
 int pv, k, h, s0, s1, s2;
 s0=j-i; s1=(s0+1)/2; 
 if(s0%2==0) s2=s1; else s2=s1-1; 
 h=1;
 k=i+s1;                      /* s1��s2�̌��݂̃X�e�b�v����k�𑝉� */
 while(h<s0 && A[i]==A[k])
   {
    if(h%2==1) k=k+s2; else k=k+s1;  /* ����k */
    if(k>j) k=k-j+i-1;               /* k��j���z����ꍇ�̏C�� */
    h=h+1;
   }
 if(A[i]>A[k]) pv=i; else if(A[i]<A[k]) pv=k; else pv=-1;
 return(pv);
}

void swap(int i, int j, int *A)
/* A[i]��A[j]�̈ʒu�̌��� */
{
 int temp;
 temp=A[i]; A[i]=A[j]; A[j]=temp;
 return;
}
