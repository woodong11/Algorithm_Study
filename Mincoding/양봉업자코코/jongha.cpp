#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Point {
	int y;
	int x;
};

int T, x, y, grid[16][16], check[16][16];
int result;
int dx[8] = { 0, 0, 1, -1, 1, -1, 1, -1 }, dy[8] = { 1, -1, 0, 0, -1, -1, 1, 1 };
vector<Point> v;
Point node1;
bool my = false;

void init() {
	result = 0;
}



void dfs(int x_, int y_, int level, int sum) {
	if (level == 4) {
		result = result > sum ? result : sum;
		return;
	}

	int nx, ny;

	if (level == 2) {
		node1.y = y_;
		node1.x = x_;
	}

	for (int i = 0; i < 8; i++) {
    // x_ 짝수이면 대각선으로 올라가는게 불가능
		if (x_ % 2 == 0 && i >= 6) break;
    // x_ 홀수이면 대각선으로 내려가는게 불가능
		if (x_ % 2 == 1 && (i == 4 || i == 5)) continue;
		nx = x_ + dx[i];
		ny = y_ + dy[i];

		if (nx < 0 || ny < 0 || nx >= x || ny >= y) continue;
		if (check[ny][nx] == 1) continue;

		sum += grid[ny][nx];
		check[ny][nx] = 1;
		dfs(nx, ny, level + 1, sum);
		sum -= grid[ny][nx];
		check[ny][nx] = 0;
	}

  // ㅗ ㅓ ㅏ ㅜ 모양의 합 구하기
	if (level == 3) {
		int nx_, ny_;
		for (int z = 0; z < 4; z++) {
			nx_ = node1.x + dx[z];
			ny_ = node1.y + dy[z];

			if (nx_ < 0 || ny_ < 0 || nx_ >= x || ny_ >= y) continue;
			if (check[ny_][nx_] == 1) continue;
			
			sum += grid[ny_][nx_];
			check[ny_][nx_] = 1;
			dfs(nx_, ny_, level + 1, sum);
			sum -= grid[ny_][nx_];
			check[ny_][nx_] = 0;
		}
	}
}

int main() {
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> y >> x;
		init();
		for (int i = 0; i < y; i++) {
			for (int z = 0; z < x; z++) {
				cin >> grid[i][z];
			}
		}

		for (int i = 0; i < y; i++) {
			for (int z = 0; z < x; z++) {
				check[i][z] = 1;
				dfs(z, i, 1, grid[i][z]);
				check[i][z] = 0;
			}
		}

		cout << "#" << tc << " " << result << "\n";
	}



	return 0;
}
