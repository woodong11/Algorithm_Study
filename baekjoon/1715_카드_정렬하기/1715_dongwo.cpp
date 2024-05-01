#include <iostream>
#include <queue>
using namespace std;

int N, temp, answer;
priority_queue <int, vector<int>, greater<>> pq;

int main() {

	cin >> N;
	for (int i = 0; i < N; i++){
		cin >> temp;
		pq.push(temp);
	}

	while (1) {
		if (pq.size() == 1)
			break;

		int lessFirst = pq.top();
		pq.pop();
		int lessSecond = pq.top();
		pq.pop();
		int newNum = lessFirst + lessSecond;
		answer += newNum;
		pq.push(newNum);
	}

	cout << answer;

	return 0;
}
