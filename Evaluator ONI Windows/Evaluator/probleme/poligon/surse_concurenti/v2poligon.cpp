#include <cstdio>
#include <cmath>

#define Pmax 10000
#define cos45 0.707106781L

struct Punct {
	int x, y;
	Punct() { x = 0; y = 0; }
	Punct(int vx, int vy) { x = vx; y = vy; }
	bool operator<(const Punct &p2) { return x*p2.y < y*p2.x; }
	bool operator==(const Punct &p2) { return y*p2.x == x*p2.y; }
};

int N, R;
Punct pct[Pmax];
int cnt[Pmax], nr_cnt, nr_pct;

inline long double abs(long double x) { return x < 0 ? -x : x; }
inline bool is_int(long double x) { return (abs(x - (int)x)) < 0.00000000000000001L; }

int qsort(int st, int dr) {
	int i = st, j = dr;
	Punct mij = pct[(st + dr) >> 1];

	while (st < dr) {
		while (pct[st] < mij) ++st;
		while (mij < pct[dr]) --dr;
		if (st <= dr) {
			Punct temp = pct[st]; pct[st] = pct[dr]; pct[dr] = temp;
			++st; --dr;
		} 
	}

	if (i < dr) qsort(i, dr);
	if (st < j) qsort(st, j);
}


int main() {
	freopen("poligon.in", "r", stdin);
	freopen("poligon.out", "w", stdout);

	scanf("%d\n", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d ", &R);
		double L = R*cos45;
		int R2 = R*R;
		for (int j = 1; j <= L; ++j) {
			int temp = R2 - j*j;
			long double y = sqrtl((long double)temp);
			if (is_int(y))
				pct[nr_pct++] = Punct(j, (int)y);
		}
	}
	printf("%d\n", nr_pct*2);
	
	qsort(0, nr_pct - 1);
	int j;
	for (int i = 0, j; i < nr_pct; i = j) {
		Punct asta = pct[i];
		j = i + 1;
		for (; j < nr_pct; ++j)
			if (!(pct[j] == asta))
				break;

		cnt[nr_cnt++] = j - i;
	}
	printf("%d\n", nr_cnt * 2);

	for (int i = 0; i < nr_cnt; ++i) printf("%d ", cnt[i]);
	for (int i = nr_cnt - 1; i >=0; --i) printf("%d ", cnt[i]);
	printf("\n");

	return 0;
}

