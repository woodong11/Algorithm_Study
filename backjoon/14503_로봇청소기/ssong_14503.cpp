#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <queue>
using namespace std;

//dfs -> 작동 멈출 때까지

int N, M;
int robotR, robotC, robotD;
int cnt; // 청소 횟수
int map[51][51];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

struct Point {
	int y;
	int x;
	int dir;
};

void input() {
	cin >> N >> M;
	cin >> robotR >> robotC >> robotD;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
		}
	}
}

void bfs(int nr, int nc, int nd) {
	queue<Point> q;
	q.push({ nr,nc,nd });
	Point now;
	Point next;

	while (!q.empty()) {
		now = q.front();
		q.pop();
		if (map[now.y][now.x] == 0) {
			map[now.y][now.x] = -1; // 현재 칸 청소
			cnt++;
		}

		int flag = 0; // 주변 청소할곳 유무 확인

		for (int i = 0; i < 4; i++) // 현재 칸 주변 청소
		{
			// 체킹을 반시계 방향으로
			int checkDir = (now.dir + 3 - i) % 4;
			int ny = now.y + dy[checkDir];
			int nx = now.x + dx[checkDir];
			if (map[ny][nx] == 0) // 청소 x이면 청소(-1)
			{
				map[ny][nx] = -1;
				cnt++;
				flag = 1;
				q.push({ ny, nx,checkDir });
				break;
			}
		}

		if (flag == 1) continue; 
    
    // 청소되지 않은 빈칸이 없는 경우
		int backIdx = (now.dir + 2) % 4;
		next.y = now.y + dy[backIdx];
		next.x = now.x + dx[backIdx];
    
		if (map[next.y][next.x] == 1) return;

		q.push({ next.y, next.x, now.dir });
	}
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	input();
	bfs(robotR, robotC, robotD);
	cout << cnt;
}
