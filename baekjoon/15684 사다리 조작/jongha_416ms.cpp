#include <iostream>


using namespace std;


int arr[31][11];
int check[11];
int N, M, H;
int result;



bool dfs(int level) {
	int lxr = 0;

	for (int j = 1; j <= N; j++) {
		lxr = 0;
		for (int i = 1; i <= H; i++) {
			if (j + lxr > N || j + lxr < 0) continue;
			lxr += arr[i][j + lxr];
		}
		if (lxr == 0) {
			check[j] = 1;
		}
		else {
			for (int i = 1; i <= j; i++) {
				check[i] = 0;
			}
			return false;
		}
	}

	return true;
}


int main() {
	cin >> N >> M >> H;

	int x1, x2;

	for (int i = 0; i < M; i++) {
		cin >> x1 >> x2;
		arr[x1][x2] = 1;
		arr[x1][x2 + 1] = -1;
	}


	if (dfs(0)) {
		cout << 0;
		return 0;
	}

	for (int i = 1; i <= H; i++) {
		for (int j = 1; j < N; j++) {
			if (arr[i][j] != 0 || arr[i][j + 1] != 0) continue;
			arr[i][j] = 1;
			arr[i][j + 1] = -1;
			if (dfs(1)) {
				cout << 1;
				return 0;
			}
			arr[i][j] = 0;
			arr[i][j + 1] = 0;

		}
	}

	for (int i = 1; i <= H; i++) {
		for (int j = 1; j < N; j++) {
			if (arr[i][j] != 0 || arr[i][j + 1] != 0) continue;
			arr[i][j] = 1;
			arr[i][j + 1] = -1;
			for (int z = i; z <= H; z++) {
				for (int d = 1; d < N; d++) {
					if (arr[z][d] != 0 || arr[z][d + 1] != 0) continue;
					arr[z][d] = 1;
					arr[z][d + 1] = -1;
					if (dfs(2)) {
						cout << 2;
						return 0;
					}
					arr[z][d] = 0;
					arr[z][d + 1] = 0;
				}
			}
			arr[i][j] = 0;
			arr[i][j + 1] = 0;
		}
	}

	for (int i = 1; i <= H; i++) {
		for (int j = 1; j < N; j++) {
			if (arr[i][j] != 0 || arr[i][j + 1] != 0) continue;
			arr[i][j] = 1;
			arr[i][j + 1] = -1;
			for (int z = i; z <= H; z++) {
				for (int d = 1; d < N; d++) {
					if (arr[z][d] != 0 || arr[z][d + 1] != 0) continue;
					arr[z][d] = 1;
					arr[z][d + 1] = -1;
					for (int z2 = z; z2 <= H; z2++) {
						for (int d2 = 1; d2 < N; d2++) {
							if (arr[z2][d2] != 0 || arr[z2][d2 + 1] != 0) continue;
							arr[z2][d2] = 1;
							arr[z2][d2 + 1] = -1;
							if (dfs(3)) {
								cout << 3;
								return 0;
							}
							arr[z2][d2] = 0;
							arr[z2][d2 + 1] = 0;
						}
					}
					arr[z][d] = 0;
					arr[z][d + 1] = 0;
				}
			}
			arr[i][j] = 0;
			arr[i][j + 1] = 0;
		}
	}
	
	cout << -1;
	return 0;
}
