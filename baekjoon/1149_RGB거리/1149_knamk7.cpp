#include<iostream>
#include<algorithm>
#include<climits>
using namespace std;

int dp[1000][3];

int main()
{
	int n;
	cin >> n;
	cin >> dp[0][0] >> dp[0][1] >> dp[0][2];
	for (int i = 1; i < n; i++)
	{
		cin >> dp[i][0];
		dp[i][0] += min(dp[i - 1][1], dp[i - 1][2]);
		cin >> dp[i][1];
		dp[i][1] += min(dp[i - 1][0], dp[i - 1][2]);
		cin >> dp[i][2];
		dp[i][2] += min(dp[i - 1][0], dp[i - 1][1]);
	}
	cout << min(dp[n - 1][0], min(dp[n - 1][1], dp[n - 1][2]));
	return 0;
}
