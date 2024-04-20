#include <iostream>
#include <queue>

using namespace std;

struct point {
	int y, x;
};
struct ct {
	int cnt;
	vector<point> vec;
	int num;
};
vector<ct> vec;
int map[30][30], map1[30][30], dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 };
int N, group = 1, result;

void bfs1(int num,int y, int x,int g) {
	int cnt = 1;
	/*int tmp_visited[30][30] = { 0, };*/
	vector<point> tmp_vec;
	queue<point> q;
	map1[y][x] = g;
	q.push({ y,x });
	while (!q.empty()) {
		point now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			point next = {};
			next.y = now.y + dy[i];
			next.x = now.x + dx[i];
			if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N)
				continue;
			/*if (tmp_visited[next.y][next.x] != 0)
				continue;*/
			if (map[next.y][next.x] != num) {
				/*tmp_visited[next.y][next.x] = 1;*/
				tmp_vec.push_back({ next.y,next.x });
				continue;
			}
			if (map1[next.y][next.x] != 0)
				continue;
			/*tmp_visited[next.y][next.x] = 1;*/
			map1[next.y][next.x] = g;
			cnt++;
			q.push(next);
		}
	}
	vec.push_back({ cnt,tmp_vec,num });
}
int get_score() {
	int size = vec.size();
	int tmp_cnt = 0;
	for (int i = 1; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			int tmp_size = vec[i].vec.size();
			int tmp_size1 = vec[j].vec.size();
			int tmp_tmp_cnt = 0;
			int tmp_tmp_cnt1 = 0;
			for (int k = 0; k < tmp_size; k++) {
				if (map1[vec[i].vec[k].y][vec[i].vec[k].x] == j)
					tmp_tmp_cnt++;
			}
			for (int k = 0; k < tmp_size1; k++) {
				if (map1[vec[j].vec[k].y][vec[j].vec[k].x] == i)
					tmp_tmp_cnt1++;
			}
			int t1 = (vec[i].cnt + vec[j].cnt) * vec[i].num* vec[j].num* tmp_tmp_cnt;
			int t2 = (vec[i].cnt + vec[j].cnt) * vec[i].num * vec[j].num * tmp_tmp_cnt1;
			if (tmp_tmp_cnt >= tmp_tmp_cnt1)
				tmp_cnt += t1;
			else
				tmp_cnt += t2;
		}
	}
	return tmp_cnt;
}
void rotate() {
	int std = N / 2;
	int tmp_map[30][30] = { 0, };
	tmp_map[std][std] = map[std][std];
	for (int i = 1; i <= std; i++) {
		for (int j = 0; j < 4; j++) {
			int dir = (j + 3) % 4;
			point now = { std + dy[j]*i, std + dx[j]*i };
			point next = { std + dy[dir] * i,std + dx[dir] * i };
			tmp_map[next.y][next.x] = map[now.y][now.x];
		}
	}
	
	queue<int>q1, q2, q3, q4;
	for (int i = 0; i < std; i++) {
		for (int j = 0; j < std; j++) {
			q1.push(map[i][j]);
			q2.push(map[i][std + 1 +j]);
			q3.push(map[std + 1 + i][j]);
			q4.push(map[std + 1 + i][std + 1 + j]);
		}
	}
	for (int i = std - 1; i >= 0; i--) {
		for (int j = 0; j < std; j++) {
			tmp_map[j][i] = q1.front();
			q1.pop();
			tmp_map[j][std + 1 + i] = q2.front();
			q2.pop();
			tmp_map[std + 1 + j][i] = q3.front();
			q3.pop();
			tmp_map[std + 1 + j][std + 1 + i] = q4.front();
			q4.pop();
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = tmp_map[i][j];
		}
	}
}

void input() {//인풋 받고 초기 예술점수까지 구하기.
	cin >> N;
	vec.push_back({ 0 }); // vec인덱스를 1부터 시작하게하려고
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	int group = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map1[i][j] != 0)
				continue;
			bfs1(map[i][j], i, j, group);
			group++;
		}
	}
	int temp_result = get_score();
	result += temp_result;
}
void mem_set() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map1[i][j] = 0;
		}
	}
	vec = {};
	vec.push_back({ 0 });
}


int main() {
	input();
	for (int t = 0; t < 3; t++) {
		mem_set();
		rotate();
		int group = 1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map1[i][j] != 0)
					continue;
				bfs1(map[i][j], i, j, group);
				group++;
			}
		}
		int temp_result = get_score();
		result += temp_result;
	}
	cout << result;
}
