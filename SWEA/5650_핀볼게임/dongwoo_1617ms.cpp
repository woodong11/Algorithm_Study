#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int T, N, answer;
int MAP[101][101];
int dy[4] = { 0, 1, 0, -1 };		// 우 하 좌 상
int dx[4] = { 1, 0, -1, 0 };
bool isBlackhole = false;
int changeDirection[6][4] = {
	{},
	{2, 0, 3, 1},
	{2, 3, 1, 0},
	{1, 3, 0, 2},
	{3, 2, 0, 1},
	{2, 3, 0, 1}
};

struct wormhole {
	int y;
	int x;
};
vector <wormhole> wormholes[11];	// 0 ~ 10

void init() {
	memset(MAP, 0, sizeof(MAP));
	answer = 0;
	for (int i = 6; i < 11; i++)		// 웜홀 초기화
	{
		wormholes[i].clear();
	}
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int temp;
			cin >> temp;
			MAP[i][j] = temp;
			if (temp >= 6) {		// 웜홀 저장
				wormholes[temp].push_back({i, j});
			}
		}
	}
}

int game(int startY, int startX, int direction) {
	int cnt = 0;
	int curY = startY;
	int curX = startX;
	while (true) {
		int ny = curY + dy[direction];
		int nx = curX + dx[direction];

		// 맵 바깥 -> direction 반대
		if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
			direction = (direction + 2) % 4;
			curY = ny; curX = nx;
			cnt++;
			continue;
		}

		// 블랙홀일때 혹은 시작지점에 도착했을때
		if ((MAP[ny][nx] == -1) || (ny == startY && nx == startX)) {
			break;
		}

		// 빈칸이었을때
		else if (MAP[ny][nx] == 0) {
			curY = ny; curX = nx;
		}

		// 블록 만났을때 
		else if (MAP[ny][nx] <= 5) {
			direction = changeDirection[MAP[ny][nx]][direction];
			curY = ny; curX = nx;
			cnt++;
		}

		// 웜홀 만났을때
		else {
			int num = MAP[ny][nx];
			if ((ny == wormholes[num][0].y) && (nx == wormholes[num][0].x)) {
				curY = wormholes[num][1].y;
				curX = wormholes[num][1].x;
			}
			else {
				curY = wormholes[num][0].y;
				curX = wormholes[num][0].x;
			}
		}
	}

	return cnt;
}



void solve() {

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (MAP[i][j] == 0) {				// 핀볼 상하좌우 시작
				for (int k = 0; k < 4; k++)		// 이거 < 3으로 해놔서 1시간 날림.....
				{
					int curResult = game(i, j, k);
					answer = max(answer, curResult);
				}	
			}
		}
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		solve();
		cout << "#" << tc << " " << answer << "\n";
	}

	return 0;
}
