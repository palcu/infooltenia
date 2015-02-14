#include <cstdio>

int sol[100003][4];

int main() {
	int N, cheat_steps, nr_cheats;
    
    freopen("teleport.in", "r", stdin);
    freopen("teleport.out", "w", stdout);
    scanf("%d %d %d", &N, &nr_cheats, &cheat_steps);
    for (int i = 2; i <= N + 1; ++i) 
        for (int j = 0; j <= nr_cheats; ++j) 
            sol[i][j] = 999999;
    for (int i = 1; i <= N; ++i) {
        int x;

        scanf("%d", &x);
        for (int cheat_used = 0; cheat_used <= nr_cheats; ++cheat_used) {
            if (i + 1 <= N + 1 && sol[i + 1][cheat_used] > sol[i][cheat_used] + 1)
                sol[i+1][cheat_used] = sol[i][cheat_used] + 1;
            if (i + x <= N + 1 && sol[i + x][cheat_used] > sol[i][cheat_used] + 1)
                sol[i + x][cheat_used] > sol[i][cheat_used] + 1;
            if (i + cheat_steps <= N + 1 && cheat_used < nr_cheats && sol[i + cheat_steps][cheat_used + 1] > sol[i][cheat_used] + 1)
                sol[i + cheat_steps][cheat_used + 1] = sol[i][cheat_used] + 1;
        }
    }
    for (int i = 1; i <= nr_cheats; ++i)
        if (sol[N + 1][0] > sol[N + 1][i])
            sol[N + 1][0] = sol[N + 1][i];
    printf("%d\n", sol[N + 1][0]);

    return 0;
}
