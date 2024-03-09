#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct point {
	int y, x;
};
struct block {
	int y, x, cnt;
};
struct max_val {
	int tmp_block;
	int rain_block;
};

vector<point> tmp_route, max_route;


int map[20][20], visited[20][20], dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
int N, M, result;

void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}


void input() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}

max_val check_block(int y, int x, int val) {
	tmp_route = {};
	max_val return_th = { 1,0 };
	queue<point> q;
	q.push({ y,x });
	vector<point> zero_loca = {};
	tmp_route.push_back({ y,x });

	while (!q.empty()) {
		point now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			point next = { 0 };
			next.y = now.y + dy[i];
			next.x = now.x + dx[i];
			if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N)
				continue;
			if (visited[next.y][next.x] == 1)
				continue;
			if (map[next.y][next.x] == 0 || map[next.y][next.x] == val) {
				q.push(next);
				visited[next.y][next.x] = 1;
				tmp_route.push_back({ next.y,next.x });
				if (map[next.y][next.x] == 0) {
					zero_loca.push_back(next);
					return_th.rain_block++;
				}

				return_th.tmp_block++;
			}

		}
	}
	//0인 부분의 visited는 0으로 만들어 다른 숫자가 갈 수 있게
	for (int i = 0; i < zero_loca.size(); i++) {
		visited[zero_loca[i].y][zero_loca[i].x] = 0;
	}
	return return_th;
}
void map_ch() {
	for (int i = 0; i < max_route.size(); i++) {
		map[max_route[i].y][max_route[i].x] = 6;
	}
	max_route = {};
}

void grav() {
	for (int i = N - 1; i >= 1; i--) {
		for (int j = N - 1; j >= 0; j--) {
			if (map[i][j] != 6)
				continue;
			vector<int> vec;
			for (int y = i - 1; y >= 0; y--) {
				if (map[y][j] == -1)
					break;
				if (map[y][j] == 6)
					continue;
				vec.push_back({ map[y][j] });
				map[y][j] = 6;
			}
			for (int a = 0; a < vec.size(); a++) {
				map[i - a][j] = vec[a];
			}
			vec = {};
		}
	}
}
void arr_turn() {
	int arr[20][20] = { 0, };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[i][j] = map[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = arr[j][N - 1 - i];
		}
	}
}
int main() {
	cin >> N >> M;
	input();

	while (1) {
		max_val tmpval = { 0,0 };
		//맵 전체 돌면서 플루드 필로 크기 확인하고 들린곳은 visited처리 되서 다시 안가게
		//대신 0인곳은 다시 갈 수 있도록 처리 now수가 기존의 tmp보다 크거나 같으면 갱신
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {

				if (visited[i][j] == 1)
					continue;
				if (map[i][j] == -1 || map[i][j] == 0 || map[i][j] == 6)
					continue;
				max_val now_block = { 0,0 };
				visited[i][j] = 1;

				now_block = check_block(i, j, map[i][j]); //now블록에는 지금 최대 부신갯수 , 레인보우 갯수

				if (now_block.tmp_block > tmpval.tmp_block) {
					tmpval = now_block;
					max_route = tmp_route;
				}
				if (now_block.tmp_block == tmpval.tmp_block && now_block.rain_block > tmpval.rain_block) {
					tmpval = now_block;
					max_route = tmp_route;
				}
				if (now_block.tmp_block == tmpval.tmp_block && now_block.rain_block == tmpval.rain_block) {
					tmpval = now_block;
					max_route = tmp_route;
				}
			}
		}
		map_ch();
		grav();
		arr_turn();
		grav();

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				visited[i][j] = 0;
			}
		}

		if (tmpval.tmp_block < 2)
			break;
		result += tmpval.tmp_block * tmpval.tmp_block;
	}
	cout << result;
	return 0;
}
