#include <cstdio>

static const int NMAX = 1000001;
static const int MMAX = 4;

int N, M, K, rez;
int v[NMAX];
int d[NMAX][MMAX];

inline int min(const int &x, const int &y) {
    return x < y ? x : y;
}

int main() {
    freopen("teleport.in", "r", stdin);
    freopen("teleport.out", "w", stdout);
    
    scanf("%d %d %d\n", &N, &M, &K);
    for (int i = 0; i < N; ++i) {
        scanf("%d ", v + i);
    }
   
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= M; ++j) {
            d[i][j] = 1410065407;
        }
    }
    d[0][0] = 0;

    for (int i = 1; i <= N; ++i) {
        for (int k = 0; k <= M; ++k) {
            // pas in fata
            d[i][k] = min(d[i][k], d[i-1][k] + 1);
            
            // Teleport pe podea
            for (int j = i - 1; j >=0; --j) {
                if (j + v[j] == i) {
                    d[i][k] = min(d[i][k], d[j][k] + 1);
                }
            }
            
            // Teleport personal
            if (i - K >= 0 && k > 0) {
                d[i][k] = min(d[i][k], d[i - K][k - 1] + 1);
            }
        }
    }
    
    rez = d[N][0];
    for (int i = 1; i <= M; ++i) {
        rez = min(rez, d[N][i]);
    }
    
    printf("%d\n", rez);

    //for (int i = 0; i <= M; ++i) {
    //    for (int j = 0; j <= N; ++j) {
    //        printf("%d ", d[j][i]);
    //    }
    //    printf("\n");
    //}
    return 0;
}
