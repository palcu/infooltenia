// WOW, @palcu, 100 puncte

#include <cstdio>
#include <queue>
#include <cstring>
#include <utility>

using namespace std;

const int MAX_LG_MATRICE = 128,
          MAX_CARACTERE = 128;

int sol[MAX_LG_MATRICE][MAX_LG_MATRICE],
    m[MAX_LG_MATRICE][MAX_LG_MATRICE];
int lgMatrice_n, lgMatrice_m;
bool obstacole[MAX_LG_MATRICE][MAX_LG_MATRICE];

bool inbound_n(int x) {
    return 0 <= x && x < lgMatrice_n;
}

bool inbound_m(int x) {
    return 0 <= x && x < lgMatrice_m;
}

void lee(int x, int y) {
    memset(m, 0, sizeof(int) * MAX_LG_MATRICE * MAX_LG_MATRICE);
    m[x][y] = 1;
    queue<pair<int,int> > q;
    q.push(make_pair(x, y));

    while (!q.empty()) {
        pair<int,int> currentPosition = q.front();
        q.pop();
        int vertical[] = {0, 0, 1, -1},
            horizontal[] = {1, -1, 0, 0};
        for (int i=0; i<4; i++) {
            int x = currentPosition.first + vertical[i],
                y = currentPosition.second + horizontal[i];
            if (inbound_n(x) && inbound_m(y) && !obstacole[x][y]) {
                int cost = m[currentPosition.first][currentPosition.second] + 1;
                if (!m[x][y] || (cost < m[x][y])) {
                    m[x][y] = cost;
                    q.push(make_pair(x, y));
                }
            }
        }
    }
}

void aduna_matrice() {
    for (int i=0; i<lgMatrice_n; i++)
        for (int j=0; j<lgMatrice_m; j++)
            if (m[i][j])
                sol[i][j] += m[i][j] - 1;
}


int main() {
    freopen("wow.in", "r", stdin);
    freopen("wow.out", "w", stdout);

    int nCaractere;
    scanf("%d%d%d\n", &lgMatrice_n, &lgMatrice_m, &nCaractere);

    for (int i=0; i<lgMatrice_n; i++)
        for (int j=0; j<lgMatrice_m; j++)
            scanf("%d", &obstacole[i][j]);

    for (int i=0; i<nCaractere; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        lee(x, y);
        aduna_matrice();
    }

    int solMin = 999999999, pozX=0, pozY=0; // XXX @palcu: I should find the
                                            // first viable element
    for (int i=0; i<lgMatrice_n; i++)
        for (int j=0; j<lgMatrice_m; j++)
            if (sol[i][j] && (sol[i][j] < solMin)) {
                solMin = sol[i][j];
                pozX=i;
                pozY=j;
            }

    printf("%d\n%d %d\n", solMin, pozX, pozY);
    // for (int i=0; i<lgMatrice_n; i++) {
    //     for (int j=0; j<lgMatrice_m; j++)
    //         printf("%d ", sol[i][j]);
    //     printf("\n");
    // }
    return 0;
}

