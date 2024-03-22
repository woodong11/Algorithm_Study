#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int MAP[9][9];
int visited[9][9];
int N, M;
int emptyCnt;
int answer = 0;
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

struct Node {
	int y;
	int x;
};
vector <Node> startPoints;

void input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAP[i][j];
			if (MAP[i][j] == 0)
				emptyCnt++;

			else if (MAP[i][j] == 2) {
				startPoints.push_back({ i, j });
			}
		}
	}

	emptyCnt = emptyCnt - 3;	// 짜피 벽 3개 세울꺼니깐

}

// BFS로 바이러스 퍼뜨리기
void spread() {
	int curEmptyCnt = emptyCnt;
	for (auto startPoint : startPoints){

		queue <Node> q;
		q.push({ startPoint.y, startPoint.x });

		while (!q.empty()){
			Node now = q.front();
			q.pop();

			for (int k = 0; k < 4; k++)
			{
				int ny = now.y + dy[k];
				int nx = now.x + dx[k];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M)
					continue;

				if (MAP[ny][nx] != 0)
					continue;

				MAP[ny][nx] = 2;
				curEmptyCnt--;
				q.push({ ny, nx });
			}
		}
	}
	answer = max(answer, curEmptyCnt);
}


void func(int level, int preRow, int preCol) {

	// 종료조건
	if (level == 3) {
		int backupMAP[9][9];
		memcpy(backupMAP, MAP, sizeof(MAP));
		spread();
		memcpy(MAP, backupMAP, sizeof(MAP));
		return;
	}

	// 탐색
	for (int i = preRow; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (MAP[i][j] != 0)
				continue;

			if (visited[i][j] == 1)
				continue;

			MAP[i][j] = 1;
			visited[i][j] = 1;
			func(level + 1,i ,j);
			MAP[i][j] = 0;
			visited[i][j] = 0;
		}
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	input();
	func(0, 0, 0);

	cout << answer;

	return 0;
}
