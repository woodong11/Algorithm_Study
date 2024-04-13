#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

struct Point {
    int y, x;
};

struct Point_b {
    int y, x, visited;
};

struct Point_v {
    int visited;
    queue<Point> q;
};

struct Participant {
    Point now;
    Point target;
    queue<Point> q;
    bool is_escape = false;
};

int dy[4] = { -1, 0, 0, 1 }, dx[4] = { 0, -1, 1, 0 };
int grid[15][15];
int n, m, cnt;
// 베이스캠프 좌표
vector<Point_b> v;
Participant participant[30];
queue<Point> q;

queue<Point> search_min(Point now, Point target) {
    q = queue<Point>();
    Point_v visited[15][15];
    q.push({ now.y, now.x });

    visited[now.y][now.x].visited = 1;
    //visited[now.y][now.x].q.push(now);

    while (!q.empty()) {
        Point now = q.front();
        q.pop();


        Point next;

        for (int i = 0; i < 4; i++) {
            next = { now.y + dy[i], now.x + dx[i] };

            if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n) continue;
            if (visited[next.y][next.x].visited == 1) continue;
            if (grid[next.y][next.x] == -1) continue;

            visited[next.y][next.x].visited = 1;
            visited[next.y][next.x].q = visited[now.y][now.x].q;
            visited[next.y][next.x].q.push({ next.y, next.x });
            if (next.y == target.y && next.x == target.x) return visited[next.y][next.x].q;

            q.push(next);
        }
    }

    return queue<Point>();
}

void search_basecamp(int num) {
    int res_d = 999999;
    int res_i = -1;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].visited == 1) continue;
        int d = abs(participant[num].target.y - v[i].y) + abs(participant[num].target.x - v[i].x);
        
        if (res_d > d) {
            participant[num].now = {v[i].y, v[i].x};
            res_d = d;
            res_i = i;
        }
        else if (res_d == d) {
            if (participant[num].now.y > v[i].y) {
                participant[num].now = {v[i].y, v[i].x};
                res_i = i;
            }
            else if (participant[num].now.y == v[i].y && participant[num].now.x > v[i].x) {
                participant[num] = {v[i].y, v[i].x};
                res_i = i;
            }
        }
    }

    if (res_i == -1) {
        cout << "error\n";
    }
    else {
        v[res_i].visited = 1;
    }
}

int t = 0;
void solve() {
    while (true) {
        if (cnt == 0) return;
        for (int i = 0; i <= t; i++) {
            if (i >= m) break;
            if(participant[i].is_escape == true) continue;
            if (t == i) {
                search_basecamp(i);
                participant[i].q = search_min(participant[i].now, participant[i].target);
                grid[participant[i].now.y][participant[i].now.x] = -1;
                break;
            }

            Point next = participant[i].q.front();

            if (grid[next.y][next.x] == -1) {
                participant[i].q = search_min(participant[i].now, participant[i].target);
                next = participant[i].q.front();
            }

            if (next.y == participant[i].target.y && next.x == participant[i].target.x) {
                participant[i].is_escape = true;
                cnt--;
            }
            participant[i].q.pop();
            participant[i].now = next;
        }
        t++;
    }
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 1) {
                v.push_back({ i, j });
            }
        }
    }

    cnt = m;

    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;

        a--; b--;

        participant[i].target = { a, b };
    }

    solve();
    cout << t;

    return 0;
}
