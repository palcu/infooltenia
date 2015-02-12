#include <stdio.h>
#define M 502
int main()
{FILE *fi,*fo;
int i,j,m,n,k,k1,min,s,np,a[M][M],b[M][M];
fi=fopen("tort.in","rt");
fscanf(fi,"%d %d %d",&m,&n,&k);
for(i=1;i<=m;i++) for(j=1;j<=n;j++) fscanf(fi,"%d",&a[i][j]); fclose(fi);
min=m*n+1;
for(i=0;i<=m;i++) b[i][0]=0; for(j=0;j<=n;j++) b[0][j]=0; b[1][1]=a[1][1];
for(i=2;i<=m;i++) b[i][1]=b[i-1][1]+a[i][1];
for(j=2;j<=n;j++) b[1][j]=b[1][j-1]+a[1][j];
for(i=2;i<=m;i++) for(j=2;j<=n;j++) b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+a[i][j];
for(k1=0;k1<=k;k1++)
 for(i=m-k1;i<=m;i++) for(j=n-k+k1;j<=n;j++) {
   s=b[i][j]-b[i-m+k1][j]-b[i][j-n+k-k1]+b[i-m+k1][j-n+k-k1];
   if(s<min) {min=s; np=1;} else if(s==min) np++; }
fo=fopen("tort.out","wt"); fprintf(fo,"%d\n%d\n",b[m][n]-min,np);
fclose(fo); return 0;}
