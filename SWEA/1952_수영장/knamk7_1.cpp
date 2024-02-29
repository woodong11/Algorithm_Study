#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>

using namespace std;

int minVal;
int price[4]; // { 1일, 1달, 3달, 1년 }
int schedule[12];

void run(int level, int expense)
{
	if (level >= 12)
	{
		minVal = min(minVal, expense);
		return;
	}

	if (schedule[level])
	{
		run(level + 1, expense + price[0] * schedule[level]);	// 1일
		run(level + 1, expense + price[1]);			// 1달
		run(level + 3, expense + price[2]);			// 3달
	}
	else								// 이번 달 0회일 때 스킵 (필수 아님, 추가하면 17ms에서 14ms로 시간 단축)
	{
		run(level + 1, expense);
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		for (int i = 0; i < 4; i++)
		{
			cin >> price[i];
		}
		for (int i = 0; i < 12; i++)
		{
			cin >> schedule[i];
		}
		minVal = price[3]; // 1년
		run(0, 0);
		printf("#%d %d\n", test_case, minVal);
	}
	return 0;
}
