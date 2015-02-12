#include <fstream>
#include <vector>
#include <algorithm>
#define MMAX 101
using namespace std;

ifstream f("lipsa.in");
ofstream g("lipsa.out");


int missing_number[MMAX];
vector <int> max_count_list;

int main() {
    int N, M, max_count = 0;

    f >> N >> M;
    for (int it = 1; it <= M; ++it) {
        unsigned long long Sum;
        if (N%2 == 0)
            Sum = N/2 * (N+1);
        else
            Sum = (N+1)/2 * N;
        for (int in_it = 1; in_it < N; ++in_it) {
            int in_value;
            f >> in_value;
            Sum -= in_value;
        }
        /* Sum is the missing number */
        missing_number[it] = Sum;
    }
    sort(missing_number + 1, missing_number + M + 1);
    for (int it = 1; it <= M; ++it) {
	int missing_nr_count = 1;
	while (it + 1 <= M && missing_number[it + 1] == missing_number[it])
	    ++missing_nr_count, ++it;
    	if (missing_nr_count >= max_count) {
            if (missing_nr_count > max_count) {
                max_count = missing_nr_count;
                max_count_list.clear();
            }
            max_count_list.push_back(missing_number[it]);
        }
    }

    g << max_count << " " << max_count_list.size() << "\n";
    sort(max_count_list.begin(), max_count_list.end());
    for (int list_it = 0; list_it < max_count_list.size(); ++list_it)
        g << max_count_list[list_it] << " ";
    g << "\n";
    return 0;
}
