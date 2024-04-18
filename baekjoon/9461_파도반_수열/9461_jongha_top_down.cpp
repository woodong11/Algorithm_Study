#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long memo[101];

long long dp(int level) {
	if (level == 1 || level == 2 || level == 3) {
		return 1;
	}
	if (memo[level] != 0) return memo[level];

	long long a = dp(level - 2);
	long long b = dp(level - 3);

	memo[level] = a + b;
	return a + b;
}

int T, a;
int main() {
	cin >> T;

	for (int i = 0; i < T; i++) {
		cin >> a;

		cout << dp(a) << "\n";
	}

	return 0;
}
