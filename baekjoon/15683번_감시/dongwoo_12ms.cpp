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

	for (int i = 0; i < curDirList.size(); i구
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
