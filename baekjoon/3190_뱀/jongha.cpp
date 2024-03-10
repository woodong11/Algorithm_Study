#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

struct Point {
    int time;
    int dirt;
};

struct Pointx {
    int y, x;
};


int grid[101][101], visited[101][101], timer = 1, N, K, L, taildir;
// 오른쪽 ++ 왼쪽 --
int dy[4] = { 0, 1, 0, -1 }, dx[4] = { 1, 0, -1, 0 }, dir, snakelength = 1;
bool check = false;
unordered_set<int> us;
queue<Point> transdir;
queue<Point> transtaildir;
queue<Pointx> snake;





int main() {
    int a, b; char c;
    Point transbox;


    cin >> N >> K;

    for (int i = 0; i < K; i++) {
        cin >> a >> b;
        grid[a - 1][b - 1] = 1;

    }

    cin >> L;
    for (int i = 0; i < L; i++) {
        cin >> a >> c;
        b = ('H' - c) / 4;

        transdir.push({ a, b });

    }
    visited[0][0] = 1;
    snake.push({ 0, 0 });
    snake.push({ 0, 0 });
    transbox = transdir.front();
    transdir.pop();
    if (transbox.time == timer) {
        dir = (4 + dir + transbox.dirt) % 4;
        transbox = transdir.front();
        transdir.pop();
    }


    Pointx tail, head;
    Point tailtrans;


    while (1) {
        timer++;

        head = snake.front();
        snake.pop();
        tail = snake.front();
        snake.pop();

        head.y += dy[dir];
        head.x += dx[dir];

        if (head.y >= N || head.x >= N || head.y < 0 || head.x < 0 || visited[head.y][head.x] == 1) {
            break;
        }

        visited[head.y][head.x] = 1;
        snake.push(head);
        if (grid[head.y][head.x] == 1) {
            snake.push(tail);
            snakelength++;
        }
        else {
            visited[tail.y][tail.x] = 0;
            tail.y += dy[taildir];
            tail.x += dx[taildir];
            snake.push(tail);
        }

        if (timer == transbox.time) {
            dir = (4 + dir + transbox.dirt) % 4;
            transtaildir.push({ timer + snakelength, dir});
            if (!check) {
                tailtrans = transtaildir.front();
                transtaildir.pop();
                check = true;
            }
            if (!transdir.empty()) {
                transbox = transdir.front();
                transdir.pop();
            }
        }

        if (check) {
            if (timer == tailtrans.time) {
                tail.y -= dy[taildir];
                tail.x -= dx[taildir];
                taildir = tailtrans.dirt;
                tail.y += dy[taildir];
                tail.x += dx[taildir];
                if (!transtaildir.empty()) {
                    tailtrans = transtaildir.front();
                    transtaildir.pop();
                }
            }
        }

        cout << "\n";
    }
    cout << timer;

    return 0;
}
