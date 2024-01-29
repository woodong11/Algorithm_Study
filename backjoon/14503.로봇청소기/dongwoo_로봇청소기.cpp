#include <iostream>
using namespace std;

int N, M;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int MAP[50][50];
int cnt;
int curR, curC, direction;

// 반시계 방향으로 value만큼 방향 변환 - 만약 시계방향이었다면 간단하게 direction = (direction + value) % 4 해도 된다.
int directionChange(int direction, int value) {
	int temp = direction - value;
	if (temp < 0) temp += 4;
	return temp;
}

// 주변 4칸 중 먼지 찾기 함수
bool dustFind(int row, int col) {
	for (int k = 0; k < 4; k++)
	{
		int newRow = row + dx[k];
		int newCol = col + dy[k];

		if (MAP[newRow][newCol] == 0) {
			return true;
		}
	}
	return false;
}

int main() {

	cin >> N >> M;
	cin >> curR >> curC >> direction;
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAP[i][j];
		}
	}

	// 청소 안 된 칸: 0, 벽: 1 청소된 칸: 2
	while (1){

		// 1번: 현재칸 청소
		if (MAP[curR][curC] == 0) {
			MAP[curR][curC] = 2;
			cnt++;
		}

		// 3번
		if (dustFind(curR, curC)) {
			direction = directionChange(direction, 1);
			int tempRow = curR + dx[direction];
			int tempCol = curC + dy[direction];
			
			if (MAP[tempRow][tempCol] == 0) {
				curR = tempRow;
				curC = tempCol;
			}
		
		}

		// 2번
		else {
			int tempDirection = directionChange(direction, 2);
			int tempRow = curR + dx[tempDirection];
			int tempCol = curC + dy[tempDirection];
			if (MAP[tempRow][tempCol] != 1) {
				curR = tempRow;
				curC = tempCol;
			}

			else {
				break;		// 작동 종료
			}
		
		}
	}

	cout << cnt;

}