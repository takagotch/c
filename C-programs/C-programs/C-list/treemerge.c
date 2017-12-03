/* �X�\���ɂ��W������MERGE��FIND�̃v���O������ */

#include <stdio.h>
#define N 7         /* �v�f�� */
#define M 4         /* �ő�W���� */ 
struct set          /* �\����set�̒�` */
{
 int size[M];
 int root[M];
 int parent[N];
};
/* �֐��̐錾 */
void treemerge(int i, int k, struct set *S);
int treefind(int j, struct set *S);

main()
/* �X�\���ɂ��W�����̃e�X�g�v���O���� */
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
/* �W��i��k�̂Q�̖؂̕��� */
{
 int j, large, small;

 if(S->size[i] <= S->size[k]) {small=i; large=k;}
 else {small=k; large=i;}
 j=S->root[small];               /* �������W��j��傫�����֕��� */
 if(S->size[small] == 0) return;
 S->parent[j] = S->root[large];  /* �W�����f�[�^S�̍X�V */
 S->size[large] = S->size[large]+S->size[small];
 S->size[small] = 0; S->root[small] = -1;
 return;
}

int treefind(int j, struct set *S)
/* j��v�f�Ƃ���W��i�̏o�͂ƘH�̈��k */
{
 int i, k, temp;

 k=j;                            /* �W��i�̔��� */
 while(k>=0) k = S->parent[k]; 
 i = -k-1;
 k=j;                            /* �H�̈��k */
 while(k>=0) 
   {
    temp = S->parent[k];
    if(temp>=0) S->parent[k] = S->root[i];
    k=temp;
   }
 return(i);
}
