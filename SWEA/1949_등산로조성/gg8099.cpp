#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
struct yx {
	int y, x;
};
struct point {
	int y, x, flag, num, b_num_y, b_num_x;
	//yx는 좌표고 flag는 깎았는지 유무, num 해당 위치의 산높이
	vector<yx> sh;
};

int map[9][9], T, N, K;
int dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
int max_val;
int max_route;
vector<point> vec;

void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = 0;
		}
	}
	max_val = 0;
	vec = {};
	max_route = 0;
}

void bfs(point st, int(&map)[9][9]) {
	int route[9][9];
	int tmp_map[9][9];
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			route[i][j] = 1;
			tmp_map[i][j] = map[i][j];
		}
	}
	queue<point> q;
	q.push(st);
	while (!q.empty()) {
		point now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			point next = now;
			next.y = now.y + dy[i];
			next.x = now.x + dx[i];
			next.num = map[next.y][next.x];
			
			if (now.b_num_y == next.y && now.b_num_x == next.x)
				continue;
			int flag = 0;
			for (int t = 0; t < next.sh.size(); t++) {
				if (next.y == now.sh[t].y && next.x == now.sh[t].x) {
					flag = 1;
					break;
				}				
			}
			if (flag == 1)
				continue;
			next.sh.push_back({ now.y,now.x });
			next.b_num_y = now.y, next.b_num_x = now.x;
			if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N)
				continue;
			if (next.num >= now.num && next.num - now.num < K && next.flag == 0) {
				tmp_map[next.y][next.x] = tmp_map[now.y][now.x] - 1;
				next.num = now.num - 1;
				next.flag = 1;
			}
			if (next.num >= now.num)
				continue;
			if (route[next.y][next.x] > route[now.y][now.x] + 1)
				continue;
			if (next.y == st.y && next.x == st.x)
				continue;
			route[next.y][next.x] = route[now.y][now.x] + 1;
			max_route = max(max_route, route[next.y][next.x]);
			q.push(next);
		}
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> K;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] > max_val) {
					vec = {};
					max_val = map[i][j];
				}
				if (map[i][j] == max_val) {
					vec.push_back({ i,j,0,map[i][j],0,0 });
				}
			}
		}
		for (int i = 0; i < vec.size(); i++) {
			bfs(vec[i], map);
		}
		cout << '#' << tc << ' ' << max_route << '\n';
		init();
	}


	return 0;
}
