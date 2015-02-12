// sursa Chesca Ciprian - 100 p
#include <fstream>
#define nmax 10001

using namespace std;

typedef struct solutie
	{ 
	short x,y;
	};

ifstream f("poligon.in");
ofstream g("poligon.out");


int main()
{
int n,k,x,y,i,e,pmax,ok,t;
short d[nmax],v[nmax],a[nmax];
solutie s[nmax],aux;

// citire date de intrare
f>>n;
for(i=1;i<=n;i++)
	f>>a[i];


//determin potentiale tinte
k=0;
for(i=1;i<=n;i++)
	for(x=1;x<=a[i];x++)
		{
		t=a[i]*a[i]-x*x;
		y=1;
		while (y*y<t&&y<x) y++;
		if (y*y==t) {s[++k].x=x;s[k].y=y;}
					
		}

// sortez vectorul tintelor dupa inclinatie
do
{
ok=0;
for(i=1;i<=k-1;i++)
	if (s[i].x*s[i+1].y<s[i].y*s[i+1].x) 
				{
				aux=s[i];
				s[i]=s[i+1];
				s[i+1]=aux;
				ok=1;
				}
}
while (ok);


// asociez fiecare punct la o dreapta ce trece prin origine
for(i=1;i<=k;i++)
	d[i]=0;

e=1;d[1]=1;
for(i=2;i<=k;i++)
	if (s[i-1].x*s[i].y==s[i-1].y*s[i].x) 	d[i]=d[i-1];
										else d[i]=++e;

	
// determin numarul maxim de directii	
pmax=1;
for(i=2;i<=k;i++)
	if (d[i]>d[pmax]) pmax=i;


// determin cate tinte sunt pe fiecare directie
for(i=1;i<=d[pmax];i++) v[i]=0;
for(i=1;i<=k;i++) v[d[i]]++;


// afisez rezultatele
g<<2*k<<"\n";
g<<2*d[pmax]<<"\n";	
for(i=1;i<=d[pmax];i++)
	g<<v[i]<<" ";
for(i=d[pmax];i>=1;i--)
	g<<v[i]<<" ";
g<<"\n";


f.close();
g.close();
	
return 0;
}

