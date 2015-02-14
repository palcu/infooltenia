// @palcu
// InfoOltenia 2015, teleport, backtracking

#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 100000,
          PASI_INFINITI = NMAX*2;

int v[NMAX],
    nVector, sizeOfCheat;


int back(int pozitieCurenta, int cheatsAvailable) {
    if (pozitieCurenta > nVector)
        return PASI_INFINITI;

    if (pozitieCurenta == nVector)
        return 0;

    int sol = min(back(pozitieCurenta+1, cheatsAvailable) + 1,
                  back(pozitieCurenta+v[pozitieCurenta], cheatsAvailable) + 1);
    if (cheatsAvailable)
        sol = min(sol, back(pozitieCurenta+sizeOfCheat, cheatsAvailable-1) + 1);
    return sol;
}


int main() {
    freopen("teleport.in", "r", stdin);
    freopen("teleport.out", "w", stdout);

    int nCheats;
    scanf("%d%d%d", &nVector, &nCheats, &sizeOfCheat);

    for(int i=0; i<nVector; i++)
        scanf("%d", &v[i]);

    printf("%d\n", back(0, nCheats));

    return 0;
}
