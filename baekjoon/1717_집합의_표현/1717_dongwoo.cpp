#include <iostream>
using namespace std;

int N, M;
int parent[1000001];

int find(int target) {
	if (target == parent[target]) return target;
	int ret = find(parent[target]);
	parent[target] = ret;
	return ret;
}

void setUnion(int a, int b) {
	int t1 = find(a);
	int t2 = find(b);
	if (t1 == t2) return;
	parent[t2] = t1;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> N >> M;

	// 부모 초기화
	for (int i = 0; i <= N; i++){
		parent[i] = i;
	}

	// 연산 수행
	int command, input1,input2;
	for (int i = 0; i < M; i++) {
		cin >> command >> input1 >> input2;

		if (command == 0){
			setUnion(input1, input2);
		}
		else {
			if (find(input1) == find(input2)) cout << "YES\n";
			else cout << "NO\n";
		}
	}

	return 0;
}
