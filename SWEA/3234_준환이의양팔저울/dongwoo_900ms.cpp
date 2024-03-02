// 최악의 케이스 경우도 int를 넘지는 않음. (1억 8천 회). 단 1초는 넘음(1억회 이상이니깐)
// 처음엔 순열 다 만들고 각 경우마다 테스트할랬는데 20에서 시간초과
// -> 순열 만들면서 동시에 판단하기
// 가지치기 2개
// 가지치기 1번 for문 밖으로 빼니깐 시간초과 해결

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cmath>
#include <stdio.h>
using namespace std;

int T, N, answer, totalWeight;
int choo[10];
int visited[10];	// 순열 만들기 위한 체크 함수
//int factorial[] = {0, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};	이거 써봤자 의미 거의 없음

void init() {
	memset(choo, 0, sizeof(choo));
	answer = 0;
	totalWeight = 0;
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> choo[i];
		totalWeight += choo[i];
	}
}

// 팩토리얼을 위한 함수 구현
int factorial(int num) {
	if (num == 1)
		return num;
	int ret = num * factorial(num - 1);
	return ret;
}

void func(int level, int leftWeight, int rightWeight, int remainedWeight) {
	
	if (level == N) {	
		answer++;
		return;
	}

	// 가지치기1: 이게 true면 남은것들 왼쪽 오른쪽 순열 걱정없이 아무렇게나 올릴 수 있음. 바로 return
	bool returnNow = (leftWeight >= (rightWeight + remainedWeight));	
	if (returnNow) {
		answer += pow(2, N - level) * factorial(N - level);		// 주의 ! 2^남은 경우로 만들 수 있는 부분집합 X 남은 순열 가지수
		return;
	}

	for (int i = 0; i < N; i++)
	{
		if (visited[i] == 1) continue;
		visited[i] = 1;

		// 가지치기2: 현재 추를 오른쪽에 올렸을때 더 무겁다면 남아 있는 것들은 무조건 왼쪽에 다 올려야함.
		bool isLeft = (leftWeight < rightWeight + choo[i]);					

		if (isLeft) {
			func(level + 1, leftWeight + choo[i], rightWeight, remainedWeight - choo[i]);
		}
		else {
			func(level + 1, leftWeight + choo[i], rightWeight, remainedWeight - choo[i]);
			func(level + 1, leftWeight, rightWeight + choo[i], remainedWeight - choo[i]);
		}
		visited[i] = 0;
	}
}


void solve() {
	func(0, 0, 0, totalWeight);
}

int main() {
	
	freopen("sample_input.txt", "r", stdin);

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		solve();

		cout << "#" << tc << " " << answer << "\n";
	}
	return 0;
}
