/* �o�u���\�[�g�̃v���O������ */

#include <stdio.h>
#include <stdlib.h>
#define N 500   /* The max size of array. */
void bubblesort(int h, int k, int *A);
void swap(int i, int j, int *A);

main()
/* �o�u���\�[�g�̃e�X�g�v���O���� */
{
 int A[N];
 int n, i;
 FILE *file;

 file=fopen("sortdata", "r");  /* �f�[�^�̓Ǎ��� */
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
 bubblesort(0, n-1, A);      /* �z��A[0]����A[n-1]�̐��� */
 for(i=0; i<n; i++) printf("%d ",A[i]);
 printf("\n");
 return(0);
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
