#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int T, N, W, H;
vector<vector <int>> MAP;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int cnt; 
int maxBroken;
int curbrokenNum;
//int curMAP[16][13];

struct Node{
	int y;
	int x;
	int num;
};


void init() {
	cnt = 0;
	maxBroken = 0;
	MAP.clear();
}

void input() {
	cin >> N >> W >> H;
	MAP.resize(H, vector <int>(W));
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> MAP[i][j];
			if (MAP[i][j] > 0)
				cnt++;
		}
	}
}

vector<vector <int>> breakBlock(vector<vector <int>> curMAP, int col) {
	curbrokenNum = 0;
	// 출발 위치 찾기
	int startRow = 0;
	bool breakable = false;				// 모두 부서진 블록들 조건때매 추가함
	for (int i = 0; i < H; i++) {
		if (curMAP[i][col] > 0) {
			startRow = i;
			breakable = true;
			break;
		}
	}

	// 큐로 돌리기
	queue<Node> q;
	q.push({ startRow, col, curMAP[startRow][col] });
	curMAP[startRow][col] = 0;
	if (breakable)
		curbrokenNum++;

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();							// 이 다음에 바로 curbrokenNum++; 했어서 논리적으로 실수해서 디버깅함.

		// 빼낸 숫자가 2보다 클때
		if (now.num > 1) {
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < now.num; j++) {
					int ny = now.y + dy[i] * j;
					int nx = now.x + dx[i] * j;

					if (ny < 0 || nx < 0 || ny >= H || nx >= W)
						continue;
					if (curMAP[ny][nx] == 0)
						continue;

					q.push({ny, nx, curMAP[ny][nx]});
					curMAP[ny][nx] = 0;
					curbrokenNum++;
				}
			}
		}
	}

	return curMAP;
}

// 중력 적용해주는 함수
vector<vector <int>> gravity(vector<vector <int>> curMAP) {

	for (int i = 0; i < W; i++)
	{
		queue <int> q;
		for (int j = H-1; j >= 0 ; j--)
		{
			if (curMAP[j][i] > 0)
				q.push(curMAP[j][i]);
			curMAP[j][i] = 0;
		}

		int index = H-1;
		while (!q.empty()) {
			int curNum = q.front();
			q.pop();
			curMAP[index][i] = curNum;
			index--;
		}
	}
	return curMAP;
}


void dfs(vector<vector <int>> curMAP, int level, int brokenNum) {
	// 탈출조건
	if (level == N) {
		if (maxBroken < brokenNum)
			maxBroken = brokenNum;
		return;
	}	

	for (int i = 0; i < W; i++)	
	{
		// temp맵 안 만들어서 디버깅 오래걸림
		vector<vector <int>> tempMAP = curMAP;
		// 가지치기 (바닥에 아예 없거나 1일때 -> 의미없음) -> 모두 부서진 경우때매 조건 수정함
		if ((tempMAP[H-2][i] == 0 && tempMAP[H-1][i] <= 1) && (i != W-1))
			continue;

		tempMAP = breakBlock(tempMAP, i);
		tempMAP = gravity(tempMAP);
		dfs(tempMAP, level + 1, brokenNum + curbrokenNum);
	}

}

void solve() {
	dfs(MAP, 0, 0);	
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++){
		init();
		input();
		solve();

		cout << "#" << tc << " " << cnt - maxBroken << "\n";
	}
	
	return 0;
}
