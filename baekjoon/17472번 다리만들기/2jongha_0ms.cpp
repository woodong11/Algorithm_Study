#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

struct PointV {
	int y;
	int x;
	int val;
};

struct Point {
	int y;
	int x;
};

int dat[6], N, M, dx[4] = { 0, 0, 1, -1 }, dy[4] = { 1, -1, 0, 0 };
int grid[11][11], cnt = 1, result;
int visited[11][11];
queue<Point> q;
vector<PointV> v;

void drawing(int y, int x) {
	int ny, nx, y_, x_;
	q.push({ y, x });
	visited[y][x] = 1;
	grid[y][x] = cnt;
	
	while (!q.empty()) {
		y_ = q.front().y;
		x_ = q.front().x;
		q.pop();

		for (int i = 0; i < 4; i++) {
			ny = y_ + dy[i];
			nx = x_ + dx[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
				continue;
			}
			if (grid[ny][nx] == 0) continue;
			if (visited[ny][nx] == 1) continue;

			grid[ny][nx] = cnt;
			visited[ny][nx] = 1;

			q.push({ ny, nx });
		}
	}
}

int find(int tar) {
	if (dat[tar] == tar) return tar;

	int ret = find(dat[tar]);
	dat[tar] = ret;
	return ret;
}

void merge(int a, int b) {
	int t1 = find(a);
	int t2 = find(b);

	if (t1 == t2) return;
	dat[t2] = t1;
}

bool compare(PointV a1, PointV a2) {
	if (a1.val < a2.val) return true;
	return false;
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < 6; i++) {
		dat[i] = i;
	}

	for (int i = 0; i < N; i++) {
		for (int z = 0; z < M; z++) {
			cin >> grid[i][z];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int z = 0; z < M; z++) {
			if (grid[i][z] == 1) {
				cnt++;
				drawing(i, z);
			}
		}
	}

	int ny, nx, temp = 0;

	for (int i = 0; i < N; i++) {
		for (int z = 0; z < M; z++) {
			if (grid[i][z] >= 1) {
				int a = grid[i][z] - 1;
				ny = i;
				nx = z;

				for (int k = 0; k < 4; k++) {
					temp = 0;
					while (true) {
						ny += dy[k];
						nx += dx[k];

						if (ny < 0 || nx < 0 || ny >= N || nx >= M) break;
						if (grid[i][z] == grid[ny][nx]) break;
						
						temp++;

						if (grid[ny][nx] > 0 && grid[ny][nx] != grid[i][z] && temp <= 2) break;
						if (grid[ny][nx] > 0 && temp > 2) {
							v.push_back({ a, grid[ny][nx] - 1, temp - 1 });
							break;
						}
					}
				}
			}
		}
	}

	sort(v.begin(), v.end(), compare);
	int tempR = 0;

	for (PointV l : v) {
		if (find(l.y) == find(l.x)) continue;

		merge(l.y, l.x);
		result += l.val;
		tempR++;

		if (tempR == cnt - 2) {
			cout << result;
			break;
		}
	}

	if (tempR != cnt - 2 || tempR == 0) cout << "-1";

	return 0;
}
