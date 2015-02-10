#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

ifstream f("lipsa.in");
ofstream g("lipsa.out");

unordered_map <int, int> missing_number;
vector <int> max_count_list;

int main() {
    int N, M, max_count = 0;

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
        if (temp_missing_nr_count >= max_count) {
            if (temp_missing_nr_count > max_count) {
                max_count = temp_missing_nr_count;
                max_count_list.clear();
            }
            max_count_list.push_back(Sum);
        }
    }

    g << max_count << " " << max_count_list.size() << "\n";
    sort(max_count_list.begin(), max_count_list.end());
    for (int list_it = 0; list_it < max_count_list.size(); ++list_it)
        g << max_count_list[list_it] << " ";
    g << "\n";
    return 0;
}
