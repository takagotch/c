/* ２分探索木に対するMEMBER, INSERT, MIN, DELETEのプログラム例 */

#include <stdio.h>
#include <stdlib.h>
enum yn {yes, no};         /* 列挙型データynの定義 */
struct node                /* 構造体nodeの宣言 */
{
 int element;
 struct node *left;
 struct node *right;
};

/* 関数の宣言 */
enum yn member(int x, struct node *init);
void insert(int x, struct node **p);
int min(struct node *p);
void delete(int x, struct node **p);
struct node *off(struct node *p);
void printpre(struct node *p);
void inorder(struct node *p);

main()
/* ２分探索木の処理のテストプログラム */
{
 struct node *init;
 int i, x;
 enum yn a;

 init=NULL;           /* データの生成 */
 for(i=0; i<10; i++) insert((8-3*i)*(2-i/2), &init);
 insert(30, &init);
 insert(25, &init);
 insert(31, &init);
 insert(37, &init);
 printf("init = %p\n", init);
 printf("inorder\n");
 if(init != NULL) inorder(init);
 printf("preorder\n");
 if(init != NULL) printpre(init);
 x=31;               /* 2分探索木の操作のテスト */
 a=member(x, init);
 if(a==yes) printf("Yes: x = %d\n", x);
 else printf("No: x = %d\n", x); 
 x=-2;
 a=member(x, init);
 if(a==yes) printf("Yes: x = %d\n", x);
 else printf("No: x = %d\n", x); 
 x=min(init);
 printf("min = %d\n", x);
 x=16;
 delete(x, &init);
 printf("deleted x = %d\n", x);
 printf("init = %p\n", init);
 if(init != NULL) printpre(init);
 x=32;
 delete(x, &init);
 printf("deleted x = %d\n", x);
 printf("init = %p\n", init);
 if(init != NULL) printpre(init);
 x=37;
 delete(x, &init);
 printf("deleted x = %d\n", x);
 printf("init = %p\n", init);
 if(init != NULL) printpre(init); 
 x=25;
 delete(x, &init);
 printf("deleted x = %d\n", x);
 printf("init = %p\n", init);
 if(init != NULL) printpre(init); 
 return(0);
 }

enum yn member(int x, struct node *p)
/* pが指す２分探索木にxの存在を判定 */
{
 struct node *q;

 q=p;                                 /* 根initから探索開始 */
 while(q!=NULL)
   {
    if(q->element == x) return(yes);  /* xを発見 */
    if(q->element < x)  q = q->right;
    else q = q->left;
   }
 return(no);                          /* x存在せず */
}

void insert(int x, struct node **p)
/* ポインタ*pが指す２分探索木にxを挿入し、*pを更新 */
{
 struct node *q, **r;           /* qは探索中のポインタ、rはその親 */

 r=p; q=*r;                           /* rとqの初期化 */
 while(q != NULL)
   {
    if(q->element == x) return;       /* xはすでに存在 */
    if(q->element < x)                /* 右の子へ */
      {r=&(q->right); q=q->right;}
    else                              /* 左の子へ */
      {r=&(q->left); q=q->left;}
   }
          /* *pの指す木が空の場合、*rと*pは同じところを指している */
 *r=(struct node *)malloc(sizeof(struct node));  /* xを入れる場所 */
 (*r)->element=x; (*r)->left=NULL; (*r)->right=NULL;   /* xの挿入 */
 return;
}

int min(struct node *p)
/* pが指す２分探索木の最小要素を出力 */
{
 struct node *q, *r;          /* qは探索中のポインタ、rはその親 */

 q=p;                         /* 根から左端の路を下がる */
 if(q==NULL) {printf("Error: Tree is empty.\n"); exit(1);} /* 木は空 */
 while(q!=NULL) 
   {
    r = q; q = q->left;
   }
 return(r->element);          /* 結果を返す */
}

void delete(int x, struct node **p)
/* ポインタ*pが指す２分探索木から要素xを除去し、*pの更新 */
{
 struct node *q, **r;         /* qは探索中のポインタ、rはその親 */

 r=p; q=*r;                   /* 根から探索の開始 */
 while(q!=NULL)
   {
    if(q->element == x)       /* xを発見 */
      {
       *r=off(q);             /* xのセルqを除去し、qの部分木を更新 */
       return;                /* 終了 */
      }
    if(q->element < x) {r = &(q->right);}    /* 探索を続ける */
    else {r = &(q->left);}  
    q=*r;
   }
 return;                      /* xは存在せず */
}

struct node *off(struct node *p)
/* ポインタpが指す節点を除去、pの部分木を更新、根へのポインタを返す */
{
 struct node *q, **r;             /* qは探索中のポインタ、rはその親 */

 if(p->left==NULL && p->right==NULL) /* pの子は共に空 */
   {free(p); return(NULL);}
 if(p->left==NULL)                   /* pの左の子が空 */
   {q=p->right; free(p); return(q);}
 if(p->right==NULL)                  /* pの右の子が空 */
   {q=p->left; free(p); return(q);}
 r=&(p->right);      /* pの子は共に存在; 右の部分木の最小要素を探索 */
 q=*r;
 while(q->left != NULL)
   {r=&(q->left); q=q->left;}
 p->element = q->element;
 *r=off(q);                          /* 最小要素qの除去；再帰的実行 */
 return(p);
}


void printpre(struct node *p) 
/* 節点 *p の全ての子節点を前順に出力する */
{
 printf("p = %p, element = %d, left = %p, right = %p\n", 
         p, p->element, p->left, p->right);
 if(p->left != NULL) printpre(p->left);
 if(p->right != NULL) printpre(p->right);
 return;  
}

void inorder(struct node *p) 
/* 節点 *p の全ての子節点を中順に出力する */
{
 if(p->left != NULL) inorder(p->left);
 printf("p = %p, element = %d, left = %p, right = %p\n", 
         p, p->element, p->left, p->right);
 if(p->right != NULL) inorder(p->right);
 return;  
}
