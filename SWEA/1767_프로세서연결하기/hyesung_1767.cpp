#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pos;
typedef pair<int, int> dir;

vector<dir> wire_dirs = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

pair<int, int> operator+(pair<int, int>& l, pair<int, int>& r) {
	return { l.first + r.first, l.second + r.second };
}

void select_core(vector<vector<int>>& board, vector<pos>& cores, int core_num, int connected_core_count, int& connected_core_count_max, int length, int& min_length) {
	if (length > min_length) {
		if (connected_core_count_max >= connected_core_count + cores.size() - core_num) {
			return;
		}
	}

	if (core_num == cores.size()) {
		if (connected_core_count > connected_core_count_max) {
			connected_core_count_max = connected_core_count;
			min_length = length;
		} else if (connected_core_count == connected_core_count_max) {
			min_length = min(min_length, length);
		}
		return;
	}

	pos core_pos = cores[core_num];

	for (dir wire_dir : wire_dirs) {
		queue<pos> wired;
		pos next_pos = core_pos + wire_dir;

		while (board[next_pos.first][next_pos.second] == 0) {
			wired.push(next_pos);
			board[next_pos.first][next_pos.second] = 2;
			next_pos = next_pos + wire_dir;
		}

		if (board[next_pos.first][next_pos.second] == -1) {
			select_core(board, cores, core_num + 1, connected_core_count + 1, connected_core_count_max, length + wired.size(), min_length);
		}

		while (!wired.empty()) {
			pos wire_pos = wired.front();
			wired.pop();
			board[wire_pos.first][wire_pos.second] = 0;
		}
	}

	select_core(board, cores, core_num + 1, connected_core_count, connected_core_count_max, length, min_length);
}

void solve(int test_case) {
	int size;
	cin >> size;

	vector<vector<int>> board(size + 2, vector<int>(size + 2, -1));

	vector<pos> cores;

	int count = 0;
	for (int i = 1; i <= size; i++) {
		for (int j = 1; j <= size; j++) {
			cin >> board[i][j];

			if (board[i][j] == 1) {
				if (i == 1 || i == size || j == 1 || j == size) continue;
				cores.push_back({ i, j });
			}
		}
	}

	int connected_core_count_max = 0;
	int min_length = INT_MAX;
	select_core(board, cores, 0, 0, connected_core_count_max, 0, min_length);

	if (min_length != INT_MAX) cout << "#" << test_case << " " << min_length << endl;
	else cout << "#" << test_case << " " << 0 << endl;
}

int main() {

	int test_num;
	cin >> test_num;

	for (int test_case = 1; test_case <= test_num; test_case++) {
		solve(test_case);
	}

	return 0;
}