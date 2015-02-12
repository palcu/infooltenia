#include<fstream.h>
#include<stdlib.h>
#include <math.h>
#include<iomanip.h>
#include<stdio.h>

ifstream fin("stalpi.in");
long n,d,k,x1[10001],x2[10001],c1[10001],c2[10001],xx1[101],xx2[101];
long a[30001],b[30001];
double dmin=0;

void cit(){
long i;
fin>>n>>d;k=0;
for(i=1;i<=n;i++){
	fin>>x1[i]>>c1[i];
	if(c1[i]>k)
		k=c1[i];
	}
for(i=1;i<=n;i++)
fin>>x2[i]>>c2[i];
fin.close();
}

void rezolva(){
long c,i,j,xa,xb,min;
double r,rr;
dmin=0;
for(c=1;c<=k;c++){
	 r=1000000;
	 for(i=1;i<=n;i++)
		 if(c1[i]==c)
		  for(j=1;j<=n;j++)
		   if(c2[j]==c)
			  {
				rr=sqrt(d*d+(x1[i]-x2[j])*(x1[i]-x2[j]));
				if(r>rr){
					xx1[c]=i;
					xx2[c]=j;
					r=rr;
				}
		   }
		   dmin+=r;
}
	
freopen("stalpi.out","w",stdout);
printf("%0.3f\n",dmin);
for(i=1;i<=k;i++)
printf("%d %d\n",xx1[i],xx2[i]);
//fout.close();
}

int main(){
cit();
rezolva();
return 0;
}
