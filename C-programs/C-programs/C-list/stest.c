#include <stdio.h>
#define N 4      /* �e�L�X�g�̍ő咷 */
#define M 10        /* �p�^�[���̍ő咷 */ 

main()
/* ������ƍ��̃e�X�g�v���O���� */
{
 char str1[N], str2[M];

 strcpy(str1, "algori");
 strcpy(str2, "algorithm");
 printf("str1 = %s, str2 = %s\n", str1, str2); /* ���ʂ̏o�� */
/* srtcpy(str1, str2); */
 printf("str1 = %s, str2 = %s\n", str1, str2); /* ���ʂ̏o�� */
 printf("compare = %d\n", strcmp(str1, str2));
 return(0);
}

