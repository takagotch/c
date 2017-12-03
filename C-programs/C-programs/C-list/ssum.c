#include <stdio.h>      /* �W�����o�͂̃w�b�_�t�@�C���̓Ǎ��� */
#include <stdlib.h>     /* �W�����C�u�����̃w�b�_�t�@�C���̓Ǎ��� */
#define N 100           /* �z��a[ ]�̍ő�T�C�Y�̒�` */
enum yn {yes, no};      /* �񋓃f�[�^�^�̒�` */
/* �֐��̐錾 */
enum yn ssum(int *a, int b, int *x, int n);
void next(int *x, int n);

main()  
/* ���C���v���O�����F���SUBSET-SUM�̓��o�� */
{
 int a[N], x[N], b;              /* �ϐ��̐錾 */
 int n, j;
 FILE *file;

 file=fopen("ssumdata", "r");    /* ���̓t�@�C�����J�� */
 fscanf(file, "%d", &n);         /* �t�@�C��������̓f�[�^n��Ǎ��� */
 if(n>N)                         /* n�̑傫���`�F�b�N */
   {printf("Illegal array size n = %d for N = %d\n", n, N); exit(1);}
 printf("n = %d\na = ", n);
 for(j=0; j<n; j++) fscanf(file, "%d", &a[j]); /* ���̓f�[�^a[j]�̓Ǎ��� */
 for(j=0; j<n; j++) printf("%d ", a[j]);
 printf("\n");
 fscanf(file, "%d", &b);         /* ���̓f�[�^b�̓Ǎ��� */
 printf("b = %d\n", b);
 if(ssum(a, b, x, n)==yes)       /* �֐�ssum�Ŗ��������A���ʂ��o�� */
   {
    printf("Yes\nx = ");         /* Yes�̏o�� */
    for(j=0; j<n; j++) printf("%d", x[j]);   /* ���̏o�� */
    printf("\n");
   }
 else printf("No\n");            /* No�̏o�� */
 return(0);
}

enum yn ssum(int *a, int b, int *x, int n) 
/* �񋓖@�ɂ��SUBSET-SUM�̃A���S���Y�� */
/* ���̓f�[�^�͔z��a[ ]��b. �ϐ���n��. ����x[ ]�ɒu�����. */
{
 int j, full, temp;              /* �ϐ��̐錾 */

 for(j=0; j<n; j++) x[j]=0;      /* x[ ]�̏����� */
 while(1)                        /* 0-1�x�N�g���̗񋓂Ə����̃`�F�b�N */
   {
    temp=0;
    for(j=0; j<n; j++) temp=temp+x[j]*a[j];
    if(temp==b) return(yes);     /* ���𔭌� */
    full=1; j=0;
    do {full=full*x[j]; j=j+1;} while(full==1 && j<=n-1);
    if(full==1) return(no);      /* ���Ȃ������_ */
    next(x, n);                  /* ����2�i���x�N�g�� */
   }
}

void next(int *x, int n) 
/* 0-1�x�N�g���i�z��jx[0,...,n-1]������2�i���ɍX�V */
{
 int j;

 j=n-1;
 do {x[j]=1-x[j]; j=j-1;} while(x[j+1]==0); 
 return;  
}
