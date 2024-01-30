#include <iostream>
#include <vector>
using namespace std;

int n, st, en, num;
vector<int> family[100];
int map[101][101];
int cnt;
int visited[101];
int flag;
void func(int now)
{
	if (now == en)
	{
		cout << cnt;
		flag = 1;
		return;
	}
	for (int i = 0; i < n; i++)
	{
		if (visited[i] == 1)
			continue;
		if (map[now][i] == 0)
			continue;
		cnt++;
		visited[i] = 1;
		func(i);
		visited[i] = 0;
		cnt--;
	}
}

int main()
{
	cin >> n >> st >> en >> num;
	for (int i = 0; i < num; i++)
	{
		int from, to;
		cin >> from >> to;
		family[from].push_back(to);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < family[i].size(); j++)
		{
			map[i][family[i][j]] = 1;
			map[family[i][j]][i] = 1;
		}
	}
	func(st);
	if (flag ==0)
		cout << -1;

	return 0;

}
