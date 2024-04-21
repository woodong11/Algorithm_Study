#include <iostream>
using namespace std;

int N;
int memo[1000001];

int find(int n) {
	if (memo[n] != 0) return memo[n];

	int a = find(n - 1);
	int b = find(n - 2);
	memo[n] = (a + b) % 15746;
	return memo[n];
}

int main() {
	memo[1] = 1; memo[2] = 2;
	cin >> N;
	cout << find(N);

	return 0;
}
