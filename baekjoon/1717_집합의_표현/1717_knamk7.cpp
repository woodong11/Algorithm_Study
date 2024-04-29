#include<iostream>
using namespace std;

int parent[1000000];

void init(int n)
{
	for (int i = 0; i <= n; i++)
	{
		parent[i] = i;
	}
}

int find(int target)
{
	if (target == parent[target]) return target;
	else
	{
		int ret = find(parent[target]);
		parent[target] = ret;
		return ret;
	}
}

void setUnion(int a, int b)
{
	if (find(a) == find(b)) return;
	else
	{
		parent[find(b)] = find(a);
	}
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	int n, m;
	cin >> n >> m;
	init(n);
	for (int i = 0; i < m; i++)
	{
		int cmd;
		cin >> cmd;
		if (cmd == 0)
		{
			int a, b;
			cin >> a >> b;
			setUnion(a, b);
		}
		else
		{
			int a, b;
			cin >> a >> b;
			if (find(a) == find(b))
			{
				cout << "YES\n";
			}
			else
			{
				cout << "NO\n";
			}
		}
	}
	return 0;
}
