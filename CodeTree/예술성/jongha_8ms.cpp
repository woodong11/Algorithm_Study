#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Point {
    int y, x;
};

int grid[30][30], visited[30][30], visited2[30][30], reach[1000][1000];
Point num_size[1000];
int dy[4] = { 0, 0, 1, -1 }, dx[4] = { 1, -1, 0, 0 };
int n, num = 1;

int search_size(int y, int x) {
    int cnt = 1;
    queue<Point> q;
    Point now = { y, x };
    q.push(now);

    while (!q.empty()) {
        now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            Point next = { now.y + dy[i], now.x + dx[i] };

            if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n) continue;
            if (visited[next.y][next.x] != 0) continue;
            if (grid[next.y][next.x] == grid[y][x]) {
                cnt++;
                visited[next.y][next.x] = num;
                q.push(next);
            }
        }
    }

    return cnt;
}

void search_adjacent(int y, int x) {
    visited2[y][x] = 1;

    for (int i = 0; i < 4; i++) {
        Point next = { y + dy[i], x + dx[i] };

        if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n || visited[next.y][next.x] == visited[y][x]) continue;
        if (visited2[next.y][next.x] == 1) continue;
        reach[visited[y][x]][visited[next.y][next.x]]++;
        reach[visited[next.y][next.x]][visited[y][x]]++;
    }
}

void check() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i][j] == 0) {
                visited[i][j] = num;
                num_size[num] = { search_size(i, j), grid[i][j] };
                num++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            search_adjacent(i, j);
        }
    }
}

void init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = 0;
            visited2[i][j] = 0;
        }
    }

    for (int i = 1; i < num; i++) {
        for (int j = 1; j < num; j++) {
            reach[i][j] = 0;
        }
    }

    for (int i = 1; i < num; i++) {
        num_size[i] = { 0, 0};
    }

    num = 1;
}

void rotate() {
    int range = n * 0.5;
    queue<int> q;

    for (int i = 0; i < range; i++) {
        for (int j = 0; j < range; j++) {
            q.push(grid[i][j]);
        }
    }

    for (int j = range - 1; j >= 0; j--) {
        for (int i = 0; i < range; i++) {
            grid[i][j] = q.front();
            q.pop();
        }
    }

    for (int i = range + 1; i < n; i++) {
        for (int j = 0; j < range; j++) {
            q.push(grid[i][j]);
        }
    }

    for (int j = range - 1; j >= 0; j--) {
        for (int i = n - range; i < n; i++) {
            grid[i][j] = q.front();
            q.pop();
        }
    }

    for (int i = 0; i < range; i++) {
        for (int j = n - range; j < n; j++) {
            q.push(grid[i][j]);
        }
    }

    for (int j = n - 1; j > range; j--) {
        for (int i = 0; i < range; i++) {
            grid[i][j] = q.front();
            q.pop();
        }
    }

    for (int i = range + 1; i < n; i++) {
        for (int j = range + 1; j < n; j++) {
            q.push(grid[i][j]);
        }
    }

    for (int j = n - 1; j > range; j--) {
        for (int i = range + 1; i < n; i++) {
            grid[i][j] = q.front();
            q.pop();
        }
    }

    for (int i = 0; i < n; i++) {
        if (i != range) q.push(grid[i][range]);
        else {
            for (int j = 0; j < n; j++) {
                q.push(grid[i][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (i != range) {
            grid[range][i] = q.front();
            q.pop();
        }
        else {
            for (int j = n - 1; j >= 0; j--) {
                grid[j][i] = q.front();
                q.pop();
            }
        }
    }
}

int result = 0;
void solve() {
    for (int i = 0; i < 4; i++) {
        check();

        for (int j = 1; j < num; j++) {
            for (int z = j + 1; z < num; z++) {
                int a = reach[j][z];
                int b = num_size[j].y;
                int c = num_size[z].y;
                int d = num_size[j].x;
                int e = num_size[z].x;
                result += reach[j][z] * (num_size[j].y + num_size[z].y) * num_size[j].x * num_size[z].x;
            }
        }
        
        rotate();
        init();
    }

    cout << result;
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    solve();


    return 0;
}
