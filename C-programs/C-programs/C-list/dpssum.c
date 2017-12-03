/* SUBSET-SUM�����������I�v��@�̃v���O������ */

#include <stdio.h>
#include <stdlib.h>
#define N 100          /* �z��A�̍ő�T�C�Y */
#define B 10000        /* �W��b+1�̍ő�T�C�Y */
enum yn {yes, no};     /* �񋓌^�f�[�^yn�̒�` */

/* �֐��̐錾 */
enum yn dpssum(int *a, int b, int n);  

main()  
/* SUBSET-SUM�����������I�v��@�̃e�X�g�v���O���� */
{
 int a[N], b;
 int n, j;
 FILE *file;

 file=fopen("ssumdata", "r");
 fscanf(file, "%d", &n);
 if(n>N) 
   {
    printf("Illegal array size n = %d for N = %d\n", n, N); 
    exit(1);
   }
 printf("n = %d\na = ", n);
 for(j=0; j<n; j++) fscanf(file, "%d", &a[j]);
 for(j=0; j<n; j++) printf("%d ", a[j]);
 printf("\n");
 fscanf(file, "%d", &b); 
 if(b>=B) 
   {
    printf("Illegal size b = %d for B = %d\n", b, B); 
    exit(1);
   }
 printf("b = %d\n", b);
 if(dpssum(a, b, n)==yes) printf("Yes\n");
 else printf("No\n");
 return(0);
}

enum yn dpssum(int *a, int b, int n) 
/* �W��a[0],...,a[n-1],b�ɑ΂�SUBSET-SUM���̉��̑��ݔ��� */
{
 int y[N][B];                   /* ���I�v��@�̌v�Z�\ */
 int k, p;

 for(k=0; k<n; k++) for(p=0; p<=b; p++) y[k][p]=0;  /* �����ݒ� */
 y[0][0]=1; 
 if(a[0]<=b) y[0][a[0]]=1;
 for(k=1; k<n; k++)             /* ���I�v��@�̔��� */
   for(p=0; p<=b; p++)
     {
      if(y[k-1][p]==1) y[k][p]=1;
      else if(p-a[k]>=0 && y[k-1][p-a[k]]==1) y[k][p]=1;
     }
 if(y[n-1][b]==1) return(yes);  /* ���� */
 else return(no);
}

