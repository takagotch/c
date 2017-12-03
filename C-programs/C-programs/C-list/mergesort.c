/* �}�[�W�\�[�g�̃v���O������ */

#include <stdio.h>
#include <stdlib.h>
#define N 500      /* �z��A�̍ő�T�C�Y */

/* �֐��̐錾 */
void mergesort(int i, int j, int *A);
void merge(int *A, int nA, int *B, int nB, int i, int *C);

main()
/* �}�[�W�\�[�g�̃e�X�g�v���O���� */
{
 int A[N];
 int n, i;
 FILE *file;

 file=fopen("sortdata", "r");   /* �f�[�^�̓Ǎ��� */
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
 mergesort(0, n-1, A);          /* �}�[�W�\�[�g�ɂ�鐮�� */
 for(i=0; i<n; i++) printf("%d ",A[i]);
 printf("\n");
 return(0);
}

void mergesort(int i, int j, int *A)
/* �z��A[i],...,A[j]���}�[�W�\�[�g�ɂ�萮�� */
{
 int k, n, n1, n2, mid;
 int A1[N], A2[N];

 n=j-i+1;                    /* �z��̃T�C�Y */
 if(n>1)
   {
    mid=i+(n-1)/2;           /* �����l�ɂ��O��̕����z��֕��� */
    mergesort(i, mid, A);    /* �O���̐��� */
    mergesort(mid+1, j, A);  /* �㔼�̐��� */
    n1=mid-i+1; 
    for(k=i; k<=mid; k++) A1[k-i]=A[k];       /* A1�͑O���̕����z�� */
    n2=j-mid;
    for(k=mid+1; k<=j; k++) A2[k-mid-1]=A[k]; /* A2�͌㔼�̕����z�� */
    merge(A1, n1, A2, n2, i, A);              /* A1��A2�̕��� */
   }
 return;
}

void merge(int *A, int nA, int *B, int nB, int i, int *C)
/* ����z��A[0],...,A[nA-1]��B[0],...,B[nB-1]�𕹍�������z��
C[i],...,C[i+nA+nB-1]�ɓ���� */
{
 int iA, iB, iC;       /* iA��A�̓Y���AiB��B�̓Y���AiC�͍��v */

 iA=iB=iC=0;           /* �����̊J�n */
 while(iC <= nA+nB-1)
   {
    if(iA>=nA) {C[i+iC]=B[iB]; iB=iB+1;}      /* A�͊��ɋ� */
    else 
      {
       if(iB>=nB) {C[i+iC]=A[iA]; iA=iA+1;}   /* B�͊��ɋ� */
       else            /* A[iA]��B[iB]�̏���������C�ֈڂ� */
         {
          if(A[iA]<=B[iB]) {C[i+iC]=A[iA]; iA=iA+1;}
          else {C[i+iC]=B[iB]; iB=iB+1;}
         }
      }
    iC=iC+1;
   }
 return;
}
