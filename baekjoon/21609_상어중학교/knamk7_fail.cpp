#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;

int N, M;
int point;
int blocks_left;
vector<vector<int>> map;
vector<vector<int>> checked;
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };

struct Coord
{
	int y;
	int x;
};

void input0()
{
	cin >> N >> M;
}

void init()
{
	vector<vector<int>> v(N + 2, vector<int>(N + 2, -1));
	map = v;
	vector<vector<int>> v2(N + 2, vector<int>(N + 2));
	checked = v2;
}

void input1()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> map[i][j];
			if (map[i][j] >= 0)
			{
				blocks_left++;
			}
		}
	}
}

int bfs(int y, int x)
{
	vector<vector<int>> visited(N + 2, vector<int>(N + 2));
	queue<Coord> q;
	int blocktype = map[y][x];
	q.push({ y,x });
	visited[y][x] = 1;
	int cnt = 1;
	while (!q.empty())
	{
		Coord now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (map[ny][nx] != blocktype && map[ny][nx] != 0)
			{
				continue;
			}
			q.push({ ny,nx });
			visited[ny][nx] = 1;
			if (map[ny][nx] != 0)
			{
				checked[ny][nx] = 1;
			}
			cnt++;
		}
	}
	return cnt;
}

void floodfill(int y, int x)
{
	vector<vector<int>> visited(N + 2, vector<int>(N + 2));
	queue<Coord> q;
	int blocktype = map[y][x];
	q.push({ y,x });
	visited[y][x] = 1;
	map[y][x] = -2;
	blocks_left--;
	while (!q.empty())
	{
		Coord now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (map[ny][nx] != blocktype && map[ny][nx] != 0)
			{
				continue;
			}
			q.push({ ny,nx });
			visited[ny][nx] = 1;
			map[ny][nx] = -2;
			blocks_left--;
		}
	}
}

void remove()
{
	int y = 0;
	int x = 0;
	int maxVal = 0;
	//vector<vector<int>> checked(N + 2, vector<int>(N + 2));
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			checked[i][j] = 0;
		}
	}
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (map[i][j] <= 0 || checked[i][j] == 1)
			{
				continue;
			}
			
			int cnt = bfs(i, j);
			if (cnt >= maxVal)
			{
				maxVal = cnt;
				y = i;
				x = j;
			}
		}
	}

	floodfill(y, x);
	point += maxVal * maxVal;
}

void fall()
{
	vector<vector<int>> newMap(N + 2, vector<int>(N + 2, -1));
	for (int j = 1; j <= N; j++)
	{
		queue<int> blocks;
		queue<int> blackY;
		for (int i = N; i > 0; i--)
		{
			blocks.push(map[i][j]);
			if (map[i][j] == -1)
			{
				blackY.push(i);
			}
		}
		int y = N;
		while (!blocks.empty())
		{
			int now = blocks.front();
			blocks.pop();
			if (now >= 0)
			{
				newMap[y][j] = now;
			}
			else if (now == -1)
			{
				while (y > blackY.front())
				{
					newMap[y][j] = -2;
					y--;
				}
				blackY.pop();
				newMap[y][j] = -1;
			}
			y--;
		}
		while (y > 0)
		{
			newMap[y][j] = -2;
			y--;
		}
	}
	map = newMap;
}

void rotateCCW()
{
	vector<vector<int>> next_map(N + 2, vector<int>(N + 2, -1));
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			next_map[i][j] = map[j][N + 1 - i];
		}
	}
	map = next_map;
}

void run()
{
	remove();
	fall();
	rotateCCW();
	fall();
}

int main()
{
	input0();
	init();
	input1();
	while (blocks_left > 0)
	{
		run();
	}
	cout << point;
	return 0;
}
