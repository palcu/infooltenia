/**
    Problema: conjectura
    Solutie: Fara numere mari. Valorile tinute in long long. Simularea tuturor iteratiilor.
    Autor: Robert Hasna
 */

#include <cstdio>

using namespace std;

int N, M;
long long x;

// Calculeaza inversul unui numar
long long invers(long long x) {
    long long invers = 0;
    while (x != 0) {
        invers = invers * 10 + x % 10;
        x /= 10;
    }

    return invers;
}

// Calculeaza daca un numar este palindrom
bool estePalindrom(long long x) {
    return x == invers(x);
}


int main() {
    freopen("conjectura.in", "r", stdin);
    freopen("conjectura.out", "w", stdout);

    scanf("%d %d", &N, &M);
    while (N-- > 0) {
        scanf("%lld", &x);

        if (estePalindrom(x)) {
            // Numarul este deja palindrom dupa 0 iteratii

            printf("0\n");
            continue;
        }

        int stop = 0;
        for (int i = 1; i <= M; ++i) {
            x += invers(x);

            if (estePalindrom(x)) {
                printf("%d\n", i);
                stop = 1;
                break;
            }
        }
        if (!stop) {
            printf("LYCHREL\n");
        }
    }

    return 0;
}
