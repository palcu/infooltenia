#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Record {
    int i, j, s;
    Record(long long vs, int vi, int vj) { s = vs; i = vi; j = vj; }
};

int N, M;
int rez;
vector<Record> sume;
vector<int> v;

bool sortare(const Record &x, const Record &y) {
    return x.s < y.s;
}

int cate(int poz) {
    int rezPartial = 0;
    int ceCaut = M - sume[poz].s;
    for (vector<Record>::iterator it = lower_bound(sume.begin(), sume.end(), Record(ceCaut, 0, 0), sortare); it != sume.end() && it->s == ceCaut; ++it) {
        if ((sume[poz].i != it->i) && (sume[poz].i != it->j) && (sume[poz].j != it->i) && (sume[poz].j != it->j)) {
            ++rezPartial;
        }
    }
    
    return rezPartial;
}

int main() {
    freopen("sesiune.in", "r", stdin);
    freopen("sesiune.out", "w", stdout);
    
    scanf("%d %d\n", &N, &M);
    v.reserve(N);
    for (int i = 0, x; i < N; ++i) {
        scanf("%d", &x);
        v.push_back(x);
    }
    
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            sume.push_back(Record(v[i] + v[j], i, j));
        }
    }
    sort(sume.begin(), sume.end(), sortare);
    
    for (int i = 0; i < sume.size(); ++i) {
        rez += cate(i);
    }
    
    printf("%d\n", rez / 6);
    
    return 0;
}
