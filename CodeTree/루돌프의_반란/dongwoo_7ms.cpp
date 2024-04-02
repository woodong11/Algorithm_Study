// 루돌프의 반란
/* 겪었던 에러 해결들:
1. santaQ에서 정렬 때리고 제일 처음꺼 뽑을때 [0] 인덱스로 접근해서, 만약 없으면 벡터 인덱스 오류남
2. 밖에 나가있는 산타도 로직상 santaQ에 넣어버려서 살아있는걸로 착각해서 루돌프가 엉뚱한데로 뜀
3. 산타가 상우하좌 순으로 이동한다고 해서 무지성으로 순서대로 때려넣었는데, 그 안에서도 순서가 바뀔 수 있는 거였음..
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, P, C, D, rudolY, rudolX, curTurn = 1;
int MAP[51][51];								// 양수는 산타, -1은 루돌프
int dy[8] = {-1, 0, 1, 0, -1, -1, 1, 1 };		// 상우하좌 좌상 우상 우하 좌하
int dx[8] = {0, 1, 0, -1, -1, 1, 1, -1 };
int changDir[8] = { 2, 3, 0, 1, 6, 7, 4, 5 };	// 튕겨져나갈때 방향 바꾸기 위한 배열
int santaScore[31];

struct Node {
	int y;
	int x;
	int dist;
	int dirNum;		// 움직였던 방향
};

struct santa {
	int y;
	int x;
	int num;
	int stuned;
	int isOut;
};

santa santaList[31];	// 산타 정보 저장 배열
queue <int> santaQ;		// 실행할 산타 번호 담은 큐. 맵에 살아있는 산타들이 된다.

bool rudolCompare(Node a, Node b) {
	return a.dist < b.dist;			// 오름차순
}

bool compare(Node a, Node b) {
	if (a.dist == b.dist) {
		if (a.y == b.y)
			return a.x > b.x;	// 내림차순
		return a.y > b.y;		// 내림차순
	}
	return a.dist < b.dist;		// 오름차순
}

int findDist(int y1, int x1, int y2, int x2) {
	return (y1 - y2) * (y1 - y2) + (x1 - x2) * (x1 - x2);
}

void input() {
	cin >> N >> M >> P >> C >> D;
	int temp1, temp2;
	cin >> temp1 >> temp2;
	rudolY = temp1-1;
	rudolX = temp2-1;
	MAP[rudolY][rudolX] = -1;

	int  santaNum, santaRow, santaCol;
	for (int i = 1; i <= P; i++){
		cin >> santaNum >> santaRow >> santaCol;
		MAP[santaRow - 1][santaCol - 1] = santaNum;
		santaList[santaNum] = { santaRow - 1, santaCol - 1, santaNum, 0, 0 };
		santaQ.push(i);				// 요건 일부러 1부터 P까지 담을려고
		
	}
}

// 충돌시 이벤트 구현
void colide(int isRudolFirst, int startY, int startX, int dirNum, int firstSanta) {
	int moveDir, santaArivedY, SantaArivedX;
	santaList[firstSanta].stuned = curTurn + 2;		// 기절, 해당 턴부터 움직일 수 있다.
	//MAP[startY][startX] = 0;

	if (isRudolFirst == 1) {				// 루돌프가 먼저 들이받은 경우
		santaScore[firstSanta] += C;
		moveDir = dirNum;
		santaArivedY = startY + dy[moveDir] * C;
		SantaArivedX = startX + dx[moveDir] * C;
	}
	else {
		santaScore[firstSanta] += D;
		moveDir = changDir[dirNum];
		santaArivedY = startY + dy[moveDir] * D;
		SantaArivedX = startX + dx[moveDir] * D;
	}

	// 만약 밀려났는데 게임판 밖이라면 
	if (santaArivedY < 0 || SantaArivedX < 0 || santaArivedY >= N || SantaArivedX >= N) {
		santaList[firstSanta].isOut = 1;
		return;
	}

	// 만약 해당 칸에 산타가 존재한다면 - 상호작용 발생
	if (MAP[santaArivedY][SantaArivedX] > 0) {
		int flag = 1;
		int oldSanta, newSanta, curSantaY, curSantaX, nextSantaY, nextSantaX;
		newSanta = firstSanta;
		curSantaY = santaArivedY;
		curSantaX = SantaArivedX;

		while (flag) {
			oldSanta = MAP[curSantaY][curSantaX];
			MAP[curSantaY][curSantaX] = newSanta;		// 해당 칸에 newSanta가 차지
			santaList[newSanta].y = curSantaY;
			santaList[newSanta].x = curSantaX;
			nextSantaY = curSantaY + dy[moveDir];		// oldSanta가 이동할 위치
			nextSantaX = curSantaX + dx[moveDir];

			// 만약 oldSanta가 맵 벗어나는 경우
			if (nextSantaY < 0 || nextSantaX < 0 || nextSantaY >= N || nextSantaX >= N) {
				santaList[oldSanta].isOut = 1;
				break;
			}

			// 만약 다음 자리에 또 산타 있었을 경우
			if (MAP[nextSantaY][nextSantaX] > 0) {
				newSanta = oldSanta;
				oldSanta = MAP[nextSantaY][nextSantaX];
				santaList[oldSanta].y = nextSantaY;
				santaList[oldSanta].x = nextSantaX;
				curSantaY = nextSantaY;
				curSantaX = nextSantaX;
			}
			else {
				MAP[nextSantaY][nextSantaX] = oldSanta;		// oldSanta가 해당 칸 차지
				santaList[oldSanta].y = nextSantaY;
				santaList[oldSanta].x = nextSantaX;
				flag = 0;									// while문 종료
			}	
		}
	}

	// 해당 칸에 산타가 존재하지 않는다면
	else {
		MAP[santaArivedY][SantaArivedX] = firstSanta;
		santaList[firstSanta].y = santaArivedY;
		santaList[firstSanta].x = SantaArivedX;
	}
}

// 루돌프 이동
void rudolMove() {

	if (santaQ.size() == 0)		// 살아있는 산타 아무도 없을때
		return;
	
	// 맵에 존재하는 산타 넣고 정렬
	vector <Node> curSantas;
	queue <int> tempSantaQ;
	tempSantaQ = santaQ;
	while (!tempSantaQ.empty()){				
		int nowSanta = tempSantaQ.front();
		tempSantaQ.pop();

		if (santaList[nowSanta].isOut == 1)		// 이미 밖에 나간 산타는 치면 안된다.
			continue;

		int nowDist = findDist(rudolY, rudolX, santaList[nowSanta].y, santaList[nowSanta].x);
		curSantas.push_back({santaList[nowSanta].y, santaList[nowSanta].x, nowDist, 0 });		// 여기선 dirNum이 의미 없으니깐 그냥 0 넣었다
	}
	sort(curSantas.begin(), curSantas.end(), compare);

	if (curSantas.size() == 0)
		return;

	Node targetSanta = curSantas[0];

	// 인접 8칸 중 최적의 이동위치 찾기
	vector <Node> rudolMoveList;
	for (int i = 0; i < 8; i++) {
		int ny = rudolY + dy[i];
		int nx = rudolX + dx[i];
		
		if (ny < 0 || nx < 0 || ny >= N || nx >= N)
			continue;
		int nowDist = findDist(ny, nx, targetSanta.y, targetSanta.x);
		rudolMoveList.push_back({ny, nx, nowDist, i});
	}
	sort(rudolMoveList.begin(), rudolMoveList.end(), rudolCompare);
	Node targetPoint = rudolMoveList[0];

	// 만약 해당 위치에 산타가 있었을 경우
	if (MAP[targetPoint.y][targetPoint.x] > 0)
		colide(1, targetPoint.y, targetPoint.x, targetPoint.dirNum, MAP[targetPoint.y][targetPoint.x]);
	
	// 루돌프가 해당 자리로 이동
	MAP[rudolY][rudolX] = 0;
	MAP[targetPoint.y][targetPoint.x] = -1;
	rudolY = targetPoint.y;
	rudolX = targetPoint.x;


	int de = -1;
}

// 산타 이동
void santaMove() {

	int santaNum = santaQ.size();			// 있는 산타 수만큼
	for (int i = 0; i < santaNum; i++) {
		int curSantaNum = santaQ.front();
		santaQ.pop();
		int curSantaY = santaList[curSantaNum].y;
		int curSantaX = santaList[curSantaNum].x;
		
		if (santaList[curSantaNum].stuned > curTurn) {	// 기절해있는 산타는 움직이지 않는다.
			santaQ.push(curSantaNum);
			continue;
		}
		if (santaList[curSantaNum].isOut == 1){		// 맵 바깥에 나간 산타인 경우
			continue;
		}

		// 산타가 맵에 살아있고, 기절x
		santaQ.push(curSantaNum);
		vector <Node> moveList;
		int curDist = findDist(curSantaY, curSantaX, rudolY, rudolX);

		// 산타가 움직이는 방향 찾기
		for (int i = 0; i < 4; i++)
		{
			int ny = curSantaY + dy[i];
			int nx = curSantaX + dx[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N)			// 맵 밖으로 나가는 경우 못 움직임
				continue;
			if (MAP[ny][nx] > 0)								// 다른 산타가 있는 경우 못 움직임
				continue;

			int newDist = findDist(ny, nx, rudolY, rudolX);
			if (newDist < curDist)
				moveList.push_back({ ny, nx, newDist, i });		// 움직였던 방향 넣기
		}
		sort(moveList.begin(), moveList.end(), rudolCompare);

		// 루돌프에게 다가갈 수 있다면... 이동하기
		if (moveList.size() > 0) {
			MAP[curSantaY][curSantaX] = 0;
			Node targetPoint = moveList[0];
			if (MAP[targetPoint.y][targetPoint.x] == -1) {						// 해당 위치에 루돌프가 있었을때
				colide(0, targetPoint.y, targetPoint.x, targetPoint.dirNum, curSantaNum);

			}
			else {
				MAP[targetPoint.y][targetPoint.x] = curSantaNum;
				santaList[curSantaNum].y = targetPoint.y;
				santaList[curSantaNum].x = targetPoint.x;
			}
		}
	}

	int de = -1;

}

void solve() {
	while (curTurn <= M) {
	
		rudolMove();
		santaMove();

		// 살아남은 산타들 점수 부여
		for (int i = 1; i <= P; i++){
			if (santaList[i].isOut == 0)
				santaScore[i]++;
		}

		curTurn++;
	}
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	input();
	solve();

	// 최종 스코어 계산
	for (int i = 1; i <= P; i++){
		cout << santaScore[i] << " ";
	}

	return 0;
}
