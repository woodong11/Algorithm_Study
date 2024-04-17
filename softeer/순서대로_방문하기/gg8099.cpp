#include <iostream>
#include <vector>

using namespace std;

struct point {
	int y, x;
};

int N, M, cnt;
int map[5][5], dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
vector<point> vec;
void dfs(point now, point ed, int level, int (&visited)[5][5]) {
	if (now.y == ed.y && now.x == ed.x) {
		if (level == M - 1) {
			cnt++;
			return;
		}
		dfs(now, vec[level], level + 1, visited);
	}


	for (int i = 0; i < 4; i++) {
		point next = { 0 };
		next.y = now.y + dy[i];
		next.x = now.x + dx[i];
		if (next.y <= 0 || next.x <= 0 || next.y > N || next.x > N)
			continue; //맵 밖으로 나가면
		if (map[next.y][next.x] == 1)
			continue; //장애물
		if (map[next.y][next.x] == -1 && next.y != ed.y && next.x != ed.x)
			continue; //목적지 리스트에 해당하지만 지금 가야할 목적지가 아닌경우
		if (visited[next.y][next.x] == 1)
			continue; //한번 간곳인경우
		visited[next.y][next.x] = 1;
		dfs(next, ed, level, visited);
		visited[next.y][next.x] = 0;
	}

}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	point st;
	cin >> st.y >> st.x;
	for (int i = 1; i < M; i++) {
		int y, x;
		cin >> y >> x;
		vec.push_back({ y,x });
		map[y][x] = -1;
	}
	int visited[5][5] = { 0, };
	visited[st.y][st.x] = 1;
	dfs(st, vec[0], 0, visited);
	cout << cnt;
	return 0;
}
