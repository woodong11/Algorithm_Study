#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct cmp {
	bool operator() (int a, int b) {
		return a > b;
	}
};

int main() {
	int N;
	cin >> N;
	priority_queue<int, vector<int>, cmp>pq;
	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		pq.push(a);
	}
	if (N == 1) {
		cout << 0;
		return 0;
	}
	int sum = 0;
	while (!pq.empty()) {
		if (pq.size() == 1)
			break;
		int a = pq.top();
		pq.pop();
		int b = pq.top();
		pq.pop();
		int tmp = a + b;
		sum += tmp;
		pq.push(tmp);
	}
	cout << sum;
	return 0;
}
