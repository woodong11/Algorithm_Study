#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

struct Point {
    int x;
    int y;
};

int direction[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
int result = 99999 , N, M, core_num;
int grid[13][13];
int check[13][13];
vector<Point> v;

void init() {
    memset(check, 0, sizeof(check));
    result = 99999;
    core_num = 0;
    v.clear();
}

void input() {
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            cin >> grid[i][k];
            if (grid[i][k] == 1) {
                v.push_back({ k, i });
            }
        }
    }
}

void dfs(int cnt, int level, int type, int temp_core_num) {
    if (temp_core_num + (v.size() - level) < core_num) return;
    if (level == v.size()) {
        if (core_num <= temp_core_num) {
            core_num = temp_core_num;
            if (cnt != 0) result = result < cnt ? result : cnt;
        }
        return;
    }
    if (type == 0) {
        for (int i = 0; i <= v[level].x; i++) {
            if (check[v[level].y][i] != 0) {
                return;
            }
        }
        for (int i = 0; i <= v[level].x; i++) {
            check[v[level].y][i] = 1;
            cnt++;
        }
        temp_core_num++;
    }
    else if (type == 1) {
        for (int i = v[level].x; i < N; i++) {
            if (check[v[level].y][i] != 0) {
                return;
            }
        }
        for (int i = v[level].x; i < N; i++) {
            check[v[level].y][i] = 1;
            cnt++;
        }
        temp_core_num++;
    }
    else if (type == 2) {
        for (int i = 0; i <= v[level].y; i++) {
            if (check[i][v[level].x] != 0) {
                return;
            }
        }
        for (int i = 0; i <= v[level].y; i++) {
            check[i][v[level].x] = 1;
            cnt++;
        }
        temp_core_num++;
    }
    else {
        for (int i = v[level].y; i < N; i++) {
            if (check[i][v[level].x] != 0) {
                return;
            }
        }
        for (int i = v[level].y; i < N; i++) {
            check[i][v[level].x] = 1;
            cnt++;
        }
        temp_core_num++;
    }

    for (int i = 0; i < 4; i++) {
        dfs(cnt,level + 1, i, temp_core_num);
    }

    if (type == 0) {
        for (int i = 0; i <= v[level].x; i++) {
            check[v[level].y][i] = 0;
            cnt--;
        }
        temp_core_num--;
    }
    else if (type == 1) {
        for (int i = v[level].x; i < N; i++) {
            check[v[level].y][i] = 0;
            cnt--;
        }
        temp_core_num--;
    }
    else if (type == 2) {
        for (int i = 0; i <= v[level].y; i++) {
            check[i][v[level].x] = 0;
            cnt--;
        }
        temp_core_num--;
    }
    else {
        for (int i = v[level].y; i < N; i++) {
            check[i][v[level].x] = 0;
            cnt--;
        }
        temp_core_num--;
    }
}

int main() {
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N;
        init();
        input();
        for (int k = 0; k < 4; k++) {
            dfs(0, 0, k, 0);
        }

        if (result == 99999) result = 0;
        cout << "#" << i << " " << result - core_num << "\n";
    }

    return 0;
 }
