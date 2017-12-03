/* ２分探索木に対するMEMBER, INSERT, MIN, DELETEのプログラム例
（単純なアルゴリズム） */

#include <stdio.h>
#include <stdlib.h>
enum yn {yes, no};         /* 列挙型データynの定義 */
enum LR {LEFT, RIGHT};
struct node                /* 構造体nodeの宣言 */
{
 int element;
 struct node *left;
 struct node *right;
};
/* 関数の宣言 */
enum yn member(int x, struct node *init);
struct node *insert(int x, struct node *init);
int min(struct node *init);
struct node *delete(int x, struct node *init);
struct node *off(struct node *p);
void printpre(struct node *p);
void inorder(struct node *p);

main()
/* ２分探索木の処理のテストプログラム */
{
 struct node *init;
 int i, x;
 enum yn a;

 init=NULL;
 for(i=0; i<10; i++) init=insert((8-3*i)*(2-i/2), init);
 init=insert(30, init);
 init=insert(25, init);
 init=insert(31, init);
 init=insert(37, init);
 printf("init = %p\n", init);
 printf("inorder\n");
 if(init != NULL) inorder(init);
 printf("preorder\n");
 if(init != NULL) printpre(init);
 x=31;
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
 init=delete(x, init);
 printf("deleted x = %d\n", x);
 printf("init = %p\n", init);
 if(init != NULL) printpre(init);
 x=32;
 init=delete(x, init);
 printf("deleted x = %d\n", x);
 printf("init = %p\n", init);
 if(init != NULL) printpre(init);
 x=37;
 init=delete(x, init);
 printf("deleted x = %d\n", x);
 printf("init = %p\n", init);
 if(init != NULL) printpre(init);
 return(0);
}

enum yn member(int x, struct node *init)
/* initが指す２分探索木にxの存在を判定 */
{
 struct node *q;

 q=init;                   /* 根initから探索開始 */
 while(q!=NULL)
   {
    if(q->element == x) return(yes);    /* xを発見 */
    if(q->element < x)  q = q->right;
    else q = q->left;
   }
 return(no);               /* x存在せず */
}

struct node *insert(int x, struct node *init)
/* initが指す２分探索木にxを挿入し、initを更新 */
{
 struct node *p, *q, *r;

 p=(struct node *)malloc(sizeof(struct node)); /* 新しいポインタ */
 q=init;                   /* 根initから探索開始 */
 if(init==NULL) init=p;
 while(q!=NULL)
   {
    if(q->element == x) {free(p); return(init);}  /* xはすでに存在 */
    r = q;
    if(q->element < x)     /* 右の子へ */
      {
       q = q->right;
       if(q==NULL) r->right = p;
      }
    else                   /* 左の子へ */
      {
       q = q->left;
       if(q==NULL) r->left = p;
      }
   }
 p->element = x;           /* xを挿入 */
 p->left = p->right = NULL;
 return(init);
}

int min(struct node *init)
/* initが指す２分探索木の最小要素を出力 */
{
 struct node *q, *r;

 q=init;                   /* 根から左端の路を下がる */
 if(q==NULL) {printf("Error: Tree is empty.\n"); exit(1);} /* 木は空 */
 while(q!=NULL) 
   {
    r = q; q = q->left;
   }
 return(r->element);       /* 結果を返す */
}

struct node *delete(int x, struct node *init)
/* initが指す２分探索木から要素xを除去し、initの更新 */
{
 struct node *q, *r, *p;   /* qは探索中のポインタ、rはその親 */
 int side;                 /* side==1: rの右の子がq、0: 左の子がq */

 q=init;                   /* 根から探索の開始 */
 while(q!=NULL)
   {
    if(q->element == x)    /* xの発見 */
      {
       p=off(q);           /* xのセルqを除去し、qの部分木を更新 */
       if(p==NULL)         /* 部分木は空 */
         {
          if(q==init) init=NULL;  /* qが根initである場合 */
          else             /* その他の場合 */
            {
             if(side==1) r->right = NULL;
             else r->left = NULL;
            }
         }
       return(init);       /* 終了 */
      }
    r=q;                   /* 探索を続ける */
    if(r->element < x) {q = r->right; side=1;}
    else {q = r->left; side=0;}  
   }
 return(init);
}

struct node *off(struct node *p)
/* ポインタpが指す節点を除去、pの部分木を更新 */
{
 struct node *q, *r, *s;  /* qは探索中のポインタ、rはその親、sはrの親 */
 int side;

 if(p->left==NULL && p->right==NULL) return(NULL);  /* pの子は共に空 */
 if(p->left==NULL || p->right==NULL)  /* pの子の一方が空 */
   {
    if(p->left == NULL) q=p->right;   /* 空でない方をpへ上げる */
    else q=p->left;   
    p->element = q->element;
    p->left = q->left;
    p->right = q->right;
    return(p);
   }
 s=p; side=1;              /* pの子は共に存在 */
 r = s->right;             /* pの右の部分木の最小要素を探索 */
 q = r->left;
 while(q!=NULL) 
   {
    s=r; side=0;
    r = q; q = r->left;
   }
 p->element = r->element;
 r=off(r);                 /* 最小要素rの除去；再帰的実行 */
 if(r==NULL)               /* rが空の場合 */
   {
    if(side==1) s->right = NULL;
    else s->left = NULL;
   }
 return(p);
}


void printpre(struct node *p) 
/* Print all children of node *p in preorder. */
{
 printf("p = %p, element = %d, left = %p, right = %p\n", 
         p, p->element, p->left, p->right);
 if(p->left != NULL) printpre(p->left);
 if(p->right != NULL) printpre(p->right);
 return;  
}

void inorder(struct node *p) 
/* Print all children of node *p in inorder. */
{
 if(p->left != NULL) inorder(p->left);      /* 左の子孫のなぞり */
 printf("p = %p, element = %d, left = %p, right = %p\n", 
         p, p->element, p->left, p->right); /* pが指す節点の出力 */
 if(p->right != NULL) inorder(p->right);    /* 右の子孫のなぞり */
 return;  
}
