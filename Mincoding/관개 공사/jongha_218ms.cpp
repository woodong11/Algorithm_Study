#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;


struct Point {
	int y;
	int x;
};

struct P_V {
	int val;
	int index_a;
	int index_b;
};

int grid[2000], N, K, y, x, result;

vector<Point> v;
vector<P_V> p_v;

void init() {
	for (int i = 0; i < N; i++) {
		grid[i] = i;
	}
}

int find(int tar) {
	if (grid[tar] == tar) return tar;
	int ret = find(grid[tar]);
	grid[tar] = ret;
	return ret;
}

void merge(int a, int b) {
	int t1 = find(a);
	int t2 = find(b);
	if (t1 == t2) return;
	grid[t2] = t1;
}

bool compare(P_V a, P_V b) {
	if (a.val < b.val) return true;
	return false;
}

void input() {
	for (int i = 0; i < N; i++) {
		cin >> y >> x;
		v.push_back({ y, x });
	}
}

int main() {
	
	cin >> N >> K;

	init();
	input();

	int a;

	for (int i = 0; i < N; i++) {
		for (int z = i + 1; z < N; z++) {
			a = (v[i].x - v[z].x) * (v[i].x - v[z].x) + (v[i].y - v[z].y) * (v[i].y - v[z].y);
			if( a >= K) {
				p_v.push_back({ a, i, z });
			}
		}
	}

	sort(p_v.begin(), p_v.end(), compare);

	int cnt = 0, i = 0;

	while (cnt < N - 1) {
		if (i >= p_v.size()) {
			result = -1;
			break;
		}
		if (find(p_v[i].index_a) == find(p_v[i].index_b)) {
			i++;
			continue;
		}
		merge(p_v[i].index_a, p_v[i].index_b);
		result += p_v[i].val;
		cnt++;
		i++;
	}

	cout << result;
}
