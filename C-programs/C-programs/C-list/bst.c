/* �Q���T���؂ɑ΂���MEMBER, INSERT, MIN, DELETE�̃v���O������ */

#include <stdio.h>
#include <stdlib.h>
enum yn {yes, no};         /* �񋓌^�f�[�^yn�̒�` */
struct node                /* �\����node�̐錾 */
{
 int element;
 struct node *left;
 struct node *right;
};

/* �֐��̐錾 */
enum yn member(int x, struct node *init);
void insert(int x, struct node **p);
int min(struct node *p);
void delete(int x, struct node **p);
struct node *off(struct node *p);
void printpre(struct node *p);
void inorder(struct node *p);

main()
/* �Q���T���؂̏����̃e�X�g�v���O���� */
{
 struct node *init;
 int i, x;
 enum yn a;

 init=NULL;           /* �f�[�^�̐��� */
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
 x=31;               /* 2���T���؂̑���̃e�X�g */
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
/* p���w���Q���T���؂�x�̑��݂𔻒� */
{
 struct node *q;

 q=p;                                 /* ��init����T���J�n */
 while(q!=NULL)
   {
    if(q->element == x) return(yes);  /* x�𔭌� */
    if(q->element < x)  q = q->right;
    else q = q->left;
   }
 return(no);                          /* x���݂��� */
}

void insert(int x, struct node **p)
/* �|�C���^*p���w���Q���T���؂�x��}�����A*p���X�V */
{
 struct node *q, **r;           /* q�͒T�����̃|�C���^�Ar�͂��̐e */

 r=p; q=*r;                           /* r��q�̏����� */
 while(q != NULL)
   {
    if(q->element == x) return;       /* x�͂��łɑ��� */
    if(q->element < x)                /* �E�̎q�� */
      {r=&(q->right); q=q->right;}
    else                              /* ���̎q�� */
      {r=&(q->left); q=q->left;}
   }
          /* *p�̎w���؂���̏ꍇ�A*r��*p�͓����Ƃ�����w���Ă��� */
 *r=(struct node *)malloc(sizeof(struct node));  /* x������ꏊ */
 (*r)->element=x; (*r)->left=NULL; (*r)->right=NULL;   /* x�̑}�� */
 return;
}

int min(struct node *p)
/* p���w���Q���T���؂̍ŏ��v�f���o�� */
{
 struct node *q, *r;          /* q�͒T�����̃|�C���^�Ar�͂��̐e */

 q=p;                         /* �����獶�[�̘H�������� */
 if(q==NULL) {printf("Error: Tree is empty.\n"); exit(1);} /* �؂͋� */
 while(q!=NULL) 
   {
    r = q; q = q->left;
   }
 return(r->element);          /* ���ʂ�Ԃ� */
}

void delete(int x, struct node **p)
/* �|�C���^*p���w���Q���T���؂���v�fx���������A*p�̍X�V */
{
 struct node *q, **r;         /* q�͒T�����̃|�C���^�Ar�͂��̐e */

 r=p; q=*r;                   /* ������T���̊J�n */
 while(q!=NULL)
   {
    if(q->element == x)       /* x�𔭌� */
      {
       *r=off(q);             /* x�̃Z��q���������Aq�̕����؂��X�V */
       return;                /* �I�� */
      }
    if(q->element < x) {r = &(q->right);}    /* �T���𑱂��� */
    else {r = &(q->left);}  
    q=*r;
   }
 return;                      /* x�͑��݂��� */
}

struct node *off(struct node *p)
/* �|�C���^p���w���ߓ_�������Ap�̕����؂��X�V�A���ւ̃|�C���^��Ԃ� */
{
 struct node *q, **r;             /* q�͒T�����̃|�C���^�Ar�͂��̐e */

 if(p->left==NULL && p->right==NULL) /* p�̎q�͋��ɋ� */
   {free(p); return(NULL);}
 if(p->left==NULL)                   /* p�̍��̎q���� */
   {q=p->right; free(p); return(q);}
 if(p->right==NULL)                  /* p�̉E�̎q���� */
   {q=p->left; free(p); return(q);}
 r=&(p->right);      /* p�̎q�͋��ɑ���; �E�̕����؂̍ŏ��v�f��T�� */
 q=*r;
 while(q->left != NULL)
   {r=&(q->left); q=q->left;}
 p->element = q->element;
 *r=off(q);                          /* �ŏ��v�fq�̏����G�ċA�I���s */
 return(p);
}


void printpre(struct node *p) 
/* �ߓ_ *p �̑S�Ă̎q�ߓ_��O���ɏo�͂��� */
{
 printf("p = %p, element = %d, left = %p, right = %p\n", 
         p, p->element, p->left, p->right);
 if(p->left != NULL) printpre(p->left);
 if(p->right != NULL) printpre(p->right);
 return;  
}

void inorder(struct node *p) 
/* �ߓ_ *p �̑S�Ă̎q�ߓ_�𒆏��ɏo�͂��� */
{
 if(p->left != NULL) inorder(p->left);
 printf("p = %p, element = %d, left = %p, right = %p\n", 
         p, p->element, p->left, p->right);
 if(p->right != NULL) inorder(p->right);
 return;  
}
