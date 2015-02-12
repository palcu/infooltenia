#include<fstream>
using namespace std;
ifstream f1("tort.in");
ofstream f2("tort.out");
int b[503][503],m,n,k,kn,ks,kv,ke,i,j,xmax,x,nr,xmin,y;

int main()
{
	f1>>m>>n>>k;
	y=0;
	for (i=1;i<=m;i++)
		for (j=1;j<=n;j++)
		{
			f1>>x;
			b[i][j]=x;
			y=y+x;
		}
	if (k<n/2 && k<m/2)
	{
	xmax=0;
	for (kn=0;kn<=k;kn++)
		for (ks=0;ks<=k-kn;ks++)
			for (kv=0;kv<=k-kn-ks;kv++)
			{
				ke=k-kn-ks-kv;
				x=0;
				for (j=1;j<=n;j++)
				{
					for (i=1;i<=kn;i++) x=x+b[i][j];
					for (i=m-ks+1;i<=m;i++) x=x+b[i][j];
				}
				for (i=kn+1;i<=m-ks;i++)
				{
					for (j=1;j<=kv;j++)x=x+b[i][j];
					for (j=n-ke+1;j<=n;j++)x=x+b[i][j];
				}
				
				if (x>xmax)
				{
					nr=1; 
					xmax=x; 
				}
				else if (x==xmax)
						{
							nr++;
						}
			}
	f2<<xmax<<"\n"<<nr;
	}
	else
	{
	xmin=m*n;
	for (kn=0;kn<=k;kn++)
		for (ks=0;ks<=k-kn;ks++)
			for (kv=0;kv<=k-kn-ks;kv++)
			{
				ke=k-kn-ks-kv;
				x=0;
				for (i=kn+1;i<=m-ks;i++)
					for (j=kv+1;j<=n-ke;j++)
						x=x+b[i][j];
				if (x<xmin)
				{
					nr=1; 
					xmin=x; 
				}
				else if (x==xmin)
						{
							nr++;
						}
			}
	f2<<y-xmin<<"\n"<<nr;
	}
		
	f2.close();
	f1.close();
	return 0;
}
			