#include<iostream>
#include<cstring>
#include<deque>
using namespace std;

struct Snake
{
	int y;
	int x;
};

int N;
int K;
int L;
int T;
int direction;
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int map[102][102];
deque<Snake> snake;

void init()
{
	memset(map, -1, sizeof(map));
}

void input()
{
	cin >> N;
	cin >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			map[i][j] = 0;
		}
	}
	for (int i = 0; i < K; i++)
	{
		int y, x;
		cin >> y >> x;
		map[y][x] = 1;
	}
	cin >> L;
}

void game()
{
	map[1][1] = -1;
	snake.push_back({ 1,1 });
	for (int aaa = 0; aaa < L; aaa++)
	{
		int t;
		char rotate;
		cin >> t >> rotate;
		while (T < t)
		{
			T++;
			int ny = snake.back().y + dy[direction];
			int nx = snake.back().x + dx[direction];
			if (map[ny][nx] == -1) return;
			snake.push_back({ ny,nx });
			if (map[ny][nx] == 0)
			{
				Snake tail = snake.front();
				snake.pop_front();
				map[tail.y][tail.x] = 0;
			}
			map[ny][nx] = -1;
		}
		if (rotate == 'D')
		{
			direction = (direction + 1) % 4;
		}
		else
		{
			direction = (direction + 3) % 4;
		}
	}
	while (true)
	{
		T++;
		int ny = snake.back().y + dy[direction];
		int nx = snake.back().x + dx[direction];
		if (map[ny][nx] == -1)
		{
			return;
		}
		snake.push_back({ ny,nx });
		if (map[ny][nx] == 0)
		{
			Snake tail = snake.front();
			snake.pop_front();
			map[tail.y][tail.x] = 0;
		}
		map[ny][nx] = -1;
	}
}

void print()
{
	cout << T;
}

int main()
{
	init();
	input();
	game();
	print();
	return 0;
}
