#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

struct attack {
	int num, atk, recent_atk, recent_atked, r_p_c, col, row;
};

struct Point {
	int y, x;
};

struct LaserPoint {
	int y, x;
	vector<Point> v;
};

bool compare_attack(attack *a, attack *b) {
	if (a->atk != b->atk) return a->atk < b->atk;
	else if (a->recent_atk != b->recent_atk) return a->recent_atk > b->recent_atk;
	else if (a->r_p_c != b->r_p_c) return a->r_p_c > b->r_p_c;
	else return a->col > b->col;
}

bool compare_attacked(attack *a, attack *b) {
	if (a->atk != b->atk) return a->atk > b->atk;
	else if (a->recent_atk != b->recent_atk) return a->recent_atk < b->recent_atk;
	else if (a->r_p_c != b->r_p_c) return a->r_p_c < b->r_p_c;
	else return a->col < b->col;
}

int N, M, K, zeronum = 0;
attack grid[10][10];
int visited[11][11], dy[4] = { 0, 1, 0, -1 }, dx[4] = { 1, 0, -1, 0 };
int dy_8[8] = { 0, 0, 1, 1, 1, -1, -1, -1 }, dx_8[8] = { 1, -1, 1, -1, 0, 1, -1, 0 };
vector<attack *> v;
queue<LaserPoint> q;

void printf(int time) {
	cout << "time : " << time << "\n";

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << grid[i][j].atk << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void process(vector<Point> v, int power, int time) {
	int h_power = power * 0.5;
	for (int i = 1; i < v.size() - 1; i++) {
		grid[v[i].y][v[i].x].atk -= h_power;
		grid[v[i].y][v[i].x].recent_atked = time;
		if (grid[v[i].y][v[i].x].atk <= 0) {
			zeronum++;
		}
	}

	Point end = v[v.size() - 1];
	grid[end.y][end.x].atk -= power;
	grid[end.y][end.x].recent_atked = time;
	if (grid[end.y][end.x].atk <= 0) zeronum++;
}

bool laser_attack_valid(Point start, Point end, int power, int time) {
	LaserPoint now = { start.y, start.x, vector<Point>() };
	now.v.push_back({ now.y, now.x });

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visited[i][j] = 0;
		}
	}

	q.push(now);
	visited[now.y][now.x] = 1;

	while (!q.empty()) {
		LaserPoint now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			LaserPoint next;
			next = { now.y + dy[i], now.x + dx[i], now.v };

			if (next.y < 0) next.y = N - 1;
			else if (next.y >= N) next.y = 0;
			if (next.x < 0) next.x = M - 1;
			else if (next.x >= M) next.x = 0;

			next.v.push_back({ next.y, next.x });
			if (grid[next.y][next.x].atk <= 0) continue;
			if (visited[next.y][next.x] == 1) continue;

			visited[next.y][next.x] = 1;

			if (next.y == end.y && next.x == end.x) {
				q = queue<LaserPoint>();
				process(next.v, power, time);
				return true;
			}

			q.push(next);
		}
	}

	q = queue<LaserPoint>();
	return false;
}

void bomb_attack(Point start, Point target, int power, int time) {
	int h_power = power * 0.5;

	for (int i = 0; i < 8; i++) {
		Point next = target;
		next.y += dy_8[i];
		next.x += dx_8[i];

		if (next.y >= N) next.y = 0;
		else if (next.y < 0) next.y = N - 1;
		if (next.x >= M) next.x = 0;
		else if (next.x < 0) next.x = M - 1;

		if (grid[next.y][next.x].atk <= 0 || (next.y == start.y && next.x == start.x)) continue;

		grid[next.y][next.x].atk -= h_power;
		if (grid[next.y][next.x].atk <= 0) zeronum++;
		grid[next.y][next.x].recent_atked = time;
	}

	grid[target.y][target.x].atk -= power;
	if (grid[target.y][target.x].atk <= 0) zeronum++;
	grid[target.y][target.x].recent_atked = time;
}

void solve() {
	for (int i = 1; i <= K; i++) {
		sort(v.begin(), v.end(), compare_attack);

		v[zeronum]->atk += (N + M);
		v[zeronum]->recent_atk = i;

		Point start = { v[zeronum]->num / M, v[zeronum]->num % M };
		Point end = { v[v.size() - 1]->num / M, v[v.size() - 1]->num % M };


		if (laser_attack_valid(start, end, grid[start.y][start.x].atk, i)) {
			for (int z = 0; z < N; z++) {
				for (int j = 0; j < M; j++) {
					if (grid[z][j].atk <= 0 || grid[z][j].recent_atked == i || grid[z][j].recent_atk == i) continue;
					grid[z][j].atk++;
				}
			}

			if (zeronum == N * M - 1) break;
			continue;
		}
		else {
			bomb_attack(start, end, grid[start.y][start.x].atk, i);
		}

		for (int z = 0; z < N; z++) {
			for (int j = 0; j < M; j++) {
				if (grid[z][j].atk <= 0 || grid[z][j].recent_atked == i || grid[z][j].recent_atk == i) continue;
				grid[z][j].atk++;
			}
		}

		if (zeronum == N * M - 1) break;
	}

	int max_v = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (grid[i][j].atk <= 0) continue;
			max_v = max(max_v, grid[i][j].atk);
		}
	}

	cout << max_v;
}

int main() {
	cin >> N >> M >> K;

	int a, i_j;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> a;
			if (a == 0) {
				zeronum++;
				continue;
			}

			i_j = i * M + j;
			grid[i][j] = { i_j, a, 0, 0, i + j, j, i };
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			v.push_back(&grid[i][j]);
		}
	}

	solve();

	return 0;
}
