#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

int T;
int N;
int map[101][101];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1 ,0, -1 };
int maxVal;

int block[6][4] = {
	{0,0,0,0},
	{2,3,1,0},
	{1,3,0,2},
	{3,2,0,1},
	{2,0,3,1},
	{2,3,0,1}
};

struct Point {
	int y, x;
};

vector<Point> w[5];
vector<Point> bhole;

void init() {
	maxVal = 0;
	for (int i = 0; i < 5; i++)
	{
		w[i].clear();
	}
	
	bhole.clear();
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
			if (map[i][j] >= 6 && map[i][j] <= 10) {
				w[map[i][j] - 6].push_back({ i, j });
			}
			if (map[i][j] == -1) bhole.push_back({ i, j });
		}
	}
}


void processbyCase(int sty, int stx) {
	
	for (int i = 0; i < 4; i++) 
	{
		int stdir = i;
		int cnt = 0;
		Point now = { sty, stx };
		Point next;
		
		while (true) {
			next.y = now.y + dy[stdir];
			next.x = now.x + dx[stdir];

			if (map[next.y][next.x] == -1) break;

			else if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N) {
				stdir = (stdir + 2) % 4;
				cnt++;
			}

			else if (map[next.y][next.x] > 0 && map[next.y][next.x] < 6) {
				stdir = block[map[next.y][next.x]][stdir];
				cnt++;
			}

			else if (map[next.y][next.x] >=6 && map[next.y][next.x]<=10) {
				for (int i = 0; i < 2; i++)
				{
					if (next.y == w[map[next.y][next.x] - 6][i].y && next.x == w[map[next.y][next.x] - 6][i].x) continue;
					now.y = w[map[next.y][next.x] - 6][i].y;
					now.x = w[map[next.y][next.x] - 6][i].x;
					break;
				}
				continue;
			}
			else {
				now = next;
			}

			if (now.y == sty && now.x == stx) break;
			now = next; 
		}
		maxVal = max(maxVal, cnt);
	}

}

void process() {
	for (int stY = 0; stY < N; stY++)
	{
		for (int stX = 0; stX < N; stX++)
		{
			if (map[stY][stX] == 0) {
				processbyCase(stY, stX);
			}
		}
	}
}

int main() {
	//freopen("sample_input.txt", "r", stdin);

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		process();
		cout << "#" << tc << " " << maxVal <<'\n';
	}
}
