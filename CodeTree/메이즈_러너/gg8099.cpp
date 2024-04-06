#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct point {
	int y, x;
};
struct peo {
	int y, x, life, flag;
};
vector<peo> per;
int N, M, K, result;
int map[12][12], dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
point goal;
int per_cnt;
void input() {
	cin >> N >> M >> K;
	per_cnt = M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		int y, x;
		cin >> y >> x;
		per.push_back({ y,x,1,0 });
		map[y][x] += -1;
	}
	int y, x;
	cin >> y >> x;
	goal = { y,x };
	map[y][x] = 10;
	for (int i = 0; i <= N + 1; i++) {//벽 만들기
		map[0][i] = -5;
		map[i][0] = -5;
		map[N + 1][i] = -5;
		map[i][N + 1] = -5;
	}
}

void per_move() {
	for (int x = 0; x < per.size(); x++) {
		point now = { per[x].y, per[x].x };
		int st_dist = abs(now.y - goal.y) + abs(now.x - goal.x);
		int min_dist = 9999, min_idx = 0;
		if (per[x].life == 0)
			continue;
		for (int i = 0; i < 4; i++) {
			point next = { 0 };
			next.y = now.y + dy[i];
			next.x = now.x + dx[i];
			if (next.y <= 0 || next.x <= 0 || next.x > N || next.y > N)
				continue; //맵 밖
			if (map[next.y][next.x] >= 1 && map[next.y][next.x] <= 9)
				continue; //벽만난경우
			if (map[next.y][next.x] == 10) { //출구인경우
				result++;
				per[x].life = 0;
				map[per[x].y][per[x].x]++;
				per_cnt--;
				break;
			}
			int dist = abs(next.y - goal.y) + abs(next.x - goal.x);
			if (dist > st_dist)
				continue;
			if (dist < min_dist) {
				min_dist = dist, min_idx = i;
			}
		}
		if (min_dist == 9999)
			continue;
		map[per[x].y][per[x].x]++;
		per[x].y += dy[min_idx], per[x].x += dx[min_idx];
		map[per[x].y][per[x].x]--;
		result++;
	}
}
void func(point before, point after) {
	int a = abs(map[before.y][before.x]);
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < per.size(); j++) {
			if (per[j].y == before.y && per[j].x == before.x && per[j].life != 0 && per[j].flag == 0){
				per[j] = { after.y,after.x,1,1 };
			}

		}
	}
}
void mk_sq() {
	for (int i = 0; i < per.size(); i++) {
		per[i].flag = 0;
	}
	int min_dist = 9999, min_idx;
	for (int i = 0; i < per.size(); i++) {
		if (per[i].life == 0)
			continue;
		int yval = abs(per[i].y - goal.y);
		int xval = abs(per[i].x - goal.x);
		int mxval = max(yval, xval);
		if (mxval < min_dist) {
			min_idx = i;
			min_dist = mxval;
			continue;
		}
		if (mxval == min_dist) {
			point st1, st2; //st1은 기존 2는 새로운놈
			int ytmp1, xtmp1, ytmp2, xtmp2;
			ytmp1 = max(goal.y, per[min_idx].y);
			xtmp1 = max(goal.x, per[min_idx].x);
			ytmp2 = max(goal.y, per[i].y);
			xtmp2 = max(goal.x, per[i].x);
			st1 = { ytmp1 - min_dist,xtmp1 - min_dist };
			st2 = { ytmp2 - mxval, xtmp2 - mxval };
			while (1) {
				int flag = 0;
				if (st1.y < 1) {
					st1.y++;
					flag = 1;
				}
				if (st1.x < 1) {
					st1.x++;
					flag = 1;
				}
				if (st2.y < 1) {
					st2.y++;
					flag = 1;
				}
				if (st2.x < 1) {
					st2.x++;
					flag = 1;
				}
				if (flag == 0)
					break;
			}
			if (st1.y < st2.y)
				continue;
			else if (st1.y > st2.y)
				min_idx = i;
			else if (st1.x > st2.x)
				min_idx = i;
		}
	}
	if (min_dist == 9999)
		return;
	point st, ed;
	int ytmp, xtmp;
	ytmp = max(goal.y, per[min_idx].y);
	xtmp = max(goal.x, per[min_idx].x);
	ed = { ytmp, xtmp };
	st = { ytmp - min_dist,xtmp - min_dist };
	while (1) {
		int flag = 0;
		if (st.y < 1) {
			st.y++, ed.y++;
			flag = 1;
		}
		if (st.x < 1) {
			st.x++, ed.x++;
			flag = 1;
		}
		if (flag == 0)
			break;
	}
	point st_ = st, ed_ = ed;
	int t = (min_dist + 1) / 2;
	int tmp[11][11] = { 0, };
	for (int i = 0; i < t; i++) {
		int len = ed.y - st.y + 1;
		for (int j = 0; j < len; j++) {
			tmp[st.y][st.x + j] = map[ed.y - j][st.x];
			if (map[ed.y - j][st.x] < 0)
				func({ ed.y - j, st.x }, { st.y,st.x + j });
			tmp[st.y + j][ed.x] = map[st.y][st.x + j];
			if (map[st.y][st.x + j] < 0)
				func({ st.y,st.x + j }, { st.y + j,ed.x });
			tmp[ed.y][ed.x - j] = map[st.y + j][ed.x];
			if (map[st.y + j][ed.x] < 0)
				func({ st.y + j,ed.x }, { ed.y,ed.x - j });
			tmp[ed.y - j][st.x] = map[ed.y][ed.x - j];
			if (map[ed.y][ed.x - j] < 0)
				func({ ed.y,ed.x - j }, { ed.y - j,st.x });
		}
		st.y++, st.x++, ed.y--, ed.x--;
		if (st.y == ed.y && st.x == ed.x)
			tmp[st.y][st.x] = map[st.y][st.x];
	}

	for (int i = st_.y; i <= ed_.y; i++) {
		for (int j = st_.x; j <= ed_.x; j++) {
			if (tmp[i][j] >= 1 && tmp[i][j] <= 9)
				tmp[i][j]--;
			map[i][j] = tmp[i][j];
			if (map[i][j] == 10)
				goal.y = i, goal.x = j;
		}
	}
}

int main() {
	input();
	for (int i = 0; i < K; i++) {

		per_move();
		mk_sq();
		if (per_cnt == 0)
			break;
	}
	cout << result << endl;
	cout << goal.y << " " << goal.x;
}
