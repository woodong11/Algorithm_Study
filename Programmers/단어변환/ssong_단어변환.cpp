#include <iostream>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>

using namespace std;

int visited[51];
int stSize;
int ans = 51;

struct W {
	string word;
	int cnt;
};

int cmpX(string strN, string strX) {
	int cnt = 0;
	for (int i = 0; i < stSize; i++)
	{
		if (strN[i] != strX[i]) {
			cnt++;
		}
	}
	if (cnt == 1) return 1; // 하나만 달라~~ 가능
	return 0;
}

void bfs(string beginSt, string target, vector<string> words) {
	queue<W>q;
	q.push({ beginSt, 0 });
	W now;
	W next;

	while (!q.empty()) {
		now = q.front();
		q.pop();
		if (now.word == target) {
			ans = min(ans, now.cnt);
		}

		for (int i = 0; i < words.size(); i++)
		{
			if (visited[i] == 1) continue;

			// 한 글자만 바뀌었는지 체크(1)
			int cmpWord = cmpX(now.word, words[i]); // 지금, 다음 비교
			if (cmpWord == 0) continue;

			visited[i] = 1;
			q.push({ words[i] , now.cnt + 1 });
		}
	}
}


int solution(string begin, string target, vector<string> words) {
	vector<string>::iterator iter;
	iter = find(words.begin(), words.end(), target);
	if (iter == words.end()) return 0; // list에 target 없을때

	stSize = begin.length();
	bfs(begin, target, words);
	if (ans == 51) return 0;
	return ans;
}
