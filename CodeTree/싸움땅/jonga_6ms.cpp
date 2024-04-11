#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Grid{
	int parti_num;
	priority_queue<int, vector<int>, less<int>> pq;
};

struct Participant {
	int y, x, d, s;
};

struct Point {
	int y, x;
};

Grid grid[20][20];
Participant participant[30];
int score[30];
int p_gun[30];
int dy[4] = { -1, 0, 1, 0 }, dx[4] = { 0, 1, 0, -1 };
int n, m, k;

void changeGun(int i) {
	if (!grid[participant[i].y][participant[i].x].pq.empty()) {
		int tmp_gun = grid[participant[i].y][participant[i].x].pq.top();
		grid[participant[i].y][participant[i].x].pq.pop();

		if (tmp_gun > p_gun[i]) {
			int temp = p_gun[i];
			p_gun[i] = tmp_gun;

			if (temp != 0) {
				grid[participant[i].y][participant[i].x].pq.push(temp);
			}
		}
		else {
			grid[participant[i].y][participant[i].x].pq.push(tmp_gun);
		}
	}
}

void lose(int num) {
	if (p_gun[num] != 0) {
		grid[participant[num].y][participant[num].x].pq.push(p_gun[num]);
		p_gun[num] = 0;
	}

	grid[participant[num].y][participant[num].x].parti_num = -1;

	Point next;
	while (true) {
		next = { participant[num].y + dy[participant[num].d], participant[num].x + dx[participant[num].d]};

		if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n || grid[next.y][next.x].parti_num != -1) {
			participant[num].d = (participant[num].d + 1) % 4;
		}
		else {
			break;
		}
	}

	participant[num].y = next.y;
	participant[num].x = next.x;
	grid[participant[num].y][participant[num].x].parti_num = num;
	changeGun(num);
}

void battle(int num1, int num2) {
	int  a = participant[num1].s + p_gun[num1] - (participant[num2].s + p_gun[num2]);
	if (a > 0) {
		lose(num2);
		grid[participant[num1].y][participant[num1].x].parti_num = num1;
		changeGun(num1);
		score[num1] += a;
	}
	else if (a < 0) {
		lose(num1);
		grid[participant[num2].y][participant[num2].x].parti_num = num2;
		changeGun(num2);
		score[num2] -= a;
	}
	else {
		if (participant[num1].s > participant[num2].s) {
			lose(num2);
			grid[participant[num1].y][participant[num1].x].parti_num = num1;
			changeGun(num1);
		}
		else {
			lose(num1);
			grid[participant[num1].y][participant[num1].x].parti_num = num2;
			changeGun(num2);
		}
	}
}

void move() {
	for (int i = 0; i < m; i++) {
		Point next;
		grid[participant[i].y][participant[i].x].parti_num = -1;
		next = { participant[i].y, participant[i].x };

		next.y += dy[participant[i].d];
		next.x += dx[participant[i].d];

		if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n) {
			participant[i].d = (participant[i].d + 2) % 4;
			participant[i].y += dy[participant[i].d];
			participant[i].x += dx[participant[i].d];
		}
		else {
			participant[i].y = next.y;
			participant[i].x = next.x;
		}

		if (grid[participant[i].y][participant[i].x].parti_num != -1) {
			battle(i, grid[participant[i].y][participant[i].x].parti_num);
		}
		else {
			grid[participant[i].y][participant[i].x].parti_num = i;
			changeGun(i);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;

	int a = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a;
			grid[i][j].parti_num = -1;
			if (a == 0) continue;
			grid[i][j].pq.push(a);
		}
	}

	for (int i = 0; i < m; i++) {
		cin >> participant[i].y >> participant[i].x >> participant[i].d >> participant[i].s;
		participant[i].y--;
		participant[i].x--;
		grid[participant[i].y][participant[i].x].parti_num = i;
	}

	for (int i = 0; i < k; i++) {
		move();
	}

	for (int i = 0; i < m; i++) {
		cout << score[i] << " ";
	}

	return 0;
}
