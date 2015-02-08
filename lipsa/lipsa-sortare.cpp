/**
    Problema: lipsa
    Solutie: Calcularea numarului lipsa din sir se face prin sortarea elementelor.
    Complexitate: M * N * log N + M * log M
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
        for (int j = 1; j <= N-1; ++j) {
            if (v[j - 1] != j) {
                numarLipsa = j;
                break;
            }
        }
        
        numereLipsa.push_back(numarLipsa);
    }
    
    // Calculam de cate ori lipseste un numar cel mai mult, si cate astfel de numere exista ( X si Y din enunt )
    sort(numereLipsa.begin(), numereLipsa.end());
    
    int maxim = 0, numarDeMaxime = 0, curent = 0, valoare = 0;
    for (int i = 0; i < numereLipsa.size(); ++i) {
        if (numereLipsa[i] != valoare) {
            valoare = numereLipsa[i];
            
            if (curent > maxim) {
                maxim = curent;
                numarDeMaxime = 1;
            }
            
            if (curent == maxim) {
                numarDeMaxime++;
            }
            curent = 1;
        } else {
            curent++;
        }
    }
    if (curent > maxim) {
        maxim = curent;
    }
    
    // Afisarea rezultatului
    printf("%d %d\n", maxim, numarDeMaxime);
    curent = valoare = 0;
    for (int i = 0; i < numereLipsa.size(); ++i) {
        if (numereLipsa[i] == valoare) {
            curent++;
            
            if (curent == maxim) {
                printf("%d ", valoare);
            }
        } else {
            valoare = numereLipsa[i];
            curent = 1;
        }
    }
    printf("\n");
    
    return 0;
}
