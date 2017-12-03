#include <stdio.h>
#define N 100        /* �z��A�̍ő�T�C�Y */
enum yn {yes, no};   /* �񋓌^�f�[�^yn�̒�` */
/* �֐��̐錾 */
enum yn bsearch(int x, int *A, int n); 

main()
/* �z���̂Q���T���̃e�X�g�v���O���� */
{
 int A[N];
 int i, x, nA;
 enum yn ans;
 nA=15; 
 for(i=0; i<nA; i++)
   {
    A[i]=5+2*i;
   }
 printf("A = ");
 for(i=0; i<nA; i++) printf("%d ", A[i]); 
 printf("\n");
 x=7;
 printf("x = %d\n", x);
 ans=bsearch(x, A, nA);
 if(ans==yes) printf("Answer = yes\n");
 else printf("Answer = no\n"); 
 return(0);
}

enum yn bsearch(int x, int *A, int n)
/* ����z��A[0],...,A[n-1]���x�̂Q���T���Gyes���邢��no�̏o�� */
{
 int iL, iR, iM;     /* iL�͍��AiR�͉E�AiM�͒����̃C���f�b�N�X */
 iL=0; iR=n-1;
 if(A[iL]==x || A[iR]==x) return(yes);  /* ���������ł̃`�F�b�N */
 if(x<A[iL] || x>A[iR]) return(no);
 while(iR-iL>1)               /* 2���T�� */
   {
    iM=(iL+iR)/2;             /* �����l */
    if(A[iM]==x) return(yes);
    if(A[iM]<x) iL=iM;        /* �V�����C���f�b�N�X�̐ݒ� */
    else iR=iM;
   }
 return(no);
}

