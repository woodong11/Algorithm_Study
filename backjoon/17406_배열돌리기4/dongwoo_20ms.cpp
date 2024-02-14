#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct rotateInfo {	// 회전 중앙 행, 중앙 열, 크기
	int r;
	int c;
	int s;
};

int N, M, K;
int answer = 21e8;
int A[51][51];
int backupA[51][51];
rotateInfo rotateInfos[7];
int visited[7];
int dy[4] = { 1, 0, -1, 0};		// 하우상좌
int dx[4] = { 0, 1, 0, -1};

int path[7];

int minValue() {
	int minVal = 21e8;
	for (int i = 0; i < N; i++)
	{
		int sum = 0;
		for (int j = 0; j < M; j++)
		{
			sum += A[i][j];
		}
		minVal = min(minVal, sum);
	}
	
	return minVal;
}

// rotateInfo 배열 중 해당 번호번 실행하는 함수
void rotate(int num) {
	rotateInfo now = rotateInfos[num];

	for (int i = 1; i <= now.s; i++)
	{
		// 시작하는 좌상단 좌표
		int curY = now.r - i;
		int curX = now.c - i;

		int temp = A[curY][curX];
		int direction = 0;
		
		while (1) {
			int ny = curY + dy[direction];
			int nx = curX + dx[direction];
			
			// 벗어나면 방향 바꾸기
			if (ny < now.r - i || nx < now.c - i || ny > now.r + i || nx > now.c + i) {
				direction += 1;
				ny = curY + dy[direction];	
				nx = curX + dx[direction];
			}

			if (ny == now.r - i && nx == now.c - i)		// 시작위치에 돌아오면 break
				break;

			A[curY][curX] = A[ny][nx];
			curY = ny;
			curX = nx;

		}
		A[now.r - i][now.c - i + 1] = temp;		// 맨 마지막 복구
	}
}

// 왜 순열로 할때만 풀리는지?
// 왜 memcpy를 먼저 해야 답이 맞는걸까? 
void func(int level) {
	
	if (level == K) {
		memcpy(A, backupA, sizeof(A));
		for (int i = 0; i < K; i++)
		{
			rotate(path[i]);
		}
		answer = min(answer, minValue());
		return;
	}

	for (int i = 0; i < K; i++)
	{
		if (visited[i] == 1)
			continue;

		visited[i] = 1;
		path[level] = i;
		rotate(i);
		func(level + 1);
		visited[i] = 0;
	}
}

int main() {
  
	// 입력부
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> A[i][j];
			backupA[i][j] = A[i][j];
		}
	}
	for (int i = 0; i < K; i++)
	{
		int r, c, s;
		cin >> r >> c >> s;
		rotateInfos[i] = { r-1, c-1, s };
	}

	// 수행부
	func(0);
	cout << answer;

	return 0;
}
