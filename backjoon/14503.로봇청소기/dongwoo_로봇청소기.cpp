#include <iostream>
using namespace std;

int N, M;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int MAP[50][50];
int cnt;
int curR, curC, direction;

// �ݽð� �������� value��ŭ ���� ��ȯ - ���� �ð�����̾��ٸ� �����ϰ� direction = (direction + value) % 4 �ص� �ȴ�.
int directionChange(int direction, int value) {
	int temp = direction - value;
	if (temp < 0) temp += 4;
	return temp;
}

// �ֺ� 4ĭ �� ���� ã�� �Լ�
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

	// û�� �� �� ĭ: 0, ��: 1 û�ҵ� ĭ: 2
	while (1){

		// 1��: ����ĭ û��
		if (MAP[curR][curC] == 0) {
			MAP[curR][curC] = 2;
			cnt++;
		}

		// 3��
		if (dustFind(curR, curC)) {
			direction = directionChange(direction, 1);
			int tempRow = curR + dx[direction];
			int tempCol = curC + dy[direction];
			
			if (MAP[tempRow][tempCol] == 0) {
				curR = tempRow;
				curC = tempCol;
			}
		
		}

		// 2��
		else {
			int tempDirection = directionChange(direction, 2);
			int tempRow = curR + dx[tempDirection];
			int tempCol = curC + dy[tempDirection];
			if (MAP[tempRow][tempCol] != 1) {
				curR = tempRow;
				curC = tempCol;
			}

			else {
				break;		// �۵� ����
			}
		
		}
	}

	cout << cnt;

}