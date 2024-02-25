#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

struct point {
	int y, x, num, dir;
};
struct temp_point {
	int index, num;
};
vector<point> mesang;
vector<temp_point> temp_mesang;
int T, N, M, K;
int map[101][101], dy[] = { 0,-1,1,0,0 }, dx[] = { 0,0,0,-1,1 };

void mapset() {
	for (int i = 0; i < N; i++) {
		map[0][i] = -1, map[N - 1][i] = -1, map[i][0] = -1, map[i][N - 1] = -1;
	}
}
void init() {
	memset(map, 0, sizeof(map));
	mesang = {};
	temp_mesang = {};
}
int dir_func(int a) {
	if (a == 1 || a == 3)
		return a + 1;
	else if (a == 2 || a == 4)
		return a - 1;
}
void solve() {
	int temp[101][101] = { 0 };
	for (int i = 0; i < mesang.size(); i++) {
		mesang[i].y = mesang[i].y + dy[mesang[i].dir], mesang[i].x = mesang[i].x + dx[mesang[i].dir];
		temp[mesang[i].y][mesang[i].x]++;
		if (map[mesang[i].y][mesang[i].x] == -1) {
			mesang[i].num = mesang[i].num / 2, mesang[i].dir = dir_func(mesang[i].dir);
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (temp[i][j] >= 2) {
				for (int x = 0; x < mesang.size(); x++) {
					if (mesang[x].y == i && mesang[x].x == j)
						temp_mesang.push_back({ x,mesang[x].num });

				}
				int max_num = 0, max_index = 0;
				for (int x = 0; x < temp_mesang.size(); x++) {
					if (temp_mesang[x].num > max_num)
						max_num = temp_mesang[x].num, max_index = temp_mesang[x].index;
				}
				for (int x = 0; x < temp_mesang.size(); x++) {
					if (mesang[temp_mesang[x].index].num == 0)
						continue;
					if (temp_mesang[x].index != max_index) {
						mesang[max_index].num += mesang[temp_mesang[x].index].num;
						mesang[temp_mesang[x].index].num = 0;
					}
				}
				temp_mesang = {};
			}
		}
	}

}
int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M >> K;
		for (int i = 0; i < K; i++) {
			int diry, dirx, me_num, dir_yx;
			cin >> diry >> dirx >> me_num >> dir_yx;
			mesang.push_back({ diry,dirx,me_num,dir_yx });
		}
		mapset();
		for (int i = 0; i < M; i++) {
			solve();
		}
		int result = 0;
		for (int i = 0; i < mesang.size(); i++) {
			if (mesang[i].num != 0)
				result += mesang[i].num;
		}
		cout << '#' << tc << ' ' << result << endl;
		init();
	}
}
