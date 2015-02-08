#include <fstream>
#include <unordered_map>
using namespace std;

ifstream f("lipsa.in");
ofstream g("lipsa.out");

unordered_map <int, int> missing_number;

int main() {
    int N, M, max_count = 0, max_count_val;

    f >> N >> M;
    for (int it = 1; it <= M; ++it) {
        int Sum = N * (N + 1) / 2;
        for (int in_it = 1; in_it < N; ++in_it) {
            int in_value;

            f >> in_value;
            Sum -= in_value;
        }
        /* Sum is the missing number */
        int temp_missing_nr_count = ++missing_number[Sum];
        if (temp_missing_nr_count > max_count)
            max_count = temp_missing_nr_count, max_count_val = Sum;
    }

    g << max_count_val << "\n";
    return 0;
}
