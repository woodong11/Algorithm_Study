#include <iostream>
#include <algorithm>
using namespace std;

int N;
int MAP[1000][3];

int main() {

	// 입력받기
	cin >> N;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < 3; j++){
			cin >> MAP[i][j];
		}
	}

	// dp로 합 저장하면서 수행
	for (int i = 1; i < N; i++){
		int preCostSumR = MAP[i - 1][0];
		int preCostSumG = MAP[i - 1][1];
		int preCostSumB = MAP[i - 1][2];
		MAP[i][0] = MAP[i][0] + min(preCostSumG, preCostSumB);
		MAP[i][1] = MAP[i][1] + min(preCostSumR, preCostSumB);
		MAP[i][2] = MAP[i][2] + min(preCostSumR, preCostSumG);
	}

	cout << min({ MAP[N-1][0], MAP[N - 1][1], MAP[N - 1][2] });

	return 0;
}
