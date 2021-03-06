/* 外部ハッシュ法のプログラム例 */

#include <stdio.h>    /* 標準入出力のヘッダファイルの読込み */
#include <stdlib.h>   /* 標準ライブラリのヘッダファイル */
#define B 4          /* バケット数 */
#define W 6           /* 語長 */
enum yn {yes, no};    /* 列挙型データynの定義 */
struct cell           /* 構造体cellの定義 */
{
 char name[W+1];
 struct cell *next;
};
/* 関数の宣言 */
void insert(char *x, struct cell **A);
void delete(char *x, struct cell **A);
enum yn member(char *x, struct cell **A);
int h(char *x);

main()  
/* 外部ハッシュ法のテストプログラム */
{
 struct cell *A[B], *q;
 int j;
 enum yn t;
 for(j=0; j<B; j++) A[j]=NULL;
 insert("abcdef", A);
 insert("abcdefg", A);
 insert("abc", A);
 insert("cd", A);
 insert("def", A);
 insert("abcdef", A);
 insert("azc", A);
 insert("azd", A);
 insert("bzd", A);
 for(j=0; j<B; j++) 
   {
    printf("A[%d] = %p, ", j, A[j]);
    q=A[j];
    while(q != NULL) 
      {
       printf("%s, next = %p, ", q->name, q->next);
       q=q->next;
      }
    printf("\n");
   }
 t=member("azd",A);
 if(t==yes) printf("member = yes\n");
 else printf("member = no\n");
 t=member("vwx",A);
 if(t==yes) printf("member = yes\n");
 else printf("member = no\n");
 delete("azd", A);
 delete("cccc", A);
 delete("cd", A);
 delete("abcdefg", A);
 for(j=0; j<B; j++) 
   {
    printf("A[%d] = %p, ", j, A[j]);
    q=A[j];
    while(q != NULL) 
      {
       printf("%s, next = %p, ", q->name, q->next);
       q=q->next;
      }
    printf("\n");
   }
 return(0);
}

void insert(char *x, struct cell **A)
/* ハッシュ表Aへ文字列xの挿入 */
{
 int k;
 struct cell *p, *q, *r;

 k=h(x);                         /* xの入るバケット番号 */
 q=A[k];                         /* バケットk内の探索 */
 p=(struct cell *)malloc(sizeof(struct cell)); /* 新しいポインタの獲得 */
 if(q==NULL) A[k]=p;
 else
   {
    while(q != NULL)             /* xの存在のチェック */
      {  
       if(strcmp(q->name, x)==0) /* xはすでに存在 */
        {
         free(p); return; 
        } 
       else {r=q; q=q->next;}     
      }
    r->next=p;
   }
 strcpy(p->name, x);            /* xの挿入 */
 p->next=NULL;
 return;
}

void delete(char *x, struct cell **A)
/* ハッシュ表Aから文字列xの除去 */
{
 int k;
 struct cell *q, *r;

 k=h(x);                         /* xのハッシュ関数値 */
 q=A[k];                         /* バケットk内でxの探索 */
 r=NULL;
 while(q != NULL) 
   {
    if(strcmp(q->name, x)==0)    /* xを発見 */
      {
       if(r==NULL) A[k]=q->next; /* xの除去 */
       else r->next=q->next;
       free(q); return;               /* 作業終了 */
      }
    r=q; q=q->next;
   }
 return;                         /* xは存在せず */
}

enum yn member(char *x, struct cell **A)
/* ハッシュ表Aに文字列xの存在判定 */
{
 struct cell *q, *r;

 q=A[h(x)];                      /* バケットh(x)内でxの探索 */
 while(q != NULL) 
   {
    if(strcmp(q->name, x) == 0) return(yes);     /* xを発見 */
    r=q; q=q->next;
   }
 return(no);                     /* xは存在せず */
}

int h(char *x)
/* ハッシュ関数値h(x)の計算 */
{
 int i, hash;

 hash=i=0;
 while(i<W && x[i]!=0)
  {hash=hash+(int)x[i]; i=i+1;}
 hash=hash%B;
 return(hash);
}

