/* 2�i���̊�\�[�g�̃v���O������ */

#include <stdio.h>
#include <stdlib.h>
#define N 100         /* �z��A�̍ő�T�C�Y */
#define K 5           /* �꒷ */
struct word           /* �\����word�̒�` */
{
 int letter[K];
};

/* �֐��̐錾 */
void biradixsort(struct word *A, int *iA, int n);

main()  
/* 2�i���̊�\�[�g�̃e�X�g�v���O���� */
{
 struct word A[N];    /* K����2�i��word�̔z�� */
 int iA[N];           /* �z��A�̃C���f�b�N�X */
 int i, h, n;
 FILE *file;

 file=fopen("bidata", "r");  /* �f�[�^�̓Ǎ��� */
 fscanf(file, "%d", &n);
 if(n>N) 
   {
    printf("Illegal size n = %d for N = %d\n", n, N); 
    exit(1);
   }
 printf("n = %d, K = %d\nA = \n", n, K);
 for(i=0; i<n; i++) 
   {
    for(h=0; h<K; h++) fscanf(file, "%1d", &A[i].letter[h]);
   }
 for(i=0; i<n; i++) 
   {
    for(h=0; h<K; h++) printf("%1d", A[i].letter[h]);
    printf("\n");
   }
 biradixsort(A, iA, n);       /* 2�i���̊�\�[�g�̎��s */
 printf("Sorted A =\n");
 for(i=0; i<n; i++) 
   {
    for(h=0; h<K; h++) printf("%1d", A[iA[i]].letter[h]);
    printf("\n");
   }
 return(0);
}

void biradixsort(struct word *A, int *iA, int n)
/* 2�i���i�\����word�j�̔z��A[0],...,A[n-1]����\�[�g�ɂ�萮�� */
{
 int i, k, count, i0, i1;
 int iB[N];                   /* �z��̃C���f�b�N�X */

 for(i=0; i<n; i++) iA[i]=i;         /* ������ */
 for(k=K-1; k>=0; k--)
   {
    count=0;                 /* k���ڂ̒l��0�ł���v�f���𐔂��� */
    for(i=0; i<n; i++) if(A[i].letter[k]==0) count=count+1;
    i0=0; i1=count;
    for(i=0; i<n; i++)       /* k���ڂ̒l�ɂ���������A����B�ֈړ� */
      {
       if(A[iA[i]].letter[k]==0)     /* k���ڂ̒l��0 */
         {  
          iB[i0]=iA[i];
          i0=i0+1;
         }
       else                          /* k���ڂ̒l��1 */
         {  
          iB[i1]=iA[i];
          i1=i1+1;
         }
      }
    for(i=0; i<n; i++) iA[i]=iB[i];  /* iB��iA�ֈړ� */
   }
 return;
}


