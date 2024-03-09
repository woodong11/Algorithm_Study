#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct snk {
	int time;
	char dir;
};
struct point {
	int y, x, dir;
};
queue<snk> q;
queue<point> snake;
//상 우 하 좌
int dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 }, map[101][101];
int N, K, L;

int changedir(int dir_num, char dir_char) {
	if (dir_char == 'D') 
		return (dir_num + 1) % 4;
	else 
		return (dir_num + 3) % 4;
}

int main() {
	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		int y, x;
		cin >> y >> x;
		map[y-1][x-1] = 1;
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int t;
		char dir;
		cin >> t >> dir;
		q.push({ t,dir });
	}
	int cnt = 0;
	snk chg = q.front();
	q.pop();
	snake.push({ 0,0,1 });
	point now = snake.front();
	map[0][0] = 2;

	while (1) {
		if (cnt == chg.time) {
			now.dir = changedir(now.dir, chg.dir);
			
			if (!q.empty()){
				chg = q.front();
				q.pop();
			}
		}
		point next = { now.y, now.x, now.dir };
		next.y = now.y + dy[now.dir];
		next.x = now.x + dx[now.dir];
		if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N) {
			cnt++;
			break;
		}
		if (map[next.y][next.x] == 2) {
			cnt++;
			break;
		}

		//사과 없으면 다음지점 push하고 꼬리가 있는 map은 0으로
		if (map[next.y][next.x] == 0) {
			map[next.y][next.x] = 2;
			snake.push(next);
			point tail = snake.front();
			map[tail.y][tail.x] = 0;
			snake.pop();
			now = next;
		}
		else if (map[next.y][next.x] == 1) {
			map[next.y][next.x] = 2;
			snake.push(next);
			now = next;
		}
		cnt++;
	}
	cout << cnt;
	return 0;
}
