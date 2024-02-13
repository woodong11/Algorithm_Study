#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point{
	int y;
	int x;
};

int N, W, H, T, result, tempResult, cnt, wallcnt;
int grid[16][13], tempgrid[16][13], xgrid[5][16][13];
int dx[4] = { 0, 0, 1, -1 }, dy[4] = { 1, -1, 0, 0 };
queue<Point> qp;
vector<int> v;
int temp[5];
int i;

void init() {
	tempResult = 0;
	cnt = 0;
	wallcnt = 0;
}

void gridInit() {
	for (int i = 0; i < H; i++) {
		for (int z = 0; z < W; z++) {
			tempgrid[i][z] = grid[i][z];
		}
	}
}

void xGridInit(int x, int level) {
	if (x == 0) {
		for (int i = 0; i < H; i++) {
			for (int z = 0; z < W; z++) {
				xgrid[level][i][z] = tempgrid[i][z];
			}
		}
	}
	else {
		for (int i = 0; i < H; i++) {
			for (int z = 0; z < W; z++) {
				tempgrid[i][z] = xgrid[level][i][z];
			}
		}
	}
}

void sortWall() {
	for (int i = 0; i < W; i++) {
		for (int z = 0; z < H; z++) {
			if (tempgrid[z][i] == 0) continue;
			v.push_back(tempgrid[z][i]);
			tempgrid[z][i] = 0;
		}
		if (v.empty()) continue;
		for (int z = H - 1; z >= 0; z--) {
			tempgrid[z][i] = v.back();
			v.pop_back();
			if (v.empty()) break;
		}
	}
}

void breakWall(int y, int x) {
	if (tempgrid[y][x] == 0) return;
	if (tempgrid[y][x] == 1) {
		cnt++;
		tempgrid[y][x] = 0;
		return;
	}

	int a;
	a = tempgrid[y][x];
	tempgrid[y][x] = 0;
	int ny, nx;

	for (int i = 1; i < a; i++) {
		ny = y + dy[0] * i;
		nx = x + dx[0] * i;

		if (ny < 0 || nx < 0 || ny >= H || nx >= W) break;
		if (tempgrid[ny][nx] == 1) {
			tempgrid[ny][nx] = 0;
			cnt++;
		}
		else if (tempgrid[ny][nx] > 1) {
			breakWall(ny, nx);
		}
	}
	for (int i = 1; i < a; i++) {
		ny = y + dy[1] * i;
		nx = x + dx[1] * i;

		if (ny < 0 || nx < 0 || ny >= H || nx >= W) break;
		if (tempgrid[ny][nx] == 1) {
			tempgrid[ny][nx] = 0;
			cnt++;
		}
		else if (tempgrid[ny][nx] > 1) {
			breakWall(ny, nx);
		}
	}
	for (int i = 1; i < a; i++) {
		ny = y + dy[2] * i;
		nx = x + dx[2] * i;

		if (ny < 0 || nx < 0 || ny >= H || nx >= W) break;
		if (tempgrid[ny][nx] == 1) {
			tempgrid[ny][nx] = 0;
			cnt++;
		}
		else if (tempgrid[ny][nx] > 1) {
			breakWall(ny, nx);
		}
	}
	for (int i = 1; i < a; i++) {
		ny = y + dy[3] * i;
		nx = x + dx[3] * i;

		if (ny < 0 || nx < 0 || ny >= H || nx >= W) break;
		if (tempgrid[ny][nx] == 1) {
			tempgrid[ny][nx] = 0;
			cnt++;
		}
		else if (tempgrid[ny][nx] > 1) {
			breakWall(ny, nx);
		}
	}
	cnt++;
}

void bfs(int y, int x, int coin, int tempcnt) {

	for (int i = y - 1; i >= 0; i--) {
		if (tempgrid[i][x] == 0) {
			break;
		}
		coin++;
	}
	if (coin > N) {
		return;
	} 

	breakWall(y, x);
	sortWall();

	if (coin == N) {
		tempResult = tempResult > cnt ? tempResult : cnt;
		return;
	}

	tempcnt = cnt;
	xGridInit(0, coin);

	for (int i = 0; i < H; i++) {
		for (int z = 0; z < W; z++) {
			if (tempgrid[i][z] != 0) {
				bfs(i, z, coin + 1, 0);
				cnt = tempcnt;
				xGridInit(1,coin);
			}
		}
	}
}

int main() {
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> W >> H;
		init();

		for (int i = 0; i < H; i++) {
			for (int z = 0; z < W; z++) {
				cin >> grid[i][z];
				tempgrid[i][z] = grid[i][z];
				if (grid[i][z] != 0) {
					wallcnt++;
				}
			}
		}

		for (int i = 0; i < H; i++) {
			for (int z = 0; z < W; z++) {
				if (grid[i][z] != 0) {
					bfs(i, z, 1, 0);
					cnt = 0;
					gridInit();
				}
			}
		}

		cout << "#" << tc << " " << wallcnt - tempResult << "\n";
	}





	return 0;
}
