#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int T;
int N, W, H;
int map[20][20];
int tryMap[20][20];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

vector<int>v;
vector<vector<int>> permutation;
int minVal = 21e8;

struct Point {
	int y, x, scale;
};

void input() {
	cin >> N >> W >> H;

	for (int i = 0; i < H; i++)
	{
		for (int  j = 0; j < W; j++)
		{
			cin >> tryMap[i][j];
		}
	}
}

void init() {
	// map
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			map[i][j] = tryMap[i][j];
		}
	}
}

// 폭탄이 존재하는 row idx 찾기
int findRowidx(int col) {
	for (int i = 0; i < H; i++)
	{
		if (map[i][col] != 0)
			return i;
	}
	return -1;
}

// 터져라얍
void bomb(int stX) {
	queue<Point>q;
	int stY = findRowidx(stX);
	if (stY == -1) return; // 해당 row에 폭탄이 존재하지 않는 경우 

	q.push({ stY, stX, map[stY][stX] });
	Point now;
	int cnt = 0;
	while (!q.empty()) {
		now = q.front();
		q.pop();
		if (map[now.y][now.x] == 0) continue;
		map[now.y][now.x] = 0;
		cnt++;

		if (now.scale == 1) continue;

		for (int d = 0; d < 4; d++)
		{
			for (int b = 1; b <= now.scale -1; b++)// bomb scale
			{
				int ny = now.y + b*dy[d];
				int nx = now.x + b*dx[d];

				if (ny < 0 || nx < 0 || ny >= H || nx >= W) continue;
				if (map[ny][nx] == 0) continue;
				
				q.push({ ny, nx, map[ny][nx] });
			}
		}
	}
}

// 후처리
void down() {
	for (int x = 0; x < W; x++)
	{
		for (int y = H - 1; y >= 1; y--)
		{
			if (map[y][x] != 0) continue;
			for (int p = y-1; p >=0; p--)
			{
				if (map[p][x] == 0) continue;
				map[y][x] = map[p][x];
				map[p][x] = 0;
				break;
			}
		}
	}
}

// 남은 폭탄 세기
int count() {
	int restB = 0;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (map[i][j] == 0)continue;
			restB++;
		}
	}
	return restB;
}

// 중복순열 (폭탄 터트릴 수 있는 경우의 수)
void P(int depth) {
	if (depth == N) {
		permutation.push_back(v);
		return;
	}
	for (int i = 0; i < W; i++)
	{
		v.push_back(i);
		P(depth + 1);
		v.pop_back();
	}
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		v.clear();
		permutation.clear();
		int minVal = 21e8;

		input();
		P(0);
		for (vector<int> p : permutation)
		{
			init();
			for (int i = 0; i < N; i++)
			{
				bomb(p[i]);
				down();
			}
			int restBomb = count();
      
			minVal = min(restBomb, minVal);
			if (minVal == 0) {
				break;
			}
		}
		cout<< '#'<<tc<<' ' << minVal << '\n';
	}
	return 0;
}
