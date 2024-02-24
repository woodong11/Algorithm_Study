#include <iostream>
#include <vector>

using namespace std;

struct point {
	int y, x, dir;
};
int dy[] = { 0,-1,0,1 }, dx[] = { 1,0,-1,0 }, map[101][101];
int cnt, T, gen;
void check() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j] == 1 && map[i + 1][j + 1] == 1)
				cnt++;
		}
	}
}

int main() {
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		point input;
		vector<int> dragon = {};
		cin >> input.x >> input.y >> input.dir >> gen;
		map[input.y][input.x] = 1;
		int next_y = input.y + dy[input.dir], next_x = input.x + dx[input.dir];
		map[next_y][next_x] = 1; // 여기까지가 0세대 끝
		point st = { next_y,next_x,(input.dir + 1) % 4 };
		dragon.push_back(st.dir);
		for (int i = 0; i < gen; i++) { // 여기서 부터는 1세대 시작
			for (int j = dragon.size() - 1; j >= 0; j--) {
				st.y = st.y + dy[dragon[j]], st.x = st.x + dx[dragon[j]];
				dragon.push_back((dragon[j] + 1) % 4);
				map[st.y][st.x] = 1;
			}
		}
	}
	check();
	cout << cnt;
	return 0;
}
