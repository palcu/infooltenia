#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 100000;

int conuri[2][MAXN], n;

int back(int index, int value) {
    if (index >= n)
        return 0;

    int sol = 0;
    for (int i=index; i<n; i++)
        for (int j=0; j<2; j++)
            if (conuri[j][i] == value) {
                sol = max(sol, 1 + back(i + 1, conuri[1-j][i]));
            }
    return sol;
}

int main() {
    freopen("conuri.in", "r", stdin);
    freopen("conuri.out", "w", stdout);

    scanf("%d", &n);
    for (int i=0; i<n; i++)
        scanf("%d%d", &conuri[0][i], &conuri[1][i]);

    int sol = 1;

    for (int index=0; index<n; index++)
        for (int position=0; position<2; position++)
            sol = max(back(index+1, conuri[position][index]) + 1, sol);

    printf("%d\n", sol);
    return 0;
}
