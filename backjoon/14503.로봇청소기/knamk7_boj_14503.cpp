#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int N, M;

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int room[50][50];
int cnt;

bool cleaned(int r, int c)
{
	for (int i = 0; i < 4; i++)
	{
		int ny = r + dy[i];
		int nx = c + dx[i];
		if (room[ny][nx] == 0)
		{
			return false;
		}
	}
	return true;
}

void f(int r, int c, int d)
{
	if (room[r][c] == 0)
	{
		cnt++;
		room[r][c] = 2;
	}
	if (cleaned(r, c))
	{
		if (room[r - dy[d]][c - dx[d]] == 1)
		{
			return;
		}
		f(r - dy[d], c - dx[d], d);
	}
	else
	{
		d = (d + 3) % 4;
		while (room[r + dy[d]][c + dx[d]] != 0)
		{
			d = (d + 3) % 4;
		}
		f(r + dy[d], c + dx[d], d);
	}
}

int main()
{
	int r, c, d;
	cin >> N >> M;
	cin >> r >> c >> d;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> room[i][j];
		}
	}

	f(r, c, d);

	cout << cnt;
	return 0;
}
