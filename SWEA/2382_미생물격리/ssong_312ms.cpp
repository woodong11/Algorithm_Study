#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>

using namespace std;

// N*N 정사각형 모양의 셀
// 가장 바깥자리에는 특수 약품 칠해져있음
// 
// 약품 칠해진 셀에 도착 시
// >> 군집 내 미생물의 절반 사망(살아남은 미생물 수 = 2로 나눈 후 소수점 이하 버린 값)
// >> 이동 방향 반대로 바뀜
// >>> 미생물 수 == 0 -> 군집 사라짐
// 
// 이동 후 두개 이상의 군집이 한 셀에 모이는 경우
// >> 군집 합쳐짐 (두 집단의 미생물 합)
// >> 이동방향: 미생물 수가 많은 군집의 이동방향
// 
// 상: 1, 하: 2, 좌: 3, 우: 4
// 
//세로 위치, 가로 위치, 미생물 수, 이동 방향 순

int T;
int N, M, K; // 셀의 개수, 격리 시간, 미생물 군집 수
int m, d;
int total;

int map[101][101][3]; // 각각 미생물 수, 방향, 겹치는 경우 max 미생물 수
int aftermap[101][101][3];

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

struct Point {
	int y, x, t;
};

queue<Point>q; // 이동할 미생물들 담기

void input() {
	cin >> N >> M >> K;
	int a, b, c, d, e = 0;
	for (int i = 0; i < K; i++)
	{
		cin >> a >> b >> c >> d;
		// 편의로 방향 num 전환
		if (d == 1) e = 0;
		else if (d == 4) e = 1;
		else if (d == 2) e = 2;
		else e = 3;
		map[a][b][0] = c; // 군집 수
		map[a][b][1] = e; // 방향 저장
		q.push({ a, b, 0 }); // 시간에 따른 이동 위함
	}
}

void init() {
	total = 0;
	memset(aftermap, 0, sizeof(aftermap));
	memset(map, 0, sizeof(map));
}

void process() {
	Point now;
	while (!q.empty()) {
		int qsize = q.size();
		memset(aftermap, 0, sizeof(aftermap));

		for (int i = 0; i < qsize; i++)
		{
			now = q.front();
			q.pop();
			m = map[now.y][now.x][0]; // 현재 군집 수
			d = map[now.y][now.x][1]; // 현재 방향

			if (now.t == M) {
				total += map[now.y][now.x][0];
				continue;
			}

			int ny = now.y + dy[d];
			int nx = now.x + dx[d];

			// 약품
			if (ny == 0 || nx == 0 || ny == N - 1 || nx == N - 1) {
				m /= 2;
				if (m == 0) continue;
				d = (d + 2) % 4;
			}

			// 아무것도 없을 때
			if (aftermap[ny][nx][0] == 0) {
				aftermap[ny][nx][0] = m;
				aftermap[ny][nx][1] = d;
				aftermap[ny][nx][2] = m;
				q.push({ ny, nx, now.t + 1 });
			}
			// 겹치는 경우
			else {
				// 현재 군집 수가 클때 현재 군집의 방향으로
				if (aftermap[ny][nx][2] < m) {
					aftermap[ny][nx][2] = m;
					aftermap[ny][nx][1] = d;
				}
				aftermap[ny][nx][0] += m;
			}
		}
		// 현재 맵 상태 업데이트
		memcpy(map, aftermap, sizeof(map));
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		process();
		cout << "#" << tc << " " << total << '\n';
	}
	return 0;
}
