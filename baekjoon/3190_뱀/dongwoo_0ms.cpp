// 0초에는 안 움직임!
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dy[4] = { 0, 1, 0, -1 };	// 우하좌상
int dx[4] = { 1, 0, -1, 0 };
int direction = 0;				// 뱀 방향

struct Node
{
	int y;
	int x;
};

struct info
{
	int time;
	char direction;
};

int MAP[101][101];
int N, K, L;
int answer = 1;
queue <Node> snake;
vector <info> directionInfo;

void input() {
	cin >> N >> K;
	int row, col;
	for (int i = 0; i < K; i++)
	{
		cin >> row >> col;
		MAP[row - 1][col - 1] = 1;	// 사과 위치하기
	}
	
	cin >> L;
	int tempTime;
	char charactor;
	for (int i = 0; i < L; i++)
	{
		cin >> tempTime >> charactor;
		directionInfo.push_back({ tempTime, charactor });
	}

}

int main() {

	input();
	
	// 뱀 이동 시작
	MAP[0][0] = 2;
	snake.push({ 0, 0 });
	int curY = 0;
	int curX = 0;

	while (true)
	{
		int ny = curY + dy[direction];
		int nx = curX + dx[direction];

		// 종료조건 
		if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
			break;
		}
		if (MAP[ny][nx] == 2)
			break;
		
		// 사과일때, 아닐때 판단
		if (MAP[ny][nx] == 1) {
			MAP[ny][nx] = 2;
			snake.push({ ny, nx });
		}
		else {
			MAP[ny][nx] = 2;
			snake.push({ ny, nx });
			Node tail = snake.front();
			snake.pop();
			MAP[tail.y][tail.x] = 0;
		}


		// 방향 바꾸기 여부 판단하고 바꾸기
			if (directionInfo.size() > 0 && answer == directionInfo[0].time) {
				if (directionInfo[0].direction == 'L') {	// 반시계로 이동
					if (direction == 0)
						direction = 3;
					else
						direction--;
				}
				else {
					direction = (direction + 1) % 4;
				}
				directionInfo.erase(directionInfo.begin());
			}

		curY = ny;
		curX = nx;
		answer++;
	}

	cout << answer;

	return 0;
}
