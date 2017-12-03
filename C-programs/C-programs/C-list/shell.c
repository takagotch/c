/* �V�F���\�[�g�̃v���O������ */

#include <stdio.h>
#define N 500                   /* �z��A�̍ő�T�C�Y */

/* �֐��̐錾 */
void shellsort(int *A, int n);  

main()
/* �V�F���\�[�g�̃e�X�g�v���O���� */
{
 int A[N];
 int n, i;
 FILE *file;

 file=fopen("sortdata", "r");   /* �f�[�^�̓Ǎ��� */
 fscanf(file, "%d", &n);
 if(n>N) 
   {
    printf("Illegal array size n = %d for N = %d\n", n, N); 
    exit();
   }
 printf("n = %d\nA = ", n);
 for(i=0; i<n; i++) fscanf(file, "%d", &A[i]);
 for(i=0; i<n; i++) printf("%d ", A[i]);
 printf("\nA = ");
 shellsort(A, n);               /* �V�F���\�[�g�ɂ�鐮�� */
 for(i=0; i<n; i++) printf("%d ",A[i]);
 printf("\n");
 return(0);
}

void shellsort(int *A, int n)
/* �z��A[0],...,A[n-1]���V�F���\�[�g�ɂ�萮�� */
{
 int i, j, h, a;

 h=1;
 do {h=3*h+1;} while(h<=n);     /* ����h�̌v�Z */
 do
   {
    h=h/3;                      /* ���̔����Ɏg��h */
    for(i=h; i<n; i++)          /* G[i%h]�֑}���\�[�g */
      {
       a=A[i];
       j=i;
       while(a<A[j-h] && j-h>=0)
         {
          A[j]=A[j-h];
          j=j-h;
         }
       A[j]=a;
      }
   }
 while(h>1);
}

