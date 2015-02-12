#include <fstream>
#include <iostream>
#include <string>

#include <cstdlib>
#include <cmath>

using namespace std;

ifstream fok("stalpi.ok");
ifstream fout("stalpi.out");
ifstream fin("stalpi.in");
long n,d,k,x1[10001],x2[10001],c1[10001],c2[10001],xc1[101],xc2[101],v[101];
int distincte(long x[101]){
	int i,j;

	for(i=1;i<k;i++){
		if(x[i]>n || x[i]<1) {return 0;}
		for(j=i+1;j<=k;j++)
			if(x[i]==x[j]) {return 0;}}
	return 1;	
}
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


void Msg(int pct, string msg )
{
    cout << pct << ' ' << msg;
    try
    {
        fok.close();
        fout.close();
    }
    catch (string ex) {}
    exit(0);
}

int main(int argc, char* argv[])
{
	cit();
    if ( !fout )
        Msg(0, "Nu exista fisierul munte.out!");

//    int testNumber, testPoints;
//   testNumber = atoi(argv[1]);           // numarul testului
//    testPoints = atoi(argv[2]);           // nr puncte/test

    int total = 0;    // punctajul total
    // doua cerinte, punctaje partiale
    double a;   // valori corecte
    double x, dc,ddc;   // valorile concurentului
	int i;
    bool ok1 = false, ok2 = false;
    fok >> a;
    if ( !(fout >> x) )   // daca nu pot citi din fisier
        Msg(0, "Incorect !");

    if ( abs(a-x)<0.01 )
    {
        total += (5 * 40) / 100;  // 20 % din punctajul pe test
        ok1 = true;
    }
  	
	for(i=1;i<=k;i++)
			 if(!(fout>>xc1[i]>>xc2[i]))
				 if(total==0)
					Msg(total,"Min incorect, Multime puncte incorecta!");
					else
					Msg(total,"Min corect, Multime puncte incorecta!");
	
	if(distincte(xc1)==0)
		if(total==0)
					Msg(total,"Min incorect, Multime puncte incorecta!");
					else
					Msg(total,"Min corect, Multime puncte incorecta!");
	if(distincte(xc2)==0)
		if(total==0)
					Msg(total,"Min incorect, Multime puncte incorecta!");
					else
					Msg(total,"Min corect, Multime puncte incorecta!");
	dc=0;ok2=true;
	for(i=1;i<=k;i++)
	{
		if(c1[xc1[i]]!=c2[xc2[i]]) ok2=false;
		v[c1[xc1[i]]]=1;
		ddc=d*d+abs(x1[xc1[i]]-x2[xc2[i]])*abs(x1[xc1[i]]-x2[xc2[i]]);
		ddc=sqrt(ddc);
		dc+=ddc;
	}		
	for(i=1;i<=k;i++)
		if (v[i]==0) ok2=false;
	if (abs(a-dc)>0.1) ok2=false;
				
    if ( ok2 )
    {
        total += (5 * 60) / 100; // 80 % din punctaj
        ok2 = true;
    }

    if ( ok1 && ok2 )
       Msg(total, "Corect !");
    if (!ok1 && !ok2)
        Msg(total, "Incorect !" );
    if ( ok1 )
        Msg(total, "Multime de puncte incorecta !");
    if ( ok2 )
        Msg(total, "Minim incorect !");

    return 0;
}
