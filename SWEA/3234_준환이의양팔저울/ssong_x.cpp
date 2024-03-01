// (18/21) 시간초과

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include<queue>
#include<cstring>

using namespace std;

int T;
int N;
int W[10];
int visited[10];
int cnt;

void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> W[i];
	}
}

void init() {
	cnt = 0;
	for (int i = 0; i < 10; i++)
	{
		visited[i] = 0;
	}
}

void dfs(int level, int rw, int lw) {
	int right = 0;
	int left = 0;
	if (rw > lw) {
		return;
	}

	if (level == N) {
		// 무게 비교 + 업데이트
		if (rw <= lw) cnt++;
		return;
	}

	for (int chu = 0; chu < N; chu++)
	{
		if (visited[chu] == 1) continue;
		
		for (int i = 0; i < 2; i++)
		{
			if (i == 0) {
				// 오른쪽에 올리기
				right = W[chu];
				left = 0;
			}
			else {
				// 왼쪽에 올리기
				left = W[chu];
				right = 0;
			}

			visited[chu] = 1;
			dfs(level + 1, rw + right, lw + left);
			visited[chu] = 0;
		}
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		int leftW =0, rightW =0;
    
		dfs(0, leftW, rightW);
		
		cout << "#" << tc << " " << cnt<<'\n';
	}
}
