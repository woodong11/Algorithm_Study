#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include<queue>
#include<cstring>

using namespace std;

struct Point {
	int y, x, heart, activation, inputT;
};

int T;
int N, M, K;
int map[1000][1000];
int dy[] = { -1, 0, 1, 0 };
int dx[] = { 0, 1, 0, -1 };
int cnt;

struct cmp {
	bool operator()(Point a, Point b) {
		if (a.activation == b.activation) {
			return a.heart < b.heart;
		}
		return a.activation < b.activation;
	}
};

priority_queue<Point, vector<Point>, cmp> pq;
queue<Point>tempq; // 번식하는 미생물 저장 용도

void init() {
	cnt = 0;
	while (!pq.empty()) pq.pop();
	while (!tempq.empty()) tempq.pop();
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			map[i][j] = 0;
		}
	}
}

void input() {
	cin >> N >> M >> K; // 세로, 가로, 배양시간
	int a;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> a;
			map[i+450][j + 450] = a;
			if (a == 0)continue;
			pq.push({ i + 450, j + 450, a, 0, 0 });
		}
	}
}

void moveQ() {
	int tempqsize = tempq.size();
	Point move;
	for (int i = 0; i < tempqsize; i++)
	{
		move = tempq.front();
		tempq.pop();
		pq.push(move);
	}
}

void process() {
	int time = 0;
	int ny, nx = 0;
	Point now;

	while (!pq.empty()) {
		// time == K이면 break;
		if (time == K) break;
		time++;

		int cellsize = pq.size();
		for (int i = 0; i < cellsize; i++)
		{
			now = pq.top();
			pq.pop();

			// 비활성 상태일때>> continue
			//활성화 시켜주고 continue
			if (now.activation == 0) {
				if (now.inputT + now.heart == time) {
					now.activation = 1;
				}
				
				tempq.push(now);
				continue;
			}
			else if (now.activation == -1) break;

			//4방향대로 번식 >> map에 visited 체크
			for (int i = 0; i < 4; i++)
			{
				ny = now.y + dy[i];
				nx = now.x + dx[i];

				if (map[ny][nx] != 0)continue;

				map[ny][nx] = now.heart;
				tempq.push({ ny, nx, now.heart, 0, time });
			}

			if (now.inputT + 2 * now.heart == time) {
				now.activation = -1;
			}
			// 원본 세포 push
			tempq.push(now);

		}

		// tempq에 있는거 pq에 넣어두기
		moveQ();
	}
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		input();
		process();
		Point check;
		while (1) {
			check =  pq.top();
			pq.pop();
			if (check.activation == -1) break;
			cnt++;
		}
		
		cout << "#" << tc << " " << cnt<<'\n';
	}
	return 0;

}
