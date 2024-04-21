#include <iostream>
using namespace std;

int T, N;
long long memo[101] = {0, 1, 1, 1, 2, 2, 0, };	// 1~5까지는 미리 구해 놓았다.

long long findP(int num) {
	if (memo[num] != 0) return memo[num];
	
	long long a = findP(num - 5);
	long long b = findP(num - 1);
	memo[num] = a + b;
	return a + b;
}

int main() {

	cin >> T;
	for (int tc = 1; tc <= T; tc++){
		cin >> N;
		cout << findP(N) << "\n";
	}

	return 0;
}
