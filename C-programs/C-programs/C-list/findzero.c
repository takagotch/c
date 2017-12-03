/* 2���T���ɂ���_�̌v�Z�̃v���O������ */

#include <stdio.h>
#include <math.h>
float epsilon=0.0001;    /* �O���ϐ�; x�̋��e�덷 */
float delta=0.0001;      /* �O���ϐ�; f�̋��e�덷 */
/* �֐��̐錾 */
float findzero(float a, float b);
float f(float x);

main()
/* 2���T���ɂ�� f(x)=0.0 �������e�X�g�v���O���� */
{
 float a, b, x;

 a=0.0; b=10.0;
 x=findzero(a, b);
 printf("a = %f, b = %f, epsilon = %f, delta = %f\n", a, b, epsilon, delta);
 printf("zero x* = %f, f(x*) = %f\n", x, f(x));
 return(0);
}

float findzero(float a, float b)
/* �񌸏��A���֐�f()�̗�_�����[a, b]���łQ���T���ɂ�苁�߂� */
{
 float xL, xR, xM, fx;               /* xL�͍��AxR�͉E�AxM�͒����l */

 xL=a; xR=b;                         /* �����ݒ� */
 if(f(a)>delta || f(b)<-delta) {printf("There is no zero f(x)=0.\n"); exit(1);}
 while(xR-xL>epsilon)
   {
    xM=(xL+xR)/2.0;                  /* ���_ */
    fx=f(xM);
    if(fabs(fx)<=delta) return(xM);  /* �֐��l�\����; ��_���� */
    if(fx<=0.0) xL=xM; else xR=xM;   /* �V������Ԃ̐ݒ� */
   }
 return(xL);                         /* ��_��Ԃ� */
}

float f(float x)
/* �֐��lf(x)��^����v���O���� */
{
 float fx;

 fx=x*x*x-10.0;
 return(fx);
}

