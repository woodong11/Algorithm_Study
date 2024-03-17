#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
struct point {
	int y, x;
};
vector<point> wall;
vector<point> two;
int N, M, max_val;
int dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
int map[8][8];
int cnt_zero;

void bfs() {
	int tmp[8][8];
	int cnt_two = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			tmp[i][j] = map[i][j];
		}
	}
	for (int i = 0; i < wall.size(); i++) {
		tmp[wall[i].y][wall[i].x] = 1;
	}
	for (int i = 0; i < two.size(); i++) {
		queue<point> q;
		q.push(two[i]);
		while (!q.empty()) {
			point now = q.front();
			q.pop();
			for (int j = 0; j < 4; j++) {
				point next = { 0 };
				next.y = now.y + dy[j];
				next.x = now.x + dx[j];
				if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= M)
					continue;
				if (tmp[next.y][next.x] != 0)
					continue;
				cnt_two++;
				if (cnt_zero - cnt_two < max_val)
					return;
				tmp[next.y][next.x] = 2;
				q.push(next);
			}
		}
	}
	max_val = max(cnt_zero - cnt_two, max_val);

}

void dfs(int level) {
	if (level == 3) {
		bfs();
		return;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != 0)
				continue;
			if (level > 0 && wall[level - 1].y > i)
				continue;
			if (level > 0 && wall[level - 1].y == i && wall[level - 1].x >= j)
				continue;
			
			wall.push_back({ i,j });
			dfs(level + 1);
			wall.pop_back();
		}
	}
}

int main() {
	cin >> N >> M;

	int cmp = N * M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2)
				two.push_back({ i,j });
			if (map[i][j] == 0)
				cnt_zero++;
		}
	}
	dfs(0);

	cout << max_val - 3;

	return 0;
}
