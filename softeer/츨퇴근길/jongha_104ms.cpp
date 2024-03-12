#include<iostream>
#include<vector>
#include<queue>

using namespace std;


int a, b, n, m, cnt;
int visited1[100001], visited2[100001], visited3[100001], visited4[100011];
vector<int> v1[100001], v2[100001];

void go(int s, int visited[], vector<int> v[]) {
	if (visited[s]) {
		return;
	}
	else { visited[s] = 1; }

	for (int t : v[s]) {
		go(t, visited, v);
	}
}

int check(int visited1[], int visited2[], int visited3[], int visited4[]) {
	for (int i = 1; i <= n; i++) {
		if (visited1[i] && visited2[i] && visited3[i] && visited4[i]) {
			cnt++;
		}
	}

	return cnt;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		v1[a].push_back(b);
		v2[b].push_back(a);
	}

	cin >> a >> b;

	visited1[b] = 1, visited2[a] = 1;

	go(a, visited1, v1);
	go(b, visited2, v1);
	
	go(a, visited3, v2);
	go(b, visited4, v2);
	
	cout << check(visited1, visited2, visited3, visited4) - 2;

	return 0;
}
