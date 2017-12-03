/* �j���[�g���@�ɂ���_�̌v�Z�̃v���O������ */

#include <stdio.h>
#include <math.h>
float zero=0.001;        /* �O���ϐ�; ���W��>0�̋��e�͈� */
float delta=0.0001;      /* �O���ϐ�; |f(x)|�̋��e�͈� */
/* �֐��̐錾 */
float f(float x);
float df(float x);
float newton(float xinit);

main()
/* �j���[�g���@�ɂ�� f(x)=0.0 �������e�X�g�v���O���� */
{
 float xinit, x;

 xinit=5.0;
 x=newton(xinit);
 printf("xinit = %f, delta = %f\n", xinit, delta);
 printf("zero x* = %f, f(x*) = %f\n", x, f(x));
 return(0);
}

float newton(float xinit)
/* �����\�����֐�f(x)�̗�_��x=xinit����j���[�g���@�ɂ�苁�߂� */
/* �֐�f(x)�Ƃ��̔��W��df(x)�̓v���O�����ɂ���ė^���� */
{
 float x, y, dy;

 x=xinit;
 y=f(x);
 while(fabs(y)>delta)    /* �j���[�g���@�̔��� */
   {
    dy=df(x);
    if(fabs(dy)<zero)    /* ���i���W����0�j�̃`�F�b�N */
      {printf("Error: derivative at x = %f is zero.\n", x); exit(1);}
    x=x-y/dy;            /* ���̔����� */
    y=f(x);
   }
 return(x);              /* ���ʂ�Ԃ� */
}

float f(float x)
/* �֐��lf(x)��^����v���O���� */
{
 float fx;

 fx=x*x*x-10.0;
 return(fx);
}

float df(float x)
/* f(x)�̔��W����^����v���O���� */
{
 float d;

 d=3*x*x;
 return(d);
}

