#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int T, N, map[10], total;
int total_cnt = 0;
int visited[10];
int cnt = 0;

void dfs(int left, int right, int level) {
    if (level == N) {
        cnt++;
        return;
    }
    if (right >= total_cnt - right)
        return;
    if (right > left)
        return;


    for (int i = 0; i < N; i++) {
        if (visited[i] == 1)
            continue;
        visited[i] = 1;
        if (right + map[i] > left) {
            dfs(left + map[i], right, level + 1);
        }
        else {
            dfs(left, right + map[i], level + 1);
            dfs(left + map[i], right, level + 1);

        }
        visited[i] = 0;
    }

}

int main() {
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> map[i];
            total_cnt += map[i];
        }
        dfs(0, 0, 0);
        cout << '#' << tc << ' ' << cnt << '\n';

        for (int i = 0; i < 10; i++) {
            visited[i] = 0;
        }
        cnt = 0, total_cnt = 0;
    }
    return 0;
}
