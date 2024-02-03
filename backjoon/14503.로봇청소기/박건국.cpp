#include <iostream>

using namespace std;

int n, m;					// n*m 배열맵
int  map[51][51];
int flag;
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
int cnt;
int endplay;
struct point
{
	int y;
	int x;
	int way;
};

void wasd(point now)   // 현재칸 기준으로 4방향에 청소할 곳이 있는지 탐색
{
	for (int i = 0; i < 4; i++)
	{
		if (endplay == 1)
			break;
		point next = { 0 };
		next.y = now.y + dy[i];
		next.x = now.x + dx[i];
		if (map[next.y][next.x] == 0)
		{
			flag = 1;  // 있으면 flag 를 1로 반환하고3번으로, 0이면 2번으로
			return;
		}
	}
}

void func(point now)
{
	if (endplay == 1)
		return;
	flag = 0;
	if (map[now.y][now.x] == 0)
	{
		map[now.y][now.x] = 3;    // 0은 색칠해야할곳, 3은 색칠한곳으로
		cnt++;					  // 색칠하면 cnt ++
	}
		
	wasd(now);  // 2,3번 판단


	if (flag == 0)
	{
		point next = now;
		if (now.way == 0)
		{
			next.y = now.y + 1;
			next.x = now.x;
		}
		else if (now.way == 1)
		{
			next.y = now.y;
			next.x = now.x - 1;
		}
		else if (now.way == 2)
		{
			next.y = now.y - 1;
			next.x = now.x;
		}
		else if (now.way == 3)
		{
			next.y = now.y;
			next.x = now.x + 1;
		}
		if (map[next.y][next.x] == 1)
		{
			endplay = 1;
			return;
		}
		else
			func(next);
	}

	if (flag == 1)
	{
		if (now.way == 0)
		{
			now.way = 3;
		}
		else if (now.way == 1)
		{
			now.way = 0;
		}
		else if (now.way == 2)
		{
			now.way = 1;
		}
		else if (now.way == 3)
		{
			now.way = 2;
		}
		point next = now;

		if (now.way == 0)
		{
			next.y = now.y - 1;
			next.x = now.x;
		}
		else if (now.way == 1)
		{
			next.y = now.y;
			next.x = now.x + 1;
		}
		else if (now.way == 2)
		{
			next.y = now.y + 1;
			next.x = now.x;
		}
		else if (now.way == 3)
		{
			next.y = now.y;
			next.x = now.x - 1;
		}
		if (map[next.y][next.x] == 0)
		{
			func(next);
		}
	}

	func(now);
}


int main()
{
	point st;
	cin >> n >> m;
	cin >> st.y >> st.x >> st.way;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
		}
	}
	func(st);
	cout << cnt;

	return 0;
}
