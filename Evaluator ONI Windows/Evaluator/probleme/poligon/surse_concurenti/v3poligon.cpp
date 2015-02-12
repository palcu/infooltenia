// sursa PitRada Vasile - 100 p
#include<fstream>
#include<math.h>
using namespace std;
ifstream f1("poligon.in");
ofstream f2("poligon.out");

int n,i,c,s,aux,r[1001],j,k;
int x[10000],y[10000];


int main()
{
	f1>>n;
	c=0;
	for (i=1;i<=n;i++)
	{
		f1>>r[i];
		for (j=1;j<=r[i]-1;j++)
		{
			k=(int)sqrt((double)r[i]*r[i]-j*j);
			if (k*k+j*j==r[i]*r[i])
			{
				c++;
				x[c]=j; y[c]=k;

			}
		}
	}
	f2<<c<<"\n";
	for (i=1;i<c;i++)
		for (j=i+1;j<=c;j++)
			if (x[i]*y[j]>x[j]*y[i])
			{
				aux=x[i]; x[i]=x[j]; x[j]=aux;
				aux=y[i]; y[i]=y[j]; y[j]=aux;
			}
	x[0]=0; y[0]=1;
	s=0;
	for (i=1;i<=c;i++)
	{
		if (x[i-1]*y[i]<x[i]*y[i-1])
			s++;
	}
	f2<<s<<"\n";
	s=1;
	for (i=2;i<=c;i++)
	{
		if (x[i-1]*y[i]==x[i]*y[i-1])
		{
			s++;
		}
		else
		{
			f2<<s<<" ";
			s=1;
		}
	}
	f2<<s;
	f2.close();
	f1.close();
	return 0;
}
