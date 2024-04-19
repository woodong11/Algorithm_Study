#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int T;
long long memo[105];

void init() {
	memset(memo, 0, sizeof(memo));
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	int a;
	cin >> T;
	for (int tc = 0; tc < T; tc++)
	{
		init();
		memo[1] = memo[2] = 1;
		cin >> a;
		for (int i = 3; i <= a; i++)
		{
			memo[i] = memo[i - 3] + memo[i - 2];
		}
		cout << memo[a] << '\n';
	}
	return 0;
}
