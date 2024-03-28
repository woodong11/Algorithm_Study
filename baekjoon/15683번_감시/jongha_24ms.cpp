#include <iostream>
#include<vector>
#include <queue>

using namespace std;

struct Point {
	int y;
	int x;
};

int arr[8][8];
int N, M, result = 999999, tempcnt;
int dy[4] = { 0, 1, 0, -1 }, dx[4] = { 1, 0, -1, 0 };
vector<Point> v[6];

void dfs(int t_arr[8][8], int level, int type) {
	if (level == 5) {
		tempcnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (t_arr[i][j] == 0) tempcnt++;
			}
		}
		result = result >= tempcnt ? tempcnt : result;
		return;
	}
	else if (v[level].size() == type) {
		dfs(t_arr, level + 1, 0);
		return;
	}

	int t_arr2[8][8];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			t_arr2[i][j] = t_arr[i][j];
		}
	}

	Point now = v[level][type];

	if (level == 1) {
		for (int i = 0; i < 4; i++) {
			int ny = now.y, nx = now.x;
			queue<Point> q;
			while (1) {
				ny += dy[i];
				nx += dx[i];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M || t_arr2[ny][nx] == 6) break;
				if (t_arr2[ny][nx] != 0) continue;

				t_arr2[ny][nx] = -1;
				q.push({ ny, nx });
			}
			int abcvc = 0;
			dfs(t_arr2, level, type + 1);

			while (!q.empty()) {
				Point erasePoint = q.front();
				q.pop();

				t_arr2[erasePoint.y][erasePoint.x] = 0;
			}
		}
	}
	else if (level == 2) {
		for (int i = 0; i < 4; i++) {
			int ny = now.y, nx = now.x;
			queue<Point> q;
			while (1) {
				ny += dy[i];
				nx += dx[i];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M || t_arr2[ny][nx] == 6) break;
				if (t_arr2[ny][nx] != 0) continue;

				t_arr2[ny][nx] = -1;
				q.push({ ny, nx });
			}
			ny = now.y, nx = now.x;
			int dir = (i + 2) % 4;

			while (1) {
				ny += dy[dir];
				nx += dx[dir];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M || t_arr2[ny][nx] == 6) break;
				if (t_arr2[ny][nx] != 0) continue;

				t_arr2[ny][nx] = -1;
				q.push({ ny, nx });
			}
			dfs(t_arr2, level, type + 1);

			while (!q.empty()) {
				Point erasePoint = q.front();
				q.pop();

				t_arr2[erasePoint.y][erasePoint.x] = 0;
			}
		}
	}
	else if (level == 3) {
		for (int i = 0; i < 4; i++) {
			int ny = now.y, nx = now.x;
			queue<Point> q;
			while (1) {
				ny += dy[i];
				nx += dx[i];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M || t_arr2[ny][nx] == 6) break;
				if (t_arr2[ny][nx] != 0) continue;

				t_arr2[ny][nx] = -1;
				q.push({ ny, nx });
			}
			ny = now.y, nx = now.x;
			int dir = (i + 3) % 4;

			while (1) {
				ny += dy[dir];
				nx += dx[dir];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M || t_arr2[ny][nx] == 6) break;
				if (t_arr2[ny][nx] != 0) continue;

				t_arr2[ny][nx] = -1;
				q.push({ ny, nx });
			}

			dfs(t_arr2, level, type + 1); 
			
			while (!q.empty()) {
				Point erasePoint = q.front();
				q.pop();

				t_arr2[erasePoint.y][erasePoint.x] = 0;
			}
		}
	}
	else if (level == 4) {
		for (int i = 0; i < 4; i++) {
			int ny = now.y, nx = now.x;
			queue<Point> q;
			while (1) {
				ny += dy[i];
				nx += dx[i];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M || t_arr2[ny][nx] == 6) break;
				if (t_arr2[ny][nx] != 0) continue;

				t_arr2[ny][nx] = -1;
				q.push({ ny, nx });
			}
			ny = now.y, nx = now.x;
			int dir = (i + 1) % 4;

			while (1) {
				ny += dy[dir];
				nx += dx[dir];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M || t_arr2[ny][nx] == 6) break;
				if (t_arr2[ny][nx] != 0) continue;

				t_arr2[ny][nx] = -1;
				q.push({ ny, nx });
			}
			ny = now.y, nx = now.x;
			dir = (i + 3) % 4;

			while (1) {
				ny += dy[dir];
				nx += dx[dir];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M || t_arr2[ny][nx] == 6) break;
				if (t_arr2[ny][nx] != 0) continue;

				t_arr2[ny][nx] = -1;
				q.push({ ny, nx });
			}

			dfs(t_arr2, level, type + 1);

			int arbr = 1;
			while (!q.empty()) {
				Point erasePoint = q.front();
				q.pop();

				t_arr2[erasePoint.y][erasePoint.x] = 0;
			}
		}
	}
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1) {
				v[1].push_back({i, j});
			}
			else if (arr[i][j] == 2) {
				v[2].push_back({ i, j });
			}
			else if (arr[i][j] == 3) {
				v[3].push_back({ i, j });
			}
			else if (arr[i][j] == 4) {
				v[4].push_back({ i, j });
			}
			else if (arr[i][j] == 5) {
				v[5].push_back({i, j});
			}
		}
	}

	for (int i = 0; i < v[5].size(); i++) {
		Point now = v[5][i];

		for (int i = 0; i < 4; i++) {
			int ny, nx;
			ny = now.y;
			nx = now.x;
			while (1) {
				ny += dy[i];
				nx += dx[i];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M || arr[ny][nx] == 6) {
					break;
				}
				if (arr[ny][nx] != 0) continue;
				arr[ny][nx] = -1;
			}
		}
	}
	
	dfs(arr, 1, 0);

	cout << result;

	return 0;
}
