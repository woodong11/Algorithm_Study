#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;

int N, M, H, target, answer = -1;
int MAP[31][11];

void input() {
    cin >> N >> M >> H;
    int a, b;
    for (int i = 0; i < M; i++)
    {
        cin >> a >> b;
        MAP[a][b] = 1;
        MAP[a][b + 1] = 2;     
    }
}

// 맵에서 사다리 타고 체크하는 타고, 2를 만나면 왼쪽으로 타게 된다.
bool check() {
    for (int i = 1; i <= N; i++) {
        int col = i;
        int row = 0;
        while (row <= H) {
            if (MAP[row][col] == 1) {       // 오른쪽으로 가는 경우
                col++;
            }
            else if (MAP[row][col] == 2) {  // 왼쪽으로 가는 경우
                col--;
            }
            row++;
        }
        if (col != i)
            return false;
    }
    return true;
}

// DFS로 조합짜면서 체크 - level, 이전 행, 이전 열
void func(int level, int preRow, int preCol) {

    if (level == target) {
        if (check())
            answer = level;
        return;
    }
    // for문 변수 설정 이렇게 해주면 j돌때 이전에 돌았던 거 다시 안돌아도 된다
    // 첫 i의 j만 preCol부터 시작하고, 그 다음번엔 정해둔 1부터 시작한다.
    // -> 조합 구현이 가능해서 가지치기 효과를 낸다!!
    for (int i = preRow; i <= H; i++, preCol = 1) {
        for (int j = preCol; j <= N-1; j++) {
            if (MAP[i][j])
                continue;
            if ((MAP[i][j - 1])== 1)    // 왼쪽 체크
                continue;
            if (MAP[i][j + 1] == 1)    // 오른쪽 체크
                continue;

            MAP[i][j] = 1;
            MAP[i][j + 1] = 2;
            func(level + 1, i, j);
            MAP[i][j] = 0;
            MAP[i][j + 1] = 0;

        }
    }
}

void solve() {

    // 0번, 1번, 2번, 3번 재귀타는 코드
    for (int i = 0; i <= 3; i++) {
        target = i;
        func(0, 1, 1);
        if (answer != -1) {
            cout << answer;
            return;
        }
    }
    cout << -1;
}

int main() {
    freopen("sample_input.txt", "r", stdin);

    input();
    solve();

    return 0;
}
