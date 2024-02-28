#include<iostream>
#include<climits>

using namespace std;

int price[4];
int schedule[12];

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

		int dp[12];
		dp[0] = min(price[0] * schedule[0], price[1]);

		for (int i = 1; i < 12; i++)
		{
			dp[i] = dp[i - 1] + min(price[0] * schedule[i], price[1]);
			if (i > 2)
			{
				dp[i] = min(dp[i], dp[i - 3] + price[2]);
			}
			else if (i == 2) // if문의 순서와 실행시간에 대해 생각해보기
			{
				dp[2] = min(dp[2], price[2]);
			}
		}
		dp[11] = min(min(dp[11], dp[9] + price[2]), dp[10] + price[2]); // 모든 경우의 수 따져보기(3달 가격 < 1달 가격 × 2, 3달 가격 < 1달 가격)
		printf("#%d %d\n", test_case, min(dp[11], price[3]));
	}
	return 0;
}
