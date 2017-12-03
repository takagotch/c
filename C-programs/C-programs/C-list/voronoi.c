#include <stdio.h>
#include <math.h>
#define P 100  /* The max number of points. */
#define N 200  /* The max number of Voronoi vertices. */
#define M 500  /* The max number of Voronoi edges. */ 
#define ZERO 0.0001  /* Allowance of rouding errors. */
#define INFTY 1.7e+38 /* Very large floating number. */

struct point
{
 float x, y;
 int cend, aend;
};
/* Initial given points, where cend denotes the diverging edge of
the Voronoi polygon P(p(x,y)) in the clockwise direction, and aend in the
anticlockwise directiron. */

struct vertex
{
 float x, y;
 int div;
};
/* Vertices of Voronoi diagram, where div=0: the end vertex of an Voronoi 
edge, div=1: intermediate vertex of an diverging edge, and 
div=-1: not used. */

struct edge
{
 int v1, v2;
 int p1, p2;
 int clock1, clock2;
 int anti1, anti2;
 int alive;
};
/* The Voronoi edge is defined by two vertices v1 and v2, and separate
two points p1 and p2.  The clockwise adjacent edge of the Voronoi polygon
P(p1) is clock1, and the anti-clockwise adjacent edge is anti1.
Similarly for clock2 and anti2.  alive=1 if the edge is used, while
alive=0 if not used.  */

struct pair
{
 int ltop, lbot, rtop, rbot;
};
struct point S[P];
struct vertex V[N];
struct edge E[M];
int p, n, m;
/* Arrarys S, V, M are main external variables used in the whole compuation.
S: Data of p points, initially given as input.
V: Data of n Voronoi vertices.
E: Data of m Voronoi edges.  */


/* List of programs. */
struct point intersect(int i1, int i2, int i3, int i4);
void voronoi(int p1, int p2);
void voronoi1(int p1, int p2);
void voronoi2(int p1, int p2);
struct pair topbot(int p1, int p2, int p3, int p4);
void bubblesort(struct point *A, int n);
void swap(int i, int j, struct point *A);
void veprint(int p1, int p2);
void pprint(int p);
void cut(int v, int e, int pt, int side);
void rcut(int n, int m);
int eclock(int pt, int e);
int vclock(int pt, int v1, int v2);


/****************************************************************/
main()
/* Voronoi diagram. */
{
 int i, j, k, i1, i2, i3, i4, p1, p2;
 struct point pint;
 FILE *file;
 file=fopen("pointdata6", "r");
    {
     fscanf(file, "%d", &p);
    }
 for(i=0; i<p; i++)
   {
    fscanf(file, "%f", &S[i].x);
    fscanf(file, "%f", &S[i].y);
   }
 for(i=0; i<p; i++) S[i].cend=S[i].aend=-1;
 bubblesort(S, p);
 p1=0; p2=p-1;
 voronoi(p1, p2);
/* Kill the edges not used in the Voronoi diagram.  */
 for(i=0; i<m; i++)
   {
    if(V[E[i].v1].div==-1 || V[E[i].v2].div==-1) E[i].alive=0;
   }

 printf("Final computational result\n");
 pprint(p);
 veprint(p1, p2);

}



/***********************************************************************/
void voronoi(int p1, int p2)
/* Compute Voronoi diagram for the point set S[p1, p2]. */
{
 int i, j, k, pa, pb, pc, pd, half, lt, lb, rt, rb;
 int leinit, reinit, le, re, lenext, renext, markpre, ltest, rtest, side;
 int lp, rp, lepre, repre, vcur, etemp, enew;
 float xa, ya, xb, yb, x12, y12;
 struct point pint, lint, rint;
 struct pair q;
 if(p2-p1<=0) 
   {
    printf("Error in voronoi: p1 = %d, p2 = %d|n", p1, p2); 
    return;
   }
 if(p2-p1==1) {voronoi1(p1, p2); return;}
 if(p2-p1==2) {voronoi2(p1, p2); return;}

/* The case of p2-p1>2. */
 half=(p2-p1)/2;
 pa=p1; pb=p1+half; pc=pb+1; pd=p2;
 voronoi(pa, pb);
 voronoi(pc, pd);

/* pprint(p);
 veprint(pa, pd); */

 q=topbot(pa, pb, pc, pd);

/*  printf("topbot\n");
 printf("pa = %d, pb = %d, pc = %d, pd = %d\n", pa, pb, pc, pd);
 printf("ltop = %d, lbot = %d, rtop = %d, rbot = %d\n", 
     q.ltop, q.lbot, q.rtop, q.rbot);  */

 lt=q.ltop; lb=q.lbot; rt=q.rtop; rb=q.rbot;

/***********************************/
/* Find the first incoming line; V[n] and V[n+1]. */
 xa=(S[lt].x+S[rt].x)/2.0;
 ya=(S[lt].y+S[rt].y)/2.0;
 V[n].x=xa; V[n].y=ya; V[n].div=1;
 x12=S[rt].x-S[lt].x;
 y12=S[rt].y-S[lt].y;
 if(fabs(y12)>ZERO) 
   {
    xb=xa+1.0; yb=-x12/y12 + ya;
   }
 else
   {
    xb=xa; yb=ya+1.0;
   }
 V[n+1].x=xb; V[n+1].y=yb; V[n+1].div=1;
/* Find the left edge le and right edge re intersecting the incoming line. 
Intersecting left point in V[n+2] and right point in V[n+3]. */
 le=leinit=S[lt].aend; re=reinit=S[rt].cend; 
 lp=lt; rp=rt;
 ltest=0; rtest=0;
 do
   {
    pint=intersect(E[le].v1, E[le].v2, n, n+1);
    if(pint.x>-0.9*INFTY)
      {
       ltest=1;
       V[n+2].x=pint.x; V[n+2].y=pint.y; V[n+2].div=0;
      }
    else
      {
/*       V[E[le].v1].div=-1; V[E[le].v2].div=-1; */
       if(E[le].p1==lp) le=E[le].clock1;
       else le=E[le].clock2;
       if(le==leinit) 
         {
          ltest=1;
          V[n+2].x=-INFTY; V[n+2].y=-INFTY; V[n+2].div=1;
         }
      }
   }
 while(ltest==0);
 do
   {
    pint=intersect(E[re].v1, E[re].v2, n, n+1);
    if(pint.x>-0.9*INFTY)
      {
       rtest=1;
       V[n+3].x=pint.x; V[n+3].y=pint.y; V[n+3].div=0;
      }
    else
      {
/*       V[E[re].v1].div=-1; V[E[re].v2].div=-1; */
       if(E[re].p1==rp) re=E[re].anti1;
       else re=E[re].anti2;
       if(re==reinit) 
         {
          rtest=1;
          V[n+3].x=-INFTY; V[n+3].y=-INFTY; V[n+3].div=1;
         }
      }
   }
 while(rtest==0);


/* printf("initial line found: current parameters:\n");
 printf("le=%d, re=%d, lp=%d, rp=%d, lt=%d, rt=%d, lb=%d, rb=%d, side=%d, vcur=%d\n",
        le, re, lp, rp, lt, rt, lb, rb, side, vcur);
 pprint(p);
 veprint(p1, p2); */


/***********************************/
/* Construct the first incoming Voronoi edge m. */
/* Parallel lines. */
 if(V[n+2].y<-0.9*INFTY && V[n+3].y<-0.9*INFTY)
   {
    if(y12<=ZERO)
      {
       E[m].v1=n; E[m].v2=n+1; E[m].p1=lt; E[m].p2=rt; 
       E[m].clock1=le; E[m].clock2=re; E[m].anti1=le; E[m].anti2=re; 
      }
    else
      {
       E[m].v1=n; E[m].v2=n+1; E[m].p1=rt; E[m].p2=lt; 
       E[m].clock1=re; E[m].clock2=le; E[m].anti1=re; E[m].anti2=le;
      }
    E[m].alive=1;
    n=n+2; m=m+1;
    return;
   }
/* There is the intersection vertex. */
 lp=lt; rp=rt;
 if(V[n+2].y >= V[n+3].y-ZERO)
   {
    side=0;
    if(fabs(V[n+2].x-V[n].x)<=ZERO && fabs(V[n+2].y-V[n].y)<=ZERO)
      {
       V[n]=V[n+1];
      }
    V[n+1].x=V[n+2].x;  V[n+1].y=V[n+2].y; V[n+1].div=0;
    if(V[n].y < V[n+1].y-ZERO)
      {
       V[n].x=2.0*V[n+1].x-V[n].x; V[n].y=2.0*V[n+1].y-V[n].y;
      }
    V[n].div=1;
    E[m].v1=n+1; E[m].v2=n; E[m].p1=lt; E[m].p2=rt; 
    E[m].clock1=le; E[m].clock2=S[rt].aend; 
    E[m].anti1=S[lt].cend; E[m].anti2=-1; 
    E[m].alive=1;
    S[lt].aend=m; S[rt].cend=m;
    i=S[lt].cend;
    if(E[i].p1==lt)  E[i].clock1=m; else E[i].clock2=m;
    i=S[rt].aend;
    if(E[i].p1==rt)  E[i].anti1=m; else E[i].anti2=m;
    if(E[le].p1==lt) 
      {
       E[le].anti1=m; lp=E[le].p2;
      }
    if(E[le].p2==lt) 
      {
       E[le].anti2=m; lp=E[le].p1;
      }
    cut(n+1, le, lp, side);
   }
 else
   {
    side=1;
    if(fabs(V[n+3].x-V[n].x)<=ZERO && fabs(V[n+3].y-V[n].y)<=ZERO)
      {
       V[n]=V[n+1];
      }
    V[n+1].x=V[n+3].x;  V[n+1].y=V[n+3].y; V[n+1].div=0;
    if(V[n].y < V[n+1].y-ZERO)
      {
       V[n].x=2.0*V[n+1].x-V[n].x; V[n].y=2.0*V[n+1].y-V[n].y;
      }
    V[n].div=1;
    E[m].v1=n+1; E[m].v2=n; E[m].p1=lt; E[m].p2=rt; 
    E[m].clock1=-1; E[m].clock2=S[rt].aend; 
    E[m].anti1=S[lt].cend; E[m].anti2=re; 
    E[m].alive=1;
    S[lt].aend=m; S[rt].cend=m;
    i=S[lt].cend;
    if(E[i].p1==lt)  E[i].clock1=m; else E[i].clock2=m;
    i=S[rt].aend;
    if(E[i].p1==rt)  E[i].anti1=m; else E[i].anti2=m;
    if(E[re].p1==rt) 
      {
       E[re].clock1=m; rp=E[re].p2;
      }
    if(E[re].p2==rt) 
      {
       E[re].clock2=m; rp=E[re].p1;
      }
    cut(n+1, re, rp, side);
   }
 vcur=n+1;
 enew=m;
 n=n+2; m=m+1;

/* printf("initial segment found: current parameters:\n");
 printf("le=%d, re=%d, lp=%d, rp=%d, lt=%d, rt=%d, lb=%d, rb=%d, side=%d, vcur=%d\n",
         le, re, lp, rp, lt, rt, lb, rb, side, vcur);
 pprint(p);
 veprint(p1, p2); */



/****************************/
/* General construction of the middle voroni edges. */
/* le: current left edge, re: current right edge
   lp: P[lp] is currently searched, rp: P[rp] is ...
   side: 0 if currently in left, 1 if currently in right.
   vcur: current vertex being searched.  If side=0, vcur is on
   edge le which belongs to P[lp]; similarly for the case of side=1. 
   enew: the latest edge created in the process. */
 while(lp!=lb || rp!=rb)
   {   
    x12=S[rp].x-S[lp].x;
    y12=S[rp].y-S[lp].y;
    if(fabs(x12)>ZERO)
      {
       ya=V[vcur].y-1.0;
       xa=V[vcur].x+y12/x12;
      }
    else 
      {
       ya=V[vcur].y;
       if(side==1) xa=V[vcur].x-1.0;
       else xa=V[vcur].x+1.0;
      }
    V[n].x=xa; V[n].y=ya; V[n].div=1;

/*************************/
/* Current vertex is in the left side (i.e. side == 0).*/
    if(side==0)
      {
/* Find the next intersecting edges in both sides. */
       lint.x=lint.y=rint.x=rint.y=-INFTY;
       lepre=le; repre=re; 
       if(lp!=lb)
         {
          do
            {
             if(le==lepre) markpre=1;
             else markpre=0;
             if(E[le].p1==lp) le=E[le].clock1;
             else le=E[le].clock2;
             if(markpre==1) lenext=le;
             if(le != lepre) lint=intersect(vcur, n, E[le].v1, E[le].v2);
            }
          while(lint.x < -0.9*INFTY && le != lepre && le != enew);
          if(le==enew) le=lepre;
         }
       if(rp!=rb)
         {
          do
            {
             rint=intersect(vcur, n, E[re].v1, E[re].v2);
             if(rint.x < -0.9*INFTY)
                {
                 if(E[re].p1==rp) re=E[re].anti1;
                 else re=E[re].anti2;
                }
            }
          while(rint.x < -0.9*INFTY && re != repre && re != enew);
          if(re==enew) re=repre;
         }

/* printf("intersection found.\n");
printf("lint.x=%f, lint.y=%f, rint.x=%f, rint.y=%f\n", lint.x, lint.y, rint.x, rint.y); */
/* Update the current vertex, and add new edge. */
       if(lint.y>=rint.y-ZERO)
         {
          side=0;
          V[n].x=lint.x; V[n].y=lint.y; V[n].div=0;
          E[m].v1=vcur; E[m].v2=n; E[m].p1=rp; E[m].p2=lp;
          E[m].clock1=enew; E[m].anti1=-1; E[m].clock2=le; E[m].anti2=lepre;
          E[m].alive=1;
          if(E[lepre].p1==lp) E[lepre].clock1=m;
          else E[lepre].clock2=m;
          if(E[enew].p1==rp) E[enew].anti1=m;
          else E[enew].anti2=m;
          if(E[le].p1==lp) E[le].anti1=m; 
          else  E[le].anti2=m;
          if(E[le].p1==lp) lp=E[le].p2;
          else lp=E[le].p1;
          cut(n, le, lp, side);
        }
       else
         {
          side=1; le=lenext;
          V[n].x=rint.x; V[n].y=rint.y; V[n].div=0;
          E[m].v1=vcur; E[m].v2=n; E[m].p1=lp; E[m].p2=rp;
          E[m].anti1=lepre; E[m].clock1=-1; E[m].anti2=re; E[m].clock2=enew;
          E[m].alive=1;
          if(E[lepre].p1==lp) E[lepre].clock1=m;
          else E[lepre].clock2=m;
          if(E[enew].p1==rp) E[enew].anti1=m;
          else E[enew].anti2=m;
          if(E[re].p1==rp) E[re].clock1=m; 
          else  E[re].clock2=m;
          if(E[re].p1==rp) rp=E[re].p2;
          else rp=E[re].p1;
          cut(n, re, rp, side);
         }
      }

/* ***********************/
/* Current vertex is in the right side (i.e. side == 1).*/
    else
      {
/* Find the next intersecting edges in both sides. */
       rint.x=rint.y=lint.x=lint.y=-INFTY;
       repre=re; lepre=le; 
       if(rp!=rb)
         {
          do
            { 
             if(re==repre) markpre=1;
             else markpre=0;
             if(E[re].p1==rp) re=E[re].anti1;
             else re=E[re].anti2; 
             if(markpre==1) renext=re;
             if(re != repre) rint=intersect(vcur, n, E[re].v1, E[re].v2);
            }
          while(rint.y < -0.9*INFTY && re != repre && re != enew);
          if(re==enew) re=repre;
         }
       if(lp!=lb)
         {
          do
            {
             lint=intersect(vcur, n, E[le].v1, E[le].v2);
             if(lint.y < -0.9*INFTY)
                {
                 if(E[le].p1==lp) le=E[le].clock1;
                 else le=E[le].clock2;
                }
            }
          while(lint.y < -0.9*INFTY && le != lepre && le != enew);
          if(le==enew) le=lepre;
         }

/* printf("intersection found.\n");
printf("le=%d, re=%d, lp=%d, rp=%d\n", le, re, lp, rp); */

/* Update the current vertex, and add new edge. */
       if(rint.y>=lint.y-ZERO)
         {
          side=1;
          V[n].x=rint.x; V[n].y=rint.y; V[n].div=0;
          E[m].v1=vcur; E[m].v2=n; E[m].p1=lp; E[m].p2=rp;
          E[m].anti1=enew; E[m].clock1=-1; E[m].anti2=re; E[m].clock2=repre;
          E[m].alive=1;
          if(E[repre].p1==rp) E[repre].anti1=m;
          else E[repre].anti2=m;
          if(E[enew].p1==lp) E[enew].clock1=m;
          else E[enew].clock2=m;
          if(E[re].p1==rp) E[re].clock1=m; 
          else  E[re].clock2=m;
          if(E[re].p1==rp) rp=E[re].p2;
          else rp=E[re].p1;
          cut(n, re, rp, side);
         }
       else
         {
          side=0; re=renext;
          V[n].x=lint.x; V[n].y=lint.y; V[n].div=0;
          E[m].v1=vcur; E[m].v2=n; E[m].p1=rp; E[m].p2=lp;
          E[m].clock1=repre; E[m].anti1=-1; E[m].clock2=le; E[m].anti2=enew;
          E[m].alive=1;
          if(E[repre].p1==rp) E[repre].anti1=m;
          else E[repre].anti2=m;
          if(E[enew].p1==lp) E[enew].clock1=m;
          else E[enew].clock2=m;
          if(E[le].p1==lp) E[le].anti1=m; 
          else  E[le].anti2=m;
          if(E[le].p1==lp) lp=E[le].p2;
          else lp=E[le].p1;
          cut(n, le, lp, side);
         }
      }
    enew=m; vcur=n;
    n=n+1; m=m+1;

/* printf("One iteration over\n");
printf("le=%d, re=%d, lepre=%d, repre=%d, lp=%d, rp=%d, lt=%d, rt=%d, lb=%d, rb=%d, enew=%d, side=%d, vcur=%d\n", le, re, lepre, repre, lp, rp, lt, rt, lb, rb, enew, side, vcur);
veprint(p1, p2); */

   } 
 
/***********************/
/* Final line segment. */
 x12=S[rp].x-S[lp].x;
 y12=S[rp].y-S[lp].y;
 ya=V[vcur].y-1.0;
 xa=V[vcur].x+y12/x12;
 V[n].x=xa; V[n].y=ya; V[n].div=1;
 if(side==0)
   {
    E[m].v1=vcur; E[m].v2=n; E[m].p1=lp; E[m].p2=rp; E[m].alive=1;
    E[m].anti1=le; E[m].clock1=S[lp].aend; E[m].anti2=S[rp].cend; E[m].clock2=enew;
    S[lp].cend=m; S[rp].aend=m;
    if(E[le].p1==lp) E[le].clock1=m;
    else E[le].clock2=m;
    if(E[enew].p1==rp) E[enew].anti1=m;
    else E[enew].anti2=m;
    if(E[S[rp].cend].p1==rp) E[S[rp].cend].clock1=m;
    else E[S[rp].cend].clock2=m; 
    if(E[S[lp].aend].p1==lp) E[S[lp].aend].anti1=m;
    else E[S[lp].aend].anti2=m; 
   }
 else
   {
    E[m].v1=vcur; E[m].v2=n; E[m].p1=rp; E[m].p2=lp; E[m].alive=1;
    E[m].clock1=re; E[m].anti1=S[rp].cend; E[m].clock2=S[lp].aend; E[m].anti2=enew;
    S[rp].aend=m; S[lp].cend=m;
    if(E[re].p1==rp) E[re].anti1=m;
    else E[re].anti2=m;
    if(E[enew].p1==lp) E[enew].clock1=m;
    else E[enew].clock2=m;
    if(E[S[lp].aend].p1==lp) E[S[lp].aend].anti1=m;
    else E[S[lp].aend].anti2=m; 
    if(E[S[rp].cend].p1==rp) E[S[rp].cend].clock1=m;
    else E[S[rp].cend].clock2=m; 
   }
 n=n+1; m=m+1;

/* printf("Last iteration over\n");
printf("le=%d, re=%d, lp=%d, rp=%d, lt=%d, rt=%d, lb=%d, rb=%d, enew=%d, side=%d, vcur=%d\n", le, re, lp, rp, lt, rt, lb, rb, enew, side, vcur);
veprint(p1, p2);
pprint(p); */

 return;  
}




/*********************************************************************/
void voronoi1(int p1, int p2)
/* Construction of Voronoi diagram when p2-p1=1. */
{
 float xa, ya, xb, yb, x12, y12;
 xa=(S[p1].x+S[p2].x)/2.0;
 ya=(S[p1].y+S[p2].y)/2.0;
 x12=S[p2].x-S[p1].x;
 y12=S[p2].y-S[p1].y;
 if(fabs(y12)>ZERO) 
   {
    xb=xa+1.0; yb=-x12/y12 + ya;
   }
 else
   {
    xb=xa; yb=ya+1.0;
   }
 V[n].x=xa; V[n].y=ya; V[n].div=1;
 V[n+1].x=xb; V[n+1].y=yb; V[n+1].div=1;
 if(y12<=ZERO)
   {
    E[m].v1=n; E[m].v2=n+1; E[m].p1=p1; E[m].p2=p2; 
   }
 else
   {
    E[m].v1=n; E[m].v2=n+1; E[m].p1=p2; E[m].p2=p1; 
   }
 E[m].clock1=m; E[m].clock2=m; E[m].anti1=m; E[m].anti2=m; 
 E[m].alive=1;
 S[p1].cend=S[p1].aend=m;
 S[p2].cend=S[p2].aend=m;
 n=n+2;
 m=m+1;
 return;
}




/*******************************************************************/
void voronoi2(int p1, int p2)
/* Construction of Voronoi diagram when p2-p1=2. */
{
 int polarity;
 float xa, ya, xb, yb, x12, y12, x23, y23, x13, y13;
 float xa1, ya1, xb1, yb1, xa2, ya2, xb2, yb2, xa3, ya3;
 float sa12, sb12, sa23, sb23, sa13, sb13;
 float d12, d13;
 struct point pint;
 xa1=(S[p1].x+S[p1+1].x)/2.0;
 ya1=(S[p1].y+S[p1+1].y)/2.0;
 x12=S[p1+1].x-S[p1].x;
 y12=S[p1+1].y-S[p1].y;
 if(fabs(y12)>ZERO) 
   {
    xb1=xa1+1.0; yb1=-x12/y12 + ya1;
   }
 else
   {
    xb1=xa1; yb1=ya1+1.0;
   }
 xa2=(S[p1+1].x+S[p2].x)/2.0;
 ya2=(S[p1+1].y+S[p2].y)/2.0;
 x23=S[p2].x-S[p1+1].x;
 y23=S[p2].y-S[p1+1].y;
 if(fabs(y23)>ZERO) 
   {
    xb2=xa2+1.0; yb2=-x23/y23 + ya2;
   }
 else
   {
    xb2=xa2; yb2=ya2+1.0;
   }
 x13=S[p2].x-S[p1].x;
 y13=S[p2].y-S[p1].y;
 if(fabs(x12)<=ZERO)
   {
    if(y12>ZERO) d12=INFTY;
    else d12=-INFTY;
   }
 else d12=y12/x12; 
 if(fabs(x13)>ZERO) d13=y13/x13;
 if(d12>d13) polarity=1;
 else polarity=0;

/***************************/
/* Find the intersection of the first two lines. */
 V[n].x=xa1; V[n].y=ya1; V[n].div=1;
 V[n+1].x=xb1; V[n+1].y=yb1; V[n+1].div=1;
 V[n+2].x=xa2; V[n+2].y=ya2; V[n+2].div=1;
 V[n+3].x=xb2; V[n+3].y=yb2; V[n+3].div=1;  
 pint=intersect(n, n+1, n+2, n+3); 
/* There is the intersection. */
 if(fabs(pint.x)<0.9*INFTY && fabs(pint.y)<0.9*INFTY)
   {
    if(fabs(pint.x-V[n].x)<=ZERO && fabs(pint.y-V[n].y)<=ZERO)
      {
       V[n].x=2.0*V[n].x-V[n+1].x;
       V[n].y=2.0*V[n].y-V[n+1].y;
      }
    V[n+1].x=pint.x; V[n+1].y=pint.y; V[n+1].div=0;
    xa=(S[p1].x+S[p2].x)/2.0;
    ya=(S[p1].y+S[p2].y)/2.0;
    V[n+3].x=xa; V[n+3].y=ya; V[n+3].div=1; 
    sa12=x12*(V[n+1].y-S[p1].y)-y12*(V[n+1].x-S[p1].x);
    sb12=x12*(S[p2].y-S[p1].y)-y12*(S[p2].x-S[p1].x);
    if(sa12*sb12<-ZERO)
      {
       V[n].x=2.0*V[n+1].x-V[n].x;
       V[n].y=2.0*V[n+1].y-V[n].y;
      }
    sa23=x23*(V[n+1].y-S[p1+1].y)-y23*(V[n+1].x-S[p1+1].x);
    sb23=x23*(S[p1].y-S[p1+1].y)-y23*(S[p1].x-S[p1+1].x);
    if(sa23*sb23<-ZERO)
      {
       V[n+2].x=2.0*V[n+1].x-V[n+2].x;
       V[n+2].y=2.0*V[n+1].y-V[n+2].y;
      }
    sa13=x13*(V[n+1].y-S[p1].y)-y13*(V[n+1].x-S[p1].x);
    sb13=x13*(S[p1+1].y-S[p1].y)-y13*(S[p1+1].x-S[p1].x);
    if(sa13*sb13<-ZERO)
      {
       V[n+3].x=2.0*V[n+1].x-V[n+3].x;
       V[n+3].y=2.0*V[n+1].y-V[n+3].y;
      }  

/**************************/
/* Determine the adjacent edges and diverging edges. */
    if(polarity==1)
      {
       E[m].v1=n+1; E[m].v2=n; E[m].p1=p1; E[m].p2=p1+1; 
       E[m].clock1=m+2; E[m].clock2=m+1; 
       E[m].anti1=m+2; E[m].anti2=m+1;
       E[m+1].v1=n+1; E[m+1].v2=n+2; E[m+1].p1=p1+1; E[m+1].p2=p2; 
       E[m+1].clock1=m; E[m+1].clock2=m+2; 
       E[m+1].anti1=m; E[m+1].anti2=m+2; 
       E[m+2].v1=n+1; E[m+2].v2=n+3; E[m+2].p1=p1; E[m+2].p2=p2; 
       E[m+2].clock1=m; E[m+2].clock2=m+1; 
       E[m+2].anti1=m; E[m+2].anti2=m+1; 
       S[p1].aend=m; S[p1].cend=m+2; 
       S[p1+1].aend=m+1; S[p1+1].cend=m; 
       S[p2].aend=m+2; S[p2].cend=m+1; 
      } 
    else
      {
       E[m].v1=n+1; E[m].v2=n; E[m].p1=p1+1; E[m].p2=p1; 
       E[m].clock1=m+1; E[m].clock2=m+2; 
       E[m].anti1=m+1; E[m].anti2=m+2; 
       E[m+1].v1=n+1; E[m+1].v2=n+2; E[m+1].p1=p2; E[m+1].p2=p1+1; 
       E[m+1].clock1=m+2; E[m+1].clock2=m; 
       E[m+1].anti1=m+2; E[m+1].anti2=m; 
       E[m+2].v1=n+1; E[m+2].v2=n+3; E[m+2].p1=p2; E[m+2].p2=p1; 
       E[m+2].clock1=m+1; E[m+2].clock2=m; 
       E[m+2].anti1=m+1; E[m+2].anti2=m; 
       S[p1].aend=m+2; S[p1].cend=m; 
       S[p1+1].aend=m; S[p1+1].cend=m+1; 
       S[p2].aend=m+1; S[p2].cend=m+2; 
      }
    E[m].alive=E[m+1].alive=E[m+2].alive=1;
    n=n+4; m=m+3;
   }   
 else /* Two lines are parallel. */
   {
    E[m].v1=n; E[m].v2=n+1; E[m].p1=p1; E[m].p2=p1+1; 
    E[m].clock1=m; E[m].clock2=m+1; 
    E[m].anti1=m; E[m].anti2=m+1; 
    E[m+1].v1=n+2; E[m+1].v2=n+3; E[m+1].p1=p1+1; E[m+1].p2=p2; 
    E[m+1].clock1=m; E[m+1].clock2=m+1; 
    E[m+1].anti1=m; E[m+1].anti2=m+1; 
    S[p1].aend=m; S[p1].cend=m; 
    S[p1+1].aend=m; S[p1+1].cend=m+1; 
    S[p2].aend=m+1; S[p2].cend=m+1; 
    E[m].alive=E[m+1].alive=1;
    n=n+4; m=m+2;
   }
 return;
}




/******************************************************************/
struct pair topbot(int p1, int p2, int p3, int p4)
/* Find top and bottm supporting pairs of the convex full
   defined by intervals [S[p1], S[p2]] and [S[p3], S[p4]],
   where p1<=p2<=p3<=p4. */
{
 int i;
 int ltest, rtest;
 int lt, lb, rt, rb;
 struct pair q;
 float xt12, yt12, xb12, yb12;
 lt=lb=p1;
 for(i=p1; i<=p2; i++)
   {
    if(S[i].y>=S[lt].y-ZERO) lt=i;
    if(S[i].y<=S[lb].y+ZERO) lb=i;
   }
 rt=rb=p3;
 for(i=p3; i<=p4; i++)
   {
    if(S[i].y>S[rt].y+ZERO) rt=i;
    if(S[i].y<S[rb].y-ZERO) rb=i;
   }
/*  printf("lt = %d, lb = %d, rt = %d, rb = %d\n", lt, lb, rt, rb); */
 ltest=rtest=1;
 xt12=S[rt].x-S[lt].x;
 yt12=S[rt].y-S[lt].y;
 xb12=S[rb].x-S[lb].x;
 yb12=S[rb].y-S[lb].y;
 while(ltest==1 || rtest==1)
   {
    if(ltest==1)
      {
       ltest=0;
       for(i=p1; i<=p2; i++)
         {
          if(xt12*(S[i].y-S[lt].y) >= yt12*(S[i].x-S[lt].x)-ZERO)
            {
             lt=i; rtest=1;
             xt12=S[rt].x-S[lt].x;
             yt12=S[rt].y-S[lt].y;
            }
          if(xb12*(S[i].y-S[lb].y) <= yb12*(S[i].x-S[lb].x)+ZERO)
            {
             lb=i; rtest=1;
             xb12=S[rb].x-S[lb].x;
             yb12=S[rb].y-S[lb].y;
            }
         }
      }
    if(rtest==1)
      {
       rtest=0;
       for(i=p3; i<=p4; i++)
         {
          if(xt12*(S[i].y-S[lt].y) > yt12*(S[i].x-S[lt].x)+ZERO)
            {
             rt=i; ltest=1;
             xt12=S[rt].x-S[lt].x;
             yt12=S[rt].y-S[lt].y;
            }
          if(xb12*(S[i].y-S[lb].y) < yb12*(S[i].x-S[lb].x)-ZERO)
            {
             rb=i; ltest=1;
             xb12=S[rb].x-S[lb].x;
             yb12=S[rb].y-S[lb].y;
            }
         }
      }
   } 
 q.ltop=lt; q.lbot=lb; q.rtop=rt; q.rbot=rb;
 return(q);
}



/********************************************************************/
struct point intersect(int i1, int i2, int i3, int i4)
/* Compute the intersection of edge (V[i1], V[i2]) and 
   the line passing (V[i3], V[i4]); in case of no intersection, 
   output (-INFTY, -INFTY). */
{
 int i, j, k;
 float x12, x34, y12, y34, xd, yd, xy12, xy34, xint, yint;
 struct point p;
 p.x=-INFTY; p.y=-INFTY;
 x12=V[i2].x-V[i1].x; x34=V[i4].x-V[i3].x;
 y12=V[i2].y-V[i1].y; y34=V[i4].y-V[i3].y;
 xy34=V[i4].y*V[i3].x-V[i3].y*V[i4].x;
 xy12=V[i2].y*V[i1].x-V[i1].y*V[i2].x;
 xd=y34*x12-y12*x34;
 yd=y34*x12-y12*x34;
 if(fabs(xd)<ZERO || fabs(yd)<ZERO) return(p);
 xint=(xy34*x12-xy12*x34)/xd;
 yint=(xy34*y12-xy12*y34)/yd;
 if(fabs(x12)>ZERO)
   {
    if(x12*(xint-V[i2].x)>ZERO && V[i2].div==0) return(p);
    if(x12*(V[i1].x-xint)>ZERO && V[i1].div==0) return(p);
   }
 else
   {
    if(y12*(yint-V[i2].y)>ZERO && V[i2].div==0) return(p);
    if(y12*(V[i1].y-yint)>ZERO && V[i1].div==0) return(p);
   }
 if(fabs(x34)>ZERO)
   {
    if(x34*(xint-V[i4].x)>ZERO && V[i4].div==0) return(p);
    if(x34*(V[i3].x-xint)>ZERO && V[i3].div==0) return(p);
   }
 else
   {
    if(y34*(yint-V[i4].y)>ZERO && V[i4].div==0) return(p);
    if(y34*(V[i3].y-yint)>ZERO && V[i3].div==0) return(p);
   }
 p.x=xint; p.y=yint;
 return(p); 
}



/**************************************************************/
void bubblesort(struct point *A, int nn)
/* Bubble sort from A[0] to A[nn-1]. */
{
 float xdif, ydif;
 int i, j;
 for(i=0; i<nn-1; i++)
   {
    for(j=nn-1; j>=i+1; --j)
      {
       xdif=A[j-1].x-A[j].x;
       ydif=A[j-1].y-A[j].y;
       if(xdif>ZERO || (fabs(xdif)<=ZERO && ydif>ZERO)) swap(j, j-1, A);
      };
   }
}

void swap(int i, int j, struct point *A)
/* Swap A[i] and A[j]. */
{
 struct point temp;
 temp=A[i]; A[i]=A[j]; A[j]=temp;
 return;
}

void veprint(int p1, int p2)
/* Print the current vertex data and edge data. */
{
 int i;
 printf("current voronoi data: p1 = %d, p2 = %d\n", p1, p2);
 printf("edge data, m = %d\n", m);
 for(i=0; i<m; i++) 
   printf("i = %d, v1 = %d, v2 = %d, p1 = %d, p2 = %d, c1 = %d, c2 = %d, a1 = %d, a2 = %d, al = %d\n", i, E[i].v1, E[i].v2, E[i].p1, E[i].p2, E[i].clock1, E[i].clock2, E[i].anti1, E[i].anti2, E[i].alive);
 printf("vertex data, n = %d\n", n);
 for(i=0; i<n; i++) 
   printf("i = %d, x = %f, y = %f, d = %d\n", i, V[i].x, V[i].y, V[i].div);
 return;
}



/********************************************************************/
void pprint(int p)
/* Print the current point data. */
{
 int i;
 printf("point data (sorted on x), p = %d\n", p);
 for(i=0; i<p; i++) 
   printf("i = %d, x = %f, y = %f, cend = %d, aend = %d\n", 
          i, S[i].x, S[i].y, S[i].cend, S[i].aend);
 return;
}



/*******************************************************************/
void cut1(int n, int m)
/* Cut off edge m at the intersection vertex n. */
{
 float x12, y12, xn, yn, xdif1, xdif2, ydif1, ydif2;
 int s1, s2;
 x12=(S[E[m].p1].x+S[E[m].p2].x)/2.0; 
 y12=(S[E[m].p1].y+S[E[m].p2].y)/2.0;
 xn=V[n].x; yn=V[n].y;
 xdif1=(V[E[m].v1].x-xn)*(x12-xn);
 ydif1=(V[E[m].v1].y-yn)*(y12-yn);
 xdif2=(V[E[m].v2].x-xn)*(x12-xn);
 ydif2=(V[E[m].v2].y-yn)*(y12-yn);
 s1=s2=0;
 if(xdif1>ZERO && ydif1>ZERO) s1=1;
 if(xdif2>ZERO && ydif2>ZERO) s2=1;
 if(s1==1 && s2==0)
   {
    V[E[m].v2].div=-1;
    E[m].v2=n;
   }
 if(s1==0 && s2==1)
   {
    V[E[m].v1].div=-1;
    E[m].v1=n;
   }
 if(s1==1 && s2==1)
   {
    if(xdif1>xdif2)
      {
       V[E[m].v2].div=-1;
       E[m].v2=n;
      }
    else
      {
       V[E[m].v1].div=-1;
       E[m].v1=n;
      }
   }
 return;
}


/*********************************************************************/
void rcut(int n, int m)
/* Cut off edge m at the intersection vertex n, where m is on the 
right side. */
{
 float x1, x2, y1, y2;
 x1=V[E[m].v1].x; y1=V[E[m].v1].y; 
 x2=V[E[m].v2].x; y2=V[E[m].v2].y; 
 if(x1 >= x2-ZERO) 
   {
    if(x1 <= V[n].x+ZERO) 
      {
       V[E[m].v1].x=V[n].x+1.0;
       V[E[m].v1].y=V[n].y+(y2-y1)/(x2-x1);
      }
    V[E[m].v2].div=-1;
    E[m].v2=n;
   }
 else 
   {
    if(x2 > V[n].x+ZERO) 
      {
       V[E[m].v2].x=V[n].x+1.0;
       V[E[m].v2].y=V[n].y+(y2-y1)/(x2-x1);
      }
    V[E[m].v1].div=-1;
    E[m].v1=n;
   }
 return;
}


/*********************************************************************/
int eclock(int pt, int e)
/* Outputs 1 (resp. 2) if E[e].v1 (E[e].v2) is located on the clockwise
side, judged from the point pt.  If two vertices are very close, it
outputs 0. */
{
 float x1, x2, y1, y2, ly, rx;
 x1=V[E[e].v1].x; y1=V[E[e].v1].y; 
 x2=V[E[e].v2].x; y2=V[E[e].v2].y;  
 ly=(x2-x1)*(S[pt].y-y1);
 rx=(y2-y1)*(S[pt].x-x1);
 if(ly<rx-ZERO) return(2);
 if(rx<ly-ZERO) return(1);
 return(0);
}

int vclock(int pt, int v1, int v2)
/* Outputs 1 (resp. 2) if V[v1] (V[v2]) is located on the clockwise
side, judged from the point pt.  If two vertices are very close, it
outputs 0. */
{
 float x1, x2, y1, y2, ly, rx;
 x1=V[v1].x; y1=V[v1].y; 
 x2=V[v2].x; y2=V[v2].y;  
 ly=(x2-x1)*(S[pt].y-y1);
 rx=(y2-y1)*(S[pt].x-x1);
 if(ly<rx-ZERO) return(2);
 if(rx<ly-ZERO) return(1);
 return(0);
}


/*********************************************************************/
void cut(int v, int e, int pt, int side)
/* Cut off the edge e at the intersection vertex v.  The part cut off is
on the anti-clockwise side, judged from point pt.  The e is on the left
side if side==0, and on the right side if side==1.  */
{
 float x1, x2, y1, y2;
 int cvx, cv;
 if(side==0)
   {
    if(E[e].p1==pt) pt=E[e].p2;
    else pt=E[e].p1;
   }
 cvx=eclock(pt, e);
 if(cvx==1)
   {
    cv=vclock(pt, E[e].v1, v);
    if(cv==2 || cv==0)
      {
       V[E[e].v1].x=2.0*V[v].x-V[E[e].v2].x;
       V[E[e].v1].y=2.0*V[v].y-V[E[e].v2].y;
      }
    V[E[e].v2].div=-1;
    E[e].v2=v;   
   }
 else
   {
    cv=vclock(pt, E[e].v2, v);
    if(cv==2 || cv==0)
      {
       V[E[e].v2].x=2.0*V[v].x-V[E[e].v1].x;
       V[E[e].v2].y=2.0*V[v].y-V[E[e].v1].y;
      }
    V[E[e].v1].div=-1;
    E[e].v1=v;   
  }
 return;
}



