#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct point {
	int y, x, num;//flag가 0이면서 num ==0이면 맨처음	
	int idx;
};
struct xpoint {
	int y, x;
	vector<point> v;
};
vector<point> tow;
int dy[] = { 0,1,0,-1,-1,1,1,-1 }, dx[] = { 1,0,-1,0,1,1,-1,-1 };
int N, M, K, cnt, T, result_num;
int map[12][12];
point find_wek() { //cnt가 tow의 인덱스
	int minval = 21e8, minidx, minnum;
	for (int i = 0; i < cnt; i++) {
		int  val = map[tow[i].y][tow[i].x];
		if (val == 0)
			continue;
		if (minval > val) {
			minval = val;
			minidx = tow[i].idx;
			minnum = tow[i].num;
		}
		else if (minval == val && minnum < tow[i].num) {
			minidx = tow[i].idx;
			minnum = tow[i].num;
		}
		else if (minval == val && minnum == tow[i].num) {
			int tp1 = tow[i].y + tow[i].x;
			int tp2 = tow[minidx].y + tow[minidx].x;
			if (tp1 > tp2 || (tp1 == tp2 && tow[i].x > tow[minidx].x))
				minidx = i;
		}
	}
	if (minval == 21e8)
		return { 0,0 };
	else {
		result_num = minidx;
		return tow[minidx];
	}

}
point find_str() {
	int maxval = 0, maxidx, maxnum;
	for (int i = 0; i < cnt; i++) {
		int val = map[tow[i].y][tow[i].x];
		if (val == 0)
			continue;
		if (maxval < val) {
			maxval = val;
			maxidx = tow[i].idx;
			maxnum = tow[i].num;
		}
		else if (maxval == val && maxnum > tow[i].num) {
			maxidx = tow[i].idx;
			maxnum = tow[i].num;
		}
		else if (maxval == val && maxnum == tow[i].num) {
			int tp1 = tow[i].y + tow[i].x;
			int tp2 = tow[maxidx].y + tow[maxidx].x;
			if (tp1 < tp2 || (tp1 == tp2 && tow[i].x < tow[maxidx].x))
				maxidx = i;
		}

	}
	if (maxval == 0)
		return { 0,0 };
	else
		return tow[maxidx];
}
point find_next(point next) {
	if (next.y <= 0)
		next.y += N;
	else if (next.y > N)
		next.y = 1;
	if (next.x <= 0)
		next.x += M;
	else if (next.x > M)
		next.x = 1;
	return next;
}
vector<point> attack(point st, point ed) {
	int tmp[12][12] = { 0, };
	int min_dist = 0;
	//레이저
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			tmp[i][j] = 21e8;
		}
	}
	tmp[st.y][st.x] = 0;
	queue<xpoint> q;
	vector<point> t;
	t.push_back({ st.y,st.x });
	q.push({ st.y,st.x,t });
	while (!q.empty()) {
		xpoint now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			xpoint next = now;
			next.y = now.y + dy[i];
			next.x = now.x + dx[i];
			point temp;
			if (next.y == 0 || next.x == 0 || next.y > N || next.x > M)
				temp = find_next({ next.y,next.x });
			else
				temp = find_next({ next.y,next.x });
			next.y = temp.y, next.x = temp.x;
			if (tmp[next.y][next.x] < tmp[now.y][now.x] + 1)
				continue;
			if (map[next.y][next.x] == 0)
				continue;
			next.v.push_back({ next.y,next.x });
			tmp[next.y][next.x] = tmp[now.y][now.x] + 1;
			if (next.y == ed.y && next.x == ed.x )
				return next.v;
			q.push(next);
		}
	}
	//폭탄
	point now = ed;
	vector<point> vec;
	for (int i = 0; i < 8; i++) {
		point next = { 0 };
		next.y = now.y + dy[i];
		next.x = now.x + dx[i];
		if (next.y == 0 || next.x == 0 || next.y > N || next.x > M)
			next = find_next(next);
		if (map[next.y][next.x] == 0)
			continue;
		vec.push_back({ next.y, next.x });
	}
	return vec;
}

void input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
			if (map[i][j] != 0) {
				tow.push_back({ i,j,0,cnt });
				cnt++;
			}
		}
	}

}
int result;
int main() {
	input();

	for (int i = 1; i <= K; i++) {
		int visited[12][12] = { 0, };
		point wek, str;
		vector<point> vec;
		wek = find_wek();
		str = find_str();
		tow[result_num].num = i;
		if (wek.y == str.y && wek.x == str.x)
			break;
		vec = attack(wek, str);
		map[wek.y][wek.x] = map[wek.y][wek.x] + N + M;
		int size = vec.size();
		int power = map[wek.y][wek.x] / 2;
		//
		for (int i = 0; i < size; i++) {
			if (vec[i].y == str.y && vec[i].x == str.x)
				continue;
			if (vec[i].y == wek.y && vec[i].x == wek.x)
				continue;
			map[vec[i].y][vec[i].x] -= power;
			visited[vec[i].y][vec[i].x] = 1;
			if (map[vec[i].y][vec[i].x] < 0)
				map[vec[i].y][vec[i].x] = 0;
		}
		//공격해야할 부분에 공격
		map[str.y][str.x] -= map[wek.y][wek.x];
		if (map[str.y][str.x] < 0)
			map[str.y][str.x] = 0;
		//보수
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (visited[i][j] == 1 || map[i][j] == 0 || (i == wek.y && j == wek.x) || (i == str.y && j == str.x))
					continue;
				map[i][j]++;
			}
		}

	}
	result = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			result = max(result, map[i][j]);
		}
	}
	cout << result;


	return 0;

}
