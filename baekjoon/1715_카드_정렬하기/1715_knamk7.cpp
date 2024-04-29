#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct cmp
{
	bool operator()(int a, int b)
	{
		return a > b;
	}
};

int main()
{
	int n;
	int result = 0;
	priority_queue<int, vector<int>, cmp> pq;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int tmp;
		cin >> tmp;
		pq.push(tmp);
	}
	while (pq.size() != 1)
	{
		int a, b;
		a = pq.top();
		pq.pop();
		b = pq.top();
		pq.pop();
		result += a + b;
		pq.push(a + b);
	}
	cout << result;
	return 0;
}
