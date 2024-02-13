#include <iostream>
#include <vector>
#include <queue>
#include <climits>

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

vector<s_dir> boom_dirs = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

void fall_blocks(vector<vector<int>>& map) {
	queue<int> blocks;
	for (int j = 1; j < map[0].size() - 1; j++) {
		int count = 0;
		for (int i = map.size() - 2; i >= 1; i--) {
			if (map[i][j] != 0) {
				blocks.push(map[i][j]);
				map[i][j] = 0;
			}
		}

		for (int location = map.size() - 2; !blocks.empty(); location--) {
			map[location][j] = blocks.front();
			blocks.pop();
		}
	}
}

void break_block(vector<vector<int>> &map, s_pos break_block_pos) {
	int range = map[break_block_pos.y][break_block_pos.x] - 1;
	map[break_block_pos.y][break_block_pos.x] = 0;

	for (s_dir boom_dir : boom_dirs) {
		s_pos break_pos = break_block_pos;
		for (int i = 0; i < range; i++) {
			break_pos = break_pos + boom_dir;
			if (map[break_pos.y][break_pos.x] == -1) break;
			if (map[break_pos.y][break_pos.x] == 0) continue;
			break_block(map, break_pos);
		}
	}
}

void choose_column(vector<vector<int>>& origin_map, int use_ball_num, int ball_num, int &min_remain) {

	if (use_ball_num == ball_num) {
		int remain = 0;
		for (int i = 1; i < origin_map.size() - 1; i++) {
			for (int j = 1; j < origin_map[i].size() - 1; j++) {
				if (origin_map[i][j] != 0) remain++;
			}
		}

		min_remain = min_remain < remain ? min_remain : remain;
		return;
	}

	for (int j = 1; j < origin_map[0].size() - 1; j++) {
		for (int i = 1; i < origin_map.size() - 1; i++) {
			if (origin_map[i][j] > 0) {
				vector<vector<int>> map(origin_map);
				s_pos break_block_pos = { i, j };
				break_block(map, break_block_pos);
				fall_blocks(map);

				choose_column(map, use_ball_num + 1, ball_num, min_remain);
				break;
			}
		}
	}
}



void solve(int test_case) {
	int ball_num, height, width;
	cin >> ball_num >> width >> height;

	vector<vector<int>> map(height + 2, vector<int>(width + 2, -1));

	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) {
			cin >> map[i][j];
		}
	}

	int min_remain = INT_MAX;
	choose_column(map, 0, ball_num, min_remain);

	if (min_remain == INT_MAX) {
		cout << "#" << test_case << " " << 0 << endl;
	} else {
		cout << "#" << test_case << " " << min_remain << endl;
	}
	
}

int main() {
	int test_num;
	cin >> test_num;

	for (int test_case = 1; test_case <= test_num; test_case++) {
		solve(test_case);
	}

	return 0;
}