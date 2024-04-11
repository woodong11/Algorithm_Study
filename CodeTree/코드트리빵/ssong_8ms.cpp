// 으아악 종료조건은 앞에!!!종료조건은 앞에!!!종료조건은 앞에!!!종료조건은 앞에!!!종료조건은 앞에!!!!!!!!@@@@@
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int n, m; // 격자 크기, 사람 수
int map[16][16]; // 편의점(2), 베캠 위치(1), 빈 곳(0) >> 못 가는곳 추후 -1로 업데이트?
int visited_map[16][16]; // 갈 수 있는지 판단?
int ans;

int arrive[31] = { 0, };
int dy[4] = { -1, 0, 0, 1 };
int dx[4] = { 0, -1, 1, 0 };

struct pos {
	int y, x;
};

struct pos_wroute {
	int y, x;
	vector<pos> route;
};

struct pos_l {
	int y, x, level;
};

vector<pos_wroute> cu; // 편의점 위치
vector<pos> pp; // 현재 사람 위치
vector<pos> bc_cu; // 각 편의점과 가까운 베캠 위치

void input() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}
	int a, b;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		map[a - 1][b - 1] = 2;
		cu.push_back({ a - 1, b - 1 });
	}
}


pos find_basecamp(pos_l target_cu) {
	
	queue<pos_l> q;
	q.push(target_cu);
	int ny, nx, nl = 0;
	pos_l now_cu;
	pos_l target_bc = target_cu;
	int find_flag = 0;
	int visit_qmap[16][16] = { 0, };

	while (!q.empty()) {
		now_cu = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			ny = now_cu.y + dy[i];
			nx = now_cu.x + dx[i];
			nl = now_cu.level + 1; // 몇 번 움직였는지
			
			if (find_flag == 1 && target_bc.level < nl) {
				return { target_bc.y, target_bc.x };
			}
			else if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			else if (visit_qmap[ny][nx] == 1 || visited_map[ny][nx] == 1)continue;
			else if (ny == target_cu.y && nx == target_cu.x) continue;

			else if (map[ny][nx] == 1) {
				if (find_flag == 1) { // 이미 찾았을 경우
					if (ny < target_bc.y) {
						target_bc = { ny, nx, nl };
						continue;
					}
					else if (ny == target_bc.y) {
						if (nx < target_bc.x) {
							target_bc = { ny, nx, nl };
							continue;
						}
						continue;
					}
					continue;
				}
				// 처음 찾을 경우
				target_bc = { ny, nx, nl };
				find_flag = 1;
				continue;
			}
			visit_qmap[ny][nx] = 1;
			q.push({ ny, nx, nl });
		}
	}
	return { target_bc.y, target_bc.x };
}

// 다음으로 이동할 위치 return o
pos find_minRoute(pos startP, pos_wroute endP) {
	int ny, nx;
	int visit_qmap[16][16] = { 0, };
	pos_wroute nowP;
	queue<pos_wroute> q;
	vector<pos> routeP;
	q.push({ startP.y, startP.x });

	while (!q.empty()) {
		nowP = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			ny = nowP.y + dy[i];
			nx = nowP.x + dx[i];

			if (ny == endP.y && nx == endP.x) {
				nowP.route.push_back({ nowP.y, nowP.x });
				if (nowP.route.size() == 1) {
					return { endP.y, endP.x };
				}
				return nowP.route[1];
				// 편의점 도착!!
			}
			else if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			else if (visited_map[ny][nx] == 1 || visit_qmap[ny][nx] == 1)continue;

			visit_qmap[ny][nx] = 1;
			routeP = nowP.route;
			routeP.push_back({ nowP.y, nowP.x });
			q.push({ ny, nx, routeP });
		}
	}
}

int process() {

	pos_l now_cu = { 0, };
	pos now_bc = { 0, };
	int cnt_app = 0;

	// t = 0초부터 시작 >> 결과에서 +1초 해주기
	for (int t = 0; t < 1000; t++)
	{
		//cnt_app = 0;
		if (cnt_app == m) return t;

		for (int i = 0; i < pp.size(); i++) {
			if (arrive[i] == 1) continue;
			// 현재 사람이 이동할 다음 위치 find
			pp[i] = find_minRoute(pp[i], cu[i]);
		}

		// 해당 칸 이동 불가 체크
		for (int i = 0; i < pp.size(); i++) {
			if (arrive[i] == 1) continue;
			else if (pp[i].y == cu[i].y && pp[i].x == cu[i].x) {
				visited_map[pp[i].y][pp[i].x] = 1;
				arrive[i] = 1;
				cnt_app += 1;
			}
		}

		if (t < m) {
			// 편의점과 가장 가까운 베이스캠프 위치 넣기
			now_cu = { cu[t].y, cu[t].x, 0 };
			now_bc = find_basecamp(now_cu);
			visited_map[now_bc.y][now_bc.x] = 1;
			pp.push_back(now_bc);
		}
	}
}
int main() {
	freopen("sample_input.txt", "r", stdin);
	input();
	ans = process();
	cout << ans << '\n';
	return 0;
}
