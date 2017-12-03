/* 配列によるスタック操作のプログラム例 */

#include <stdio.h>
#define N 100    /* スタック配列の最大サイズ */
struct stack     /* 構造体stackの定義 */
{
 int top;
 int element[N];
};
/* 関数の宣言 */
void push(int x, struct stack *S);
void pop(struct stack *S);

main()  
/* Implementation of a stack by an array. */
{
 struct stack S;
 int i;
 S.top=N;
 for(i=0; i<10; i++) push(i+1, &S); 
 printf("S.top = %d, N = %d\n", S.top, N);
 i=S.top;
 while(i<N)
   {
    printf("i = %d, x = %d\n", i, S.element[i]);
    i=i+1;
   }  
 for(i=0; i<8; i++) pop(&S);
 printf("S.top = %d\n", S.top);
 i=S.top;
 while(i<N)
   {
    printf("i = %d, x = %d\n", i, S.element[i]);
    i=i+1;
   }
 return(0);
}

void push(int x, struct stack *S)
/* スタックSの先頭へxを挿入 */
{
 if(S->top>=N || S->top<0) S->top=N;                /* Sが空の場合 */
 if(S->top==0)                                      /* Sは満杯 */
   {printf("Error: Stack is full.\n"); exit(1);}      
 else {S->top=S->top-1; S->element[S->top]=x;}      /* その他の場合 */
 return;
}

void pop(struct stack *S)
/* スタックSの先頭の要素を除去 */
{
 if(S->top<N) {S->top=S->top+1;}                     /* 通常の場合 */
 else {printf("Error: Stack is empty.\n"); exit(1);} /* 空の場合 */
 return;
}
