#include <vector>
#include<iostream>
#include<queue>

using namespace std;

struct Point {
    int y, x;
};

int n, m, grid[8][8], tempgrid[8][8], nm, tempcnt, result;
int dy[4] = { 0, 0, 1, -1 }, dx[4] = { 1, -1, 0, 0 };
queue<Point> q;


void bf() {

    for (int i = 0; i < nm; i++) {
        int iy = i / m;
        int ix = i % m;

        if (grid[iy][ix] != 0) continue;
        grid[iy][ix] = 1;

        for (int j = i + 1; j < nm; j++) {
            int jy = j / m;
            int jx = j % m;

            if (grid[jy][jx] != 0) continue;
            grid[jy][jx] = 1;

            for (int k = j + 1; k < nm; k++) {
                int ky = k / m;
                int kx = k % m;

                if (grid[ky][kx] != 0) continue;
                grid[ky][kx] = 1;

                queue<Point> tempq = q;

                for (int z = 0; z < n; z++) {
                    for (int qq = 0; qq < m; qq++) {
                        tempgrid[z][qq] = grid[z][qq];
                    }
                }

                while (!tempq.empty()) {
                    int ny, nx;
                    Point now = tempq.front();
                    tempq.pop();

                    for (int z = 0; z < 4; z++) {
                        ny = now.y + dy[z];
                        nx = now.x + dx[z];

                        if (ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
                        if (tempgrid[ny][nx] != 0) continue;

                        tempgrid[ny][nx] = 2;
                        tempq.push({ ny, nx });
                    }
                }

                tempcnt = 0;

                for (int z = 0; z < n; z++) {
                    for (int qq = 0; qq < m; qq++) {
                        if (tempgrid[z][qq] == 0) {
                            tempcnt++;
                        }
                    }
                }

                result = result > tempcnt ? result : tempcnt;
                grid[ky][kx] = 0;
            }
            grid[jy][jx] = 0;
        }
        grid[iy][ix] = 0;
    }
}

int main() {
    cin >> n >> m;
    nm = n * m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                q.push({ i, j });
            }
        }
    }

    bf();
    cout << result;

    return 0;
}
