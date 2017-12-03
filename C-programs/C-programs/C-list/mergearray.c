/* ����z��A��B�̕����v���O������ */

#include <stdio.h>
#define N 100                /* �z��̍ő�T�C�Y */
/* �֐��̐錾 */
void merge(int *A, int nA, int *B, int nB, int i, int *C);

main()
/* ����z��A��B�𕹍���C�ɓ����e�X�g�v���O���� */
{
 int A[N], B[N], C[2*N];
 int nA, nB, nC;
 int i;

 nA=10; nB=15;             /* �f�[�^�̐��� */
 nC=nA+nB;
 for(i=0; i<nA; i++)
   {
    A[i]=5+2*i;
   }
 for(i=0; i<nB; i++)
   {
    B[i]=3*i;
   }
 printf("A = ");
 for(i=0; i<nA; i++) printf("%d ", A[i]); 
 printf("\n");
 printf("B = ");
 for(i=0; i<nB; i++) printf("%d ", B[i]); 
 printf("\n");
 merge(A, nA, B, nB, 0, C);       /* ����z��A��B�̕��� */
 printf("C = ");
 for(i=0; i<nC; i++) printf("%d ", C[i]); 
 printf("\n");
 return(0);
}


void merge(int *A, int nA, int *B, int nB, int i, int *C)
/* ����z��A[0],...,A[nA-1]��B[0],...,B[nB-1]�𕹍�������z��
C[i],...,C[i+nA+nB-1]�ɓ���� */
{
 int iA, iB, iC;     /* iA��A�̓Y���AiB��B�̓Y���AiC�͍��v */

 iA = iB = iC = 0;   /* �����̊J�n */
 while(iC <= nA+nB-1)
   {
    if(iA >= nA) {C[i+iC] = B[iB]; iB = iB+1;}     /* A�͊��ɋ� */
    else 
      {
       if(iB >= nB) {C[i+iC] = A[iA]; iA = iA+1;}  /* B�͊��ɋ� */
       else          /* A[iA]��B[iB]�̏���������C�� */
         {
          if(A[iA] <= B[iB]) {C[i+iC] = A[iA]; iA = iA+1;}
          else {C[i+iC] = B[iB]; iB = iB+1;}
         }
      }
    iC = iC+1;
   }
 return;
}
