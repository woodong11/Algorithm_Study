#include<iostream>
#include<vector>
using namespace std;

struct Point
{
	int x;
	int y;
};

int N;
int dy[] = { 0, -1, 0, 1 };
int dx[] = { 1, 0, -1, 0 };
vector<vector<Point>> curve;
vector<Point> now;
int dat[101][101];
int map[100][100];

void input_and_draw_curves();
void draw_nextgen();
void count_and_output();

int main()
{
	input_and_draw_curves();
	count_and_output();
	return 0;
}

void input_and_draw_curves()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int x, y, d, g;
		now.clear();
		cin >> x >> y >> d >> g;
		now.push_back({ x, y });
		now.push_back({ x + dx[d], y + dy[d] });
		for (int j = 0; j < g; j++)
		{
			draw_nextgen();
		}
		curve.push_back(now);
	}
}

void draw_nextgen()
{
	Point axis = now.back();
	int limit = now.size() - 1;
	for (int i = limit - 1; i >= 0; i--)
	{
		int ny = (now[i].x - axis.x) + axis.y;
		int nx = (axis.y - now[i].y) + axis.x;
		now.push_back({ nx,ny });
	}
}

void count_and_output()
{
	for (int i = 0; i < curve.size(); i++)
	{
		for (int j = 0; j < curve[i].size(); j++)
		{
			Point now = curve[i][j];
			dat[now.y][now.x] = 1;
		}
	}

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			map[i][j] = dat[i][j] + dat[i + 1][j] + dat[i][j + 1] + dat[i + 1][j + 1];
		}
	}

	int cnt = 0;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (map[i][j] == 4)
				cnt++;
		}
	}

	cout << cnt;
}
