#include <stdio.h>
#define N 4      /* テキストの最大長 */
#define M 10        /* パターンの最大長 */ 

main()
/* 文字列照合のテストプログラム */
{
 char str1[N], str2[M];

 strcpy(str1, "algori");
 strcpy(str2, "algorithm");
 printf("str1 = %s, str2 = %s\n", str1, str2); /* 結果の出力 */
/* srtcpy(str1, str2); */
 printf("str1 = %s, str2 = %s\n", str1, str2); /* 結果の出力 */
 printf("compare = %d\n", strcmp(str1, str2));
 return(0);
}

