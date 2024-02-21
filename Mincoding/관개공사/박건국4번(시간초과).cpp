#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

int parent[16];
char map_char[51][51];
int map[51][51], dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
int T, X, Y, a_num;
struct node {
    int from, to;
    int price;
};
struct YX {
    int y, x;
};
struct cmp {
    bool operator() (node a, node b) {
        return a.price > b.price;
    }
};
priority_queue<node, vector<node>, cmp> pq;
vector<YX> locate;
void reset() {
    memset(parent, 0, sizeof(parent));
    memset(map_char, 0, sizeof(map_char));
    memset(map, 0, sizeof(map));
    pq = {}, locate = {}, a_num = 0;
}
int bfs(YX st, YX end) {
    int temp[51][51] = { 0 };
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            temp[i][j] = map[i][j];
        }
    }
    int result = 0;
    queue<YX> q;
    q.push(st);
    while (!q.empty()) {
        YX now = q.front();
        q.pop();
        YX next = { 0 };
        for (int i = 0; i < 4; i++) {
            next.y = now.y + dy[i];
            next.x = now.x + dx[i];

            if (next.y >= Y || next.x >= X || next.y < 0 || next.x < 0)
                continue;
            if (temp[next.y][next.x] != 0)
                continue;
            temp[next.y][next.x] = temp[now.y][now.x] + 1;
            if (next.y == end.y && next.x == end.x) {
                int result = temp[next.y][next.x];
                return result;
            }
            q.push(next);
        }
    }
}
void setting() {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            cin >> map_char[i][j];
            if (map_char[i][j] == '_')
                map[i][j] = 0;
            else if (map_char[i][j] == 'A' || map_char[i][j] == 'S') {
                int y = i, x = j;
                map[i][j] = 0;
                a_num++;
                locate.push_back({ i,j });
            }
            else
                map[i][j] = -1;
        }
    }
    for (int i = 0; i < locate.size(); i++) {
        for (int j = i+1; j < locate.size(); j++) {
            YX st, end;
            st = { locate[i].y, locate[i].x }, end = { locate[j].y,locate[j].x };
            int temp_price = bfs(st, end);
            pq.push({ i, j, temp_price });
        }
    }
}

void init() {
    for (int i = 0; i < a_num; i++)
        parent[i] = i;
}
int find(int tar) {
    if (tar == parent[tar])
        return tar;

    int ret = find(parent[tar]);
    parent[tar] = ret;
    return ret;
}
void unionset(int a, int b) {
    int t1 = find(a);
    int t2 = find(b);
    if (t1 == t2)
        return;
    parent[t2] = t1;;
}
void mst() {
    int result = 0, node_cnt = 0, flag = 0;
    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (find(now.from) == find(now.to))
            continue;

        unionset(now.from, now.to);
        node_cnt++, result += now.price;
        if (locate.size() - 1 == node_cnt) {
            flag = 1;
            break;
        }
    }
    cout << result << endl;
}
int main() {
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> X >> Y;
        setting();
        init();
        mst();
        reset();
    }
    return 0;
}
