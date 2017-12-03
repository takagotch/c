/* �o�P�b�g�ɂ���\�[�g�̃v���O������ */

#include <stdio.h>
#include <stdlib.h>
#define N 100     /* �z��A�̍ő�T�C�Y */
#define m 10      /* �l�͈̔͂�[0,1,...,m-1] */
#define K 3       /* �꒷ */
struct word       /* �\����word�̐錾 */
{
 int letter[K];
};
struct cell       /* �\����cell�̐錾 */
{
 int index;
 struct cell *next;
};
/* �֐��̐錾 */
void radixsort(struct word *A, int *idx, int n);
void bucketsort(struct word *A, int *idx, int n, int k);
void insert(struct word *A, int idx, struct cell **B, int k);

main()  
/* �A�����X�g�ɂ���\�[�g�̃e�X�g�v���O���� */
{
 struct word A[N];
 int idx[N];
 int i, h, n;

 n=15;
 for(i=0; i<n; i++)    /* �f�[�^�̐��� */
   {
    idx[i]=i;
    for(h=0; h<K; h++) A[i].letter[h]=(765-i*i+3*h*i)%10;
   }
 printf("n = %d\n", n);
 for(i=0; i<n; i++) 
   {
    for(h=0; h<K; h++) printf("%d", A[idx[i]].letter[h]);
    printf(" ");
   }
 printf("\n");
 radixsort(A, idx, n);    /* ��\�[�g�ɂ�鐮�� */
 for(i=0; i<n; i++) 
   {
    for(h=0; h<K; h++) printf("%d", A[idx[i]].letter[h]);
    printf(" ");
   }
 printf("\n"); 
 return(0);
}

void radixsort(struct word *A, int *idx, int n)
/* �z��A[0],...,A[n-1]�̊�\�[�g�ɂ�鐮��B*/
/* ����͔z��idx[0],...,idx[n-1]��p���ĊԐړI�ɍs�� */
{
 int k;
                                       /* �����ƂɃo�P�b�g�\�[�g */
 for(k=K-1; k>=0; k--) bucketsort(A, idx, n, k); 
 return;
}

void bucketsort(struct word *A, int *idx, int n, int k)
/* A[0],...,A[n-1]��k���ڂ̒l�ɂ��������ăo�P�b�g�\�[�g */
/* ����͔z��idx��ŊԐړI�ɍs�� */
{
 struct cell *B[m];               /* �o�P�b�g0,...,m-1 */
 struct cell *p, *q;
 int i, j;

 for(j=0; j<m; j++) B[j]=NULL;                /* �o�P�b�g�̏����� */
 for(i=0; i<n; i++) insert(A, idx[i], B, k);  /* idx[i]���o�P�b�g�� */
 i=n-1;
 for(j=m-1; j>=0; j--)            /* �o�P�b�g����idx�֖߂� */
   {
    p=B[j];
    while(p != NULL) 
      {idx[i] = p->index; i=i-1; q = p->next; free(p); p=q;}
   }
 return;
}

void insert(struct word *A, int ix, struct cell **B, int k)
/* ix��k���ڂ̒lA[ix].letter[k]�̃o�P�b�gB�ɑ}�� */
{
 struct cell *p;

 p=(struct cell *)malloc(sizeof(struct cell));  /* �V�����|�C���^�̊l�� */
 p->index = ix;                                 /* �o�P�b�g�ւ̑}�� */
 p->next = B[A[ix].letter[k]];
 B[A[ix].letter[k]] = p;
 return;
}

