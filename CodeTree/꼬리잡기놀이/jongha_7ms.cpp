#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int y, x;
};

struct Participant {
    int head, l, type = 1;
    vector<Point> v;
};

Participant team[5];
int grid[20][20], visited[20][20], team_grid[20][20];
int dy[4] = { 0, -1, 0, 1 }, dx[4] = { 1, 0, -1, 0 };
int n, m, k;
int result = 0;

void save(Point now, int level) {
    queue<Point> q;
    // team 방향을 구하기 위한 배열 ex) 좌로 바뀐게 크면 좌, 우로 바뀐게 크면 우
    // int t_grid[2] = {0,};
    q.push(now);
    visited[now.y][now.x] = 1;
    team[level].v.push_back({ now.y, now.x });
    team_grid[now.y][now.x] = level;

    int d;
    for (int i = 0; i < 4; i++) {
        if (grid[now.y + dy[i]][now.x + dx[i]] == 2) {
            // if((d + 1) % 4 == i) {
            //     t_grid[0]++;
            // }  else {
            //     t_grid[1]++;
            // }
            d = i;
            break;
        }
    }

    int l = 0;
    while (!q.empty()) {
        Point t_now = q.front();
        q.pop();

        Point next = { t_now.y + dy[d], t_now.x + dx[d] };

        if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n || grid[next.y][next.x] == 0) {
            for (int i = d + 1; i < d + 4; i += 2) {
                if (t_now.y + dy[(i % 4)] < 0 || t_now.x + dx[(i % 4)] < 0 || t_now.y + dy[(i % 4)] >= n || t_now.x + dx[(i % 4)] >= n) continue;
                if (grid[t_now.y + dy[(i % 4)]][t_now.x + dx[(i % 4)]] > 0) {
                    d = i % 4;
                    break;
                }
            }
            next = { t_now.y + dy[d], t_now.x + dx[d] };
        }

        if (grid[next.y][next.x] == 1) {
            // 원래 방향 구하는 코드
            // if(t_grid[0] > t_grid[1]) {
            //     team[level].type = 1;
            // } else if (t_grid[0] < t_grid[1]) {
            //     team[level].type = -1;
            // } else {
            //     cout << "error\n";
            // }
            return;
        }
        if (visited[next.y][next.x] == 1) continue;

        team[level].v.push_back({ next.y, next.x });
        visited[next.y][next.x] = 1;
        team_grid[next.y][next.x] = level;
        l++;
        if (grid[next.y][next.x] == 3) {
            //tail = abs(next.y - team[level].v[0].y) + abs(next.x - team[level].v[0].x);
            team[level].l = l;
        }

        q.push({ next.y, next.x });
    }
}

void ball_move(int j) {
    if (j == 32) {
        int abfdg = 3;
    }
    int d = (j / n) % 4;
    int idx = j % n;

    Point now;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            if (d == 0) {
                now = { idx, 0 };
            }
            else if (d == 1) {
                now = { n - 1, idx };
            }
            else if (d == 2) {
                now = { n - 1 - idx, n - 1 };
            }
            else {
                now = { 0, n - 1 - idx };
            }
        }
        else if (i != 0) {
            if (d < 2) {
                now = { now.y + dy[d], now.x + dx[d] };
            }
            else {
                now = { now.y + dy[d], now.x + dx[d] };
            }
        }

        if (team_grid[now.y][now.x] != -1) {
            int team_num = team_grid[now.y][now.x];

            for (int z = 0; z <= team[team_num].l; z++) {
                if (now.y == team[team_num].v[(team[team_num].head + team[team_num].type * z + team[team_num].v.size()) % team[team_num].v.size()].y && now.x == team[team_num].v[(team[team_num].head + team[team_num].type * z + team[team_num].v.size()) % team[team_num].v.size()].x) {
                    result += pow(z + 1, 2);
                    team[team_num].head = (team[team_num].head + team[team_num].l * team[team_num].type + team[team_num].v.size()) % team[team_num].v.size();
                    team[team_num].type *= -1;
                    return;
                }
            }
        }
    }
}


void solve() {
    for (int j = 0; j < k; j++) {
        for (int i = 0; i < m; i++) {
            team[i].head = (team[i].head - team[i].type + team[i].v.size()) % team[i].v.size();
        }

        ball_move(j);
    }
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin >> n >> m >> k;
    vector<Point> team_one_point;

    int level = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 1) {
                team_one_point.push_back({ i, j });
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            team_grid[i][j] = -1;
        }
    }

    for (int i = 0; i < team_one_point.size(); i++) {
        save(team_one_point[i], i);
    }

    solve();
    cout << result;

    return 0;
}
