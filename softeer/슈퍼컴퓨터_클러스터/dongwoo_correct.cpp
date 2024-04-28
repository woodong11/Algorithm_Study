#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;


long long N, idx;
long long B, minNum, maxNum;
vector <long long> computers;


long long findUpperBound(long long target) {
	long long low = 0;
	long long high = N;
	long long mid = 0;

    // BS : low <= high
    while (low < high)
    {
        mid = (low + high) / 2;
        // 같을 경우에도 이리로 옴 (계속 탐색 진행)
        if (computers[mid] <= target){
            low = mid + 1;
        }
        // BS : high = mid - 1
        else{
            high = mid;
        }
    }

    // BS : false 리턴
    return low;
}


// 최소 컴퓨터 성능이 num일때 가능한지를 판별한다. 
bool isPossible(long long num) {
	long long sum = 0;

	// num성능보다 1 큰 인덱스 찾기
	long long nextIdx = findUpperBound(num);

	for (int i = 0; i < nextIdx; i++){
		long long gap = (num - computers[i]);
		sum += gap * gap;

        if(sum > B) return false;
	}

	if (sum > B)
		return false;
	else
		return true;
}

// 1 ~ N-1번째 중 정답 인덱스
long long ps(long long start, long long end) {

	long long answer = 0;

	while (start <= end) {

		long long mid = (start + end) / 2;

		if (isPossible(mid)) {
			answer = mid;
			start = mid + 1;
		}

		else
			end = mid - 1;
	}

	return answer;
}



int main() {
	//freopen("sample_input.txt", "r", stdin);

	cin >> N >> B;
	int temp;
	for (int i = 0; i < N; i++){
		cin >> temp;
		computers.push_back(temp);
	}
	sort(computers.begin(), computers.end());	// 오름차순
	minNum = computers[0];
	maxNum = computers[N-1];

	cout << ps(1, sqrt(B)+ minNum);



	//cout << "\n" << findUpperBound(8);


	return 0;
}
