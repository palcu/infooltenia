/**
 Problema: wow
 Solutie: Algoritmul lui Lee plecand de la primul om din labirint si calculeaza distanta pana la al doilea.
 Autor: Robert Hasna
 */
#include <cstdio>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

typedef pair<int,int> Punct;

static const int NMAX = 100;
static const int dx[] = { 0, 1, 0, -1 };
static const int dy[] = { 1, 0, -1, 0 };

int N, M; // Latura labirintului
int nrPers; //
int labirint[ NMAX ][ NMAX ]; // Labirintul
int distanta[ NMAX ][ NMAX ]; // Matrice de distanta data de punctul de start
Punct sursa, destinatie;
queue< pair<Punct,int> > Q; // Coada pentru Lee. Punctul vizitat si costul de a ajunge la el

// Verifica daca un punct este in interiorul labirintului
inline bool inLabirint(Punct punct) {
    return !(punct.first < 0 || punct.first >= N || punct.second < 0 || punct.second >= M);
}

// Face un pas in algoritmul lui Lee. Primeste un puct si viziteaza toate cele 4 puncte adiacente.
inline void pas(Punct punct, int cost) {
    for (int i = 0; i < 4; ++i) {
        Punct punctNou = make_pair(punct.first + dx[i], punct.second + dy[i]);
        if (inLabirint(punctNou) && !distanta[punctNou.first][punctNou.second] && labirint[punctNou.first][punctNou.second] == 0) {
            distanta[punctNou.first][punctNou.second]+= cost + 1;
            Q.push(make_pair(punctNou, cost + 1));
        }
    }
}

// Algoritmul lui lee
void lee(Punct start) {
    Q.push(make_pair(start, 1));
    distanta[start.first][start.second] = 1;

    while (!Q.empty()) {
        pair< Punct, int > q = Q.front();
        Q.pop();
        pas(q.first, q.second);
    }
}

int main() {
    freopen("wow.in", "r", stdin);
    freopen("wow.out", "w", stdout);

    // Citirea datelor
    scanf("%d %d %d\n", &N, &M, &nrPers);

    if (nrPers != 2) {
        printf("Am rezolvat doar pentru 2 persoane in labirint ...");
        return 0;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf("%d", &labirint[i][j]);
        }
    }

    int x, y;
    scanf("%d %d", &x, &y);
    sursa = make_pair(x, y);
    scanf("%d %d", &x, &y);
    destinatie = make_pair(x, y);

    // Lee
    lee(sursa);

    // Afisarea rezultatului
    printf("%d\n", distanta[destinatie.first][destinatie.second] - 1);
    if (sursa.first < destinatie.first) {
        printf("%d %d\n", sursa.first, sursa.second);
    } else if (sursa.first > destinatie.first) {
        printf("%d %d\n", destinatie.first, destinatie.second);
    } else {
        if (sursa.second < destinatie.second) {
            printf("%d %d\n", sursa.first, sursa.second);
        } else {
            printf("%d %d\n", destinatie.first, destinatie.second);
        }
    }

    return 0;
}
