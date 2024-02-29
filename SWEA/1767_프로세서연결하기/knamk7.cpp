#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

struct Point
{
	int y;
	int x;
};

int N;
int number_of_processors;
int result;
int cnt;
int connected;
int max_connected;
int map[12][12];
int dy[] = { 1,0,-1,0 };
int dx[] = { 0,1,0,-1 };
Point processor[12];

void init()
{
	memset(map, 0, sizeof(map));
	memset(processor, 0, sizeof(processor));
	number_of_processors = 0;
	max_connected = 0;
	result = 21e8;
	cnt = 0;
}

void input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}
}

void count_proecessors()
{
	for (int i = 1; i < N - 1; i++)
	{
		for (int j = 1; j < N - 1; j++)
		{
			if (map[i][j] == 1)
			{
				processor[number_of_processors] = { i, j };
				number_of_processors++;
			}
		}
	}
}

int wiring(Point processor, int direction)
{
	int ny = processor.y + dy[direction];
	int nx = processor.x + dx[direction];
	while (!(ny == 0 || nx == 0 || ny == N - 1 || nx == N - 1))
	{
		if (map[ny][nx] != 0)
		{
			return 0;
		}
		ny += dy[direction];
		nx += dx[direction];
	}
	if (map[ny][nx] != 0)
	{
		return 0;
	}
	int ret = 1; // 테두리는 안 살펴 볼거니깐
	ny = processor.y + dy[direction];
	nx = processor.x + dx[direction];
	while (!(ny == 0 || nx == 0 || ny == N - 1 || nx == N - 1))
	{
		map[ny][nx] = 2;
		ret++;
		ny += dy[direction];
		nx += dx[direction];
	}
	connected++;
	return ret;
}

void dewire(Point processor, int direction)
{
	int ny = processor.y + dy[direction];
	int nx = processor.x + dx[direction];
	while (!(ny == 0 || nx == 0 || ny == N - 1 || nx == N - 1))
	{
		map[ny][nx] = 0;
		ny += dy[direction];
		nx += dx[direction];
	}
	connected--;
}

void dfs(int level)
{
	if (level == number_of_processors || connected + number_of_processors - level < max_connected) // 가지치기로 시간 절약
	{
		if (max_connected == connected)
		{
			result = min(result, cnt);
		}
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int connected_just_now = wiring(processor[level], i);
		if (connected_just_now == 0)
		{
			dfs(level + 1);
			continue;
		}
		cnt += connected_just_now;
		if (connected > max_connected)
		{
			max_connected = connected;
			result = 21e8;
		}
		dfs(level + 1);
		dewire(processor[level], i);
		cnt -= connected_just_now;
	}

}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		input();
		count_proecessors();
		dfs(0);
		printf("#%d %d\n", test_case, result);
	}
	return 0;
}
