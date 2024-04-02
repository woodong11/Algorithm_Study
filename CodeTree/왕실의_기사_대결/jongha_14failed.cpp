#include <iostream>
#include <vector>
#include <queue>
#include<unordered_set>

using namespace std;

// 구현할 것.
// 1. 기사가 밀 때 2차 이상으로 건너서 밀리는 애들이 배열에 넘어가는 것을 탐지 해야함
// -> dfs
// 기사가 밀고 밀리는게 있다면 q에 담아서 dfs를 돌릴까? 

struct Knight {
    int y, x;
    int h, w;
};

struct Point {
    int y, x;
};

int grid[42][42];
int position[42][42];
int knight_h[31];
int init_h[31];
int L, N, Q, dy[4] = { -1, 0, 1, 0 }, dx[4] = { 0, 1, 0, -1 };
int r, c, h, w, k;
vector<Knight> v(31);
unordered_set<int> target;

bool isthrust(int y, int x, int d, int kn_n) {
    unordered_set<int>s;

    while (1) {
        if (y > L || x > L || y < 1 || x < 1 || grid[y][x] == 2) return false;
        if (position[y][x] == 0) {
            if (s.size() != 0) {
                for (unordered_set<int>::iterator iter = s.begin(); iter != s.end(); iter++) {
                    if (d == 1 || d == 3) {
                        for (int i = 0; i < v[*iter].h; i++) {
                            if (!isthrust(v[*iter].y + i, v[*iter].x, d, *iter)) {
                                target = unordered_set<int>();
                                return false;
                            }
                        }

                        target.insert(*iter);
                    }
                    else {
                        for (int i = 0; i < v[*iter].w; i++) {
                            if (!isthrust(v[*iter].y, v[*iter].x + i, d, *iter)) {
                                target = unordered_set<int>();
                                return false;
                            }
                        }

                        target.insert(*iter);
                    }
                }

                return true;
            }
            else {
                int a = position[y - dy[d]][x - dx[d]];
                if (a != kn_n) {
                    target.insert(a);
                }
            }
            return true;
        }
        else if (position[y][x] == kn_n) {
            y += dy[d];
            x += dx[d];
        }
        else {
            s.insert(position[y][x]);
            y += dy[d];
            x += dx[d];
        }
    }
}
// 기사들을 해당 방향으로 움직이기
void push_out(int kn_n, int d) {
    // 첫줄 지우기
    if (d == 1) {
        int x = v[kn_n].x;
        for (int i = v[kn_n].y; i < v[kn_n].y + v[kn_n].h; i++) {
            position[i][x] = 0;
        }
        for (unordered_set<int>::iterator iter = target.begin(); iter != target.end(); iter++) {
            for (int i = v[*iter].y; i < v[*iter].y + v[*iter].h; i++) {
                position[i][v[*iter].x] = 0;
            }
            v[*iter].y += dy[d];
            v[*iter].x += dx[d];
        }
    }
    else if (d == 3) {
        int x = v[kn_n].x + v[kn_n].w - 1;
        for (int i = v[kn_n].y; i < v[kn_n].y + v[kn_n].h; i++) {
            position[i][x] = 0;
        }
        for (unordered_set<int>::iterator iter = target.begin(); iter != target.end(); iter++) {
            x = v[*iter].x + v[*iter].w - 1;
            for (int i = v[*iter].y; i < v[*iter].y + v[*iter].h; i++) {
                position[i][x] = 0;
            }
            v[*iter].y += dy[d];
            v[*iter].x += dx[d];
        }
    }
    else if(d == 2) {
        int y = v[kn_n].y;
        for (int i = v[kn_n].x; i < v[kn_n].x + v[kn_n].w; i++) {
            position[y][i] = 0;
        }
        for (unordered_set<int>::iterator iter = target.begin(); iter != target.end(); iter++) {
            for (int i = v[*iter].x; i < v[*iter].x + v[*iter].w; i++) {
                position[v[*iter].y][i] = 0;
            }
            v[*iter].y += dy[d];
            v[*iter].x += dx[d];
        }
    }
    else {
        int y = v[kn_n].y + v[kn_n].h - 1;
        for (int i = v[kn_n].x; i < v[kn_n].x + v[kn_n].w; i++) {
            position[y][i] = 0;
        }
        for (unordered_set<int>::iterator iter = target.begin(); iter != target.end(); iter++) {
            y = v[*iter].y + v[*iter].h - 1;
            for (int i = v[*iter].x; i < v[*iter].x + v[*iter].w; i++) {
                position[y][i] = 0;
            }
            v[*iter].y += dy[d];
            v[*iter].x += dx[d];
        }
    }

    // 해당 방향으로 한칸 움직이기
    v[kn_n].y += dy[d];
    v[kn_n].x += dx[d];
    int y = v[kn_n].y, x = v[kn_n].x;
    for (int i = 0; i < v[kn_n].h; i++) {
        for (int j = 0; j < v[kn_n].w; j++) {
            if (j > 0) x++;
            position[y][x] = kn_n;
        }
        y++;
        x = v[kn_n].x;
    }

    // isthrust 에서 탐색했던 밀쳐지는 기사들을 움직이고, 체력 깎기
    for (unordered_set<int>::iterator iter = target.begin(); iter != target.end(); iter++) {
        bool check = false;
        for (int i = 0; i < v[*iter].h; i++) {
            y = v[*iter].y + i;
            for (int j = 0; j < v[*iter].w; j++) {
                x = v[*iter].x + j;
                
                if (grid[y][x] == 1) {
                    knight_h[*iter]--;
                    if (knight_h[*iter] == 0) {
                        check = true;
                        break;
                    }
                }
                position[y][x] = *iter;
            }

            if (check) break;
        }

        if (check) {
            for (int i = 0; i < v[*iter].h; i++) {
                y = v[*iter].y + i;
                for (int j = 0; j < v[*iter].w; j++) {
                    x = v[*iter].x + j;

                    if (position[y][x] != *iter) {
                        break;
                    }
                    position[y][x] = 0;
                }
            }
        }
    }

    target = unordered_set<int>();
}
// 명령 내리기
void order(int kn_n, int d) {
    if (d == 1) {
        Point now = { v[kn_n].y, v[kn_n].x + v[kn_n].w };

        // ~h
        for (int i = 0; i < v[kn_n].h; i++) {
            if (!isthrust(now.y + i, now.x, d, position[now.y][now.x - 1])) return;
        }

        push_out(kn_n, d);
    }
    else if( d == 2 ) {
        Point now = { v[kn_n].y + v[kn_n].h, v[kn_n].x};

        // ~w
        for (int i = 0; i < v[kn_n].w; i++) {
            if (!isthrust(now.y, now.x + i, d, position[now.y - 1][now.x])) return;
        }
        
        push_out(kn_n, d);
    }
    else if (d == 3) {
        Point now = { v[kn_n].y, v[kn_n].x};

        // ~h
        for (int i = 0; i < v[kn_n].h; i++) {
            if (!isthrust(now.y + i, now.x, d, position[now.y][now.x])) return;
        }

        push_out(kn_n, d);
    }
    else {
        Point now = { v[kn_n].y, v[kn_n].x };

        // ~w
        for (int i = 0; i < v[kn_n].w; i++) {
            if (!isthrust(now.y, now.x + i, d, position[now.y][now.x])) return;
        }

        push_out(kn_n, d);
    }
}

int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> L >> N >> Q;

    for (int i = 0; i <= L + 1; i++) {
        for (int j = 0; j <= L + 1; j++) {
            if (i == 0 || j == 0 || i == L + 1 || j == L + 1) {
                grid[i][j] = 2;
                continue;
            }
            cin >> grid[i][j];
        }
    }

    for (int i = 1; i <= N; i++) {
        cin >> r >> c >> h >> w >> k;
        v[i] = { r, c, h, w };
        knight_h[i] = k;
        init_h[i] = k;

        for (int j = 0; j < h; j++) {
            for (int k = 0; k < w; k++) {
                position[r + j][c + k] = i;
            }
        }
    }

    int a, b;
    for (int i = 0; i < Q; i++) {
        cin >> a >> b;

        if (knight_h[a] <= 0) continue;
        order(a, b);
    }

    int sum = 0;
    for (int i = 1; i <= N; i++) {
        if (knight_h[i] > 0) {
            sum += (init_h[i] - knight_h[i]);
        }
    }

    cout << sum;

    return 0;
}
