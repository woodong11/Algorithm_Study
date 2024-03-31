#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;

int N, M, H, isPossible;
int MAP[31][11];

void input() {
	cin >> N >> M >> H;
	int a, b;
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b;
		MAP[a][b] = 1; 
		MAP[a][b + 1] = 1;
	}
}

bool check() {
	for (int i = 1; i <= N; i++){
		int col = i;
		int row = 0;
		while (row <= H) {
			if (MAP[row][col] == 1) {
				if (col -1>= 1 && MAP[row][col - 1] == 1)	// 왼쪽으로 가는 경우
					col--;
				else if (col +1 <= N && MAP[row][col + 1] == 1) // 오른쪽으로 가는 경우
					col++;
			}	
			row++;
		}
		if (col != i)
			return false;
	}
	return true;
}

void func(int level, int preRow, int preCol) {

	if (level == 4) {
		if (isPossible != -1) {
			isPossible = -1;
		}
		return;
	}

	if (check() == true) {
		isPossible = level;
		return;
	}

	for (int i = preRow; i <= H-1; i++)
	{
		for (int j = 1; j <= N-1; j++)
		{
			if (MAP[i][j] == 1)
				continue;

			if (j - 1 >= 1 && MAP[i][j - 1] == 1)	// 왼쪽 체크
				continue;
			if (j + 1 <= N && MAP[i][j + 1] == 1)	// 오른쪽 체크
				continue;

			MAP[i][j] = 1;
			MAP[i][j + 1] = 1;
			func(level + 1, i, j);
			MAP[i][j] = 0;
			MAP[i][j + 1] = 0;
		}
	}

}


void solve() {
	isPossible = -1;
	func(0, 1, 1);
	if (isPossible == -1)
		cout << -1;
	else
		cout << isPossible;
}


int main() {
	freopen("sample_input.txt", "r", stdin);
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	input();
	solve();

	return 0;
}
