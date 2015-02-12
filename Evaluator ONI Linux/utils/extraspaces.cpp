#include <fstream.h>
#include <string.h>
#define maxn 800001
char s[maxn];
void main(int nr, char *a[])
{
ifstream fin;
ofstream fout;
int i, j;
if (nr==1) cout<<"prea putine argumente";
      else
      {fin.open(a[1]);
       fout.open("man.txt");
       while (!fin.eof())
             {fin.getline(s,maxn);
              if (fin.good())
                 {
                  
		 while (s[0]==' ') strcpy(s,s+1);
                  if (s[0])
                      for (i=1; s[i]; )
                          if (s[i]==' ' && s[i-1]==' ')
                             strcpy(s+i,s+i+1);
                             else i++;
                   for (j=i-1; j>=0 && s[j]==' '; j--)
                       s[j]=NULL;
                   fout<<s<<endl;
                 }
              }
           fin.close();
           fout.close();
      }

}
