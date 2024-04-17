#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct Node {
    int y;
    int x;
};

int MAP[5][5];
int visited[5][5];
int order[5][5];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

int N, M, answer;
Node startPoint;

void input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
        }
    }
    // 순서 -> order맵에 기록해두기
    int row, col;
    int tempOrder = 1;
    for (int i = 0; i < M; i++) {
        cin >> row >> col;
        order[row - 1][col - 1] = tempOrder;
        if (tempOrder == 1)
            startPoint = { row - 1, col - 1 };
        tempOrder++;
    }
}

// M개 순서대로 다 하면 return하고 cnt ++
void func(int level, int curY, int curX) {
    if (level == M) {
        answer++;
        return;
    }

    for (int k = 0; k < 4; k++)
    {
        int ny = curY + dy[k];
        int nx = curX + dx[k];

        // 범위 벗어난 경우
        if (ny < 0 || nx < 0 || ny >= N || nx >= N)
            continue;

        // 벽이거나 이미 방문한 곳인 경우
        if (MAP[ny][nx] == 1 || visited[ny][nx] == 1)
            continue;
       
        // 재귀 타기
        visited[ny][nx] = 1;
        if (order[ny][nx] == level + 1) { // 다음 번호일때
            func(level + 1, ny, nx);
        }
        else {                            // 다음 번호가 아닐때
            func(level, ny, nx);
        }
        visited[ny][nx] = 0;            
    }
}

void solve() {
    visited[startPoint.y][startPoint.x] = 1;
    func(1, startPoint.y, startPoint.x);
}


int main() {
    //freopen("sample_input.txt", "r", stdin);
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    input();
    solve();

    cout << answer;

    return 0;
}
