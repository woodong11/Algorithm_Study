#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;



int T, N, M, answer;
int MAP[16][16];
int visited[16][16];
int dyOdd[6] = {-1, 1, 0, 0, -1, -1};	// 상하좌우 좌상 우상
int dxOdd[6] = { 0, 0, -1, 1, -1, 1 };
int dyEven[6] = { -1, 1, 0, 0 , 1, 1};	// 상하좌우 좌하 우하
int dxEven[6] = { 0, 0, -1, 1, -1, 1 };


void init() {
	memset(MAP, 0, sizeof(MAP));
	answer = 0;
}

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAP[i][j];
		}
	}

}

void func(int level, int sum, int curY, int curX) {
	if (level == 3) {
		if (answer < sum) {
			answer = sum;
		}
		return;
	}

	for (int i = 0; i < 6; i++)
	{
		int ny, nx;
		if (curX % 2 == 0) {
			ny = curY + dyOdd[i];
			nx = curX + dxOdd[i];
		}
		else {
			ny = curY + dyEven[i];
			nx = curX + dxEven[i];
		}

		if (ny < 0 || nx < 0 || ny >= N || nx >= M)
			continue;

		if (visited[ny][nx] == 1)
			continue;

		visited[ny][nx] = 1;
		func(level + 1, sum + MAP[ny][nx], ny, nx);
		visited[ny][nx] = 0;

	}
}

void func2(int curY, int curX) {
	int sum;
	if ((curX > 0) && (curX < M - 1)) {
		// 만약 홀수번재 열이라면
		if (curX % 2 == 0) {
			if ((curY > 0) && (curY < N - 1)) {
				sum = MAP[curY][curX] + MAP[curY - 1][curX - 1] + MAP[curY - 1][curX + 1] + MAP[curY + 1][curX];
				answer = max(sum, answer);
			}
			if ((curY > 0) && (curY <= N - 1)) {
				sum = MAP[curY][curX] + MAP[curY][curX - 1] + MAP[curY][curX + 1] + MAP[curY - 1][curX];
				answer = max(sum, answer);
			}
			
		}

		// 만약 짝수번째 열이라면
		else {
			if ((curY >= 0) && (curY < N - 1)) {
				sum = MAP[curY][curX] + MAP[curY][curX - 1] + MAP[curY][curX + 1] + MAP[curY + 1][curX];
				answer = max(sum, answer);
			}
			if ((curY > 0) && (curY < N - 1)) {
				sum = MAP[curY][curX] + MAP[curY + 1][curX + 1] + MAP[curY + 1][curX - 1] + MAP[curY - 1][curX];
				answer = max(sum, answer);
			}
		}
	
	}

}

void solve(){

	//int sum = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			// 일반 4칸 만들어보기
			visited[i][j] = 1;
			func(0, MAP[i][j], i, j);
			visited[i][j] = 0;
			// 특수 4칸 만들어보기
			func2(i, j);
		}
	}
}


int main() {
	//freopen("sample_input.txt", "r", stdin);
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		init();
		input();
		solve();
		cout << "#" << tc << " " << answer << "\n";
	}
		return 0;
}
