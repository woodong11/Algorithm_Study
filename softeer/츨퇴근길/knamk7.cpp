#include<iostream>
#include<queue>
#include<unordered_set>
#include<vector>

using namespace std;

int n, m;
int S, T;
vector<vector<int>> v;
vector<vector<int>> v_reversed;
vector<int> visited0;
vector<int> visited1;
vector<int> visited2;
vector<int> visited3;

// 출근길 순방향 탐색
void bfs0(int start)
{
    queue<int> q;
    q.push(start);
    visited0[start] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == T) continue;
        for (int i : v[now]) {
            if (visited0[i] == 1) continue;
            q.push(i);
            visited0[i] = 1;
        }
    }
}

// 출근길 역방향 탐색
void bfs1(int start)
{
    queue<int> q;
    q.push(start);
    visited1[start] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i : v_reversed[now]) {
            if (visited1[i] == 1) continue;
            q.push(i);
            visited1[i] = 1;
        }
    }
}

// 퇴근길 순방향 탐색
void bfs2(int start)
{
    queue<int> q;
    q.push(start);
    visited2[start] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == S) continue;
        for (int i : v[now]) {
            if (visited2[i] == 1) continue;
            q.push(i);
            visited2[i] = 1;
        }
    }
}

// 퇴근길 역방향 탐색
void bfs3(int start)
{
    queue<int> q;
    q.push(start);
    visited3[start] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i : v[now]) {
            if (visited3[i] == 1) continue;
            q.push(i);
            visited3[i] = 1;
        }
    }
}

int main(int argc, char** argv)
{
    cin >> n >> m;
    v = vector<vector<int>>(n+1);
    v_reversed = vector<vector<int>>(n+1);
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        v[from].push_back(to);
        v_reversed[to].push_back(from);
    }
    cin >> S >> T;
    visited0 = vector<int>(n+1);
    visited1 = vector<int>(n+1);
    visited2 = vector<int>(n+1);
    visited3 = vector<int>(n+1);

    bfs0(S);
    bfs1(T);
    bfs2(T);
    bfs3(S);

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (i == S || i == T) continue;
        cnt += (visited0[i] && visited1[i] && visited2[i] && visited3[i]);
    }
    cout << cnt;

   return 0;
}
