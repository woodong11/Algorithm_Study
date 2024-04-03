#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct KNIGHT {
    int y, x, h, w;
};

struct Point {
    int y, x, id;
};

int grid[41][41], position[41][41], knight_h[31], init_h[31], visited[31];
int r, c, h, w, k, L, N, Q;
int dy[4] = { -1, 0, 1, 0 }, dx[4] = { 0, 1, 0, -1 };
vector<KNIGHT> knight(31);
queue<Point> q;
queue<int> r_q;

void bfs(int knight_i, int knight_d) {
    q = queue<Point>();
    Point now, next;
    q.push({ knight[knight_i].y, knight[knight_i].x, knight_i });

    while (!r_q.empty()) {
        visited[r_q.front()] = 0;
        r_q.pop();
    }

    while (!q.empty()) {
        now = q.front();
        q.pop();

        for (int i = 0; i < knight[now.id].h; i++) {
            next.y = now.y + i + dy[knight_d];

            if (next.y < 1 || next.y > L) return;
            for (int j = 0; j < knight[now.id].w; j++) {
                next.x = now.x + j + dx[knight_d];
                int next_id = position[next.y][next.x];

                if (next.x < 1 || next.x > L || grid[next.y][next.x] == 2) return;
                if (next_id == now.id || next_id == 0 || knight_i == next_id) continue;
                else {
                    if (visited[next_id] == 1) continue;
                    q.push({ knight[next_id].y, knight[next_id].x, next_id});
                    r_q.push({ next_id });
                    visited[next_id] = 1;
                }
            }
        }
    }

    now.y = knight[knight_i].y;
    now.x = knight[knight_i].x;
    for (int i = 0; i < knight[knight_i].h; i++) {
        for (int j = 0; j < knight[knight_i].w; j++) {
            position[now.y + i][now.x + j] = 0;
        }
    }
    knight[knight_i].y += dy[knight_d];
    knight[knight_i].x += dx[knight_d];

    now.y = knight[knight_i].y;
    now.x = knight[knight_i].x;
    for (int i = 0; i < knight[knight_i].h; i++) {
        for (int j = 0; j < knight[knight_i].w; j++) {
            position[now.y + i][now.x + j] = knight_i;
        }
    }

    while (!r_q.empty()) {
        int k_id = r_q.front();
        visited[k_id] = 0;
        r_q.pop();
        now = { knight[k_id].y, knight[k_id].x, k_id };
        if (visited[now.id] == -1)continue;

        for (int i = 0; i < knight[now.id].h; i++) {
            for (int j = 0; j < knight[now.id].w; j++) {
                if (position[now.y + i][now.x + j] != now.id) continue;
                position[now.y + i][now.x + j] = 0;
            }
        }

        knight[k_id].y += dy[knight_d];
        knight[k_id].x += dx[knight_d];
        now = { knight[k_id].y, knight[k_id].x, now.id };

        for (int i = 0; i < knight[now.id].h; i++) {
            for (int j = 0; j < knight[now.id].w; j++) {
                if (grid[now.y + i][now.x + j] == 1) {
                    knight_h[now.id]--;
                    if (knight_h[now.id] <= 0) {
                        visited[now.id] = -1;
                        break;
                    }
                }
            }
            if (visited[now.id] == -1) break;
        }

        if (visited[now.id] == -1) {
            continue;
        }

        

        for (int i = 0; i < knight[now.id].h; i++) {
            for (int j = 0; j < knight[now.id].w; j++) {
                position[now.y + i][now.x + j] = now.id;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> L >> N >> Q;

    for (int i = 1; i <= L; i++) {
        for (int j = 1; j <= L; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                position[i][j] = -1;
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        cin >> r >> c >> h >> w >> k;
        knight[i] = { r, c, h, w };
        knight_h[i] = k;
        init_h[i] = k;

        for (int j = r; j < r + h; j++) {
            for (int z = c; z < c + w; z++) {
                position[j][z] = i;
            }
        }
    }

    int a, b;
    for (int i = 0; i < Q; i++) {
        cin >> a >> b;

        if (visited[a] == -1) continue;

        bfs(a, b);
    }

    int sum = 0;
    for (int i = 1; i <= N; i++) {
        if (visited[i] == -1) continue;
        sum += (init_h[i] - knight_h[i]);
    }

    cout << sum;

    return 0;
}
