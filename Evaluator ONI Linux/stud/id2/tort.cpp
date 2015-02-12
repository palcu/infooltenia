#include<fstream>
using namespace std;
ifstream f1("tort.in");
ofstream f2("tort.out");
int b[503][503],m,n,k,kn,ks,kv,ke,i,j,xmin,x,nr;

int main()
{
	f1>>m>>n>>k;
	for (i=0;i<=m+1;i++)
		for (j=0;j<=n+1;j++)
			b[i][j]=0;
	for (i=1;i<=m;i++)
		for (j=1;j<=n;j++)
		{
			f1>>x;
			b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+x;
		}
	xmin=m*n;
	for (kn=0;kn<=k;kn++)
		for (ks=0;ks<=k-kn;ks++)
			for (kv=0;kv<=k-kn-ks;kv++)
			{
				ke=k-kn-ks-kv;
				x=b[m-ks][n-ke]-b[kn][n-ke]-b[m-ks][kv]+b[kn][kv];
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
	f2<<b[m][n]-xmin<<"\n"<<nr;
	f2.close();
	f1.close();
	return 0;
}
			