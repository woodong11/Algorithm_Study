#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// 겪은 오류 : 지역메모리? 초과 pq 를 지역변수로 두고 풀었는데 전역변수로 두니 해결됨, 인덱스초과 

struct sanP {
    int y;
    int x;
    int score;
    int canmove;
};

struct PQ {
    int dr;
    int d;
};

struct compare {
    bool operator()(PQ a, PQ b) {
        if (a.dr != b.dr) return a.dr > b.dr;
        else return a.d >= b.d;
    }
};

int N, M, santaN, C, D, P, cnt;
int dy[8] = { -1, 0, 1, 0, 1, 1, -1, -1 }, dx[8] = { 0, 1, 0, -1, 1, -1, 1, -1 }; // 상우하좌(우하)(좌하)(우상)(좌상)
int ddy_1[4] = { 1, 0, 0, -1 }, ddx_1[4] = { 0, 1, -1, 0 };
int grid[51][51], santa_grid[31];
vector<sanP> v(31);
priority_queue<PQ, vector<PQ>, compare> pq;

void interaction(int d, int n) {
    while (1) {
        int tempn = grid[v[n].y][v[n].x];
        if (tempn < 1) {
            grid[v[n].y][v[n].x] = n;
            break;
        }

        grid[v[n].y][v[n].x] = n;
        n = tempn;
        v[tempn].y += dy[d];
        v[tempn].x += dx[d];

        if (v[tempn].y < 1 || v[tempn].y > N || v[tempn].x < 1 || v[tempn].x > N) {
            cnt--;
            santa_grid[tempn] = 0;
            return;
        }
    }
}

void back_move(int type, int d, int n) {
    if (type == 0) {
        // 루돌프 충돌
        v[n].y += (C * dy[d]);
        v[n].x += (C * dx[d]);
        v[n].score += C;
        v[n].canmove = 2;
    }
    else {
        // 산타 충돌
        d = (d + 2) % 4;
        v[n].y += (D * dy[d]);
        v[n].x += (D * dx[d]);
        v[n].score += D;
        v[n].canmove = 1;
    }

    if (v[n].y > N || v[n].x > N || v[n].y <= 0 || v[n].x <= 0) {
        cnt--;
        santa_grid[n] = 0;
        //아래 코드때매 런타임에러 ( index 초과한 접근 )
        //grid[v[n].y][v[n].x] = 0;
        return;
    }

    interaction(d, n);
}

void deer_move(int d) {
    v[0].y += dy[d];
    v[0].x += dx[d];

    if (grid[v[0].y][v[0].x] > 0) {
        grid[v[0].y][v[0].x] = 0;
        back_move(0, d, grid[v[0].y][v[0].x]);
    }
}

bool santa_move(int n, int d) {
    // 상우하좌
    int nowy = v[n].y, nowx = v[n].x;

    v[n].y += dy[d];
    v[n].x += dx[d];

    if (v[0].y == v[n].y && v[0].x == v[n].x) {
        grid[nowy][nowx] = 0;
        back_move(1, d, n);
        return true;
    }
    else if (grid[v[n].y][v[n].x] > 0) {
        v[n].y -= dy[d];
        v[n].x -= dx[d];
        return false;
    }

    grid[nowy][nowx] = 0;
    grid[v[n].y][v[n].x] = n;
    return true;
}

void solve() {
    int d = 99999;
    int n = 0;
    int tempy = 0;
    int tempx = 0;
    for (int i = 1; i <= santaN; i++) {
        if (santa_grid[i] == 0) continue;
        int a = v[0].y - v[i].y;
        int b = v[0].x - v[i].x;
        int tempd = (pow(a, 2) + pow(b, 2));

        if (tempd < d) {
            d = tempd;
            n = i;
        }
        else if (tempd == d) {
            if (v[n].y == v[i].y) {
                n = v[n].x >= v[i].x ? n : i;
            }
            else {
                n = v[n].y >= v[i].y ? n : i;
            }
        }
    }

    if (v[0].y == 3) {
        int agsdgxb = 1;
    }
    if (v[n].y - v[0].y > 0) {
        tempy = 1;
    }
    else if (v[n].y - v[0].y == 0) {
        tempy = 0;
    }
    else {
        tempy = -1;
    }
    if (v[n].x - v[0].x > 0) {
        tempx = 1;
    }
    else if (v[n].x - v[0].x == 0) {
        tempx = 0;
    } else{
        tempx = -1;
    }
    v[0].y += tempy;
    v[0].x += tempx;
    if (grid[v[0].y][v[0].x] != 0) {
        for (int i = 0; i < 8; i++) {
            if (tempy == dy[i] && tempx == dx[i]) {
                grid[v[0].y][v[0].x] = 0;
                back_move(0, i, n);
                break;
            }
        }
    }

    for (int i = 1; i <= santaN; i++) {
        if (santa_grid[i] == 0)continue;
        if (v[i].canmove > 0) {
            v[i].canmove--;
            continue;
        }
        int gapy = v[0].y - v[i].y;
        int gapx = v[0].x - v[i].x;
        // 상 우 하 좌
        if (gapy > 0 && grid[v[i].y + dy[2]][v[i].x + dx[2]] <= 0) {
            int tmpdr = pow(gapy - dy[2], 2) + pow(gapx - dx[2], 2);
            pq.push({ tmpdr, 2 });
        }
        else if (gapy < 0 && grid[v[i].y + dy[0]][v[i].x + dx[0]] <= 0) {
            int tmpdr = pow(gapy - dy[0], 2) + pow(gapx - dx[0], 2);
            pq.push({ tmpdr,0 });
        }
        if (gapx > 0 && grid[v[i].y + dy[1]][v[i].x + dx[1]] <= 0) {
            int tmpdr = pow(gapy - dy[1], 2) + pow(gapx - dx[1], 2);
            pq.push({ tmpdr, 1 });
        }
        else if (gapx < 0 && grid[v[i].y + dy[3]][v[i].x + dx[3]] <= 0) {
            int tmpdr = pow(gapy - dy[3], 2) + pow(gapx - dx[3], 2);
            pq.push({ tmpdr,3 });
        }

        while (!pq.empty()) {
            PQ s_pq = pq.top();
            pq.pop();
            if (santa_move(i, s_pq.d)) {
                pq = priority_queue<PQ, vector<PQ>, compare>();
                break;
            }
        }
    }
}


int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> santaN >> C >> D;
    int ay, ax;
    cin >> ay >> ax;
    v[0] = { ay, ax };
    int sany, sanx;
    for (int i = 0; i < santaN; i++) {
        cin >> P >> sany >> sanx;
        grid[sany][sanx] = P;
        v[P] = { sany, sanx };
        santa_grid[P] = 1;
        cnt = santaN;
    }

    while (cnt > 0 && M > 0) {
        if (M == 978) {
            int agsseg = 0;
        }
        solve();
        if (cnt == 0) break;
        for (int i = 1; i <= santaN; i++) {
            if (santa_grid[i] == 0) continue;
            v[i].score++;
        }
        M--;
    }

    for (int i = 1; i <= santaN; i++) {
        cout << v[i].score << " ";
    }


    return 0;
}
