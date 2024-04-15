#include<iostream>
using namespace std;

int main()
{
	int H, W, N, M;
	cin >> H >> W >> N >> M;
	H += N;
	W += M;
	cout << (H / (N + 1)) * (W / (M + 1));
	return 0;
}
