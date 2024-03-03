// 활성세포도 생명력만큼 살아있을 수 있는 것 못 읽어서 시간 낭비함.
// 새로 비활성세포를 만들때 경쟁하는 조건에서 잘못 짜서 1시간 반 추가 소요 (테스트케이스 2번에서 자꾸 틀렸었음)
 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <vector>
#include <queue>
#include <stdio.h>
using namespace std;
 
int T, N, M, K, answer;
int MAP[800][800];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
 
struct Cell
{
    int num;
    int remainedTime;
    int y;
    int x;
};
 
struct state {
    int state;          // 1: 죽음, 2: 활성, 3: 비활성
    int remainedTime;
    int stateTime;
};
 
state stateMAP[800][800];       
vector <Cell> startCells;
 
void init() {
    memset(MAP, 0, sizeof(MAP));
    memset(stateMAP, 0, sizeof(stateMAP));
    startCells.clear();
    answer = 0;
}
 
void input() {
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int temp;
            cin >> temp;
 
            if (temp > 0) {
                MAP[i + 310][j + 310] = temp;
                stateMAP[i + 310][j + 310] = { 3, temp, 0 };
                startCells.push_back({ temp, temp, i + 310, j + 310 });
            }
        }
    }
}
 
 
void BFS() {
    int unActiveCnt = 0;
    int ActiveCnt = 0;
 
    queue <Cell> q;
    for (int i = 0; i < startCells.size(); i++)
    {
        q.push(startCells[i]);
        unActiveCnt++;
    }
 
    // BFS 시작
    for (int curTime = 1; curTime <= K; curTime++)
    {
 
        int qsize = q.size();
        for (int j = 0; j < qsize; j++)
        {
            Cell now = q.front();
            q.pop();
 
            // 비활성 세포일때
            if (stateMAP[now.y][now.x].state == 3) {
 
                // 경쟁에서 패배한 세포가 now일때                   --- 다시보기
                if ((now.num < MAP[now.y][now.x]) && (stateMAP[now.y][now.x].stateTime == curTime-1)) {
                    int ddd = -1;
                    continue;
                }
                 
 
                int newRemainedTime = now.remainedTime - 1;
 
                // 시간 다 되었을때 -> 활성상태로 만들어줌
                if (newRemainedTime == 0) {
                    q.push({ now.num, now.num, now.y, now.x });
                    stateMAP[now.y][now.x] = { 2, now.num, curTime };
                    ActiveCnt++;
                    unActiveCnt--;
                }
 
                // 시간 아직 안 되었을때
                else {      
                    q.push({ now.num, newRemainedTime, now.y, now.x });
                    stateMAP[now.y][now.x] = {3, newRemainedTime, curTime };
                }
            }
 
            // 활성 세포일때
            else{
 
                int newRemainedTime = stateMAP[now.y][now.x].remainedTime - 1;
 
                if (newRemainedTime == (MAP[now.y][now.x] - 1)) {   // 첫 활성 기간일때
                     
                    // 만약 활성화하면서 죽을때
                    if (newRemainedTime == 0) {
                        stateMAP[now.y][now.x] = { 1, 0, curTime };     // 세포는 죽음
                        ActiveCnt--;
                    }
                    else {
                        q.push({ now.num, newRemainedTime, now.y, now.x }); // 세포는 계속 살아있음
                        stateMAP[now.y][now.x] = { 2, newRemainedTime, curTime };
                    }
                     
 
                    for (int k = 0; k < 4; k++)
                    {
                        int ny = now.y + dy[k];
                        int nx = now.x + dx[k];
 
                        if (stateMAP[ny][nx].state == 1 || stateMAP[ny][nx].state == 2)     // 상태가 죽음, 활성 세포 만날땐 피하기
                            continue;
 
                        // 빈 공간일때 - 무지성으로 그냥 퍼뜨리기
                        if (stateMAP[ny][nx].state == 0) {
                            MAP[ny][nx] = now.num;
                            stateMAP[ny][nx] = { 3, now.num, curTime };
                            unActiveCnt++;
                            q.push({ now.num, now.num, ny, nx });
                            continue;
                        }
 
                        // 새롭게 퍼져나가려는 세포를 만났을때 - 경쟁
                        else if (stateMAP[ny][nx].state == 3) {
                            if ((MAP[ny][nx] == stateMAP[ny][nx].remainedTime) && (stateMAP[ny][nx].stateTime == curTime)) {        // 만난 세포가 새로 퍼져나가려는 세포일때
                                if (now.num > MAP[ny][nx]) {
                                    MAP[ny][nx] = now.num;
                                    stateMAP[ny][nx] = { 3, now.num, curTime };
                                    q.push({ now.num, now.num, ny, nx });
                                }
                                continue;
                            }
                            else {
                                continue;
                            }
                        }
                    }
                }
 
                // 활성세포가 퍼뜨리는 기간이 아닐때
                else {
                    if (newRemainedTime == 0) {
                        stateMAP[now.y][now.x] = { 1, 0, curTime };
                        ActiveCnt--;
                        continue;
                    }
                    else {
                        q.push({ now.num, newRemainedTime, now.y, now.x }); // 세포는 계속 살아있음
                        stateMAP[now.y][now.x] = { 2, newRemainedTime, curTime };
                    }
                }
                 
            }
        }
     
        int de = -1;
     
    }
 
    //cout << unActiveCnt << " " << ActiveCnt << "\n";
    answer = unActiveCnt + ActiveCnt;
}
 
 
 
void solve() {
    BFS();
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
