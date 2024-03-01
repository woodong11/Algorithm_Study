#define _CRT_SECURE_NO_WARNINGS
//	freopen("sample_input.txt", "r", stdin);

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct cell_point {
	int y, x, num, st, state;
};
struct cmp {
	bool operator () (cell_point a, cell_point b) {
		return a.num < b.num;
	}
};

int T, N, M, K;
int map[651][651];
int dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
priority_queue<cell_point, vector<cell_point>, cmp> pq;

void grow(int time) {
	priority_queue<cell_point, vector<cell_point>, cmp> tmp = pq;
	while (!tmp.empty()) {
		cell_point now = tmp.top();
		tmp.pop();
		if (now.state != 1)
			continue;
		for (int i = 0; i < 4; i++) {
			cell_point next = now;
			next.y = now.y + dy[i];
			next.x = now.x + dx[i];
			if (map[next.y][next.x] != 0)
				continue;
			map[next.y][next.x] = next.num;
			next.st = time;
			next.state = 0;
			pq.push(next);
		}
	}
	tmp = pq;
	pq = {};
	while (!tmp.empty()) {
		cell_point now = tmp.top();
		tmp.pop();

		if (now.st <= time && time < now.st + now.num)
			now.state = 0;
		else if (now.st + now.num <= time && time < now.st + now.num * 2)
			now.state = 1;
		else if (now.st + now.num * 2 <= time)
			now.state = 2;
		if (now.state == 2)
			continue;
		pq.push(now);
	}

}

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M >> K;
		for (int i = 301; i < 301 + N; i++) {
			for (int j = 301; j < 301 + M; j++) {
				cin >> map[i][j];
				if (map[i][j] != 0) {
					int num = map[i][j];
					pq.push({ i,j,num,0, 0 });
				}
			}
		}
		for (int i = 0; i <= K; i++) {
			grow(i);
		}
		cout << '#' << tc << " " << pq.size() << endl;
		memset(map, 0, sizeof(map));
		pq = {};
	}
}
