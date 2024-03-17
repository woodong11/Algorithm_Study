#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<climits>

using namespace std;


struct Point {
	int y, x, d;

	bool operator<(Point other) const {
		return d > other.d;
	}
};

int n, m, grid[1001][1001], visited[1001][1001];
int ghost_min = 999999;
int dy[4] = { 0, 0, 1, -1 }, dx[4] = { 1, -1, 0, 0 };
priority_queue<Point> pq;
vector<Point> ghost;
Point namwoo;
Point goal;


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	string a; int temp = 0;

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> a;

		for (int j = 0; j < m; j++) {
			if (a[j] == '.') temp = 1;
			else if (a[j] == 'D') {
				goal = { i, j, 0 };
				continue;
			}
			else if (a[j] == 'G') {
				ghost.push_back({ i, j, 0 });
				temp = 999999;
			}
			else if (a[j] == 'N') {
				namwoo = { i, j, 0 };
				temp = 999999;
			}
			else {
				temp = 999999;
			}
			grid[i][j] = temp;
		}
	}

	for (int i = 0; i < ghost.size(); i++) {
		ghost[i].d = abs(goal.x - ghost[i].x) + abs(goal.y - ghost[i].y);
		ghost_min = min(ghost_min, ghost[i].d);
	}

	pq.push(namwoo);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = INT_MAX;
		}
	}
	Point now, next;
	int next_cost = 0;
	visited[namwoo.y][namwoo.x] = 0;

	while (!pq.empty()) {
		now = pq.top();
		pq.pop();

		for (int i = 0; i < 4; i++) {
			next.y = now.y + dy[i];
			next.x = now.x + dx[i];

			if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= m) continue;

			next_cost = grid[next.y][next.x] + now.d;

			if (next_cost >= visited[next.y][next.x]) continue;
			visited[next.y][next.x] = next_cost;
			next.d = next_cost;
			pq.push(next);
		}
	}

	if (ghost_min - 1 <= visited[goal.y][goal.x]) {
		cout << "No";
	}
	else {
		cout << "Yes";
	}


	return 0;
}
