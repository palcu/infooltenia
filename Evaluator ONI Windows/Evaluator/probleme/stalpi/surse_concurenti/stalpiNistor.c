// stalpi 100p
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M 20000
#define C 200
#define INF 50000
typedef struct _pct {int d; int c;} pct;
int p[C],u[C],pm[C],um[C],dm[C];
int main()
{FILE *fi,*fo;
pct a[M], b[M];
int i,n,d,c,k=0;
double dist=0;
fi=fopen("stalpi.in","r");
fscanf(fi,"%d %d",&n,&d);
for(i=1;i<=n;i++) fscanf(fi,"%d %d",&a[i].d,&a[i].c);
for(i=1;i<=n;i++) fscanf(fi,"%d %d",&b[i].d,&b[i].c);
fclose(fi);
for(i=1;i<=n;i++) if(a[i].c>k) k=a[i].c;
for(i=1;i<=k;i++) dm[i]=INF;
for(i=1;i<=n;i++)
{ c=a[i].c; p[c]=i;
  if(u[c]>0 && abs(a[p[c]].d-b[u[c]].d)<dm[c])
     {dm[c]=abs(a[p[c]].d-b[u[c]].d); pm[c]=p[c]; um[c]=u[c];}
  c=b[i].c; u[c]=i;
  if(p[c]>0 && abs(a[p[c]].d-b[u[c]].d)<dm[c])
     {dm[c]=abs(a[p[c]].d-b[u[c]].d); pm[c]=p[c]; um[c]=u[c];}
}
for(i=1;i<=k;i++) dist+=sqrt(d*d+dm[i]*dm[i]);
fo=fopen("stalpi.out","w");
fprintf(fo,"%.3f\n",dist);
for(i=1;i<=k;i++)
fprintf(fo,"%d %d\n",pm[i],um[i]);
fclose(fo);
return 0;
}

