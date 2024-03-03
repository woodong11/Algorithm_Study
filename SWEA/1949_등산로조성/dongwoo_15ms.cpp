#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stdio.h>
using namespace std;
 
int T, N, K, maxNumber, answer;
int MAP[9][9];
int visited[9][9];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
 
struct Node{
    int y;
    int x;
};
 
vector <Node> startPoint;
 
void init() {
    memset(MAP, 0, sizeof(MAP));
    memset(visited, 0, sizeof(visited));
    startPoint.clear();
    maxNumber = 0;
    answer = 0;
}
 
void input() {
    cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
            maxNumber = max(maxNumber, MAP[i][j]);
        }
    }
}
 
void dfs(int row, int col, int dist, int isUsed) {
 
    for (int i = 0; i < 4; i++)
    {
        int ny = row + dy[i];
        int nx = col + dx[i];
 
        if (ny < 0 || nx < 0 || ny >= N || nx >= N)
            continue;
 
        if (visited[ny][nx] == 1)
            continue;
 
        // 지형 아직 안 깎았을때 - 깎거나, 그대로 두기
        if (isUsed == 0) {
 
            // 그대로 두는 경우
            if (MAP[ny][nx] < MAP[row][col]) {
                visited[ny][nx] = 1;
                dfs(ny, nx, dist + 1, 0);
                visited[ny][nx] = 0;
            }
 
            // 깎는 경우
            for (int j = 1; j <= K; j++)
            {   
                int temp = MAP[ny][nx]; // 만약 파낼때, 원래 깊이 복구하기 위해 만듬
                MAP[ny][nx] -= j;
                if (MAP[ny][nx] < MAP[row][col]) {
                    visited[ny][nx] = 1;
                    dfs(ny, nx, dist + 1, 1);
                    visited[ny][nx] = 0;
                }   
                MAP[ny][nx] = temp;
            }
             
        }
         
        // 지형 안 깎을때 - 깎이면 깎인채로, 안 깎이면 안 깎인채로
        else {
            if (MAP[ny][nx] < MAP[row][col]) {
                visited[ny][nx] = 1;
                if (isUsed == 1)
                    dfs(ny, nx, dist + 1, 1);
                else
                    dfs(ny, nx, dist + 1, 0);
                visited[ny][nx] = 0;
            }       
        }
    }
 
    // 더 이상 갈 수 없을때 - 기저조건
    if (answer < dist) {
        answer = max(dist, answer); 
    }
    return;
}
 
 
 
void solve() {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (MAP[i][j] == maxNumber)
                startPoint.push_back({i, j});       // 크기가 최대인 곳 스타트포인트에 저장
        }
    }
 
    for (int i = 0; i < startPoint.size(); i++)      // 스타트포인트에서 visited 초기화하고 출발하기
    {
        memset(visited, 0, sizeof(visited));
        Node now = startPoint[i];
        visited[now.y][now.x] = 1;
        dfs(now.y, now.x, 1, 0);
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
