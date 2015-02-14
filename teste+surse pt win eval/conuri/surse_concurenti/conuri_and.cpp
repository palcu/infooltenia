#include <fstream>
using namespace std;

ifstream f("conuri.in");
ofstream g("conuri.out");

int max_length[100002];

int main() {
    int N, r1, r2;
    int max_length_absolute = 0;

    f >> N;
    while (N--) {
        f >> r1 >> r2;
        int max_length_ending_r2 = max_length[r1] + 1;
        int max_length_ending_r1 = max_length[r2] + 1;
        max_length[r2] = max(max_length[r2], max_length_ending_r2);
        max_length[r1] = max(max_length[r1], max_length_ending_r1);

        if (max_length_ending_r1 > max_length_absolute)
            max_length_absolute = max_length_ending_r1;
        if (max_length_ending_r2 > max_length_absolute)
            max_length_absolute = max_length_ending_r2;
    }

    g << max_length_absolute;
    return 0;
}
