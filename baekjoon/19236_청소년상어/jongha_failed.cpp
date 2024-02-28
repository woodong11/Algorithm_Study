#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct score {
    int ai;
    int bi;
};

struct Point {
    int y;
    int x;
};

struct Shark {
    int y;
    int x;
    int d;
};

bool operator==(const Point& p1, const Point& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const Point& p1, const score& p2) {
    return p1.x != p2.ai || p1.y != p2.bi;
}
int ai, bi, result;
int dx[8] = { 0, -1, -1, -1, 0, 1, 1, 1 }, dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
vector<Point> vinit(32);
score grid[4][4];
Shark sharkInit;
int endplus;

void fishfish(vector<Point> v, Shark shark, score(&grid)[4][4], int sum, int dsize);

void solve(int sum);

void sharkshark(vector<Point> v, Shark shark, score(&grid)[4][4], int sum, int dsize) {
    int nx, ny, d = shark.d, fishscore = 0;
    vector<Point> tempv = v;
    ny = shark.y + dy[d] * dsize;
    nx = shark.x + dx[d] * dsize;

    if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) { result = max(sum + fishscore, result); return; }
    if (grid[ny][nx].ai == 0) { result = max(sum + fishscore, result); return; }

    cout << shark.y << " " << shark.x << " 잡아먹으려 함\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << grid[i][j].ai << " " << grid[i][j].bi << " ";
        }
        cout << "\n";
    }

    grid[shark.y][shark.x] = { 0, 0 };
    fishscore = grid[ny][nx].ai;
    shark.y = ny;
    shark.x = nx;
    shark.d = grid[ny][nx].bi;
    grid[ny][nx] = { 0, 0 };
    tempv[fishscore] = { 0, 0 };

    cout << shark.y << " " << shark.x << " 잡아먹음 : " << fishscore << "\n";

    score tempgrid[4][4];
    Shark tempshark = shark;

    for (int i = 1; i < 4; i++) {
        cout << "ff : " << i << "\n";
        for (int k = 0; k < 4; k++) {
            for (int j = 0; j < 4; j++) {
                tempgrid[k][j] = grid[k][j];
            }
        }

        ny = shark.y + dy[d] * i;
        nx = shark.x + dx[d] * i;
        if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) { result = max(sum + fishscore, result); continue; }
        fishfish(tempv, tempshark, tempgrid, sum + fishscore, i);
        cout << "FF : " << i << "\n";
    }
}

void fishfish(vector<Point> v, Shark shark, score(&grid)[4][4], int sum, int dsize) {
    int n, d, nx, ny, val, tempd;
    Point fish;
    score temp;
    Shark tempshark = shark;
    Point eated = { 0, 0 };
    vector<Point> tempv = v;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            n = i * 4 + j + 1;
            if (tempv[n] == eated) {
                continue;
            }

            fish.x = tempv[n].x;
            fish.y = tempv[n].y;
            d = grid[fish.y][fish.x].bi;

            for (int k = 0; k < 8; k++) {
                tempd = (d + k) % 8;
                ny = fish.y + dy[tempd];
                nx = fish.x + dx[tempd];

                // 배열 초과 시
                if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) continue;
                // 상어가 있을 시
                if (shark.x == nx && shark.y == ny) continue;

                // 물고기 위치 정리
                temp.ai = grid[ny][nx].ai;
                temp.bi = grid[ny][nx].bi;
                grid[ny][nx].ai = grid[fish.y][fish.x].ai;
                grid[ny][nx].bi = tempd;
                grid[fish.y][fish.x].ai = temp.ai;
                grid[fish.y][fish.x].bi = temp.bi;
                tempv[n].x = tempv[temp.ai].x;
                tempv[n].y = tempv[temp.ai].y;
                tempv[temp.ai].x = fish.x;
                tempv[temp.ai].y = fish.y;
                break;
            }
        }
    }

    score tempgrid[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << grid[i][j].ai << " " << grid[i][j].bi << " ";
        }
        cout << "\n";
    }

    for (int i = dsize; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                tempgrid[j][k] = grid[j][k];
            }
        }
        d = shark.d;
        ny = shark.y + dy[d] * i;
        nx = shark.x + dx[d] * i;
        if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) {
            result = max(result, sum);
            continue;
        }
        cout << "sum : " << sum << "\n";
        cout << "ss : " << i << "\n";
        //val = sharkshark(tempv, tempshark, tempgrid, sum, i);
        sharkshark(tempv, tempshark, tempgrid, sum, i);
        if (endplus != 0) sum += endplus;
        cout << "SS : " << i << "\n";
        cout << sum << " " << " " << i << "\n";
        //if (val == 0) {
        result = max(result, sum);
        //}
        sum -= endplus;
        endplus = 0;
    }
}

void solve(int sum) {
    score tempgrid[4][4];
    Shark shark = sharkInit;
    vector<Point> v = vinit;


    for (int i = 1; i < 4; i++) {
        cout << "sff : " << i << "\n";
        for (int k = 0; k < 4; k++) {
            for (int j = 0; j < 4; j++) {
                tempgrid[k][j] = grid[k][j];
            }
        }
        fishfish(v, shark, tempgrid, sum, i);
        cout << "SFF : " << i << "\n";
    }
}

int main() {
    int a, b, sum;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> a >> b;
            grid[i][j].ai = a;
            grid[i][j].bi = b - 1;
            vinit[a] = { i, j };
        }
    }

    sum = grid[0][0].ai;
    sharkInit = { 0, 0, grid[0][0].bi };
    vinit[sum] = { 0, 0 };
    grid[0][0] = { 0, 0 };
    result = 0;

    solve(sum);

    cout << result;

    return 0;
}
