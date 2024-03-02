#include <iostream>

using namespace std;

// 시간 줄이기 위해 한 행동
// vector 썼었는데 배열로 바꿈 -> 테케 돌렸을 때 0.1 초 정도 줄어듦.
// N - 1 일 때 temp == 0 이면 templeftSum + 마지막 남은 숫자가 temprightSum 보다 작거나 같을 때
// sum + 1 하고 temprightSum이 한줄인 경우의 수 를 더한 값을 출력하는 방법을 생각했는데
// 오히려 시간 더 늘어남.

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
