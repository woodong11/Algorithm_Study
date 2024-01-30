# define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

int n; // 전체 사람 수
int pp1, pp2; // 촌수 계산해야하는 사람
int m; // 관계 수
int x, y; //부모, 자식

vector<vector<int>> relative(101);

int parents[101]; // 부모 TF
int relaNum[101];	// 1차 촌수 저장
int ppCnt = 0;		// 최종 촌수 저장
int flag = 0;
int ans;

void input() {
	cin >> n;
	cin >> pp1 >> pp2;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> x >> y;
		relative[y].push_back(x); // 자식-부모 인접리스트 (부모-자식 아님! 화살표 방향 역으로)
	}
}

void process(int pp, int cnt) {
	if (relative[pp].size() == 0) return;
	for (int i = 0; i < relative[pp].size(); i++)
	{
		int parent = relative[pp][i];
		parents[parent]++;
		relaNum[parent] = cnt + 1;
		process(parent, cnt+1);
	}
}

void checked(int pp, int cnt) {
	if (relative[pp].size() == 0) return;

	for (int i = 0; i < relative[pp].size(); i++)
	{
		int parent = relative[pp][i];
		if (parents[parent] == 1) {
			ans = cnt + 1 + relaNum[parent];
			flag = 1;
			return;
		}
		checked(parent, cnt + 1);
	}
}



int main() {
	input();
	process(pp1, 0);
	checked(pp2, 0);
	if (flag == 1) cout << ans;
	else cout << "-1";
	return 0;
}
