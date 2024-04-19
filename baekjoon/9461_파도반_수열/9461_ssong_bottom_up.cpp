#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int T;
long long memo[105];

void init() {
	memset(memo, 0, sizeof(memo));
}

long long process(int n) {
	if (memo[n] != 0) return memo[n];

	if (n == 0) return 0;
	if (n == 1||n==2) return 1;

	long long a = process(n - 3);
	long long b = process(n - 2);
	memo[n] = a + b;
	return a + b;
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	
	int a;
	cin >> T;
	for (int tc = 0; tc < T; tc++)
	{
		cin >> a;
		init();
		long long ret = process(a);
		cout << ret<<'\n';
	}
	return 0;
}
