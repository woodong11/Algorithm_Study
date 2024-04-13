#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
	int y, x;
};
struct per {
	int y, x, dir, s, gun, score, idx;
};
int map[22][22], dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 };

vector<int> gun[410];
vector<per> peo;
int n, m, k, flag;
void get_gun(int num) {
	int tmp_gun_loc = map[peo[num].y][peo[num].x];
	if (gun[tmp_gun_loc].size() == 0)
		return;
	sort(gun[tmp_gun_loc].begin(), gun[tmp_gun_loc].end());
	int tmp_pow = gun[tmp_gun_loc].back();
	if (peo[num].gun < tmp_pow) {
		gun[tmp_gun_loc].pop_back();
		if (peo[num].gun != 0){
			gun[tmp_gun_loc].push_back(peo[num].gun);
			peo[num].gun = 0;
		}
		peo[num].gun = tmp_pow;
	}
}
void lose_per(int num) {
	if (peo[num].gun != 0) {
		int tmp_gun = map[peo[num].y][peo[num].x];
		gun[tmp_gun].push_back(peo[num].gun);
		peo[num].gun = 0;
	}
	point now = { peo[num].y,peo[num].x };
	point next = now;
	int dir = peo[num].dir;
	while (1) {
		int flag = 0;
		next.y = now.y + dy[dir];
		next.x = now.x + dx[dir];
		if (next.y <= 0 || next.x <= 0 || next.y > n || next.x > n) {
			dir = (dir + 1) % 4;
			continue;
		}
		for (int i = 0; i < peo.size(); i++) {
			if (i == num)
				continue;
			if (peo[i].y == next.y && peo[i].x == next.x) {
				dir = (dir + 1) % 4;
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			continue;
		peo[num].y = next.y, peo[num].x = next.x, peo[num].dir = dir;
		int tmp_gun_loc = map[next.y][next.x];
		if (gun[tmp_gun_loc].size() != 0) {
			get_gun(num);
		}
		break;
	}

}

void move() {
	for (int i = 0; i < peo.size(); i++) {
		flag = 0;
		point now = { peo[i].y,peo[i].x };
		point next = now;
		next.y = dy[peo[i].dir] + now.y;
		next.x = dx[peo[i].dir] + now.x;
		if (next.y <= 0 || next.x <= 0 || next.y > n || next.x > n) {
			peo[i].dir = (peo[i].dir + 2) % 4;
			next.y = dy[peo[i].dir] + now.y;
			next.x = dx[peo[i].dir] + now.x;
		}
		peo[i].y = next.y, peo[i].x = next.x;
		for (int j = 0; j < peo.size(); j++) {
			if (i == j)
				continue;
			if (peo[j].y == peo[i].y && peo[j].x == peo[i].x) {//이동한 방향에 플레이어가 있어서 싸워야 하는 경우
				int tmp1 = peo[i].gun + peo[i].s;
				int tmp2 = peo[j].gun + peo[j].s;
				if ((tmp1 > tmp2) || (peo[i].s > peo[j].s && tmp1 == tmp2)) {
					int tmp_score = tmp1 - tmp2;
					peo[i].score += tmp_score;
					lose_per(j);
					get_gun(i);
					flag = 1;
				}
				else if (tmp2 > tmp1 || (peo[i].s < peo[j].s && tmp1 == tmp2)) {
					int tmp_score = tmp2 - tmp1;
					peo[j].score += tmp_score;
					lose_per(i);
					get_gun(j);
				}
			}
		}
		int tmp_gun_loc = map[peo[i].y][peo[i].x];
		if (gun[tmp_gun_loc].size() != 0 && flag == 0)
			get_gun(i);
	}
}

void input() {
	cin >> n >> m >> k;
	int cnt = 0, tmp;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] = cnt;
			cnt++;
			cin >> tmp;
			if (tmp != 0) {
				gun[map[i][j]].push_back(tmp);
			}
		}
	}
	for (int i = 0; i < m; i++) {
		int y, x, dir, s;
		cin >> y >> x >> dir >> s;
		peo.push_back({ y,x,dir,s,0,0,i });
	}
}

int main() {
	input();
	for (int i = 0; i < k; i++) {

		move();
	}
	for (int i = 0; i < peo.size(); i++) {
		cout << peo[i].score << " ";
	}
	return 0;
}
