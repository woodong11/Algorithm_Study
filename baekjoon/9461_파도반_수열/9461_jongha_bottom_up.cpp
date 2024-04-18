#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long memo[101];

int T, a;
int main() {
	cin >> T;

	for (int i = 1; i < 4; i++) {
		memo[i] = 1;
	}

	for (int i = 4; i < 101; i++) {
		memo[i] = memo[i - 3] + memo[i - 2];
	}

	for (int i = 0; i < T; i++) {
		cin >> a;

		cout << memo[a] << "\n";
	}

	return 0;
}
