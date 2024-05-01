#include <iostream>

using namespace std;

int parent[1000001];
int n, m;

int find(int tar) {
	if (tar == parent[tar])
		return tar;
	int ret = find(parent[tar]);
	parent[tar] = ret;
	return ret;
}
void setunion(int a, int b) {
	int t1 = find(a);
	int t2 = find(b);
	if (t1 == t2)
		return;
	parent[t2] = t1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i <= n; i++) {
		parent[i] = i;
	}
	for (int i = 0; i < m; i++) {
		int x, a, b;
		cin >> x >> a >> b;
		
		if (x == 0) {
			if (a == b)
				continue;
			setunion(a, b);
		}
		else if (x == 1) {
			if (find(a) == find(b))
				cout << "YES" << '\n';
			else
				cout << "NO" << '\n';
		}
	}

	return 0;
}
