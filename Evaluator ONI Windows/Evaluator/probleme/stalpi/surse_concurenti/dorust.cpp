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
double r;
dmin=0;
for(c=1;c<=k;c++)
{
 for(i=0;i<=30000;i++) {a[i]=0;b[i]=0;}
 for(i=1;i<=n;i++)
  {
   if (c1[i]==c) a[x1[i]]=i;
   if (c2[i]==c) b[x2[i]]=i;
  }

  min=100000;
  xa=0;xb=0;
  for(i=1;i<=30000;i++)
  {
	if(a[i]!=0 && xa==0) xa=i;
    if(b[i]!=0 && xb==0) xb=i;
  }
  for(i=1;i<=30000;i++)
   {
    if(a[i]!=0 && xb!=0 && abs(i-xb)<min){
     xa=i;
     min=abs(i-xb);}
    if(b[i]!=0 && xa!=0 && abs(i-xa)<min){
     xb=i;
     min=abs(i-xa);}
   }
    xx1[c]=a[xa];xx2[c]=b[xb];
    //cout<<"culoare="<<c<<" "<<xx1[c]<<" "<<xx2[c]<<" "<<min<<"\n";
	r=d;r=r*r;
	r+=min*min;
    dmin+=sqrt(r);
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
