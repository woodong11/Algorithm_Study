# define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

int n, pp1, pp2, m;
vector<int> relative[101];
int visited[101];
int ans;

void dfs(int now, int end, int cnt) {
	visited[now] = 1;
	if (now == end) {
		ans = cnt;
		return;
	}
	for (int i = 0; i < relative[now].size(); i++)
	{
		int next = relative[now][i];
		if (!visited[next]) dfs(next, end, cnt+1);
	}
}
void input() {
	int x, y;
	cin >> n;
	cin >> pp1 >> pp2;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> x >> y;
		relative[x].push_back(y);
		relative[y].push_back(x);
	}
}

int main() {
	input();
	dfs(pp1, pp2, 0);
	if (ans == 0) cout << "-1";
	else cout << ans;
}
