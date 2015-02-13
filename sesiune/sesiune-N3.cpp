#include <stdio.h>

#define NMAX 100025
#define KMAX 10000000

int N, K;
int V[NMAX];
int H[KMAX];
int cnt[KMAX];

int main() {
    freopen("sesiune.in", "r", stdin);
    freopen("sesiune.out", "w", stdout);

    scanf("%d %d ", &N, &K);

    for (int i = 0; i < N; i++) {
        scanf("%d ", &V[i]);
        H[V[i]]++;
    }

    int sol = 0;
    for (int i = 0; i < N; i++) {
        cnt[V[i]]++;
        for (int j = 0; j < N; j++) {
            if (i == j) {
                continue;
            }
            cnt[V[j]]++;
            for (int t = 0; t < N; t++) {
                if (t == j || t == i) {
                    continue;
                }

                cnt[V[t]]++;
                int s = V[i] + V[j] + V[t];
                
                if (s < K) {
                    // printf("Remaining %d's for %d %d %d : %d\n", K - s, i, j, t, H[K - s] - cnt[K - s]);
                    sol = sol + H[K - s] - cnt[K - s];
                }

                cnt[V[t]]--; 
            }
            cnt[V[j]]--;
        }

        cnt[V[i]]--;
    }

    printf("%d\n", sol / 24);
    return 0;
}
