#include <iostream>

using namespace std;

int grid[9];
int T, N, sum;
int visited[9];

void init() {
	sum = 0;
}

void solve(int temprightSum, int templeftSum, int depth) {
	if (depth == N) {
		sum++;
		return;
	}

	for (int i = 0; i < N; i++) {
		if (visited[i] == 1) continue;

		visited[i] = 1;
		if (templeftSum < temprightSum + grid[i]) {
			solve(temprightSum, templeftSum + grid[i], depth + 1);
		}
		else {
			solve(temprightSum + grid[i], templeftSum, depth + 1);
			solve(temprightSum, templeftSum + grid[i], depth + 1);
		}
		visited[i] = 0;
	}
}

int main() {
	int a;

	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		init();

		cin >> N;

		for (int i = 0; i < N; i++) {
			cin >> grid[i];
		}

		solve(0, 0, 0);

		cout << "#" << tc << " " << sum << "\n";
	}






	return 0;
}
