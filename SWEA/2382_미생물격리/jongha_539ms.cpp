#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

// 미생물의 좌표값, 수, 방향
struct PointN {
	int y;
	int x;
	int num;
	int dir;

	bool operator<(PointN other) const {
		if (x != other.x) return x > other.x;
		return y > other.y;
	}
};

bool compare(PointN a, PointN b) {
	if (a.x != b.x) return a.x > b.x;
	return a.y > b.y;
}

// grid에 있는 해당 미생물 수와 방향
struct PointDir {
	int num;
	int dir;
};

int T, N, M, K;
PointDir grid[101][101];
int dx[4] = { 0, 0, -1, 1 }, dy[4] = { -1, 1, 0, 0 };
// 미생물의 위치가 같아질 때 연산하기 위한 pq -> 대신 v를 씀.
priority_queue<PointDir> pq;
queue<PointN> q;
vector<PointN> v;

void init() {
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			grid[i][j] = { 0, 0 };
		}
	}
}

void comb(int start) {
	int maxi = start, max_n = v[start].num, sum = v[start].num;

	for (int i = start + 1; i < v.size(); i++) {
		if (v[start].x != v[i].x || v[start].y != v[i].y) {
			q.push({ v[maxi].y, v[maxi].x, sum, v[maxi].dir });
			comb(i);
			return;
		}
		if (max_n < v[i].num) {
			max_n = v[i].num;
			maxi = i;
		}

		sum += v[i].num;
	}

	q.push({ v[maxi].y, v[maxi].x, sum, v[maxi].dir });
}

void bfs(int time) {
	int nx, ny, nx2, ny2;
	PointN microA, microB;

	for (int i = 0; i < time; i++) {
		int cnt = q.size();

		for (int j = 0; j < cnt; j++) {
			microA = q.front();
			q.pop();

			ny = microA.y + dy[microA.dir];
			nx = microA.x + dx[microA.dir];

			if (ny == 0 || nx == 0 || ny == N - 1 || nx == N - 1) {
				microA.num /= 2;
				microA.dir = microA.dir % 2 == 0 ? microA.dir + 1 : microA.dir - 1;

				q.push({ ny, nx, microA.num, microA.dir });
				continue;
			}

			v.push_back({ ny, nx, microA.num, microA.dir });
		}

		if (v.size() != 0) {
			sort(v.begin(), v.end(), compare);
			comb(0);
			v.clear();
		}
	}
}

int microSum() {
	int sum = 0;
	while (!q.empty()) {
		sum += q.front().num;
		q.pop();
	}

	return sum;
}

int main() {
	int x, y, n, d;

	cin >> T;

	for (int i = 1; i <= T; i++) {
		cin >> N >> M >> K;

		init();

		for (int i = 0; i < K; i++) {
			cin >> y >> x >> n >> d;

			q.push({ y, x, n, d - 1});
		}

		bfs(M);

		cout << "#" << i << " " << microSum() << "\n";
	}

	return 0;
}
