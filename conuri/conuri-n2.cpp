#include <cstdio>

static const int NMAX = 100000;

int N, rez;
int vx[NMAX];
int vy[NMAX];
int d[NMAX];
int dinv[NMAX];

inline int max(int x, int y) {
    return x > y ? x : y;
}

int main() {
    freopen("conuri.in", "r", stdin);
    freopen("conuri.out", "w", stdout);
    scanf("%d\n", &N);
    
    for (int i = 0; i < N; ++i) {
        scanf("%d %d\n", &vx[i], &vy[i]);
        d[i] = 1;
        dinv[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (vy[j] == vx[i]) {
                d[i] = max(d[i], d[j] + 1);
            }
            if (vy[j] == vy[i]) {
                dinv[i] = max(dinv[i], d[j] + 1);
            }
            
            if (vx[j] == vx[i]) {
                d[i] = max(d[i], dinv[j] + 1);
            }
            if (vx[j] == vy[i]) {
                dinv[i] = max(dinv[i], dinv[j]);
            }
            
        }
        
        rez = max(rez, max(d[i], dinv[i]));
    }
    
    printf("%d\n", rez);
    
    return 0;
}
