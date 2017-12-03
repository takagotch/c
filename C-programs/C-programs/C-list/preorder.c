/* �O���ɂ��؂̂Ȃ���̃v���O������ */

#include <stdio.h>   /* �W�����o�͂̃w�b�_�t�@�C���̓Ǎ��� */
#include <stdlib.h>  /* �W�����C�u�����̃w�b�_�t�@�C�� */
#define N 100        /* �z��S�̍ő�T�C�Y�i�ߓ_���j */
struct cell          /* �\����cell�̒�` */
{
 int node;
 struct cell *next;
};
void preorder(int k, struct cell **S);  /* �֐��̐錾 */

main()  
/* Traverse a tree S in preorder. */
{
 struct cell *S[N], *p, *q;
 int n, j, parent, child, root;
 FILE *file;
 file=fopen("treedata", "r");
 fscanf(file, "%d", &n);
 if(n>N) 
   {
    printf("Illegal array size n = %d for N = %d\n", n, N); 
    exit(1);
   }
 printf("n = %d\n", n);
 for(j=0; j<n; j++) S[j]=NULL;
 fscanf(file, "%d", &parent);
 while(parent >= 0)
   {
    fscanf(file, "%d", &child);
    if(child >= 0)
      {
       p=(struct cell *)malloc(sizeof(struct cell));
       S[parent]=q=p;
      } 
    while(child >= 0)
      {
       q->node=child;
       q->next=NULL;
       fscanf(file, "%d", &child);
       if(child >= 0)
         {
          p=(struct cell *)malloc(sizeof(struct cell));
          q->next=p;
          q=p;
         }
      }
    fscanf(file, "%d", &parent);
   }
 for(j=0; j<n; j++) 
   {
    printf("S[%d] = %p, ", j, S[j]);
    q=S[j];
    while(q != NULL) 
      {
       printf("node = %d, next = %p, ", q->node, q->next);
       q=q->next;
      }
    printf("\n");
   }
 root=0;
 printf("preorder =");
 preorder(root, S);
 printf("\n");
 return(0);
}

void preorder(int k, struct cell **S) 
/* S[k]�����Ƃ��镔���؂̑O���ɂ��Ȃ��� */
{
 struct cell *q;

 printf(" %d", k);      /* �ߓ_k�̏o�� */
 q=S[k];                /* k����O���̂Ȃ��� */
 while(q != NULL)
   {
    preorder(q->node, S);   /* �ċA�Ăяo�� */
    q=q->next;
   }
 return;
}

