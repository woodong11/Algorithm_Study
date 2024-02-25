#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>

using namespace std;

int N;
int x, y, d, g;
int map[101][101];
int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { 1, 0, -1, 0 };
int ny, nx;
int cnt;

vector<int> v; // 방향 저장

int main() {
	freopen("sample_input.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		v.clear();
		cin >> x >> y >> d >> g;

		map[y][x] = 1;
		ny = y + dy[d];
		nx = x + dx[d];
		map[ny][nx] = 1;

		v.push_back(d);

		for (int i = 0; i < g; i++) // 세대만큼
		{
			int newd = 0;

			for (int j = v.size() -1; j >=0; j--)
			{
				newd = (v[j] + 1) % 4;

				ny += dy[newd];
				nx += dx[newd];
				map[ny][nx] = 1;

				v.push_back(newd);
			}
		}	
	}

	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			if (map[i][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j] == 1 && map[i + 1][j + 1] == 1) cnt++;
		}
	}
	cout << cnt;
}
