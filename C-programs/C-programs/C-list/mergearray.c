/* 整列配列AとBの併合プログラム例 */

#include <stdio.h>
#define N 100                /* 配列の最大サイズ */
/* 関数の宣言 */
void merge(int *A, int nA, int *B, int nB, int i, int *C);

main()
/* 整列配列AとBを併合しCに入れるテストプログラム */
{
 int A[N], B[N], C[2*N];
 int nA, nB, nC;
 int i;

 nA=10; nB=15;             /* データの生成 */
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
 merge(A, nA, B, nB, 0, C);       /* 整列配列AとBの併合 */
 printf("C = ");
 for(i=0; i<nC; i++) printf("%d ", C[i]); 
 printf("\n");
 return(0);
}


void merge(int *A, int nA, int *B, int nB, int i, int *C)
/* 整列配列A[0],...,A[nA-1]とB[0],...,B[nB-1]を併合し整列配列
C[i],...,C[i+nA+nB-1]に入れる */
{
 int iA, iB, iC;     /* iAはAの添字、iBはBの添字、iCは合計 */

 iA = iB = iC = 0;   /* 併合の開始 */
 while(iC <= nA+nB-1)
   {
    if(iA >= nA) {C[i+iC] = B[iB]; iB = iB+1;}     /* Aは既に空 */
    else 
      {
       if(iB >= nB) {C[i+iC] = A[iA]; iA = iA+1;}  /* Bは既に空 */
       else          /* A[iA]とB[iB]の小さい方をCへ */
         {
          if(A[iA] <= B[iB]) {C[i+iC] = A[iA]; iA = iA+1;}
          else {C[i+iC] = B[iB]; iB = iB+1;}
         }
      }
    iC = iC+1;
   }
 return;
}
