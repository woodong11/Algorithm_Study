#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Arr {
    int r;
    int c;
    int s;
};

struct Point {
    int y;
    int x;
};

int grid[51][51], KVAT[7];
int K, N, M, T, result = 9999, tempResult;
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
queue<int> q;
Point p;
vector<Arr> v;

void init() {
    result = 0;
    tempResult = 0;
}

void rightrotate(int y, int x, int s) {
    int nx, ny;

    for (int i = 1; i <= s; i++) {
        ny = y + i, nx = x + i;
        p = { ny, nx };
        int z = 0, k = 1;
        q.push(grid[ny][nx]);
        while(true) {
            nx += dx[z];
            ny += dy[z];
            if (ny == p.y && nx == p.x) {
                grid[ny][nx] = q.front();
                q.pop();
                break;
            }
            q.push(grid[ny][nx]);
            grid[ny][nx] = q.front();
            q.pop();
            if (k % (i * 2) == 0 ) {
                z++;
            }
            k++;
        }
    }
}

void leftrotate(int y, int x, int s) {
    int nx, ny;

    for (int i = 1; i <= s; i++) {
        ny = y + i, nx = x + i;
        p = { ny, nx };
        int z = 3, k = 1;
        q.push(grid[ny][nx]);
        while(true) {
            nx -= dx[z];
            ny -= dy[z];
            if (ny == p.y && nx == p.x) {
                grid[ny][nx] = q.front();
                q.pop();
                break;
            }
            q.push(grid[ny][nx]);
            grid[ny][nx] = q.front();
            q.pop();
            if (k % (i * 2) == 0 ) {
                z--;
            }
            k++;
        }
    }
}

void rowsum() {
    for (int i = 0; i < N; i++) {
        for (int z = 0; z < M; z++) {
            tempResult += grid[i][z];
        }
        result = tempResult > result ? result : tempResult;
        tempResult = 0;
    }
}

void dfs(int level) {
    if (level > K) {
        rowsum();
        return;
    }
    int r, c, s;

    for (int i = 0; i < v.size(); i++) {
        if (KVAT[i] == 1) continue;

        KVAT[i] = 1;
        rightrotate(v[i].r, v[i].c, v[i].s);
        dfs(level + 1);
        leftrotate(v[i].r, v[i].c, v[i].s);
        KVAT[i] = 0;
    }
}

int main() {
    int r, c, s;
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < M; k++) {
            cin >> grid[i][k];
        }
    }
    for (int i = 0; i < K; i++) {
        cin >> r >> c >> s;
        v.push_back({ r - 1, c - 1, s });
    }

    dfs(1);

    cout << result;

    return 0;
}
