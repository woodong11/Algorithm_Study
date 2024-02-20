#include <iostream>
#include <queue>
#include <vector>

using namespace std;


struct PointT {
    int y;
    int x;
    int type;
};

struct PointV {
    int y;
    int x;
    int d;
};

struct Point {
    int y;
    int x;
};

int T, result, N, cnt;
int grid[101][101]; int DAT[10];
int dx[4] = { 0, -1, 0, 1 }, dy[4] = { 1, 0, -1, 0 };
vector<PointT> wormholl[5];
Point startP;
queue<PointV> q;
PointV initP;


void init() {
    result = 0;
    for (int i = 0; i < 5; i++) {
        wormholl[i].clear();
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 5;
        }
    }
}



void solve(int val) {
    int nx, ny, d, wormholl_type;
    d = initP.d;
    nx = initP.x;
    ny = initP.y;

    while (true) {

        nx += dx[d];
        ny += dy[d];

        if (grid[ny][nx] == -1) {
            result = result > val ? result : val;
            return;
        }
        if (nx < 0 || ny < 0 || nx >= N || ny >= N || grid[ny][nx] == 5) {
            val++;
            d = (d + 2) % 4;
            continue;
        }

        if (nx == startP.x && ny == startP.y) {
            result = result > val ? result : val;
            return;
        }

        if (grid[ny][nx] != 0) {
            if (grid[ny][nx] == 1) {
                if (d == 0) {
                    val++;
                    d = 3;
                }
                else if (d == 1) {
                    d++;
                    val++;
                }
                else {
                    val++;
                    d = (d + 2) % 4;
                }
            }
            else if (grid[ny][nx] == 2) {
                if (d == 1) {
                    val++;
                    d--;
                }
                else if (d == 2) {
                    d++;
                    val++;
                }
                else {
                    val++;
                    d = (d + 2) % 4;
                }
            }
            else if (grid[ny][nx] == 3) {
                if (d == 2) {
                    val++;
                    d--;
                }
                else if (d == 3) {
                    d = 0;
                    val++;
                }
                else {
                    val++;
                    d = (d + 2) % 4;
                }
            }
            else if (grid[ny][nx] == 4) {
                if (d == 3) {
                    val++;
                    d--;
                }
                else if (d == 0) {
                    d++;
                    val++;
                }
                else {
                    val++;
                    d = (d + 2) % 4;
                }
            }
            else if (grid[ny][nx] >= 6) {
                if (ny == wormholl[grid[ny][nx] - 6][0].y && nx == wormholl[grid[ny][nx] - 6][0].x) {
                    wormholl_type = wormholl[grid[ny][nx] - 6][1].type;
                }
                else {
                    wormholl_type = wormholl[grid[ny][nx] - 6][0].type;
                }

                // ny를 바꿔버리면 nx에 바뀐 ny 값이 들어가버림.
                int temp_ny = wormholl[grid[ny][nx] - 6][wormholl_type].y;
                nx = wormholl[grid[ny][nx] - 6][wormholl_type].x;
                ny = temp_ny;
            }
        }

    }
}

int main() {

    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        init();
        cin >> N;
        for (int i = 0; i < N; i++) {
            for (int z = 0; z < N; z++) {
                cin >> grid[i][z];
                if (grid[i][z] >= 6 && grid[i][z] <= 10) {
                    if (wormholl[grid[i][z] - 6].size() == 0) {
                        wormholl[grid[i][z] - 6].push_back({ i, z, 0 });
                    }
                    else {
                        wormholl[grid[i][z] - 6].push_back({ i, z, 1 });
                    }
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int z = 0; z < N; z++) {
                if (grid[i][z] == 0) {
                    startP = { i, z };
                    for (int j = 0; j < 4; j++) {
                        initP = { i, z, j };
                        solve(0);
                    }
                }
            }
        }



        cout << "#" << tc << " " << result << "\n";
    }

    return 0;
}
