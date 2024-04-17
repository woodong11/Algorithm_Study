#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
int map[5][5]; // 0:빈공간, -1:벽, 나머지 방문해야하는 곳의 순서(1,2,..)
int visited[5][5];
int sequence_dat[17]; //방문했는지확인
int sty, stx, edy, edx;

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int ans;

void input() {
	int a, b;
	cin >> n >> m; // 격자 크기, 방문해야 하는 곳의 수
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> a;
			if (a == 1) a = -1;
			map[i][j] = a;
		}
	}
	for (int i = 1; i <= m; i++)
	{
		cin >> a >> b;
		map[a - 1][b - 1] = i;
		if (i == 1) {
			sty = a - 1;
			stx = b - 1;
		}
		else if (i == m) {
			edy = a - 1;
			edx = b - 1;
		}
	}
}

void dfs(int y, int x) {
	int ny, nx;
	int flag = 0;
	if (y == edy && x == edx) {
		ans++;
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		ny = y + dy[i];
		nx = x + dx[i];
		if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
		else if (visited[ny][nx] == 1 || map[ny][nx] == -1) continue;

		if (map[ny][nx] > 0) {
			if (sequence_dat[map[ny][nx] - 1] == 0) continue;
			flag = 1;
			sequence_dat[map[ny][nx]] = 1;
		}

		visited[ny][nx] = 1;
		dfs(ny, nx);
		visited[ny][nx] = 0;
		if (flag == 1) sequence_dat[map[ny][nx]] = 0;
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	input();
	
	sequence_dat[1]=1;
	visited[sty][stx] = 1;
	dfs(sty, stx);
	cout << ans;
	return 0;
}
