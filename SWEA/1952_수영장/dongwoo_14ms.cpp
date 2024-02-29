#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int T, N, answer;
int price[4];
int plan[14];

void init() {
	memset(plan, 0, sizeof(plan));
	answer = 21e8;
}

void input() {
	cin >> price[0] >> price[1] >> price[2] >> price[3];

	for (int i = 1; i <= 12; i++)
	{
		cin >> plan[i];
	}
}


void func(int level, int sum) {

	if (level >= 13) {
		answer = min(answer, sum);
		return;
	}

	// 가지치기
	if (sum > answer)
		return;

	// 플랜 일정 없는 경우
	if (plan[level] == 0) {
		func(level + 1, sum);
	}

	// 일일, 한달, 3달 사용하는 경우
	else {
		for (int i = 0; i < 3; i++) {

			if (i == 0) {
				func(level + 1, sum + price[0] * plan[level]);
			}

			else if (i == 1) {
				func(level + 1, sum + price[1]);
			}

			else {
				func(level + 3, sum + price[2]);
			}
		}
	}
}

void solve() {

	answer = price[3];
	func(1, 0);
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
{
		init();
		input();
		solve();

		cout << "#" << tc << " " << answer << "\n";
	}
	
	return 0;
}
