#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point {
    int y, x, score;
};

int grid[12][12];
Point participant[10];
int lifePoint;
bool isescape[10];
int N, M, K;
vector<int> rotate_v;
Point escapePoint;

// size = y2 - y1 + 1;
// 회전한 벽은 1씩 깎임.
void rotate(int y, int x, int size) {
    int ny, nx;
    int rotategrid[12][12] = { 0, };

    for (int i = y; i < y + size; i++) {
        for (int j = x; j < x + size; j++) {
            if (grid[i][j] > 0) --grid[i][j];
            int check = x + size - i;
            int checkb = y - x + j;
            rotategrid[y - x + j][x + size - i] = grid[i][j];
        }
    }

    for (int i = y; i < y + size; i++) {
        for (int j = x; j < x + size; j++) {
            grid[i][j] = rotategrid[i][j];
        }
    }

    for (int i = 0; i < M; i++) {
        if (isescape[i] == true) continue;
        if (participant[i].y >= y && participant[i].y < y + size && participant[i].x >= x && participant[i].x < x + size) {
            int tempy = participant[i].y;
            participant[i].y = y - x + participant[i].x;
            participant[i].x = abs(y - x) + 1 + size - tempy;
        }
    }

    int tempy = escapePoint.y;
    escapePoint.y = y - x + escapePoint.x;
    escapePoint.x = abs(y - x) + 1 + size - tempy;
}

// 가장 아래에 있는 좌표를 기준으로 올리기, 가장 오른쪽에 있는 좌표를 기준으로 왼쪽으로 움직이기
// 크기는 y 좌표의 차와 x 좌표의 차 중 큰 것을 기준으로 잡는다.
void makeup_square() {
    int d, min_d = 99999999;
    Point now;

    for (int i = 0; i < M; i++) {
        if (isescape[i] == true) continue;
        d = abs(escapePoint.y - participant[i].y) + abs(escapePoint.x - participant[i].x);

        if (min_d > d) {
            min_d = d;
            now = participant[i];
        }
        else if (min_d == d) {
            if (now.y > participant[i].y) {
                now = participant[i];
            }
            else if (now.y == participant[i].y) {
                if (now.x > participant[i].x) {
                    now = participant[i];
                }
            }
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
    for (int i = 0; i < M; i++) {
        if (isescape[i] == true) {
            continue;
        }

        Point now = participant[i];
        int ny = escapePoint.y - now.y;
        int nx = escapePoint.x - now.x;
        int dy = -1, dx = -1;

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
            if (grid[now.y][now.x + dx] > 0) continue;
            participant[i].x += dx;
            participant[i].score++;
        }

        if (participant[i].y == escapePoint.y && participant[i].x == escapePoint.x) {
            isescape[i] = true;
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
    for (int i = 0; i < M; i++) {
        cin >> a >> b;

        participant[i] = { a, b, 0 };
    }

    cin >> a >> b;

    escapePoint = { a, b };

    solve();

    int sum = 0;

    for (int i = 0; i < M; i++) {
        sum += participant[i].score;
    }

    cout << sum << "\n" << escapePoint.y << " " << escapePoint.x;

    return 0;
}
