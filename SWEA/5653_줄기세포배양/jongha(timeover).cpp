#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#define SORT 305

using namespace std;


// X 시간 동안 비활성 상태
// X 시간 지난 후 활성 상태
// X 시간 동안 살아 있고, X 시간 지나면 죽음.
// 동시에 번식할 경우 생명력 수치가 높은 세포가 우선순위


/*
    활성화된 q, 활성화되지 않은 q 선언.
    활성화된 q는 번식 -> 그리드에 담고 비활성화된 건 visited 체크 ->
    담을 때 중복 되면 큰 숫자를 담기.
    활성화되면 활성화된 q에 담기.
*/

struct Cell {
    int y;
    int x;
    int active;
    int life;
};

bool compare(Cell& a, Cell& b) {
    if(a.active != b.active) return a.active < b.active;
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

int visited[700][700];
int T, N, M, K;
int dx[4] = { 0, 0, -1, 1 }, dy[4] = { 1, -1, 0, 0 };
deque<Cell> dq;

void init() {
    for (int i = 0; i < 700; i++) {
        for (int z = 0; z < 700; z++) {
            visited[i][z] = 0;
        }
    }

    dq.clear();
}



int main() {
    int a;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cin >> N >> M >> K;
        init();

        for (int i = 0; i < N; i++) {
            for (int z = 0; z < M; z++) {
                cin >> a;
                if (a == 0) continue;
                dq.push_back({ i + SORT, z + SORT, 0, a });
                visited[i + SORT][z + SORT] = 1;
            }
        }

        int dqsize, ny, nx;
        Cell cell;
        for (int i = 0; i < K; i++) {
            dqsize = dq.size();


            for (int z = 0; z < dqsize; z++) {
                if (dq[0].life == dq[0].active) {
                    cell = dq[0];
                    dq[0].active++;
                    if (dq[0].active != dq[0].life * 2) {
                        dq.push_back({ dq[0] });
                    }
                    for (int i = 0; i < 4; i++) {
                        ny = cell.y + dy[i];
                        nx = cell.x + dx[i];

                        if (visited[ny][nx] == 1) continue;
                        dq.push_back({ny, nx, 0, dq[0].life});
                    }
                    dq.pop_front();
                    continue;
                }



                dq[0].active++;
                if (dq[0].life * 2 != dq[0].active) {
                    dq.push_back(dq[0]);
                }
                
                dq.pop_front();
            }

            sort(dq.begin(), dq.end(), compare);

            if (dq[0].active != 0) continue;

            cell = dq[0];
            visited[cell.y][cell.x] = 1;
            dq.pop_front();

            if (dq[0].active != 0 ) {
                visited[cell.y][cell.x] = 1;
                break;
            }

            while (true) {
                if (cell.y == dq[0].y && cell.x == dq[0].x) {
                    cell = cell.life > dq[0].life ? cell : dq[0];
                    dq.pop_front();
                }
                else {
                    visited[cell.y][cell.x] = 1;
                    dq.push_back(cell);
                    cell = dq[0];
                }
                if (cell.active != 0) break;
            }

            dqsize = dq.size();
        }

        cout << "#" << tc << " " << dq.size() << "\n";
    }

    return 0;
}
