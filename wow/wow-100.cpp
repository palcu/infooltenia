/**
 Problema: wow
 Solutie: Algoritmul lui Lee pentru fiecare punct de plecare. Suma de distanta.
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

int N; // Latura labirintului
int M; // Numarul de persoane
int labirint[ NMAX ][ NMAX ]; // Labirintul
int drumuri[ NMAX ][ NMAX ]; // Suma drumurilor
int vizitat[ NMAX ][ NMAX ]; // Matrice de locuri vizitate, pentru Lee
vector< Punct > oameni;
queue< pair<Punct,int> > Q; // Coada pentru Lee. Punctul vizitat si costul de a ajunge la el

// Curata matricea de vizite. Pregatire pentru urmatoarea rulare a algoritmului lui lee.
void stergeVizite() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            vizitat[i][j] = 0;
        }
    }
}

// Verifica daca un punct este in interiorul labirintului
inline bool inLabirint(Punct punct) {
    return !(punct.first < 0 || punct.first >= N || punct.second < 0 || punct.second >= N);
}

// Face un pas in algoritmul lui Lee. Primeste un puct si viziteaza toate cele 4 puncte adiacente.
inline void pas(Punct punct, int cost) {
    for (int i = 0; i < 4; ++i) {
        Punct punctNou = make_pair(punct.first + dx[i], punct.second + dy[i]);
        if (inLabirint(punctNou) && !vizitat[punctNou.first][punctNou.second] && labirint[punctNou.first][punctNou.second] == 0) {
            vizitat[punctNou.first][punctNou.second] = 1;
            drumuri[punctNou.first][punctNou.second]+= cost + 1;
            Q.push(make_pair(punctNou, cost + 1));
        }
    }
}

// Algoritmul lui lee
void lee(Punct start) {
    stergeVizite();
    while(!Q.empty()) {
        Q.pop();
    }
    Q.push(make_pair(start, 0));
    vizitat[start.first][start.second] = 1;
    
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
    scanf("%d %d\n", &N, &M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", &labirint[i][j]);
        }
    }
    
    for (int i = 0; i < M; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        oameni.push_back(make_pair(x, y));
    }
    
    // Rularea algoritmului lui Lee pentru fiecare om din labirint
    for (vector<Punct>::iterator it = oameni.begin(); it != oameni.end(); it++) {
        lee(*it);
    }
    
    // Extragerea rezultatului
    int minim = -1;
    Punct loculIntalnirii;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (labirint[i][j] == 0 && (drumuri[i][j] < minim || minim == -1)) {
                minim = drumuri[i][j];
                loculIntalnirii = make_pair(i, j);
            }
        }
    }
    
    // Afisarea rezultatului
    printf("%d\n%d %d\n\n", minim, loculIntalnirii.first, loculIntalnirii.second);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d ", drumuri[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}







