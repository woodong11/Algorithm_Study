#include<iostream>
#include<vector>

using namespace std;

struct Point {
    int y, x;
};

int result, n, m;
int grid[4][4];
int dy[4] = { 0, 0, 1, -1 }, dx[4] = { 1, -1, 0, 0 };
vector<Point> v;
vector<vector<int>> visited(4, vector<int>(4, 0));

void dfs(vector<vector<int>> t_visited, Point now, int level) {
    if (level == m) {
        result++;
        return;
    }

    Point next;
    for (int i = 0; i < 4; i++) {
        next = { now.y + dy[i], now.x + dx[i] };
        if (next.y < 0 || next.y >= n || next.x < 0 || next.x >= n) continue;
        if (t_visited[next.y][next.x] == 1) continue;
        if (grid[next.y][next.x] == 1) continue;

        t_visited[next.y][next.x] = 1;
        if (next.y == v[level].y && next.x == v[level].x) {
            dfs(t_visited, next, level + 1);
        }
        else {
            dfs(t_visited, next, level);
        }
        t_visited[next.y][next.x] = 0;
    }
}

int main(int argc, char** argv)
{
    cin >> n >> m;

    int a;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a;
            grid[i][j] = a;
        }
    }

    int b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        v.push_back({ a - 1, b - 1 });
    }

    visited[v[0].y][v[0].x] = 1;
    Point now = { v[0].y, v[0].x };
    dfs(visited, now, 1);

    cout << result;
    return 0;
}
