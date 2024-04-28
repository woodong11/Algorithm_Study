#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

struct Gem
{
	int m;
	int v;
};

int N, K;
long long result;
vector<Gem> gems;
multiset<int> bags;

bool cmp(Gem a, Gem b)
{
	if (a.v == b.v)
	{
		return a.m < b.m;
	}
	else
	{
		return a.v > b.v;
	}
}

int main()
{
	cin >> N >> K;
  
	for (int i = 0; i < N; i++)
	{
		int temp1, temp2;
		cin >> temp1 >> temp2;
		gems.push_back({ temp1, temp2 });
	}
  
	sort(gems.begin(), gems.end(), cmp);
  
	for (int i = 0; i < K; i++)
	{
		int temp;
		cin >> temp;
		bags.insert(temp);
	}
  
	for (Gem i : gems)
	{
		if (bags.lower_bound(i.m) == bags.end())
		{
			continue;
		}
		else
		{
			result += i.v;
			bags.erase(bags.lower_bound(i.m));
		}
	}
  
	cout << result;
  
	return 0;
}
