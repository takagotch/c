/* シェルソートのプログラム例 */

#include <stdio.h>
#define N 500                   /* 配列Aの最大サイズ */

/* 関数の宣言 */
void shellsort(int *A, int n);  

main()
/* シェルソートのテストプログラム */
{
 int A[N];
 int n, i;
 FILE *file;

 file=fopen("sortdata", "r");   /* データの読込み */
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
 shellsort(A, n);               /* シェルソートによる整列 */
 for(i=0; i<n; i++) printf("%d ",A[i]);
 printf("\n");
 return(0);
}

void shellsort(int *A, int n)
/* 配列A[0],...,A[n-1]をシェルソートにより整列 */
{
 int i, j, h, a;

 h=1;
 do {h=3*h+1;} while(h<=n);     /* 初期hの計算 */
 do
   {
    h=h/3;                      /* この反復に使うh */
    for(i=h; i<n; i++)          /* G[i%h]へ挿入ソート */
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

