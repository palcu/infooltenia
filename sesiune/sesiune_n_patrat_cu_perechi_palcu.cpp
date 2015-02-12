#include <cstdio>

using namespace std;

const int NMAX = 1000;
int v[NMAX];
int pairs[NMAX*NMAX][3], nPairs;

int main() {
    freopen("sesiune.in", "r", stdin);
    freopen("sesiune.out", "w", stdout);

    int n, s;
    scanf("%d%d", &n, &s);

    for(int i=0; i<n; i++)
        scanf("%d", &v[i]);

    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++) {
            pairs[nPairs][0] = v[i] + v[j];
            pairs[nPairs][1] = i;
            pairs[nPairs++][2] = j;
        }

    int sol = 0;
    for(int i=0; i<nPairs; i++)
        for(int j=i+1; j<nPairs; j++)
            if (pairs[i][0] + pairs[j][0] == s) {
                bool diferite = true;
                for(int k=1; k<=2; k++)
                    for(int l=1; l<=2; l++)
                        if(pairs[i][k] == pairs[j][l]) {
                            diferite = false;
                            break;
                        }
                if (diferite) {
                    sol ++;
                    printf("%d%d\n", pairs[i][1], pairs[i][2]);
                    printf("%d%d\n", pairs[j][1], pairs[j][2]);
                    printf("\n");
                }
            }

    printf("%d\n", sol);
    return 0;
}
