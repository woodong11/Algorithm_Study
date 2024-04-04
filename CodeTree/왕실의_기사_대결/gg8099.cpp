#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct kni {
    int r, c, k, t;
};


int L, N, Q, k;
int map[42][42], visited[42][42], dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 };
vector<kni> sol[31];
vector<kni> tmp[31];
int cnt;

void input() {
    cin >> L >> N >> Q;
    for (int i = 1; i <= L; i++) {

        for (int j = 1; j <= L; j++) {
            int tmp;
            cin >> tmp;
            if (tmp == 1)
                map[i][j] = -1;
            else if (tmp == 2)
                map[i][j] = -2;
        }
    }
    for (int i = 0; i <= L + 1; i++) {//벽 만들기
        map[0][i] = -2;
        map[i][0] = -2;
        map[L + 1][i] = -2;
        map[i][L + 1] = -2;
    }
    for (int x = 1; x <= N; x++) { // 기사들 정보 받기
        int r, c, h, w, k, tmp;
        cin >> r >> c >> h >> w >> k;
        tmp = k;
        for (int i = 0; i < h; i++) { //sol[기사넘버][0]에 기준좌표, sol[기사넘버][0].size()가 방패크기
            for (int j = 0; j < w; j++) {
                sol[x].push_back({ r + i,c + j,k,tmp });
                visited[r + i][c + j] = x;
            }
        }
    }
}
void solve(int num, int dir) {
    if (sol[num][0].k == 0)
        return;
    for (int i = 1; i <= N; i++) {
        tmp[i] = sol[i];
    }
    queue<int> q;
    q.push(num);
    int flag = 0;
    int vis[31] = { 0, };
    int mv[31] = { 0, };
    while (!q.empty()) { //다음칸이 자기 자신이면 안넣고 그냥 진행
        int now = q.front();
        mv[now] = 1;
        q.pop();
        int size = sol[now].size(); // r x c
        for (int i = 0; i < size; i++) {
            tmp[now][i].r += dy[dir];
            tmp[now][i].c += dx[dir];
            if (map[tmp[now][i].r][tmp[now][i].c] == -2) {
                flag = 1; //벽이면 체력 감소 안하기
                return;
            }
            if (visited[tmp[now][i].r][tmp[now][i].c] == now)
                continue;
            if (visited[tmp[now][i].r][tmp[now][i].c] == 0)
                continue;
            if (vis[visited[tmp[now][i].r][tmp[now][i].c]] != 0)
                continue;
            q.push({ visited[tmp[now][i].r][tmp[now][i].c] });
            vis[visited[tmp[now][i].r][tmp[now][i].c]] = 1;
        }
    }
    for (int i = 1; i <= N; i++) {
        int size = sol[i].size();
        for (int j = 0; j < size; j++) {
            visited[sol[i][j].r][sol[i][j].c] = 0;
        }
        sol[i] = tmp[i];
    }

    for (int i = 1; i <= N; i++) {
        int size = sol[i].size();
        if (i == num) {
            for (int j = 0; j < size; j++) {
                visited[sol[i][j].r][sol[i][j].c] = i;
            }
            continue;
        }
        if (sol[i][0].k == 0)
            continue;
        for (int j = 0; j < size; j++) {
            if (mv[i] == 0)
                break;
            if (map[sol[i][j].r][sol[i][j].c] == -1) {
                sol[i][0].k--;
            }
            if (sol[i][0].k == 0)
                break;
        }
        if (sol[i][0].k == 0)
            continue;
        for (int j = 0; j < size; j++) {
            visited[sol[i][j].r][sol[i][j].c] = i;
        }
    }

}
int main() {
    input();
    for (int i = 0; i < Q; i++) {
        int num, dir;
        cin >> num >> dir;
        solve(num, dir);
    }
    for (int i = 1; i <= N; i++) {
        if (sol[i][0].k != 0)
            cnt += sol[i][0].t - sol[i][0].k;
    }
    cout << cnt;


    return 0;
}
