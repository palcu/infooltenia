#include <stdio.h>
#define M 502
int a[M][M];
int main()
{FILE *fi,*fo;
int i,j,m,n,k,k1,min,s,np;
fi=fopen("tort.in","rt");
fscanf(fi,"%d %d %d",&m,&n,&k);
for(i=1;i<=m;i++) for(j=1;j<=n;j++) fscanf(fi,"%d",&a[i][j]); fclose(fi);
min=m*n+1;
for(i=2;i<=m;i++) a[i][1]+=a[i-1][1];
for(j=2;j<=n;j++) a[1][j]+=a[1][j-1];
for(i=2;i<=m;i++) for(j=2;j<=n;j++) a[i][j]+=(a[i-1][j]+a[i][j-1]-a[i-1][j-1]);
for(k1=0;k1<=k;k1++)
 for(i=m-k1;i<=m;i++) for(j=n-k+k1;j<=n;j++) {
   s=a[i][j]-a[i-m+k1][j]-a[i][j-n+k-k1]+a[i-m+k1][j-n+k-k1];
   if(s<min) {min=s; np=1;} else if(s==min) np++; }
fo=fopen("tort.out","wt"); fprintf(fo,"%d\n%d\n",a[m][n]-min,np);
fclose(fo); return 0;}
