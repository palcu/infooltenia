#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NTeste  20
#define DMax 2002
int n[NTeste]       ={   411,  350,   120,   450,   512,    950,   615,    588,    876,   1000,   1024,   1215,  1445,  3112,   4444,   5600,  7819,   8210,    2000,   2000};
int m[NTeste]       ={   300,  449,   117,   750,   928,    256,   848,    512,    900,   1000,   1023,   1024,  1444,  3000,   4120,   5000,  7122,   8111,    2000,   2000};
long int p[NTeste]  ={ 15020, 3500,  1201, 22000, 10000,  31000, 19000,  40000, 110000,  99990,  50032, 475000, 10000, 95000, 160000,  75000, 40000, 110000, 1000000,   5000};
long int nro[NTeste]={ 10000,10000, 10000, 20000, 20000,  20000, 20000,  25000,  30000,  50000,  60000,  65000, 70000, 75000,  80000,   90000,95000, 100000, 1000000, 100000};
int lpret[NTeste]   ={   20,    30,  100,   100,    20,     20,    20,     10,     20,     10,       5,      10,    10,    10,      2,     10,     5,     30,      10,   10};
int lnmax[NTeste]   ={   10,    50,   30,    10,    20,     20,    30,     50,     10,     10,      10,      10,    10,    20,     10,     10,     4,      6,      10,   10};

//pentru fiecare imobil retin numarul de apartamente, precum si pretul chiriei pentru un apartament
typedef struct {int nr; int nrmax; unsigned char p;} imobil;
imobil a[DMax][DMax];
void itoa (int, char *);
int main()
{

FILE *fin;
char s[20];

int i, t, nmax, x, y, x1, y1, o, pret, nr, nrmax;
long j, ii;
srand(966573);
for (t=0; t<11; t++)
    {itoa(t,s);
     strcat(s,"-firma.in");
     fin=fopen(s,"w");
     fprintf(fin,"%d %d\n%ld\n",n[t], m[t], p[t]);
     for (i=1; i<=n[t]; i++)
         for (j=1; j<=m[t]; j++)
             a[i][j].nr=-1;
     for (ii=1; ii<=p[t]; ii++)
         {
         do {x=random()%n[t]+1; y=random()%m[t]+1;}
         while (a[x][y].nr!=-1);
         nmax=random()%lnmax[t]+1;
         pret=random()%lpret[t]+1;
         nr=random()%nmax;
         fprintf(fin,"%d %d %d %d %d\n", x, y, nmax, nr, pret);
         a[x][y].nr=nr;a[x][y].nrmax=nrmax;a[x][y].p=pret;
         }
     fprintf(fin,"%ld\n",nro[t]);
     for (j=0; j<nro[t]; j++)
         {
         if (j%2==0) o=3;
	   else	 
	   o=random()%3+1;

         x=random()%n[t]+1; y=random()%m[t]+1;
         if (o<3)
            {fprintf(fin,"%d %d %d\n", o, x, y);}
             else
             {
             x1=random()%n[t]+1; y1=random()%m[t]+1;
             fprintf(fin,"%d %d %d %d %d\n", o, x, y, x1, y1);
             }

         }
     fclose(fin);
     }
return 0;
}

void itoa (int x, char *s)
{
if (x<10) 
    {s[0]=x+'0'; s[1]=0;}
    else
    {s[0]=x/10+'0'; s[1]=x%10+'0'; s[2]=0;}
}