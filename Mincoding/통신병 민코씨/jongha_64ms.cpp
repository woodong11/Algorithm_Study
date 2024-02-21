/* 어떻게 한 지 모르겠다 처음에 코드 짠 거에서 안 돼서 속도 높이려고 했던 코드를 하나씩 지우다 보니 됨;

  일단 방향은 distance 라는 bfs 함수로 A or S 사이의 거리를 구해주고, sort 하고 find == find continue 로 싸이클 방지해주고 result 출력.
  여기서 노드가 N-1 이 되지 않을 때나 노드가 1개일 때 0 출력을 해주지 않아서 틀렸었음. 
*/





#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

struct Point {
    int y;
    int x;
    int val;
};

struct Y_X {
    int y;
    int x;
};

int N, M, a, b, c, result = 0, grid[1001], visited[51][51], temp, cnt;
int grand[51][51], dx[4] = { 0, 0, 1, -1 }, dy[4] = { 1, -1, 0, 0 };
vector<Point> v;
vector<Y_X> v_grid;
Y_X s_grid;
queue<Point> q;

void init() {
    for (int i = 0; i < cnt; i++) {
        grid[i] = i;
    }

    for (int i = 0; i < M; i++) {
        for (int z = 0; z < N; z++) {
            visited[i][z] = 0;
        }
    }
}

bool compare(Point a, Point b) {
    if (a.val < b.val) return true;

    return false;
}

int find(int a) {
    if (grid[a] == a) return a;
    int ret = find(grid[a]);
    grid[a] = ret;
    return ret;
}

void merge(int a, int b) {
    int t1 = find(a);
    int t2 = find(b);

    if (t1 == t2) return;
    grid[t2] = t1;
}

void distance(Y_X yx, int dist, int idx) {
    int y, x, ny, nx, tval, tcnt = 0;

    q.push({ yx.y, yx.x, dist });

    while (!q.empty()) {
        x = q.front().x;
        y = q.front().y;
        tval = q.front().val;
        q.pop();
        visited[y][x] = 1;

        for (int i = 0; i < 4; i++) {
            tcnt = 0;
            nx = x + dx[i];
            ny = y + dy[i];

            if (visited[ny][nx] == 1) continue;
            if (ny < 0 || nx < 0 || nx >= N || ny >= M) {
                continue;
            }
            if (grand[ny][nx] == -1) continue;
            if (grand[ny][nx] == idx) continue;

            tcnt++;
            visited[ny][nx] = 1;

            if (grand[ny][nx] >= 1) {
                if (grand[ny][nx] == 222) {
                    v.push_back({ idx, 0, tval + tcnt });
                    continue;
                }
                v.push_back({ idx, grand[ny][nx], tval + tcnt });
            }

            q.push({ ny, nx, tval + tcnt });
        }
    }
}

int main() {
    char s;
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {

        cin >> N >> M;
        cnt = 1;
        result = 0;
        temp = 0;
        v.clear();
        v_grid.clear();


        for (int i = 0; i < M; i++) {
            for (int z = 0; z < N; z++) {
                cin >> s;
                if (s == '#') {
                    grand[i][z] = -1;
                }
                else if (s == 'A') {
                    grand[i][z] = cnt;
                    v_grid.push_back({ i, z });
                    cnt++;
                }
                else if (s == '_') {
                    grand[i][z] = 0;
                }
                else if (s == 'S') {
                    grand[i][z] = 222;
                    s_grid = { i, z };
                }
            }
        }

        init();

        for (int i = 0; i < v_grid.size(); i++) {
            distance(v_grid[i], 0, i + 1);

            for (int z = 0; z < M; z++) {
                for (int k = 0; k < N; k++) {
                    visited[z][k] = 0;
                }
            }
            visited[s_grid.y][s_grid.x] = 0; 
        }

        sort(v.begin(), v.end(), compare);

        for (Point i : v) {
            if (find(i.x) == find(i.y)) {
                continue;
            }

            merge(i.x, i.y);
            result += i.val;
            temp++;

            if (temp == cnt - 1) {
                cout << result << "\n";
                break;
            }
        }
        if (temp != cnt - 1 || cnt == 1) {
            cout << 0 << "\n";
        }
    }

    return 0;
}
