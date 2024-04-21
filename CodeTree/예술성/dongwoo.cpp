#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Node {
    int y;
    int x;
};

struct group {    // 그룹의 중심좌표, 숫자, 숫자 개수
    int y;
    int x;
    int num;
    int cnt;
};

int N, totalGroupNum, answer;
int MAP[30][30];                // 숫자들 저장 (주어지는 맵)
int groupMAP[30][30];           // 각 칸마다 그룹 숫자 저장
int adjacentMAP[900][900];      // 맞닿아있는 변의 수 내용 담음
int visited[30][30];            // 맞닿아있는 변의 수 저장할때 쓸 visited
group groupList[900];           // 각 그룹들 정보

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };


void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> MAP[i][j];
        }
    }
}

// 해당 숫자 그룹 숫자 찾기용 bfs
int bfs(int startY, int startX, int groupNum) {

    queue <Node> q;
    int curNum = MAP[startY][startX];
    int curCnt = 1;
    q.push({ startY, startX });
    groupMAP[startY][startX] = groupNum;

    while (!q.empty()) {

        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                continue;
            if (groupMAP[ny][nx] > 0)
                continue;
            if (MAP[ny][nx] != curNum)
                continue;

            q.push({ ny, nx });
            groupMAP[ny][nx] = groupNum;
            curCnt++;
        }
    }

    return curCnt;
}

// 인접한 변 개수 찾기용 bfs
void bfs_adjacent(int startY, int startX) {
    int curGroup = groupMAP[startY][startX];
    queue <Node> q;
    q.push({ startY, startX });
    visited[startY][startX] = 1;

    while (!q.empty()){
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                continue;
            if (visited[ny][nx] == 1)
                continue;

            int adjacentGroup = groupMAP[ny][nx];
            if (adjacentGroup == curGroup) {        // 같은 그룹이면 계속 bfs 돌림
                q.push({ ny, nx });
                visited[ny][nx] = 1;
            }
            else {
                adjacentMAP[curGroup][adjacentGroup]++;
            }              
        }
    }
}

// 그룹 만들고 그룹마다 인접한 변의 수 찾는 함수
void makeGoup() {

    // 필요한것들 초기화
    memset(groupList, 0, sizeof(groupList));
    memset(visited, 0, sizeof(visited));
    memset(groupMAP, 0, sizeof(groupMAP));
    memset(adjacentMAP, 0, sizeof(adjacentMAP));
    int groupNum = 1;
 
    // 각 그룹마다 시작좌표, 숫자, 숫자 개수 저장
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (groupMAP[i][j] == 0) {
                int cnt = bfs(i, j, groupNum);
                groupList[groupNum] = { i, j, MAP[i][j], cnt };

                groupNum++;
            }
        }
    }
    totalGroupNum = groupNum - 1;

    // 그룹끼리 맞닿아 있는 변의 수 정의하기
    for (int i = 1; i <= totalGroupNum; i++){
        int groupY = groupList[i].y;
        int groupX = groupList[i].x;    
        bfs_adjacent(groupY, groupX);
    }
}

// 예술점수 찾고 answer에 더하는 함수
void findArtScore() {
    for (int groupA = 1; groupA <= totalGroupNum; groupA++){
        for (int groupB = groupA; groupB <= totalGroupNum; groupB++){
            if (adjacentMAP[groupA][groupB] > 0) {
                
                int groupAcnt = groupList[groupA].cnt;
                int groupBcnt = groupList[groupB].cnt;
                int groupAnum = groupList[groupA].num;
                int groupBnum = groupList[groupB].num;
                answer += ((groupAcnt + groupBcnt) * groupAnum * groupBnum * adjacentMAP[groupA][groupB]);           
            }
        }
    }
}

// 맵 회전하는 함수
void rotateMAP() {
    
    int tempMAP[30][30] = {0,};

    // 십자가 회전
    vector <Node> cross;
    Node middle = { N / 2, N / 2 };
    cross.push_back(middle);
    for (int i = 0; i < 4; i++){
        int offset = 1;
        while (1){
            int ny = middle.y + dy[i] * offset;
            int nx = middle.x + dx[i] * offset;
        
            if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                break;

            cross.push_back({ ny, nx });
            offset++;
        }
    }
    for (Node i : cross)
        tempMAP[N - 1 - i.x][i.y] = MAP[i.y][i.x];
    
    // 4개 정사각형 회전
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++) {
            int squreY = i * (N / 2 + 1);
            int squreX = j * (N / 2 + 1);
            
            for (int k = 0; k < N/2; k++){
                for (int l = 0; l < N/2; l++){
                    tempMAP[l + squreY][N/2 - 1 - k + squreX] = MAP[k + squreY][l + squreX];
                }
            }
        }
    }

    // 기존 맵에 업데이트
    memcpy(MAP, tempMAP, sizeof(MAP));
}

void solve() {
    for (int i = 0; i < 4; i++) {
        makeGoup();
        findArtScore();
        rotateMAP();
    }
    cout << answer;
}


int main() {
    //freopen("sample_input.txt", "r", stdin);
    input();
    solve();

    return 0;
}
