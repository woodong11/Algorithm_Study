#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef struct {
	int y;
	int x;
}s_pos;

typedef struct {
	int dy;
	int dx;
}s_dir;

s_pos operator+(s_pos &l, s_dir &r) {
	return { l.y + r.dy, l.x + r.dx };
}

typedef struct {
	s_pos pos;
	int cost;
}s_house;

struct cmp {
	bool operator()(s_house &t, s_house &b) {
		return t.cost < b.cost;
	}
};

vector<s_dir> select_dirs1 = { {-1, 0}, {-1, 1}, {0, 1}, {1, 0}, {0, -1}, {-1, -1} };
vector<s_dir> select_dirs2 = { {-1, 0}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1} };

void select_house(vector<vector<int>> &houses, vector<vector<bool>> &selected, s_pos crt_pos, int select_count, int crt_price, int &max_price) {
	if (select_count == 4) {
		if (max_price < crt_price) max_price = crt_price;
		return;
	}

	vector<s_dir>* select_dirs;
	if (crt_pos.x % 2 == 1) {
		select_dirs = &select_dirs1;
	} else {
		select_dirs = &select_dirs2;
	}

	for (s_dir select_dir : *select_dirs) {
		s_pos select_pos = crt_pos + select_dir;
		if (selected[select_pos.y][select_pos.x] || houses[select_pos.y][select_pos.x] == -1) continue;
		selected[select_pos.y][select_pos.x] = true;
		select_house(houses, selected, select_pos, select_count + 1, crt_price + houses[select_pos.y][select_pos.x], max_price);
		selected[select_pos.y][select_pos.x] = false;
	}
}

void solve(int test_case) {
	int height, width;
	cin >> height >> width;

	vector<vector<int>> houses(height + 2, vector<int>(width + 2, -1));
	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) {
			cin >> houses[i][j];
		}
	}

	vector<vector<bool>> selected(height + 2, vector<bool>(width + 2, false));

	int max_price = 0;
	for (int i = 1; i <= height - 1; i++) {
		for (int j = 1; j <= width - 1; j++) {
			s_pos crt_pos = { i, j };
			select_house(houses, selected, crt_pos, 0, 0, max_price);

			vector<s_dir>* select_dirs;
			if (j % 2 == 1) {
				select_dirs = &select_dirs1;
			}
			else {
				select_dirs = &select_dirs2;
			}
			priority_queue<s_house, vector<s_house>, cmp> pq;
			int total_price = houses[i][j];
			for (s_dir select_dir : *select_dirs) {
				s_pos select_pos = crt_pos + select_dir;
				pq.push({select_pos, houses[select_pos.y][select_pos.x] });
			}

			for (int i = 0; i < 3; i++) {
				total_price += pq.top().cost;
				pq.pop();
			}
			if (max_price < total_price) max_price = total_price;
		}
	}

	cout << "#" << test_case << " " << max_price << endl;
}

int main() {
	int test_num;
	cin >> test_num;

	for (int test_case = 1; test_case <= test_num; test_case++) {
		solve(test_case);
	}

	return 0;
}
