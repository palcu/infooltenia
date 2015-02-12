#include <cstdio>

using namespace std;

const int NMAX = 10000;
int v[NMAX];

int main() {
    freopen("sesiune.in", "r", stdin);
    freopen("sesiune.out", "w", stdout);

    int n, s;
    scanf("%d%d", &n, &s);

    for(int i=0; i<n; i++)
        scanf("%d", &v[i]);

    int sol = 0;
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            for(int k=j+1; k<n; k++)
                for(int l=k+1; l<n; l++)
                    if(v[i]+v[j]+v[k]+v[l] == s)
                        sol++;

    printf("%d\n", sol);
    return 0;
}
