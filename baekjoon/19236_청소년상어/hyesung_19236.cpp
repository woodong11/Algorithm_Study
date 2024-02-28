#include <iostream>
#include <vector>

using namespace std;

typedef struct {
	int y;
	int x;
}s_pos;

typedef struct {
	int dy;
	int dx;
}s_dir;

typedef struct {
	s_pos pos;
	int orient;
}s_fish;

s_pos operator+(s_pos &l, s_dir &r) {
	return { l.y + r.dy, l.x + r.dx };
}

bool operator==(s_pos &l, s_pos &r) {
	return l.y == r.y && l.x == r.x;
}

vector<s_dir> move_dirs = { {-1, -1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1} };

int total_score;
int max_score;

void move(vector<vector<int>>, vector<s_fish>, s_pos, int);
void eat(vector<vector<int>>&, vector<s_fish>, s_pos);

int main() {
	vector<vector<int>> map(6, vector<int>(6, -1));
	vector<s_fish> fish_list(17);

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			cin >> map[i][j];
			cin >> fish_list[map[i][j]].orient;
			fish_list[map[i][j]].pos = { i, j };
		}
	}

	eat(map, fish_list, { 1, 1 });

	cout << max_score;
}

void eat(vector<vector<int>>& map, vector<s_fish> fish_list, s_pos pos) {
	int fish_num = map[pos.y][pos.x];
	int dir = fish_list[fish_num].orient;

	total_score += fish_num;
	if (total_score > max_score) max_score = total_score;

	fish_list[fish_num].orient = 0;
	map[pos.y][pos.x] = 0;

	move(map, fish_list, pos, dir);

	map[pos.y][pos.x] = fish_num;
	fish_list[fish_num].orient = dir;

	total_score -= fish_num;
}

void move(vector<vector<int>> map, vector<s_fish> fish_list, s_pos shark_pos, int dir) {
	for (int i = 1; i < fish_list.size(); i++) {
		s_fish fish = fish_list[i];
		if (fish.orient == 0) continue;

		s_pos crt_pos = fish.pos;
		s_pos next_pos = crt_pos + move_dirs[fish.orient];

		while (map[next_pos.y][next_pos.x] == -1 || next_pos == shark_pos) {
			fish.orient = (fish.orient + 1) % 9;
			if (fish.orient == 0) fish.orient++;
			next_pos = crt_pos + move_dirs[fish.orient];
		}
		fish_list[i].orient = fish.orient;

		int fish_num2 = map[next_pos.y][next_pos.x];

		fish_list[i].pos = next_pos;
		fish_list[fish_num2].pos = crt_pos;

		map[next_pos.y][next_pos.x] = i;
		map[crt_pos.y][crt_pos.x] = fish_num2;
	}

	s_pos next_pos = shark_pos;
	for (int i = 0; i < 3; i++) {
		next_pos = next_pos + move_dirs[dir];
		if (map[next_pos.y][next_pos.x] == 0) continue;
		if (map[next_pos.y][next_pos.x] == -1) break;
		eat(map, fish_list, next_pos);
	}
}
