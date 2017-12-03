/* マージソートのプログラム例 */

#include <stdio.h>
#include <stdlib.h>
#define N 500      /* 配列Aの最大サイズ */

/* 関数の宣言 */
void mergesort(int i, int j, int *A);
void merge(int *A, int nA, int *B, int nB, int i, int *C);

main()
/* マージソートのテストプログラム */
{
 int A[N];
 int n, i;
 FILE *file;

 file=fopen("sortdata", "r");   /* データの読込み */
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
 mergesort(0, n-1, A);          /* マージソートによる整列 */
 for(i=0; i<n; i++) printf("%d ",A[i]);
 printf("\n");
 return(0);
}

void mergesort(int i, int j, int *A)
/* 配列A[i],...,A[j]をマージソートにより整列 */
{
 int k, n, n1, n2, mid;
 int A1[N], A2[N];

 n=j-i+1;                    /* 配列のサイズ */
 if(n>1)
   {
    mid=i+(n-1)/2;           /* 中央値により前後の部分配列へ分割 */
    mergesort(i, mid, A);    /* 前半の整列 */
    mergesort(mid+1, j, A);  /* 後半の整列 */
    n1=mid-i+1; 
    for(k=i; k<=mid; k++) A1[k-i]=A[k];       /* A1は前半の部分配列 */
    n2=j-mid;
    for(k=mid+1; k<=j; k++) A2[k-mid-1]=A[k]; /* A2は後半の部分配列 */
    merge(A1, n1, A2, n2, i, A);              /* A1とA2の併合 */
   }
 return;
}

void merge(int *A, int nA, int *B, int nB, int i, int *C)
/* 整列配列A[0],...,A[nA-1]とB[0],...,B[nB-1]を併合し整列配列
C[i],...,C[i+nA+nB-1]に入れる */
{
 int iA, iB, iC;       /* iAはAの添字、iBはBの添字、iCは合計 */

 iA=iB=iC=0;           /* 併合の開始 */
 while(iC <= nA+nB-1)
   {
    if(iA>=nA) {C[i+iC]=B[iB]; iB=iB+1;}      /* Aは既に空 */
    else 
      {
       if(iB>=nB) {C[i+iC]=A[iA]; iA=iA+1;}   /* Bは既に空 */
       else            /* A[iA]とB[iB]の小さい方をCへ移す */
         {
          if(A[iA]<=B[iB]) {C[i+iC]=A[iA]; iA=iA+1;}
          else {C[i+iC]=B[iB]; iB=iB+1;}
         }
      }
    iC=iC+1;
   }
 return;
}
