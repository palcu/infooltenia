// Problema "lipsa" - InfoOltenia 2015
// Sursa Alex Palcuie - citire stdio, verific daca fiacere element se afla in
// vector, apoi sortez cu bubble sort si verific care e de cele mai putine ori
// Numar Pasi: (MAX_SECVENTE * MAX_N) + (MAX_SECVENTE ^ 2) + MAX_SECVENTE
// Memorie: (MAX_SECVENTE * 2) * 2 bytes;

#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_SECVENTE = 100,
          MAX_N = 1000000;

int lipsa[MAX_SECVENTE], secventa[MAX_N];
int sol[MAX_SECVENTE], noSol;

int main() {
    freopen("lipsa.in", "r", stdin);
    freopen("lipsa.out", "w", stdout);

    int n, nSecventeIntrare;
    scanf("%d %d", &n, &nSecventeIntrare);

    for (int i=0; i<nSecventeIntrare; i++) {
        for (int j=0; j<n-1; j++) {
            scanf("%d", &secventa[j]);
        }
        for (int j=1; j<=n; j++) {
            bool inSecventa = false;
            for (int k=0; k<n-1; k++)
                if (j == secventa[k]) {
                    inSecventa = true;
                    break;
                }
            if (!inSecventa) {
                lipsa[i] = j;
                break;
            }
        }
    }

    bool isSorted = false;
    while (!isSorted) {
        isSorted = true;
        for (int i=0; i<nSecventeIntrare-1; i++)
            if (lipsa[i] > lipsa[i+1]) {
                isSorted = false;
                int temp = lipsa[i];
                lipsa[i] = lipsa[i+1];
                lipsa[i+1] = temp;
            }
    }

    // printf("=== Vectorul sortat ===\n");
    // for (int i=0; i<nSecventeIntrare; i++)
    //     printf("%d ", lipsa[i]);
    // printf("\n");


    int maxSolCount = 1,
        currentCount = 1,
        noSol = 1;
    sol[0] = lipsa[0];
    for (int i=1; i<nSecventeIntrare; i++) {
        if (lipsa[i] == lipsa[i-1])
            currentCount++;
        else {
            if (currentCount > maxSolCount) {
                maxSolCount = currentCount;
                memset(sol, 0, sizeof(sol));
                sol[0] = lipsa[i-1];
                noSol = 1;
            } else if (currentCount == maxSolCount) {
                sol[noSol++] = lipsa[i-1];
            }
            currentCount = 1;
        }
    }

    // Atentie la cazul acesta particular
    if (currentCount > maxSolCount) {
        maxSolCount = currentCount;
        memset(sol, 0, sizeof(sol));
        sol[0] = lipsa[nSecventeIntrare-1];
        noSol = 1;
    } else if (currentCount == maxSolCount) {
        sol[noSol++] = lipsa[nSecventeIntrare-1];
    }

    printf("%d %d\n", maxSolCount, noSol);
    for (int i=0; i<noSol; i++)
        printf("%d ", sol[i]);
    printf("\n");

    return 0;
}
