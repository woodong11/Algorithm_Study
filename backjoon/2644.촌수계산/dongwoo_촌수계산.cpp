#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;


vector <int> alis[101];
int visited[101];
int none = -1;
int N, M, input1, input2;
int answer;

void dfs(int node, int cnt) {
	visited[node] = 1;
	
	if (node == input2) {
		answer = cnt;
		return;
	}

	for (int i = 0; i < alis[node].size(); i++)
	{
		if (visited[alis[node][i]] == 1)
			continue;

		dfs(alis[node][i], cnt + 1);		
	}
	//visited[node] = 0;

}


int main() {
	//freopen("sample_input.txt", "r", stdin);
	int from, to;
	cin >> N >> input1 >> input2;
	cin >> M;

	for (int i = 0; i < M; i++)
	{
		cin >> from >> to;
		alis[from].push_back(to);
		alis[to].push_back(from);
	}
	
	dfs(input1, 0);

	if (answer > 0) {
		cout << answer;
	}
	else
		cout << -1;

}