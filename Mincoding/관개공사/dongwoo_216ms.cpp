// line벡터에 위치들 저장해놨다가
// costLine벡터에 두 위치, 거리 저장

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int N, K;
int parent[2001];

struct cool {
	int y;
	int x;
};

struct Node {
	int a;
	int b;
	int price;
};

vector <cool> line;
vector <Node> costLine;

bool compare(Node a, Node b) {
	return a.price < b.price;
}

void init() {
	for (int i = 0; i < N; i++)
	{
		parent[i] = i;
	}
}

int find(int target) {
	if (parent[target] == target) return target;
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

	cin >> N >> K;

	init();

	int y, x;
	for (int i = 0; i < N; i++)
	{
		cin >> y >> x;
		line.push_back({ y, x });
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = i+1; j < N; j++)
		{
			cool cool1 = line[i];
			cool cool2 = line[j];
			int dist = (pow(cool1.y - cool2.y, 2) + pow(cool1.x - cool2.x, 2));
			costLine.push_back({ i, j, dist });
		}
	}

	sort(costLine.begin(), costLine.end(), compare);
	

	int target = N - 1;
	int curNum = 0;
	int totalCost = 0;
	bool isOK = false;

	for (int i = 0; i < costLine.size(); i++)
	{
		int a = costLine[i].a;
		int b = costLine[i].b;
		int price = costLine[i].price;

		if (find(a) == find(b))
			continue;

		if (costLine[i].price < K)
			continue;

		setUnion(a, b);
		curNum++;
		totalCost += price;

		if (curNum == target) {
			isOK = true;
			break;
		}
	}

	if (isOK == true)
		cout << totalCost;
	else
		cout << -1;

	int de = -1;


	return 0;
}
