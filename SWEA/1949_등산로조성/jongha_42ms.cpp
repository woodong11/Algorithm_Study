#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

int T, n, tempgrid, tempresult, result, grid[9][9], k, maxval, tempcnt;
int initi, initj;
vector<vector<int>> visited(8, vector<int>(8, 0));
int dy[4] = { 0, 0, -1, 1 }, dx[4] = { 1, -1, 0, 0 };
bool flag = false;

void init() {
    tempresult = 0;
    result = 0;
    maxval = 0;
}

int dfs(vector<vector<int>> v, int y, int x, int cnt) {
    int ny, nx, gap;
    v[y][x] = 1;

    for (int i = 0; i < 4; i++) {
        ny = y + dy[i];
        nx = x + dx[i];
        gap = grid[ny][nx] - grid[y][x];

        if (ny < 0 || nx < 0 || ny >= n || nx >= n) {
            continue;
        }
        if (v[ny][nx] == 1) continue;
        if (gap < k && gap >= 0) {
            if (!flag) {
                flag = true;
                grid[ny][nx] = grid[y][x] - 1;
                tempcnt = dfs(v, ny, nx, cnt + 1);
                if (tempresult < tempcnt) tempresult = tempcnt;
                flag = false;
                grid[ny][nx] = grid[y][x] + gap;
                continue;
            }
            else {
                continue;
            }
        }
        else if (gap >= k) {
            continue;
        }

        tempcnt = dfs(v, ny, nx, cnt + 1);
        tempresult = max(tempresult, tempcnt);
    }

    if (initi == y && initj == x) return tempresult;
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    //freopen("input.txt", "r", stdin);

    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        init();
        cin >> n >> k;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
                maxval = max(grid[i][j], maxval);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == maxval) {
                    initi = i, initj = j;
                    result = max(result, dfs(visited, i, j, 1));
                }
            }
        }

        cout << "#" << tc << " " << result << "\n";
    }


    return 0;
}
