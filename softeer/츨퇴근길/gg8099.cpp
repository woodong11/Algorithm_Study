#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> vec[100001];
vector<int> vec1[100001];
int N, M, st, ed, flag, cnt;
int visited[100001], arr[100001], arr1[100001];

void bfs1(int input_val) {
    queue<int> q;
    q.push(input_val);
    visited[input_val] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0; i < vec1[now].size(); i++) {
            int next = vec1[now][i];
            if (visited[next] == 1)
                continue;
            visited[next] = 1;
            q.push(next);
        }
    }
}

void bfs2(int input_val, int not_goal) {
    queue<int> q;
    q.push(input_val);
    visited[input_val] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0; i < vec[now].size(); i++) {
            int next = vec[now][i];
            if (next == not_goal)
                continue;
            if (visited[next] == 1)
                continue;
            visited[next] = 1;
            q.push(next);
        }
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int from, to;
        cin >> from >> to;
        vec[from].push_back(to);
        vec1[to].push_back(from);
    }
    cin >> st >> ed;

    bfs1(st);
    for (int i = 1; i <= N; i++) {
        if (i == st || i == ed) {
            visited[i] = 0;
            continue;
        }
        if (visited[i] == 1)
            arr[i] = 1;
        visited[i] = 0;
    }
    bfs1(ed);
    for (int i = 1; i <= N; i++) {
        if (i == st || i == ed) {
            visited[i] = 0;
            continue;
        }
        if (visited[i] == 1 && arr[i] == 1)
            arr[i] = 1;
        else
            arr[i] = 0;
        visited[i] = 0;
    }


    bfs2(st, ed);
    for (int i = 1; i <= N; i++) {
        if (i == st || i == ed) {
            visited[i] = 0;
            continue;
        }
        if (visited[i] == 1 && arr[i] == 1)
            arr1[i] = 1;
        visited[i] = 0;
    }
    bfs2(ed, st);
    for (int i = 1; i <= N; i++) {
        if (i == st || i == ed) {
            visited[i] = 0;
            continue;
        }
        if (visited[i] == 1 && arr1[i] == 1)
            cnt++;
    }

    cout << cnt;
}
