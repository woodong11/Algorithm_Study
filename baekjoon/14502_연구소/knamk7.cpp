// 48ms
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

int N, M;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
vector<vector<int>> map;

struct Coord
{
	int y;
	int x;
};

vector<Coord> v;

int bfs()
{
	queue<Coord> q;
	vector<vector<int>> visited = map;

	for (auto i : v)
	{
		q.push(i);
	}

	while (!q.empty())
	{
		Coord now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (visited[ny][nx] > 0) continue;
			q.push({ ny,nx });
			visited[ny][nx] = 1;
		}
	}

	int ret = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (visited[i][j] == 0)
			{
				ret++;
			}
		}
	}
	return ret;
}

int main()
{
	int ans = 0;
	cin >> N >> M;
	map = vector<vector<int>>(N + 2, vector<int>(M + 2, 1));
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 2)
			{
				v.push_back({ i, j });
			}
		}
	}
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (map[i][j] != 0) continue;
			map[i][j] = 1;
			for (int k = i; k <= N; k++)
			{
				for (int l = j; l <= M; l++)
				{
					if (map[k][l] != 0) continue;
					map[k][l] = 1;
					for (int i = k; i <= N; i++)
					{
						for (int j = l; j <= M; j++)
						{

							if (map[i][j] != 0) continue;
							map[i][j] = 1;
							ans = max(ans, bfs());
							map[i][j] = 0;
						}
					}
					for (int i = k + 1; i <= N; i++)
					{
						for (int j = 1; j < l; j++)
						{

							if (map[i][j] != 0) continue;
							map[i][j] = 1;
							ans = max(ans, bfs());
							map[i][j] = 0;
						}
					}
					map[k][l] = 0;
				}
			}
			for (int k = i + 1; k <= N; k++)
			{
				for (int l = 1; l < j; l++)
				{
					if (map[k][l] != 0) continue;
					map[k][l] = 1;
					for (int i = k; i <= N; i++)
					{
						for (int j = l; j <= M; j++)
						{

							if (map[i][j] != 0) continue;
							map[i][j] = 1;
							ans = max(ans, bfs());
							map[i][j] = 0;
						}
					}
					for (int i = k + 1; i <= N; i++)
					{
						for (int j = 1; j < l; j++)
						{

							if (map[i][j] != 0) continue;
							map[i][j] = 1;
							ans = max(ans, bfs());
							map[i][j] = 0;
						}
					}
					map[k][l] = 0;
				}
			}
			map[i][j] = 0;
		}
	}

	cout << ans;
	return 0;

}
