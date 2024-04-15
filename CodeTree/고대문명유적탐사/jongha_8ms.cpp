// 실수한 것.
// 회전 우선순위 구현할 때 처음에 반대로 구현했다가 틀린 거 알고 다시 고쳤는데, 마지막 고칠 때 행렬 우선순위를 반대로 구현함 -> 문제 똑바로 읽기
// 런타임에러, 지역변수 초기화 주의할 것. 특히 놓치기 쉬운 구조체
// 탐사반복에 대한 구현을  빼먹음 -> 문제 똑바로 읽기 ㅋㅋ

#include <iostream>
#include<vector>
#include<queue>

using namespace std;

struct Point {
    int y, x;
};

struct Max_relics {
    int max_val, type;
    Point center;
    queue<Point> q;
};

vector<vector<int>> v(5, vector<int>(5, 0));
queue<int> q;
int dy[4] = { 0, 0, 1, -1 }, dx[4] = { 1, -1, 0, 0 };
int K = 5, T, M, result;

Max_relics find_relics(vector<vector<int>> tempv, Point now, int type) {
    int visited[5][5] = { 0, };
    Max_relics m_r = { 0, type, now };

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            if (visited[i][j] == 1) continue;

            queue<Point> t_q;
            queue<Point> r_q;
            r_q.push({ i, j });
            t_q.push({ i, j });
            int a = 1;

            while (!t_q.empty()) {
                Point now = t_q.front();
                visited[now.y][now.x] = 1;
                t_q.pop();
                Point next;

                for (int z = 0; z < 4; z++) {
                    next = { now.y + dy[z], now.x + dx[z] };

                    if (next.y < 0 || next.x < 0 || next.x >= K || next.y >= K) continue;
                    if (visited[next.y][next.x] == 1) continue;
                    if (tempv[i][j] == tempv[next.y][next.x]) {
                        t_q.push({ next.y, next.x });
                        r_q.push({ next.y, next.x });
                        visited[next.y][next.x] = 1;
                        a++;
                    }
                }
            }

            if (a >= 3) {
                m_r.max_val += a;
                while (!r_q.empty()) {
                    m_r.q.push(r_q.front());
                    r_q.pop();
                }
            }
        }
    }

    return m_r;
}

// type == 0 : 90, 1 : 180, 2 : 270
Max_relics rotate(vector<vector<int>> tempv, Point now, int type) {
    int startx = now.x - 1, starty = now.y - 1;
    queue<int> t_q;

    for (int i = starty; i < starty + 3; i++) {
        for (int j = startx; j < startx + 3; j++) {
            t_q.push(tempv[i][j]);
        }
    }

    if (type == 0) {
        for (int i = startx + 2; i >= startx; i--) {
            for (int j = starty; j < starty + 3; j++) {
                tempv[j][i] = t_q.front();
                t_q.pop();
            }
        }
    }
    else if (type == 1) {
        for (int i = starty + 2; i >= starty; i--) {
            for (int j = startx + 2; j >= startx; j--) {
                tempv[i][j] = t_q.front();
                t_q.pop();
            }
        }
    }
    else {
        for (int i = startx; i < startx + 3; i++) {
            for (int j = starty + 2; j >= starty; j--) {
                tempv[j][i] = t_q.front();
                t_q.pop();
            }
        }
    }

    return find_relics(tempv, now, type);
}

void solve() {
    Max_relics max_r = { 0, };
    Max_relics temp_r = { 0, };

    for (int i = 1; i < K - 1; i++) {
        for (int j = 1; j < K - 1; j++) {
            for (int z = 0; z < 3; z++) {
                temp_r = rotate(v, { i, j }, z);

                if (max_r.max_val < temp_r.max_val) {
                    max_r = temp_r;
                }
                else if (max_r.max_val == temp_r.max_val) {
                    if (max_r.type > temp_r.type) {
                        max_r = temp_r;
                    }
                    else if (max_r.type == temp_r.type) {
                        if (max_r.center.x > temp_r.center.x) {
                            max_r = temp_r;
                        }
                        else if (max_r.center.x == temp_r.center.x) {
                            if (max_r.center.y > temp_r.center.y) {
                                max_r = temp_r;
                            }
                        }
                    }
                }
            }
        }
    }

    if (max_r.q.empty()) {
        return;
    }

    // 회전하고 비우고 채우기
    queue<int> t_q;
    int starty = max_r.center.y - 1;
    int startx = max_r.center.x - 1;
    int type = max_r.type;

    for (int i = starty; i < starty + 3; i++) {
        for (int j = startx; j < startx + 3; j++) {
            t_q.push(v[i][j]);
        }
    }

    if (type == 0) {
        for (int i = startx + 2; i >= startx; i--) {
            for (int j = starty; j < starty + 3; j++) {
                v[j][i] = t_q.front();
                t_q.pop();
            }
        }
    }
    else if (type == 1) {
        for (int i = starty + 2; i >= starty; i--) {
            for (int j = startx + 2; j >= startx; j--) {
                v[i][j] = t_q.front();
                t_q.pop();
            }
        }
    }
    else {
        for (int i = startx; i < startx + 3; i++) {
            for (int j = starty + 2; j >= starty; j--) {
                v[j][i] = t_q.front();
                t_q.pop();
            }
        }
    }

    while (!max_r.q.empty()) {
        Point now = max_r.q.front();
        max_r.q.pop();

        v[now.y][now.x] = 0;
    }

    for (int i = 0; i < K; i++) {
        for (int j = K - 1; j >= 0; j--) {
            if (v[j][i] == 0) {
                v[j][i] = q.front();
                q.pop();
            }
        }
    }

    result += max_r.max_val;

    while (1) {
        int visited[5][5] = { 0, };
        Max_relics m_r = { 0, };

        for (int i = 0; i < K; i++) {
            for (int j = 0; j < K; j++) {
                if (visited[i][j] == 1) continue;

                queue<Point> t_q;
                queue<Point> r_q;
                r_q.push({ i, j });
                t_q.push({ i, j });
                int a = 1;

                while (!t_q.empty()) {
                    Point now = t_q.front();
                    visited[now.y][now.x] = 1;
                    t_q.pop();
                    Point next;

                    for (int z = 0; z < 4; z++) {
                        next = { now.y + dy[z], now.x + dx[z] };

                        if (next.y < 0 || next.x < 0 || next.x >= K || next.y >= K) continue;
                        if (visited[next.y][next.x] == 1) continue;
                        if (v[i][j] == v[next.y][next.x]) {
                            t_q.push({ next.y, next.x });
                            r_q.push({ next.y, next.x });
                            visited[next.y][next.x] = 1;
                            a++;
                        }
                    }
                }

                if (a >= 3) {
                    m_r.max_val += a;

                    while (!r_q.empty()) {
                        m_r.q.push(r_q.front());
                        r_q.pop();
                    }
                }
            }
        }

        if (m_r.max_val == 0) break;
        else {
            while (!m_r.q.empty()) {
                Point now = m_r.q.front();
                m_r.q.pop();

                v[now.y][now.x] = 0;
            }

            for (int i = 0; i < K; i++) {
                for (int j = K - 1; j >= 0; j--) {
                    if (v[j][i] == 0) {
                        v[j][i] = q.front();
                        q.pop();
                    }
                }
            }
            result += m_r.max_val;
        }
    }
}

int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T >> M;

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            cin >> v[i][j];
        }
    }

    int a;
    for (int i = 0; i < M; i++) {
        cin >> a;
        q.push(a);
    }

    for (int i = 0; i < T; i++) {
        solve();
        if (result == 0) break;
        cout << result << " ";
        result = 0;
    }

    return 0;
}
