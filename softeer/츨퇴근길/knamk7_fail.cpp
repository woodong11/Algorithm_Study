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
void dfs0(int now)
{
    if (visited0[now] == 1 || now == T) {
        return;
    }
    visited0[now] = 1;
    for (int i : v[now]) {
        dfs0(i);
    }
}

// 출근길 역방향 탐색 (T부터 역방향으로 탐색)
void dfs1(int now)
{
    if (visited1[now] == 1 || now == S) {
        return;
    }
    visited1[now] = 1;
    for (int i : v_reversed[now]) {
        dfs1(i);
    }
}

// 퇴근길 순방향 탐색
void dfs2(int now)
{
    if (visited2[now] == 1 || now == S) {
        return;
    }
    visited2[now] = 1;
    for (int i : v[now]) {
        dfs2(i);
    }
}

// 퇴근길 역방향 탐색 (S부터 역방향으로 탐색)
void dfs3(int now)
{
    if (visited3[now] == 1 || now == T) {
        return;
    }
    visited3[now] = 1;
    for (int i : v_reversed[now]) {
        dfs3(i);
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

    dfs0(S);
    dfs1(T);
    dfs2(T);
    dfs3(S);

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (i == S || i == T) continue;
        cnt += (visited0[i] && visited1[i] && visited2[i] && visited3[i]);
    }
    cout << cnt;

   return 0;
}
