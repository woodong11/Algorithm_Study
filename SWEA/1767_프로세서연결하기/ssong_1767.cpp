#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <vector>
#include <queue>

using namespace std;

// 한 방향으로만 설치 가능
// 교차X
// 가장자리 위치한 코어는 전원 연결로 간주
// 1. 최대한 많은 코어에 전원을 연결했을 경우 전선 길이의 합
// 2. 단, 전선 길이의 합은 최소화

// dfs ->

int T;
int N;
int map[13][13];
int visitedCore[13];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int coreCnt;
int turnOn[13];

struct Point{
	int y;
	int x;
};
queue<Point>q;

void input() {
	cin >> T;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 1) {
				//coreNum++;
				q.push({ i, j }); // 코어 위치 저장
			}
		}
	}
}
void init() {
	visitedCore[13] = { 0 };

	for (int i = 0; i < 13; i++)
	{
		turnOn[i] = 21e8;
	}
}

int connectCheck(int i, Point now) {
	int move = 1;
	// 한 방향으로 쭉 가 언제까지? 못 갈 때까지.. 
	while (true) {
		int ny = now.y + move * dy[i];
		int nx = now.x + move * dy[i];

		// 다른 코어에 닿음or 전선이 이미 깔림 >> 이쪽으로 못가용 return
		if (map[ny][nx] != 0) return 0;

		//무사히 벽 만났을 때 -> 연결
		if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
			return 1;
		}
		move++;
	}
}

void Connect(int i, Point nowP, int num) {
	int move = 1;
	while (1) {
		int ny = nowP.y + move * dy[i];
		int nx = nowP.x + move * dy[i];
		if (ny < 0 || nx < 0 || ny >= N || nx >= N) return;

		map[ny][nx] = num;
		move++;
	}
}

void dfs() {
	if (q.empty()) {
		cout << coreCnt;
		return;
	}
	
	Point nowPoint = q.front(); // 현재 코어
	q.pop();

	// 바깥쪽 코어
	if (nowPoint.y == 0 || nowPoint.x == 0 || nowPoint.y == (N - 1) || nowPoint.x == (N - 1)) {
		coreCnt++;
		dfs();
		coreCnt--;
	}
	
	for (int i = 0; i < 4; i++)
	{
		int possible = connectCheck(i, nowPoint);
		if (!possible) continue;
		else {// 1이면 갈수있성
			// /// 맵에 전선 체크 (빈곳0, 코어1, 전선2)
			Connect(i, nowPoint, 2);
		}
		coreCnt++;
		dfs();
		coreCnt--;
		if (possible) Connect(i, nowPoint, 0);
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	input();
	init();
	dfs();

}
