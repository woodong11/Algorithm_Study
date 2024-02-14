#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stdio.h>

using namespace std;

int T, N, checkCnt, answer, totalNum;
int MAP[9][9];
int peoples[9];
int visited[9];
int checkVisited[9];


void init() {
    memset(MAP, 0, sizeof(MAP));
    memset(peoples, 0, sizeof(peoples));
    
    checkCnt = 0;
    totalNum = 0;
    answer = 21e8;
}

void input() {
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cin >> MAP[i][j];
        }
    }
    for (int i = 1; i <= N; i++)
    {
        cin >> peoples[i];
        totalNum += peoples[i];
    }
}

// 해당 노드에서 연결된 노드 몇갠지 반환
// 이거 처음에 잘못짜서 정답 이상하게 나옴 - 처음에 모든 check 가짓수마다 checkCnt가 ++되게 짜버렸음
void check(int node) {

    for (int i = 1; i <= N; i++)
    {
        if (MAP[node][i] == 1) {
            if (visited[i] == 1)
                continue;

            visited[i] = 1;
            checkVisited[i] = 1;
            checkCnt++;
            check(i);
            //visited[i] = 0;       // 이거때매...
        }
    }
}

void dfs(int node, int cnt, int sum) {
    
    if (cnt == N)   // 깊이가 N-1이 되면 종료
        return;

    // visited 안 한 노드가 있으면 그 노드와 연결된 개수를 구한다
    memset(checkVisited, 0, sizeof(visited));
    checkCnt = 0;
    for (int i = 1; i <= N; i++)
    {
        if (visited[i] == 0) { 
            check(i);  
            break;
        }
    }
    // check 하느라 visited 체크한거 원상복구
    for (int i = 1; i <= N; i++)
    {
        if (checkVisited[i] == 1)
            visited[i] = 0;
    }

    // 알맞게 둘로 나눠졌다면
    if (cnt + checkCnt == N) {
        answer = min(answer, abs(sum - (totalNum-sum)));
    }


    for (int i = 1; i <= N; i++) {
        if (MAP[node][i] == 1) {
            if (visited[i] == 1)
                continue;

            visited[i] = 1;
            dfs(i, cnt + 1, sum + peoples[i]);
            visited[i] = 0;
        }
    }
}


void solve() {
    for (int i = 1; i <=N; i++){
        visited[i] = 1;
        dfs(i, 1, peoples[i]);
        visited[i] = 0;
    }
}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        init();
        input();
        solve();
        cout << "#" << tc << " " << answer << "\n";
    }

    return 0;
}
