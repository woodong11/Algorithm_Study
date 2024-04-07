// 메이즈 러너
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct person {
	int y;
	int x;
};

bool compare(person a, person b) {
	if (a.y == b.y)
		return a.x < b.x;
	return a.y < b.y;
}

int MAP[11][11];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int N, M, K, exitY, exitX, cnt;
int isExit[11];
person personList[11];

void input(){
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			cin >> MAP[i][j];
		}
	}
	int tempy, tempx;
	for (int i = 1; i <= M; i++){
		cin >> tempy >> tempx;
		//MAP[tempy - 1][tempx - 1] = -1;	// 사람: -1로 표시
		personList[i] = { tempy - 1, tempx - 1 };
	}
	cin >> tempy >> tempx;
	exitY = tempy - 1;
	exitX = tempx - 1;

}

// 모두 탈출했는지 체크
bool allExit() {
	int flag = 1;
	for (int j = 1; j <= M; j++) {
		if (isExit[j] == 0) {
			flag = 0;
			return false;
		}
	}
	return true;
}

// 사람들 이동
void movePerson() {
	for (int i = 1; i <= M; i++){
		if (isExit[i] == 1)
			continue;

		int curDist = abs(exitY - personList[i].y) + abs(exitX - personList[i].x);
		for (int j = 0; j < 4; j++) {
			int ny = personList[i].y + dy[j];
			int nx = personList[i].x + dx[j];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N)
				continue;
			if (MAP[ny][nx] > 0)
				continue;
			if (ny == exitY && nx == exitX) {	// 만약 그 칸이 출구라면
				cnt++;
				isExit[i] = 1;
				break;
			}

			int newDist = abs(exitY - ny) + abs(exitX - nx);
			if (newDist < curDist) {
				cnt++;
				personList[i].y = ny;
				personList[i].x = nx;
				break;
			}
		}
	}
}

// 정사각형 찾고 돌리기
void makeSqure(){

	// 사람이랑 출구 최소거리 찾기
	int minDist = 21e8;
	for (int i = 1; i <= M; i++){
		if (isExit[i] == 1)
			continue;
		int curDist = abs(personList[i].y - exitY) + abs(personList[i].x - exitX);
		minDist = min(curDist, minDist);
	}

	// 최소거리인 사람 벡터에 담고 정렬
	vector <person> curPeople;
	for (int i = 1; i <= M; i++) {
		if (isExit[i] == 1)
			continue;
		int curDist = abs(personList[i].y - exitY) + abs(personList[i].x - exitX);
		if (curDist == minDist)
			curPeople.push_back({ personList[i].y, personList[i].x });
	}
	sort(curPeople.begin(), curPeople.end(), compare );
	
	// 정사각형 위치 찾기 - 여기까지 왔을때 무조건 하나 이상은 curPeople에 담겨있음.
	// 정사각형 만들때: 출구랑 가장 가까운 사람 찾고(거리 같다면 제일 좌상단 사람),
	// 둘 중 max y, max x를 찾는다. 그리고 출구랑 x, y갭 중 큰게 정사각형 변의 길이
	person basePerson = curPeople[0];
	int endY = max(exitY, basePerson.y);
	int endX = max(exitX, basePerson.x);
	int squreLen = max(abs(exitY - basePerson.y), abs(exitX - basePerson.x)) + 1;
	int startY = endY - squreLen + 1;
	int startX = endX - squreLen + 1;

	// 정사각형 돌리기
	// 00 20    01 12   02   22
	// 10    01    12 21   22 20
	// 
	// [y][x]   -> [x][ len - y -1]
	int tempMAP[11][11] = { 0, };
	int tempMAP1[11][11] = { 0, };
	for (int i = startY; i < startY + squreLen; i++){
		for (int j = startX; j < startX + squreLen; j++){
			tempMAP[j][squreLen-i-1] = MAP[i][j];
			if (tempMAP[j + startY][squreLen - i - 1 + startX] > 0)
				tempMAP[j + startY][squreLen - i - 1 + startX]--;
		}
	}

	for (int i = startY; i < startY + squreLen; i++) {
		for (int j = startX; j < startX + squreLen; j++) {
			MAP[i][j] = tempMAP[i][j];
		}
	}
	
	for (int i = 1; i <= M; i++){
		if (isExit[i] == 1)
			continue;

		if (startY <= personList[i].y && personList[i].y <= endY && startX <= personList[i].x && personList[i].x <= endX) {
			int tempY = personList[i].y;	
			int tempX = personList[i].x;	

			personList[i].y = tempX;
			personList[i].x = squreLen - tempY - 1;

			int de = -1;
		}
	}

	int tempY = exitY;
	int tempX = exitX;
	exitY = tempX;
	exitX = squreLen - tempY  -1;

	int de = -1;

}

// 사람 이동, 정사각형 찾기, 돌리기
void solve() {
	
	for (int i = 1; i <= K; i++){

		if (allExit())
			break;

		movePerson();
		makeSqure();
	}

	cout << cnt << "\n" << exitY << exitX;


}

int main() {
	freopen("sample_input.txt", "r", stdin);
	input();
	solve();

	return 0;
}
