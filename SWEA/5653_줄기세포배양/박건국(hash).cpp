#define _CRT_SECURE_NO_WARNINGS
//freopen("sample_input.txt", "r", stdin);

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct point {
	int y, x;
};
struct cell_point {// state =0 >> begin <= time < begin + num, state = 1 >> start <= time < start + num,  state = 2 >> end <= time
	int y, x, num, begin, start, end, state;
	//y,x는 좌표, num은 해당 좌표에 있는 숫자
	//begin은 시작하는 k, start부터 활성화
	//end가 되면 죽기.
};
unordered_map<int, vector<cell_point>> cell_um;
int T, N, M, K;
int map[700][700];
int dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };

void state_check(int time, int cell_size, int num) {
	for (int i = 0; i < cell_size; i++) {
		if (cell_um[num][i].begin <= time && time < cell_um[num][i].begin + num)
			cell_um[num][i].state = 0;
		else if (cell_um[num][i].start <= time && time < cell_um[num][i].start + num)
			cell_um[num][i].state = 1;
		else if (cell_um[num][i].end <= time)
			cell_um[num][i].state = 2;
	}
}

void grow(int num, int cell_size, int time) {
	for (int i = 0; i < cell_size; i++) {
		if (cell_um[num][i].state != 1)
			continue;
		point now = { cell_um[num][i].y , cell_um[num][i].x };

		for (int j = 0; j < 4; j++) {
			point next = { 0 };
			next.y = now.y + dy[j];
			next.x = now.x + dx[j];
			if (map[next.y][next.x] != 0)
				continue;
			map[next.y][next.x] = num;
			cell_um[num].push_back({ next.y,next.x, num, time, time + num, time + num * 2 });
		}
	}
}

int count_cell() {
	int cnt = 0;
	for (int i = 1; i <= 10; i++) {
		if (!cell_um.count(i))
			continue;
		int cell_size = cell_um[i].size();
		for (int j = 0; j < cell_size; j++) {
			if (cell_um[i][j].state == 2)
				continue;
			cnt++;
		}
	}
	return cnt;
}
void init() {
	memset(map, 0, sizeof(map));
	cell_um = {};
}

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M >> K;
		for (int i = 330; i < 330 + N; i++) {
			for (int j = 330; j < 330 + M; j++) {
				cin >> map[i][j];
				if (map[i][j] != 0) {
					int num = map[i][j];
					cell_um[map[i][j]].push_back({ i,j,num,0, num, num + num,0 });
				}
			}
		}
		for (int i = 1; i <= K; i++) {
			for (int j = 10; j >= 1; j--) {
				if (!cell_um.count(j))
					continue;
				int cell_size = cell_um[j].size();
				grow(j, cell_size, i);
				state_check(i,cell_size, j);
			}
		}
		int cnt = count_cell();
		cout << '#' << tc << " " << cnt << endl;
		init();
	}
}
