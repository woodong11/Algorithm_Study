#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
	int y, x;
};
struct cpoint {
	int num, y, x;
};

vector<cpoint> vec;
int N, M, result = 21e8;
int size_vec;
int dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 };

int count_cctv(int (&tmp)[9][9]) {
	int tmp_cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (tmp[i][j] == 0)
				tmp_cnt++;
		}
	}
	return tmp_cnt;
}
void bfs(int(&tmp)[9][9], cpoint v, int t) {
	int st = 0, ed;
	vector<int> go;
	go.push_back(t);
	if (v.num == 1) {
		ed = 1;
	}
	else if (v.num == 2) {
		go.push_back((t + 2) % 4);
		ed = 2;
	}
	else if (v.num == 3) {
		go.push_back((t + 1) % 4);
		ed = 2;
	}
	else if (v.num == 4) {
		go.push_back((t + 1) % 4);
		go.push_back((t + 3) % 4);
		ed = 3;
	}
	else if (v.num == 5) {
		go.push_back((t + 1) % 4);
		go.push_back((t + 2) % 4);
		go.push_back((t + 3) % 4);
		ed = 4;
	}
	for (int i = st; i < ed; i++) {
		point now = { v.y,v.x };
		while (1) {
			point next = { 0 };
			next.y = now.y + dy[go[i]];
			next.x = now.x + dx[go[i]];
			if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= M)
				break;
			if (tmp[next.y][next.x] == 6)
				break;
			now.y = next.y, now.x = next.x;
			tmp[next.y][next.x] = 1;
		}

	}

}

void dfs(int level, int(&cc)[9][9]) {
	int tmp[9][9];
	if (level == size_vec) {
		int minval = count_cctv(cc);
		result = min(result, minval);
		return;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			tmp[i][j] = cc[i][j];
		}
	}
	for (int i = 0; i < 4; i++) {
		bfs(tmp, vec[level], i);
		dfs(level + 1, tmp);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				tmp[i][j] = cc[i][j];
			}
		}
		int de = 1;
	}
}

int main() {
	cin >> N >> M;
	int map[9][9];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] >= 1 && map[i][j] <= 5)
				vec.push_back({ map[i][j],i,j });
		}
	}
	size_vec = vec.size();

	dfs(0, map);
	cout << result;

	return 0;
}
