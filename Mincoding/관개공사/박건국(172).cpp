#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int parent[2000];
int N, K;
struct node {
	int a, b;
	int price;
};
struct yx {
	int y, x;
};
struct cmp {
	bool operator() (node a, node b) {
		return a.price > b.price;
	}
};
priority_queue<node, vector<node>, cmp> pq;

void init() {
	for (int i = 0; i < N; i++) {
		parent[i] = i;
	}
}

int find(int tar) {
	if (tar == parent[tar])
		return tar;

	int ret = find(parent[tar]);
	parent[tar] = ret;
	return ret;
}
void setUnion(int a, int b) {
	int t1 = find(a);
	int t2 = find(b);
	if (t1 == t2)
		return;
	parent[t2] = t1;
}

int main() {
	cin >> N >> K;
	init();
	int flag = 0;
	int node_cnt = 0;
	int result = 0;
	vector<yx> locate;

	for (int i = 0; i < N; i++) {
		int y, x;
		cin >> y >> x;
		locate.push_back({ y,x });
	}
	for (int i = 0; i < locate.size(); i++) {
		for (int j = i + 1; j < locate.size(); j++) {
			int price = (locate[i].y - locate[j].y) * (locate[i].y - locate[j].y) + (locate[i].x - locate[j].x) * (locate[i].x - locate[j].x);
			if (price >= K) {
				node x, y;
				x = { i,j,price }, y = { i,j,price };
				pq.push(x);
				pq.push(y);
			}
		}
	}
	while (!pq.empty()) {
		node x = pq.top();
		pq.pop();
		if (find(x.a) == find(x.b))
			continue;
		setUnion(x.a, x.b);
		result += x.price;
		node_cnt++;
		if (node_cnt == N - 1) {
			flag = 1;
			break;
		}
	}
	if (flag == 1)
		cout << result;
	else if (flag == 0)
		cout << -1;
	return 0;
}
