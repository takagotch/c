/* 森表現による集合族のMERGEとFINDのプログラム例 */

#include <stdio.h>
#define N 7         /* 要素数 */
#define M 4         /* 最大集合数 */ 
struct set          /* 構造体setの定義 */
{
 int size[M];
 int root[M];
 int parent[N];
};
/* 関数の宣言 */
void treemerge(int i, int k, struct set *S);
int treefind(int j, struct set *S);

main()
/* 森表現による集合族のテストプログラム */
{
 struct set S;
 int i, j, k;
 FILE *file;
 file=fopen("mtreedata", "r");
 for(i=0; i<M; i++)
   {
    fscanf(file, "%d", &S.size[i]);
    fscanf(file, "%d", &S.root[i]);
   }
 for(j=0; j<N; j++) fscanf(file, "%d", &S.parent[j]);
 printf("initial S\n");
 for(i=0; i<M; i++) printf("%d, %d, %d\n", i, S.size[i], S.root[i]);
 printf("initial parents\n");
 for(j=0; j<N; j++) printf("%d, %d\n", j,S.parent[j]);
 treemerge(1, 3, &S);
 printf("updated S\n");
 for(i=0; i<M; i++) printf("%d, %d, %d\n", i, S.size[i], S.root[i]);
 printf("updated parents\n");
 for(j=0; j<N; j++) printf("%d, %d\n", j, S.parent[j]);
 j=4;
 k=treefind(j, &S);
 printf("element = %d, set = %d\n", j, k);
 printf("updated S\n");
 for(i=0; i<M; i++) printf("%d, %d, %d\n", i, S.size[i], S.root[i]);
 printf("updated parents\n");
 for(j=0; j<N; j++) printf("%d, %d\n", j, S.parent[j]);
 return(0);
}

void treemerge(int i, int k, struct set *S)
/* 集合iとkの２つの木の併合 */
{
 int j, large, small;

 if(S->size[i] <= S->size[k]) {small=i; large=k;}
 else {small=k; large=i;}
 j=S->root[small];               /* 小さい集合jを大きい方へ併合 */
 if(S->size[small] == 0) return;
 S->parent[j] = S->root[large];  /* 集合族データSの更新 */
 S->size[large] = S->size[large]+S->size[small];
 S->size[small] = 0; S->root[small] = -1;
 return;
}

int treefind(int j, struct set *S)
/* jを要素とする集合iの出力と路の圧縮 */
{
 int i, k, temp;

 k=j;                            /* 集合iの発見 */
 while(k>=0) k = S->parent[k]; 
 i = -k-1;
 k=j;                            /* 路の圧縮 */
 while(k>=0) 
   {
    temp = S->parent[k];
    if(temp>=0) S->parent[k] = S->root[i];
    k=temp;
   }
 return(i);
}
