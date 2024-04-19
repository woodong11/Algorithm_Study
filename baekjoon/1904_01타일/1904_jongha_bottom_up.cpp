#?
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long memo[1000001];

int T, a;
int main() {
	cin >> T;

	memo[1] = 1;
	memo[2] = 2;

	for (int i = 3; i < 1000001; i++) {
		memo[i] = (memo[i - 2] + memo[i - 1]) % 15746;
	}

	cout << memo[T];

	return 0;
}
