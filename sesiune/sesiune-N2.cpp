#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
#define NMAX 1025
#define modulo 666013
#define pb push_back
#define mp make_pair
#define sz size()
 
long int a[NMAX],i,j,k,n,m,s,x,val,ok,nr,sol;
vector< pair<int,int> > G[modulo],H[modulo];
 
int main()
{
        freopen("sesiune.in","r",stdin);
        freopen("sesiune.out","w",stdout);
 
        scanf("%ld %ld",&n,&k);
 
        for (i=1;i<=n;i++)
                {
                scanf("%ld",&a[i]);
                val=a[i]%modulo;
 
                ok=0;
                for (x=0;x<H[val].sz;x++)
                          if (H[val][x].first==a[i]) {H[val][x].second++;ok=1;break;}
 
                if (!ok) H[val].pb( mp( a[i],1) );
                }
 
        sort(a+1,a+n+1);
                 
 
        for (i=1;i<=n;i++)
               for (j=i+1;j<=n;j++)
                {
                s=a[i]+a[j];
                val=s%modulo;
 
                ok=0;
                for (x=0;x<G[val].sz;x++)
                        if (G[val][x].first==s) {G[val][x].second++;ok=1;break;}
 
                if (!ok) G[val].pb( mp(s,1) );
                }
 
        sol=0;
 
        for (i=1;i<=n;i++)
                for (j=i+1;j<=n;j++)
                        {
                        s=k-a[i]-a[j];
                        if (s<0) continue;
 
                        val=s%modulo;
 
                        for (x=0;x<G[val].sz;x++)
                                if (G[val][x].first==s) sol=sol+G[val][x].second;
 
                        if (s>a[i])
                        {
                        val=(s-a[i])%modulo;
                        for (x=0;x<H[val].sz;x++)
                                if (H[val][x].first==s-a[i]) sol=sol-H[val][x].second;
                        if (s-a[i]==a[i]) sol++;
                        }
 
                        if (s>a[j])
                        {
                        val=(s-a[j])%modulo;
                        for (x=0;x<H[val].sz;x++)
                                if (H[val][x].first==s-a[j]) sol=sol-H[val][x].second;
                                 
                        if (s-a[j]==a[j]) sol++;
                        }                        
 
                        if (a[i]+a[j]==s) sol++;
                        }
        sol/=6;
        printf("%ld\n",sol);
        return 0;
}
