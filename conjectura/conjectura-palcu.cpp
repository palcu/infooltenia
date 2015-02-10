// InfoOltenia 2015, Cojectura, @palcu
// Solutie 100 de puncte

#include <cstdio>
#include <cstring>

const int MAX_CIFRE = 128;
int x1[MAX_CIFRE], x2[MAX_CIFRE]; // primul element din vector contine lungimea

void sum_numbers() {
    for (int i=1; i<=x1[0]; i++) {
        x1[i] += x2[i];
        if (x1[i] > 9) {
            x1[i+1]++;
            x1[i] %= 10;
        }
    }
    if (x1[x1[0] + 1]) x1[0]++;
}

bool is_palindrom() {
    for (int i=1; i<=x1[0] / 2; i++)
        if (x1[i] != x1[x1[0] - i + 1])
            return false;
    return true;
}

void set_big_numbers_to_zero() {
    memset(x1, 0, sizeof(x1));
    memset(x2, 0, sizeof(x2));
}

void set_first_number_to(int x) {
    while (x) {
        x1[++x1[0]] = x % 10;
        x /= 10;
    }
}

void generate_second_number() {
    x2[0] = x1[0];
    for (int i=1; i<=x2[0]; i++) {
        x2[i] = x1[x1[0] - i + 1];
    }
}

int main() {
    freopen("conjectura.in", "r", stdin);
    freopen("conjectura.out", "w", stdout);

    int nNumbers, nIteratii;
    scanf("%d %d", &nNumbers, &nIteratii);

    for (int i=0; i<nNumbers; i++) {
        int x;
        scanf("%d", &x);
        set_big_numbers_to_zero();
        set_first_number_to(x);
        int sol = 0;
        for (int i=0; i<nIteratii; i++) {
            if (is_palindrom()) {
                sol = i;
                break;
            }
            generate_second_number();
            sum_numbers();
        }

        if (sol) {
            printf("%d\n", sol);
        } else {
            printf("LYCHREL\n");
        }
    }
}
