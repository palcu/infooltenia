/**
    Problema: lipsa
    Solutie: Calcularea numarului lipsa din sir se face prin sortarea elementelor.
    Complexitate timp: O(M * N * log N + M * log M)
    Autor: Robert Hasna
 */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N, M; // Numerele din enunt
vector<int> v; // Stocheaza cele N-1 numere
vector<int> numereLipsa; // Stocheaza frecventa numerelor lipsa din sirurile de intrare

int main() {
    freopen("lipsa.in", "r", stdin);
    freopen("lipsa.out", "w", stdout);

    scanf("%d %d\n", &N, &M);
    numereLipsa.reserve(M+1);

    // Pentru fiecare linie, cautam care e numarul care lipseste
    while (M-- > 0) {
        v.clear();
        v.reserve(N-1);

        // Citire din fisier
        for (int j = 0, x; j < N - 1; ++j) {
            scanf("%d ", &x);
            v.push_back(x);
        }

        // Sortam vectorul
        sort(v.begin(), v.end());

        // Determinam care dintre numere lipseste
        int numarLipsa = -1;
        for (int j = 0; j < v.size(); ++j) {
            if (v[j] != j + 1) {
                numarLipsa = j + 1;
                break;
            }
        }

        if (numarLipsa == -1) {
            numarLipsa = N;
        }

        numereLipsa.push_back(numarLipsa);
    }

    // Calculam de cate ori lipseste un numar cel mai mult, si cate astfel de numere exista ( X si Y din enunt )
    sort(numereLipsa.begin(), numereLipsa.end());

    int maxim = -1, numarDeMaxime = 0, curent = 0, valoare = 0;
    for (int i = 0; i < numereLipsa.size(); ++i) {
        if (numereLipsa[i] == valoare) {
            curent++;
        } else {
            if (curent == maxim) {
                numarDeMaxime++;
            } else if (curent > maxim) {
                maxim = curent;
                numarDeMaxime = 1;
            }
            valoare = numereLipsa[i];
            curent = 1;
        }
    }

    // Afisarea rezultatului
    printf("%d %d\n", maxim, numarDeMaxime);
    curent = valoare = 0;
    for (int i = 0; i < numereLipsa.size(); ++i) {
        if (numereLipsa[i] == valoare) {
            curent++;
        } else {
            valoare = numereLipsa[i];
            curent = 1;
        }

        if (curent == maxim) {
            printf("%d ", valoare);
        }
    }

    printf("\n");

    return 0;
}
