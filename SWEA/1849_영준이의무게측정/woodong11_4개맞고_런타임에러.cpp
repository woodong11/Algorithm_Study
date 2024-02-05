#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int T, N, M;

int parent[100001];
int parentGap[100001];
//int rank[100001];


int findRoot(int node) {
	if (node == parent[node])
		return node;
	findRoot(parent[node]);
}

int findGap(int node, int sum) {
	if (node == parent[node])
		return sum;
	findGap(parent[node], sum + parentGap[node]);
}

void put(int a, int b, int w) {

	int aRoot = findRoot(a);
	int bRoot = findRoot(b);
	
	parent[aRoot] = bRoot;
	
	if (parent[a] == b) {
		parentGap[a] = -w;
	}
	else {
		int rootToA = findGap(a, 0);
		int rootToB = findGap(b, 0);
		parentGap[aRoot] = -(w + rootToA - rootToB);
	}

	//cout << rootToA << " " << rootToB;

	return;
}

void search(int a, int b) {
	if (findRoot(a) == findRoot(b)) {
		//int de = -1;
		cout << findGap(b, 0) - findGap(a, 0)<< " ";
	}
		
	else
		cout << "UNKNOWN ";
}

void init() {
	memset(parent, 0, sizeof(parent));
	memset(parentGap, 0, sizeof(parentGap));
}

int main() {

	 cin >> T;
	 for (int tc = 1; tc <= T; tc++) {
		 cin >> N >> M;
		 for (int i = 1; i <= N; i++)
		 {
			 parent[i] = i;
		 }

		 char type;
		 int a, b, w;
		 cout << "#" << tc << " ";
		 for (int i = 0; i < M; i++)
		 {
			 cin >> type;
			 if (type == '!') {
				 cin >> a >> b >> w;
				 put(a, b, w);
			 }
			 else {
				 cin >> a >> b;
				 search(a, b);
			 }
		 }
	 
		 cout << "\n";
	 }

	 int de = -1;

	return 0;
}
