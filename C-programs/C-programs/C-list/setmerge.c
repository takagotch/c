/* 配列で表された集合族の併合のプログラム例 */

#include <stdio.h>
#define N 7           /* 最大要素数 */
#define M 4           /* 最大集合数 */ 
struct set            /* 構造体setの定義 */
{
 int size[M]; int first[M];
};
struct element        /* 構造体elementの定義 */
{
 int set[N]; int next[N];
};
/* 関数の宣言 */
void setmerge(int i, int k, struct set *S, struct element *E);

main()
/* 配列で表された集合族の併合のテストプログラム */
{
 struct set S;
 struct element E;
 int i, j;
 FILE *file;

 for(i=0; i<M; i++) {S.size[i]=0; S.first[i]=-1;}
 for(j=0; j<N; j++) {E.set[j]=-1; E.next[j]=-1;}
 file=fopen("mergedata", "r");
 fscanf(file, "%d", &i);
 while(i>=0) 
   {
    fscanf(file, "%d", &S.size[i]);
    fscanf(file, "%d", &S.first[i]);
    fscanf(file, "%d", &i);
   }
 fscanf(file, "%d", &j);
 while(j>=0) 
   {
    fscanf(file, "%d", &E.set[j]);
    fscanf(file, "%d", &E.next[j]);
    fscanf(file, "%d", &j);
   }
 printf("initial S\n");
 for(i=0; i<M; i++) printf("%d, %d, %d\n", i, S.size[i], S.first[i]);
 printf("initial E\n");
 for(j=0; j<N; j++) printf("%d, %d, %d\n", j, E.set[j], E.next[j]);
 setmerge(0, 3, &S, &E);
 setmerge(0, 1, &S, &E);
 printf("updated S\n");
 for(i=0; i<M; i++) printf("%d, %d, %d\n", i, S.size[i], S.first[i]);
 printf("updated E\n");
 for(j=0; j<N; j++) printf("%d, %d, %d\n", j, E.set[j], E.next[j]);
 return(0);
}

void setmerge(int i, int k, struct set *S, struct element *E)
/* 配列SとEで定義された集合族の集合S[i]とS[k]の併合 */
{
 int j, h, large, small;

 if(S->size[i]<=S->size[k]) {small=i; large=k;} /* largeとsmallの計算 */
 else {small=k; large=i;}
 j=S->first[small];
 while(j>=0) {E->set[j]=large; h=j; j=E->next[j];}  /* 大きい方へ併合 */
 E->next[h]=S->first[large];
 S->first[large]=S->first[small];               /* 集合の配列Sの更新 */
 S->first[small]=-1;
 S->size[large]=S->size[large]+S->size[small];
 S->size[small]=0;
 return;
}
