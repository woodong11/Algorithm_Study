#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
	int y;
	int x;
};

struct cctv{
	int y;
	int x;
	int num;
};

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int N, M, unVisibleCnt, answer;
int MAP[9][9];

vector <cctv> cctvList;
vector <vector <int>> directionList[6] = {
	{{}},
	{{0}, {1}, {2}, {3}},
	{{0, 1}, {2, 3}},
	{{0, 3},{1, 3},{1, 2}, {0, 2}},
	{{0, 2, 3}, {0, 1, 3}, {1, 2, 3}, {0, 1, 2}},
	{{0, 1, 2, 3}}
};

void input() {
	cin >> N >> M;
	unVisibleCnt = N * M;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			cin >> MAP[i][j];
			if (MAP[i][j] > 0) {
				unVisibleCnt--;
				if (MAP[i][j] < 6)
					cctvList.push_back({i,j,MAP[i][j]});
			}
		}
	}
}

void func(int level, int unVisibleCnt) {
	
	// 기저조건
	if (level == cctvList.size()) {
		answer = min(unVisibleCnt, answer);
		return;
	}

	// 해당 CCTV의 방향 목록 가짓수마다
	cctv curCctv = cctvList[level];
	vector<vector <int>> curDirList = directionList[curCctv.num];

	for (int i = 0; i < curDirList.size(); i++)
	{
		int visibleCnt = 0;
		vector <Node> visibleList;
		int baseY = curCctv.y;
		int baseX = curCctv.x;

		// 해당 방향 목록의 각 방향마다 
		for (int j = 0; j < curDirList[i].size(); j++) {
			int curDir = curDirList[i][j];
		
			int curY = baseY;
			int curX = baseX;
			while (1)
			{
				int ny = curY + dy[curDir];
				int nx = curX + dx[curDir];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M)		// 범위 밖
					break;
				if (MAP[ny][nx] == 6)					// 벽 만날때
					break;
				if (MAP[ny][nx] != 0) {					// 다른 cctv나 이미 본 곳일때
					curY = ny; 
					curX = nx;
					continue;
				}
				
				MAP[ny][nx] = -1;
				visibleList.push_back({ ny, nx });
				visibleCnt ++;
				curY = ny;
				curX = nx;
			}	
		}
		// 재귀 타기
		func(level + 1, unVisibleCnt - visibleCnt);

		// 복귀
		for (auto curCctv : visibleList) {
			MAP[curCctv.y][curCctv.x] = 0;
		}
	
	}
}

void solve() {
	answer = 21e8;
	func(0, unVisibleCnt);
}

int main() {
	//freopen("sample_input.txt", "r", stdin);

	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	input();
	solve();
	
	cout << answer;

	return 0;
}
