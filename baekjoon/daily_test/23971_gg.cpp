#include <iostream>

using namespace std;

int H, W, N, M;

int main() {
	cin >> H >> W >> N >> M;
	int a, b;
	if (H % (N + 1) == 0)
		a = H / (N + 1);
	else
		a = H / (N + 1) + 1;
	if (W % (M + 1) == 0)
		b = W / (M + 1);
	else
		b = W / (M + 1) + 1;
	cout << a * b;

	return 0;
}
