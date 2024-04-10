#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<algorithm>

using namespace std;


int N, M, K;
int map[12][12];
int visited[12][12];
int relation_attack[12][12];

int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };

int bomb_dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int bomb_dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int ans;
int t;


struct pos {
	int y, x;
};

struct ptop_info {
	// 공격력, 가장 최근 공격, 행과 열의 합, 열, struct route
	int y, x, hp, latest_attack, rc_sum;
	vector<pos> route;
};


vector<ptop_info> all_ptop;
vector<ptop_info> temp_ptop;
ptop_info striker, defender;

bool sorting(ptop_info a, ptop_info b) {
	if (a.hp == b.hp) {
		if (a.latest_attack == b.latest_attack) {
			if (a.rc_sum == b.rc_sum) {
				return a.x > b.x;
			}
			return a.rc_sum > b.rc_sum;
		}
		return a.latest_attack > b.latest_attack;
	}
	return a.hp < b.hp;
}


void print() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] == 0) printf("# ");
			else if (i == striker.y && j == striker.x) printf("S ");
			else if (i == defender.y && j == defender.x) printf("E ");
			else printf("P ");
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] == 0) printf("# ");
			else printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("======================== \n");
}


void input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 0) continue;
			all_ptop.push_back({ i, j, map[i][j], 1, i + j });
		}
	}
}

void find_strikerNdefenter() {

	sort(all_ptop.begin(), all_ptop.end(), sorting);

	all_ptop[0].hp += (N + M); // 공격력 증가
	map[all_ptop[0].y][all_ptop[0].x] = all_ptop[0].hp;
	all_ptop[0].latest_attack = t;
	striker = all_ptop[0];

	defender = all_ptop[all_ptop.size() - 1];
}


void init_attack() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			visited[i][j] = 0;
			relation_attack[i][j] = 0;
		}
	}
}


void repair_ptan() {
	temp_ptop = {};
	for (int i = 0; i < all_ptop.size(); i++)
	{
		if (map[all_ptop[i].y][all_ptop[i].x] == 0) continue;

		if (relation_attack[all_ptop[i].y][all_ptop[i].x] == 0) {
			all_ptop[i].hp++;
			map[all_ptop[i].y][all_ptop[i].x]++;
		}
		else {
			all_ptop[i].hp = map[all_ptop[i].y][all_ptop[i].x];
		}
		temp_ptop.push_back(all_ptop[i]);
	}
	all_ptop = temp_ptop;
}


void attack_ptan() {
	int ny, nx = 0;

	//defender 주위 8개 방향 피해
	for (int i = 0; i < 8; i++)
	{
		ny = defender.y + bomb_dy[i];
		nx = defender.x + bomb_dx[i];

		if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
			ny = (ny + N) % N;
			nx = (nx + M) % M;
		}
		if (map[ny][nx] == 0) continue;
		else if (ny == striker.y && nx == striker.x) {
			// relation_attack[ny][nx] = 1;
			continue;
		}
		map[ny][nx] = max(0, map[ny][nx] - (striker.hp / 2));
		relation_attack[ny][nx] = 1;
	}
}


void attack_laser() {

	init_attack();

	int ny = 0, nx = 0;
	queue<ptop_info> q;
	ptop_info now_pt = {}, next_pt = {};
	q.push(striker);
	int laser_flag = 0;

	while (!q.empty()) {
		now_pt = q.front();
		visited[now_pt.y][now_pt.x] = 1;
		q.pop();

		if (now_pt.y == defender.y && now_pt.x == defender.x) {
			laser_flag = 1;
			break;
		}
		for (int i = 0; i < 4; i++)
		{
			ny = now_pt.y + dy[i];
			nx = now_pt.x + dx[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
				ny = (ny + N) % N;
				nx = (nx + M) % M;
			}
			if (map[ny][nx] == 0) continue;
			else if (visited[ny][nx] == 1) continue;

			next_pt.y = ny;
			next_pt.x = nx;
			next_pt.route = now_pt.route;
			next_pt.route.push_back({ now_pt.y, now_pt.x });
			visited[ny][nx] = 1;
			q.push(next_pt);
		}
	}

	map[defender.y][defender.x] = max(0, map[defender.y][defender.x] - striker.hp);
	relation_attack[defender.y][defender.x] = 1;	// 공격받은 포탑
	relation_attack[striker.y][striker.x] = 1;		// 공격한 포탑

	// now_pt의 route 확인
	if (laser_flag == 1) {
		for (int i = 1; i < now_pt.route.size(); i++) {
			map[now_pt.route[i].y][now_pt.route[i].x] = max(0, map[now_pt.route[i].y][now_pt.route[i].x] - (striker.hp / 2));
			relation_attack[now_pt.route[i].y][now_pt.route[i].x] = 1; // 공격과 관련된 포탑
		}
	}

	else {
		// 포탄 공격
		attack_ptan();
	}
	// 수리
	repair_ptan();
}

void process() {

	for (int i = 0; i < K; i++)
	{
		t = i + 2;
		find_strikerNdefenter();
		attack_laser();

		if (all_ptop.size() == 1) break;
	}
}


void print_ans() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] > ans) {
				ans = map[i][j];
			}
		}
	}
	cout << ans << "\n";
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	input();
	process();
	print_ans();
	return 0;
}
