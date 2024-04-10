#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct person {
	int y;
	int x;
	int directoin;
	int firstAbil;	// 초기능력치
	int gun;		// 총
};

int N, M, K;
int MAP[21][21];
int point[31];
vector <int> gunMAP[21][21];
person personList[31];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

void input() {
	cin >> N >> M >> K;
	int temp;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			cin >> temp;
			if (temp > 0)
				gunMAP[i][j].push_back(temp);
		}
	}
	int tempX, tempY, d, s;
	for (int i = 1; i <= M; i++){
		cin >> tempX >> tempY >> d >> s;
		MAP[tempX - 1][tempY - 1] = i;
		personList[i] = { tempX - 1, tempY-1, d, s, 0};
	}
}

// 자기가 가지고 있는거 포함 젤 좋은 총 줍기
void getGun(int personNum, int y, int x) {

	// 만약 총 가지고 있었다면 내려놓기
	if (personList[personNum].gun > 0){
		gunMAP[y][x].push_back(personList[personNum].gun);
		personList[personNum].gun = 0;
	}

	int maxGun = 0, maxIdx;
	if (gunMAP[y][x].size() == 0)		// 총이 없을땐 그냥 리턴
		return;
	
	for (int i = 0; i < gunMAP[y][x].size(); i++){
		if (gunMAP[y][x][i] > maxGun) {
			maxGun = gunMAP[y][x][i];
			maxIdx = i;
		}
	}

	gunMAP[y][x].erase(gunMAP[y][x].begin() + maxIdx);
	personList[personNum].gun = maxGun;
}

// 싸우기
void fight(int player1, int player2, int y, int x) {
	
	// 이긴사람 진사람 정하기, 점수만큼 포인트 획득하기
	MAP[y][x] = 0;
	int winNum, loseNum;
	int player1Power = (personList[player1].firstAbil + personList[player1].gun);
	int player2Power = (personList[player2].firstAbil + personList[player2].gun);
	if (player1Power == player2Power) {
		if (personList[player1].firstAbil > personList[player2].firstAbil) {
			winNum = player1; loseNum = player2;
		}
		else {
			winNum = player2; loseNum = player1;
		}
	}
	else if (player1Power > player2Power) {
		winNum = player1; loseNum = player2;
	}
	else {
		winNum = player2; loseNum = player1;
	}
	int powerGap = abs(player1Power - player2Power);
	point[winNum] += powerGap;


	// 진 플레이어 총 내려놓기
	if (personList[loseNum].gun > 0) {
		gunMAP[y][x].push_back(personList[loseNum].gun);
		personList[loseNum].gun = 0;
	}

	// 진 플레이어 이동하기
	int curDir = personList[loseNum].directoin;
	while (true){
		int ny = y + dy[curDir];
		int nx = x + dx[curDir];

		if (ny < 0 || nx < 0 || ny >= N || nx >= N || MAP[ny][nx] > 0) {
			curDir = (curDir + 1) % 4;
			personList[loseNum].directoin = curDir;
			continue;
		}

		MAP[ny][nx] = loseNum;
		personList[loseNum].y = ny; personList[loseNum].x = nx;

		if (gunMAP[ny][nx].size() > 0)
			getGun(loseNum, ny, nx);

		break;
	}

	// 이긴 플레이어 그 자리에서 총 줍기
	MAP[y][x] = winNum;
	personList[winNum].y = y; personList[winNum].x = x;
	getGun(winNum, y, x);
}

void movePerson(int personNum) {
	int curDir = personList[personNum].directoin;
	MAP[personList[personNum].y][personList[personNum].x] = 0;

	int ny = personList[personNum].y + dy[curDir];
	int nx = personList[personNum].x + dx[curDir];

	// 만약 범위 벗어나면 정반대로 이동
	if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
		curDir = (curDir + 2) % 4;						
		personList[personNum].directoin = curDir;
		ny = ny + dy[curDir] * 2;
		nx = nx + dx[curDir] * 2;
	}

	if (MAP[ny][nx] == 0) {					// 이동한 칸이 빈칸일때
		getGun(personNum, ny, nx);
		personList[personNum].y = ny;
		personList[personNum].x = nx;
		MAP[ny][nx] = personNum;
	}
	else {											// 이동한 칸에 사람 있을때
		fight(personNum, MAP[ny][nx], ny, nx);
	}
}

void solve() {
	for (int i = 0; i < K; i++){
		for (int j = 1; j <= M; j++){
			movePerson(j);
		}
	}
	
	// 최종 포인트 출력
	for (int i = 1; i <= M; i++){
		cout << point[i] << " ";
	}
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	input();
	solve();

	return 0;
}
