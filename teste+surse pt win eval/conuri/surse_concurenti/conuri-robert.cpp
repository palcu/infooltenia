#include <cstdio>

static const int VMAX = 100000;

int N, rez, x, y;
int d[VMAX];

inline int max(int x, int y) {
    return x > y ? x : y;
}

int main() {
    freopen("conuri.in", "r", stdin);
    freopen("conuri.out", "w", stdout);
    
    for (scanf("%d\n", &N); N > 0; --N){
        scanf("%d %d\n", &x, &y);
        int dx = max(d[x], d[y] + 1);
        int dy = max(d[y], d[x] + 1);
        d[x] = dx; d[y] = dy;
        rez = max(rez, max(d[x], d[y]));
    }
    printf("%d\n", rez);
    
    return 0;
}