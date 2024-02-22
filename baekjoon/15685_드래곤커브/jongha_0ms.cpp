#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<math.h>

using namespace std;

struct PointC {
    int x;
    int y;
    int d;
    int g;
};

struct PointD {
    int x;
    int y;
    int d;
};

int grid[101][101], dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, -1, 0, 1 };
int N, result;
vector<PointC> dv;
vector<int> tempv;

void init() {
    dv.clear();
}

// 다음 세대를 이용해서 이전 세대 만들기 (는 필요 없었고~)
void makeZG(int x, int y) {
    int d, nx, ny;
    ny = y;
    nx = x;
    for (int i = 0; i < tempv.size() - 1; i++) {
        d = tempv[i];
        nx += dx[d];
        ny += dy[d];

        if (ny < 0 || nx < 0 || ny > 100 || nx > 100) continue;
        grid[ny][nx] = 1;
    }
}

// 다음 세대 만들기
void makeNG(int a) {
    int x, y, d, g, nx, ny, cnt = 1, cutline;
    tempv = vector<int>();

    x = dv[a].x;
    y = dv[a].y;
    d = dv[a].d;
    g = dv[a].g;
    cutline = pow(2, g);

    nx = x + dx[d];
    ny = y + dy[d];

    grid[ny][nx] = 1;
    grid[y][x] = 1;

    tempv.push_back((d + 1) % 4);

    while (true) {
        if (cnt == cutline) break;

        for (int i = tempv.size() - 1; i >= 0; i--) {
            d = tempv[i];
            nx += dx[d];
            ny += dy[d];
            cnt++;

            tempv.push_back((d + 1) % 4);

            grid[ny][nx] = 1;
        }

    }

    //if (g != 0) {
    //    makeZG(x, y);
    //}
    tempv.clear();
}

// 정사각형 개수 찾기
void bfs() {
    int idx = 0, nx, ny;

    for (int i = 1; i <= 100; i += 2) {
        for (int j = 1; j <= 100; j += 2) {
            for (int z = 0; z < 4; z++) {
                nx = j;
                ny = i;
                for (int k = 0; k < 4; k++) {
                    idx = (z + k) % 4;
                    ny += dy[idx];
                    nx += dx[idx];
                    if (grid[ny][nx] == 0) break;
                    if (k == 3) {
                        result++;
                    }
                }
            }
        }
    }
}

bool compare(PointC a, PointC b) {
    if (a.g < b.g) return true;
    return false;
}

int main() {
    cin >> N;
    int x, y, d, g;

    for (int i = 0; i < N; i++) {
        cin >> x >> y >> d >> g;
        dv.push_back({ x, y, d, g });
    }

    for (int i = 0; i < dv.size(); i++) {
        makeNG(i);
    }

    bfs();

    cout << result;

    return 0;
}
