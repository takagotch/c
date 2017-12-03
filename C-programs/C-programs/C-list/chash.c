/* �����n�b�V���@�̃v���O������ */

#include <stdio.h>
#include <stdlib.h>
#define B 5                           /* �o�P�b�g�� */
#define W 6                           /* �꒷ */
enum yn {yes, no};                    /* �񋓌^�f�[�^yn�̒�` */
enum oed {occupied, empty, deleted};  /* �񋓌^�f�[�^oed�̒�` */
struct word                           /* �\����word�̒�` */
{
 char name[W+1];
 enum oed state;
};
/* �֐��̐錾 */
void insert(char *x, struct word *A);
void delete(char *x, struct word *A);
enum yn member(char *x, struct word *A);
int h(char *x);      

main()  
/* �����n�b�V���@�̃e�X�g�v���O���� */
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
/* �n�b�V���\A�֕�����x�̑}�� */
{
 int i, k, found=-1;
 enum oed cstate;
 k=i=h(x);                                  /* x�̃n�b�V���֐��l */
 do
   {
    cstate=A[k].state;
    if(cstate==empty || cstate==deleted)    /* ��Z������ */
      {if(found<0) found=k;}
    else {if(strcmp(x, A[k].name)==0) return;}    /* x�͂��łɑ��� */
    k=(k+1)%B;                              /* ���̃Z���� */
   }
 while(cstate!=empty && k!=i);
 if(found<0) {printf("Error: Dictionary is full.\n"); exit(1);} /* A�͖��t */
 strcpy(A[found].name, x); A[found].state=occupied;    /* A[found]��x�̑}��*/
 return;
}

void delete(char *x, struct word *A)
/* �n�b�V���\A���當����x�̏��� */
{
 int i, k;
 enum oed cstate;
 k=i=h(x);                                  /* x�̃n�b�V���֐��l */
 do                                         /* x�̒T�� */
   {
    cstate=A[k].state;
    if(cstate==occupied)       
      {
       if(strcmp(x, A[k].name)==0) {A[k].state=deleted; return;} /* x�̔��� */
      }
    k=(k+1)%B;                              /* ���̃Z���� */
   }
 while(cstate!=empty && k!=i);
 return;                                    /* x�͑��݂��� */
}

enum yn member(char *x, struct word *A)
/* �n�b�V���\A�ɕ�����x�̑��ݔ��� */
{
 int i, k;
 enum oed cstate;
 k=i=h(x);                                  /* x�̃n�b�V���֐��l */
 do                                         /* x�̒T�� */
   {
    cstate=A[k].state;
    if(cstate==occupied)       
      {
       if(strcmp(x, A[k].name)==0) return(yes);   /* x�̔��� */
      }
    k=(k+1)%B;                              /* ���̃Z���� */
   }
 while(cstate!=empty && k!=i);
 return(no);                                /* x�͑��݂��� */
}

int h(char *x)
/* �n�b�V���֐��lh(x)�̌v�Z */
{
 int i, hash;

 hash=i=0;
 while(x[i]!=0 && i<W)
  {hash=hash+(int)x[i]; i=i+1;}
 hash=hash%B;
 return(hash);
}
