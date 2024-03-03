#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include<queue>
#include<cstring>

using namespace std;

int T;
int plan[12];
int cost[4];

int cnt;
int minVal;

void input() {
	cnt = 0;
	for (int i = 0; i < 4; i++)
	{
		cin >> cost[i]; // cin >> costD >> costM >> cost3M >> costY;
	}

	for (int i = 0; i < 12; i++)
	{
		cin >> plan[i];
		if (plan[i] != 0) cnt++;
	}
	minVal = cost[3];
}



void dfs(int level, int c) {
	int cosst = 0;
	if (level >= 12) {
		if (c < minVal) minVal = c;
		return;
	}


	if (plan[level] == 0) dfs(level + 1, c);
    
	// 이거하나 추가했다고........ 1/4로 줄었음... 댑악...
    
	else {
		for (int i = 0; i < 3; i++) {
			// 이용권 택1
			if (i == 0) {
				cosst = cost[0] * plan[level];
				dfs(level + 1, c + cosst);
			}
			else if (i == 1) {
				dfs(level + 1, c + cost[1]);
			}
			else if (i == 2) {
				dfs(level + 3, c + cost[2]);
			}
		}
	}

}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		input();
		dfs(0, 0);

		cout << "#" << tc << " " << minVal << '\n';
	}
}
