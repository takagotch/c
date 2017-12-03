#include <stdio.h>
#define N 100   /* The max size of array. */
void arraymerge(int *A, int nA, int *B, int nB, int *C);

main()
/* Merge two sorted arrays A of nA elments and B of nB elements. */
{
 int A[N], B[N], C[2*N];
 int nA, nB, nC;
 int i;
 nA=10; nB=15; 
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
 arraymerge(A, nA, B, nB, C);
 printf("C = ");
 for(i=0; i<nC; i++) printf("%d ", C[i]); 
 printf("\n");
 return(0);
}


void arraymerge(int *A, int nA, int *B, int nB, int *C)
/* Merge two sorted arrays A of nA elments and B of nB elements
into C of nA+nB elements. */
{
 int iA, iB, iC;
 iA=0; iB=0; iC=0;
 while(iA<nA || iB<nB)
   {
    if((iA<nA && iB<nB && A[iA]<=B[iB]) || iB==nB) 
      {C[iC]=A[iA]; iA=iA+1;}
    else 
      {C[iC]=B[iB]; iB=iB+1;}
    iC=iC+1;
   }
 return;
}
