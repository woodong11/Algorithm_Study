#include<iostream>
#include<vector>
using namespace std;
vector<int> graph[101];
bool visited[101];
int start;
int finish;
int found;
void dfs(int now, int level)
{
	if (visited[now])
	{
		return;
	}
	if (now == finish)
	{
		found = level;
		return;
	}
	visited[now] = true;
	for (int i = 0; i < graph[now].size(); i++)
	{
		dfs(graph[now][i], level + 1);
	}
	visited[now] = false;
}
int main()
{
	int n;
	int m;
	cin >> n;
	cin >> start >> finish;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	dfs(start, 0);
	if (found)
	{
		cout << found;
	}
	else
		cout << -1;
	return 0;
}
