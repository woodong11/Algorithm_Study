#include <iostream>
using namespace std;
int H, W, N, M, cnt;

int main() {

	cin >> H >> W >> N >> M;	// 행, 열, 세로비우는칸, 가로비우는칸

	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			cnt++;
			j += M;
		}
		i += N;
	}
	cout << cnt;

	return 0;
}
