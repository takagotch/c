/* 内部ハッシュ法のプログラム例 */

#include <stdio.h>
#include <stdlib.h>
#define B 5                           /* バケット数 */
#define W 6                           /* 語長 */
enum yn {yes, no};                    /* 列挙型データynの定義 */
enum oed {occupied, empty, deleted};  /* 列挙型データoedの定義 */
struct word                           /* 構造体wordの定義 */
{
 char name[W+1];
 enum oed state;
};
/* 関数の宣言 */
void insert(char *x, struct word *A);
void delete(char *x, struct word *A);
enum yn member(char *x, struct word *A);
int h(char *x);      

main()  
/* 内部ハッシュ法のテストプログラム */
{
 struct word A[B];
 int i;
 enum yn t;
 for(i=0; i<B; i++) A[i].state=empty;
 A[B-1].state=deleted;
 insert("xy", A);
 insert("xyz", A);
 insert("xyzabc", A);
 insert("xywwwww", A);
 insert("xyz", A);
 delete("xyzabc", A);
 insert("xxxxx", A);
 t=member("xyz", A);
 if(t==yes) printf("member = yes\n");
 else printf("member = no\n");
 t=member("yzz", A);
 if(t==yes) printf("member = yes\n");
 else printf("member = no\n");
 t=member("xywwww", A);
 if(t==yes) printf("member = yes\n");
 else printf("member = no\n");
 t=member("xy", A);
 if(t==yes) printf("member = yes\n");
 else printf("member = no\n");
 delete("abcd", A);
 printf("deleted\n");
 printf("-------------\n");
 for(i=0; i<B; i++) 
   {
    if(A[i].state==empty) printf("empty");
    else 
      {
       if(A[i].state==deleted) printf("deleted");
       else printf("%s", A[i].name);
      }
    printf("\n");
   }
 for(i=0; i<B; i++) 
   {
    if(A[i].state==empty) printf("empty\n");
    if(A[i].state==deleted) printf("deleted\n");
    if(A[i].state==occupied) printf("occupied\n");
   }
 return(0);
}

void insert(char *x, struct word *A)
/* ハッシュ表Aへ文字列xの挿入 */
{
 int i, k, found=-1;
 enum oed cstate;
 k=i=h(x);                                  /* xのハッシュ関数値 */
 do
   {
    cstate=A[k].state;
    if(cstate==empty || cstate==deleted)    /* 空セルあり */
      {if(found<0) found=k;}
    else {if(strcmp(x, A[k].name)==0) return;}    /* xはすでに存在 */
    k=(k+1)%B;                              /* つぎのセルへ */
   }
 while(cstate!=empty && k!=i);
 if(found<0) {printf("Error: Dictionary is full.\n"); exit(1);} /* Aは満杯 */
 strcpy(A[found].name, x); A[found].state=occupied;    /* A[found]へxの挿入*/
 return;
}

void delete(char *x, struct word *A)
/* ハッシュ表Aから文字列xの除去 */
{
 int i, k;
 enum oed cstate;
 k=i=h(x);                                  /* xのハッシュ関数値 */
 do                                         /* xの探索 */
   {
    cstate=A[k].state;
    if(cstate==occupied)       
      {
       if(strcmp(x, A[k].name)==0) {A[k].state=deleted; return;} /* xの発見 */
      }
    k=(k+1)%B;                              /* つぎのセルへ */
   }
 while(cstate!=empty && k!=i);
 return;                                    /* xは存在せず */
}

enum yn member(char *x, struct word *A)
/* ハッシュ表Aに文字列xの存在判定 */
{
 int i, k;
 enum oed cstate;
 k=i=h(x);                                  /* xのハッシュ関数値 */
 do                                         /* xの探索 */
   {
    cstate=A[k].state;
    if(cstate==occupied)       
      {
       if(strcmp(x, A[k].name)==0) return(yes);   /* xの発見 */
      }
    k=(k+1)%B;                              /* つぎのセルへ */
   }
 while(cstate!=empty && k!=i);
 return(no);                                /* xは存在せず */
}

int h(char *x)
/* ハッシュ関数値h(x)の計算 */
{
 int i, hash;

 hash=i=0;
 while(x[i]!=0 && i<W)
  {hash=hash+(int)x[i]; i=i+1;}
 hash=hash%B;
 return(hash);
}
