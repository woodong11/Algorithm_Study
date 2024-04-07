#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point {
    int y, x, score;
};

struct GRIDP {
    vector<int> v;
};

int grid[12][12];
GRIDP grid_p[12][12];
vector<vector<int>> p_grid(12, vector<int>(12));
Point participant[11];
int lifePoint;
bool isescape[11];
int N, M, K;
vector<int> rotate_v;
Point escapePoint;
queue<int> q;
queue<vector<int>> q_p;

void printf(int y, int x, int size) {

    cout << "y : " << y << " x : " << x << " size : " << size << "\n";
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    for (int i = 1; i <= M; i++) {
        cout << isescape[i] << " " << participant[i].y << " " << participant[i].x << " " << participant[i].score << "\n";
    }
    cout << "탈출구 : " << escapePoint.y << " " << escapePoint.x << "\n";
}

// size = y2 - y1 + 1;
// 회전한 벽은 1씩 깎임.
void rotate(int y, int x, int size) {
    int ny, nx;
    int rotategrid[12][12] = { 0, };

    for (int i = y; i < y + size; i++) {
        for (int j = x; j < x + size; j++) {
            q.push(grid[i][j]);
            if (grid_p[i][j].v.empty()) {
                q_p.push(vector<int>());
            }
            else {
                q_p.push(grid_p[i][j].v);
            }
        }
    }

    for (int i = x + size - 1; i >= x; i--) {
        for (int j = y; j < y + size; j++) {
            grid[j][i] = q.front();
            if (grid[j][i] > 0) grid[j][i]--;
            q.pop();

            grid_p[j][i].v = q_p.front();
            if (!grid_p[j][i].v.empty()) {
                for (int k = 0; k < grid_p[j][i].v.size(); k++) {
                    if (grid_p[j][i].v[k] == -1) {
                        escapePoint = { j, i };
                        continue;
                    }
                    participant[grid_p[j][i].v[k]] = { j, i, participant[grid_p[j][i].v[k]].score};
                }
            }
            q_p.pop();
        }
    }

    printf(y, x, size);
}

// 가장 아래에 있는 좌표를 기준으로 올리기, 가장 오른쪽에 있는 좌표를 기준으로 왼쪽으로 움직이기
// 크기는 y 좌표의 차와 x 좌표의 차 중 큰 것을 기준으로 잡는다.
void makeup_square() {
    int d, min_d = 99999999;
    int min_d2 = 99999999;
    Point now;

    for (int i = 1; i <= M; i++) {
        if (isescape[i] == true) continue;
        d = abs(escapePoint.y - participant[i].y) + abs(escapePoint.x - participant[i].x);

        if (min_d > d) {
            min_d = d;
            min_d2 = pow(escapePoint.y - participant[i].y, 2) + pow(escapePoint.x - participant[i].x, 2);
            now = participant[i];
        }
        else if (min_d == d) {
            int tempd2 = pow(escapePoint.y - participant[i].y, 2) + pow(escapePoint.x - participant[i].x, 2);
            if (tempd2 < min_d2) {
                min_d2 = tempd2;
                now = participant[i];
            }
            else if (tempd2 == min_d2) {
                if (now.y > participant[i].y) {
                    now = participant[i];
                }
                else if (now.y == participant[i].y) {
                    now = now.x > participant[i].x ? participant[i] : now;
                }
            }
            /*if (now.y > participant[i].y) {
                now = participant[i];
            }
            else if (now.y == participant[i].y) {
                if (now.x > participant[i].x) {
                    now = participant[i];
                }
            }*/
        }
    }

    int gap_y = abs(now.y - escapePoint.y);
    int gap_x = abs(now.x - escapePoint.x);
    int size = gap_y > gap_x ? gap_y : gap_x;
    int y = now.y > escapePoint.y ? now.y - size : escapePoint.y - size;
    int x = now.x > escapePoint.x ? now.x - size : escapePoint.x - size;
    y = y < 1 ? 1 : y;
    x = x < 1 ? 1 : x;

    rotate(y, x, size + 1);
}

void escape() {
    for (int i = 1; i <= M; i++) {
        if (isescape[i] == true) {
            continue;
        }

        grid_p[participant[i].y][participant[i].x].v = vector<int>();
        Point now = participant[i];
        int ny = escapePoint.y - now.y;
        int nx = escapePoint.x - now.x;
        int dy = 0, dx = 0;

        if (ny > 0) {
            dy = 1;
        }
        else if (ny == 0) {
            dy = 0;
        }
        else {
            dy = -1;
        }

        if (nx > 0) {
            dx = 1;
        }
        else if (nx == 0) {
            dx = 0;
        }
        else {
            dx = -1;
        }

        if (dy != 0 && grid[now.y + dy][now.x] == 0) {
            participant[i].y += dy;
            participant[i].score++;
        }
        else if(dx != 0){
            if (grid[now.y][now.x + dx] > 0) {
                grid_p[participant[i].y][participant[i].x].v.push_back(i);
                continue;
            }
            participant[i].x += dx;
            participant[i].score++;
        }

        grid_p[participant[i].y][participant[i].x].v.push_back(i);

        if (participant[i].y == escapePoint.y && participant[i].x == escapePoint.x) {
            isescape[i] = true;
            grid_p[participant[i].y][participant[i].x].v = vector<int>(1, -1);
            lifePoint--;
        }
    }
}

void solve() {
    for (int i = 0; i < K; i++) {
        escape();
        if (lifePoint == 0) break;
        makeup_square();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> K;
    lifePoint = M;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> grid[i][j];
        }
    }

    int a, b;
    for (int i = 1; i <= M; i++) {
        cin >> a >> b;

        grid_p[a][b].v.push_back(i);
        participant[i] = { a, b, 0 };
    }

    cin >> a >> b;
    grid_p[a][b].v.push_back(-1);
    escapePoint = { a, b };

    solve();

    int sum = 0;

    for (int i = 1; i <= M; i++) {
        sum += participant[i].score;
    }

    cout << sum << "\n" << escapePoint.y << " " << escapePoint.x;

    return 0;
}
