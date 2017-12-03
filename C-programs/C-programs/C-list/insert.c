/* �}���\�[�g�̃v���O������ */

#include <stdio.h>
#include <stdlib.h>
#define N 500            /* �z��A�̍ő�T�C�Y */

/* �֐��̐錾 */
void insertionsort(int *A, int n); 

main()
/* �}���\�[�g�̃e�X�g�v���O���� */
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
 insertionsort(A, n);            /* �}���\�[�g�ɂ�鐮�� */
 for(i=0; i<n; i++) printf("%d ",A[i]);
 printf("\n");
 return(0);
}

void insertionsort(int *A, int n)
/* �z��A[0],...,A[n-1]��}���\�[�g�ɂ�萮�� */
{
 int i, k, a;

 for(i=1; i<n; i++)
   {
    a=A[i];
    k=i;
    while(a<A[k-1] && k-1>=0)
      {
       A[k]=A[k-1];
       k=k-1;
      }
    A[k]=a;
   }
}

