#include <fstream>
using namespace std;

ifstream f("sesiune.in");
ofstream g("sesiune.out");

const int SMAX = 1000001,
          NMAX = 1001;

int A[NMAX];
int pair_sum[SMAX*2];

int main()
{
    int N, S;
    long long total = 0;

    f >> N >> S;

    for (int it = 1; it <= N; ++it)
        f >> A[it];

    pair_sum[A[1] + A[2]] = 1;
    for (int it_new1 = 3; it_new1 < N; ++it_new1) {

        for (int it_new2 = it_new1 + 1; it_new2 <= N; ++it_new2) {
            total += pair_sum[S - A[it_new1] - A[it_new2]]; //query S - current_pair
        }

        for (int it_new2 = it_new1 - 1; it_new2 > 0; --it_new2) {
            ++pair_sum[A[it_new1] + A[it_new2]];   //update using current pair
        }
    }

    g << total << "\n";
return 0;
}

