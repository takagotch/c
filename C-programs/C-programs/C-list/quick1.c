/* n要素を整列するクイックソートのプログラム例その２
（軸要素の選択法が異なる） */

#include <stdio.h>
#include <stdlib.h>
#define N 10000                 /* 配列Aの最大サイズ */
/* 関数の宣言 */
void quicksort(int i, int j, int *A);
int partition(int i, int j, int a, int *A);
int pivot(int i, int j, int *A);
void swap(int i, int j, int *A);

main()
/* クイックソートのテストプログラム */
{
 int A[N];
 int n, i;
 FILE *file;

 file=fopen("sortdata", "r");            /* データの読込み */
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
 quicksort(0, n-1, A);   /* クイックソートによる配列Aの整列 */
 for(i=0; i<n; i++) printf("%d ",A[i]);
 printf("\n");
 return(0);
}

void quicksort(int i, int j, int *A)
/* 配列A[i],...,A[j]をクイックソートにより整列 */
{
 int a, pv, k;
 pv=pivot(i, j, A);
 if(pv!=-1)                    /* 軸要素が見つかった場合 */
   {
    a=A[pv];                   /* 軸要素 */
    k=partition(i, j, a, A);   /* 軸要素A[pv]により分割 */
    quicksort(i, k-1, A);      /* 前半の整列 */
    quicksort(k, j, A);        /* 後半の整列 */
   }
 return;
}

int partition(int i, int j, int a, int *A)
/* A[i],...,A[j]を軸要素aによって分割 */
/* 前半はA[i],...,A[k-1]<a, 後半はA[k],...,A[j]>=aを満たす */
{
 int l, r, k;
 l=i; r=j;                     /* lは左から、rは右から */
 while(A[l]<a) l=l+1; while(A[r]>=a) r=r-1;
 while(l<=r)                   /* A[l]>=aとA[r]<aが成立 */
   {
    swap(l, r, A); l=l+1; r=r-1;                /* A[l]とA[r]の交換 */
    while(A[l]<a) l=l+1; while(A[r]>=a) r=r-1;  /* つぎのlとrを計算 */
   }
 k=l;
 return(k);
}

int pivot(int i, int j, int *A)
/* A[i],...,A[j]から軸要素A[pv]を選びpvを出力 */
/* s1とs2の交互の幅で最初に発見した2個の値の大きい方をピボットとする */
{
 int pv, k, h, s0, s1, s2;
 s0=j-i; s1=(s0+1)/2; 
 if(s0%2==0) s2=s1; else s2=s1-1; 
 h=1;
 k=i+s1;                      /* s1とs2の交互のステップ幅でkを増加 */
 while(h<s0 && A[i]==A[k])
   {
    if(h%2==1) k=k+s2; else k=k+s1;  /* 次のk */
    if(k>j) k=k-j+i-1;               /* kがjを越える場合の修正 */
    h=h+1;
   }
 if(A[i]>A[k]) pv=i; else if(A[i]<A[k]) pv=k; else pv=-1;
 return(pv);
}

void swap(int i, int j, int *A)
/* A[i]とA[j]の位置の交換 */
{
 int temp;
 temp=A[i]; A[i]=A[j]; A[j]=temp;
 return;
}
