#include <iostream>
#include <vector>

using namespace std;

struct xy {
	int y, x;
};
int N, M, H;
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
			else if (tmp[a][b] == 1) {
				a++;
				b++;
			}
			else if (tmp[a][b] == 2) {
				a++;
				b--;
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
void dfs(int(&tmp)[31][11], int level, int goal, int(&visited)[31][11]) {
	if (num == 1)
		return;
	if (level == goal) {
		num = func(tmp);
		return;
	}
	int tp_map[31][11];
	int tp_visited[31][11];
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			tp_map[i][j] = tmp[i][j];
			tp_visited[i][j] = visited[i][j];
		}
	}
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < H; j++) {
			if (tp_map[j][i] != 0 || tp_map[j][i + 1] != 0 )
				continue;
			
			if (tp_visited[j][i] == 1) {
				continue;
			}
			tp_visited[j][i] = 1;
			tp_map[j][i] = 1;
			tp_map[j][i + 1] = 2;
			dfs(tp_map, level + 1, goal, tp_visited);
			if (num == 1)
				break;
			tp_map[j][i] = 0;
			tp_map[j][i + 1] = 0;
		}
		if (num == 1)
			break;
	}
	if (num == 1)
		return;

}

int main() {
	cin >> N >> M >> H;
	int map[31][11] = { 0, };
	int visited[31][11] = { 0, };
	for (int i = 0; i < M; i++) {
		int from, to;
		cin >> from >> to;
		vec.push_back({ from - 1 ,to - 1 });
		map[from - 1][to - 1] = 1;
		vec.push_back({ from - 1, to });
		map[from - 1][to] = 2;
	}
	int result = func(map);
	if (result == 1) {
		cout << 0;
	}
	else {
		for (int i = 1; i <= 3; i++) {
			dfs(map, 0, i, visited);
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
