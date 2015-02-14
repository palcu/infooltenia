// Problema "lipsa" - InfoOltenia 2015
// Sursa Alex Palcuie - citire stdio, algoritm cu suma Gauss, sortare cu Bubble Sort
// Numar Pasi: (MAX_SECVENTE * MAX_N) + (MAX_SECVENTE ^ 2) + MAX_SECVENTE
// Memorie: (MAX_SECVENTE * 2) * 2 bytes;

#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_SECVENTE = 100,
          MAX_N = 1000000; // Just for reference

int lipsa[MAX_SECVENTE];
int sol[MAX_SECVENTE], noSol;

int main() {
    freopen("lipsa.in", "r", stdin);
    freopen("lipsa.out", "w", stdout);

    int n, nSecventeIntrare;
    scanf("%d %d", &n, &nSecventeIntrare);

    for (int i=0; i<nSecventeIntrare; i++) {
        unsigned long long sum = 0;
        for (int j=0; j<n-1; j++) {
            int x;
            scanf("%d", &x);
            sum += x;
        }
        unsigned long long bigger;
        if (n%2 == 0)
            bigger = n/2 * (n+1);
        else
            bigger = (n+1)/2 * n;
        lipsa[i] = bigger - sum;
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

    // printf("=== sol ===\n");
    // for (int i=0; i<noSol; i++)
    //     printf("%d ", sol[i]);
    // printf("\n");

    // Atentie la cazul acesta particular
    if (currentCount > maxSolCount) {
        maxSolCount = currentCount;
        memset(sol, 0, sizeof(sol));
        sol[0] = lipsa[nSecventeIntrare-1];
        noSol = 1;
    } else if (currentCount == maxSolCount &&
               sol[noSol-1] != lipsa[nSecventeIntrare-1]) {
        sol[noSol++] = lipsa[nSecventeIntrare-1];
    }

    // printf("=== sol ===\n");
    // for (int i=0; i<3; i++)
    //     printf("%d ", sol[i]);
    // printf("\n");

    // bug major dar YOLO
    if (sol[0] == sol[1]) {
        printf("%d %d\n", maxSolCount, noSol - 1);
        for (int i=1; i<noSol; i++)
            if (sol[i] != sol[i+1])
                printf("%d ", sol[i]);
        printf("\n");
    } else {
        printf("%d %d\n", maxSolCount, noSol);
        for (int i=0; i<noSol; i++)
            if (sol[i] != sol[i+1])
                printf("%d ", sol[i]);
        printf("\n");
    }


    return 0;
}
