#include <fstream>
#include <iostream>
#include <cstdlib>
#define nmax 10001

using namespace std;

ifstream fok("poligon.ok");
ifstream fout("poligon.out");

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
	 
    if (!fout)
        Msg(0, "Nu exista fisier de iesire!");

    int i;
    
    int total = 0;    // punctajul total
    // trei cerinte
    
    // variabile problema
    long sl,ta, tl, nl[nmax];   // valorile corecte
    
	
    // variabile concurent
    long slc, tac, tlc, nlc[nmax];   // valorile concurentului
    

    bool ok1 = false, ok2 = false, ok3 = true;
    ta=tl=tac=tlc=-1;
	sl=slc=0;

    
    // prima cerinta
    if ( !(fok >> ta) )   // daca nu pot citi din fisierul .ok
        Msg(0, "Nu exista fisier .ok!");

    if ( !(fout >> tac) )   // daca nu pot citi din fisierul .out
        Msg(0, "Nu exista fisier de iesire !");

    if ( ta == tac )
    {
        total += 1;  // 20 % din punctajul pe test
        ok1 = true;
    }

    
    // a doua cerinta - numarul de lovituri
    fok >> tl;
    fout >> tlc;

    if (tl == tlc)
    {
        total += 2; // 40 % din punctaj pe test
        ok2 = true;
    }

    
    // a treia cerinta - numarul de tinte doborate la fiecare lovitura
    
	for(i=1;i<=tl;i++)
		{fok>>nl[i];sl+=nl[i];}
    
	for(i=1;i<=tlc;i++)
		{fout>>nlc[i];;slc+=nlc[i];}

	for(i=1;i<=tl;i++)
		if (nl[i]!=nlc[i]) ok3= false;
    
	if (sl!=slc) ok3=false;
		
	if (ok3==true)
	    total += 2; // 40 % din punctaj pe test
    
		

    if ( ok1 && ok2 && ok3 )
       Msg(total, "Corect !");
    if ( ok1 && ok2 && !ok3 )
       Msg(total, "Ultima cerinta incorecta !");
    if ( ok1 && !ok2 && ok3 )
       Msg(total, "A doua cerinta incorecta !");
    if ( ok1 && !ok2 && !ok3 )
       Msg(total, "A doua si a treia cerinta incorecte !");
    if ( !ok1 && ok2 && ok3 )
       Msg(total, "Prima cerinta incorecta !");
    if ( !ok1 && ok2 && !ok3 )
       Msg(total, "Prima si a treia cerinta incorecte !");
    if ( !ok1 && !ok2 && ok3 )
       Msg(total, "Prima si a doua cerinta incorecte !");
    if ( !ok1 && !ok2 && !ok3 )
       Msg(total, "Toate cerintele sunt incorecte !");



    return 0;
}


