#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N, answer;
int MAP[101][101];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

struct coordinate {
	int x;
	int y;
};

coordinate rotate(int baseX, int baseY, int x, int y) {
	coordinate newCool;
	int gapX = x - baseX;
	int gapY = y - baseY;

	if (gapX >= 0)						// 기준좌표대비 비교좌표가 오른쪽에 있었을때
		newCool.y = baseY + gapX;		// baseY보다 더 +가 됨
	else
		newCool.y = baseY + gapX;		// baseY보다 더 -가 됨

	if (gapY < 0)						// 기준좌표대비 비교좌표가 위쪽에 있었을때
		newCool.x = baseX - gapY;		// baseX보다 더 +가 됨
	else
		newCool.x = baseX - gapY;		// baseX보다 더 +가 됨
	return newCool;
}

void makeCurve(int startX, int startY, int d, int g){
	vector <coordinate> curves;
	curves.push_back({ startX, startY });

	// 0세대 만들기
	int endX = startX + dx[d];
	int endY = startY + dy[d];
	curves.push_back({ endX, endY });

	// 1세대 이상일때
	if (g > 0) {
		for (int gen = 0; gen < g; gen++)
		{
			coordinate newCoor;
			// 돌려야 할 좌표 개수: 0->1세대는 1개, 1->2세대는 2개, 2->3세대는 4개, ...
			// 맨 마지막에 끝좌표 업데이트를 위해 일부러 거꾸로 인덱스
			for (int i = pow(2, gen)-1; i >= 0; i--)	 
			{
				int nowX = curves[i].x;
				int nowY = curves[i].y;
				newCoor = rotate(endX, endY, nowX, nowY);
				curves.push_back(newCoor);
			}
			endX = newCoor.x;				// 맨 마지막꺼 업데이트
			endY = newCoor.y;
		}
	}

	for (int i = 0; i < curves.size(); i++)
	{
		coordinate temp = curves[i];
		if (temp.x >= 0 && temp.y >= 0 && temp.x <= 100 && temp.y <= 100)	// 커브 점 MAP에 찍기
			MAP[temp.y][temp.x] = 1;
	}
	
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int startX, startY, d, g;
		cin >> startX >> startY >> d >> g;
		makeCurve(startX, startY, d, g);
	}

	for (int i = 0; i <= 99; i++)		// MAP 좌표가 네 귀퉁이 모두 1이면 answer++
	{
		for (int j = 0; j <= 99; j++)
		{
			if (MAP[i][j] == 1 && MAP[i + 1][j] == 1 && MAP[i][j + 1] == 1 && MAP[i + 1][j + 1] == 1)
				answer++;
		}
	}
	cout << answer;

	return 0;
}
