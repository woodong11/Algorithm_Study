#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

int parent[101];
int ancestors[101];
int N;
int st, en;
int M;

// st의 조상을 찾는 재귀함수, DAT인 ancestors에 촌수를 저장
void find_ancestors_of_st(int child, int level)
{
	ancestors[child] = level;
	if (parent[child] == 0) return;
	find_ancestors_of_st(parent[child], level + 1);
}

int main()
{
	memset(ancestors, -1, sizeof(ancestors)); // -1로 초기화, 자기자신의 촌수를 0으로 표시, 조상이 아닌 사람은 0으로 표시하여 구별
	cin >> N;
	cin >> st >> en;
	cin >> M;

	for (int i = 0; i < M;i++) {
		int to, from;
		cin >> to >> from;
		parent[from] = to;
	}

	find_ancestors_of_st(st, 0);

	int cnt = 0; // en의 조상(현재는 자기 자신)과의 촌수

	while (en != 0) {
		if (ancestors[en] != -1) {
			cnt += ancestors[en];
			break;
		}
		en = parent[en]; // en을 en의 조상으로 바꿔줌
		cnt++;
	}

	if (en) {
		cout << cnt;
	}
	else {
		cout << -1;
	}

	return 0;
}
