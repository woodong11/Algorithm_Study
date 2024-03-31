#include <iostream>
#include <vector>

using namespace std;

struct xy {
	int y, x;
};
int N, M, H;
int visited[31][11];
vector<xy> vec;
int num;

int func(int(&tmp)[31][11]) {
	int flag = 1;
	for (int i = 0; i < N; i++) {
		int a = 0, b = i;
		while (1) {
			if (tmp[a][b] == 0) {
				a++;
			}
			else {
				int tmp_b_mi = b - 1;
				int tmp_b_pl = b + 1;
				if (tmp_b_mi >= 0 && tmp[a][tmp_b_mi] == 1){
					a++;
					b--;
				}
				else if (tmp_b_pl < N && tmp[a][tmp_b_pl] == 1){
					a++;
					b++;
				}
			}
			if (a == H) {
				if (i == b)
					break;
				else if (i != b) {
					flag = 0;
					break;
				}
			}
		}
		if (flag == 0)
			break;
	}
	return flag;
}
void dfs(int(&tmp)[31][11], int level, int goal) {
	if (num == 1)
		return;
	if (level == goal) {
		num = func(tmp);
		return;
	}
	int tp_map[31][11];
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			tp_map[i][j] = tmp[i][j];
		}
	}
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < H; j++) {
			if (tp_map[i][j] == 1)
				continue;
			if (visited[i][j] == 1) {
				continue;
			}
			visited[i][j] = 1;
			tp_map[i][j] = 1;
			tp_map[i][j + 1] = 1;
			dfs(tp_map, level + 1, goal);
			tp_map[i][j] = 0;
			tp_map[i][j + 1] = 0;
		}
	}

}

int main() {
	cin >> N >> M >> H;
	int map[31][11] = { 0, };
	for (int i = 0; i < M; i++) {
		int from, to;
		cin >> from >> to;
		vec.push_back({ from,to });
		vec.push_back({ from, to + 1 });
	}
	for (int i = 0; i < vec.size(); i++) {
		map[vec[i].y][vec[i].x] = 1;
	}
	int result = func(map);
	if (result == 1) {
		cout << 0;
	}
	else {
		for (int i = 1; i <= 3; i++) {
			dfs(map, 0, i);
			if (num == 1) {
				cout << i;
				result = num;
				break;
			}
		}
	}

	if (result == 0) {
		cout << -1;
	}

	return 0;
}
