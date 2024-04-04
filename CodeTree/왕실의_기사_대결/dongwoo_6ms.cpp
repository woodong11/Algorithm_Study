#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int L, N, Q, answer;
int MAP[41][41];
int knightMAP[41][41];
int visited[41][41];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int isDead[31];                 // 1이면 죽은거임
int damaged[31];                // 받은 데미지

struct Node {
    int y;
    int x;
};

struct knightInfo {
    int r;
    int c;
    int h;
    int w;
    int k;            // 체력
};

knightInfo knightList[31];
vector <Node> query;        // 왕의 명령 정보 쿼리 담음
int pushList[31];           // 각 쿼리마다 움직일 수 있는 기사 담기

void init() {
    memset(MAP, 0, sizeof(MAP));
    memset(knightMAP, 0, sizeof(knightMAP));
    memset(knightList, 0, sizeof(knightList));
    memset(isDead, 0, sizeof(isDead));
    memset(damaged, 0, sizeof(damaged));
    query.clear();
}

void input() {
    cin >> L >> N >> Q;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            cin >> MAP[i][j];
        }
    }

    int tempR, tempC, tempH, tempW, tempK;
    for (int i = 1; i <= N; i++) {
        cin >> tempR >> tempC >> tempH >> tempW >> tempK;
        knightList[i] = { tempR - 1, tempC - 1, tempH, tempW, tempK };

        for (int j = knightList[i].r; j < knightList[i].r + knightList[i].h; j++) {        // 기사맵에 초기위치 적기
            for (int k = knightList[i].c; k < knightList[i].c + knightList[i].w; k++) {
                knightMAP[j][k] = i;
            }
        }
    }

    int tempI, tempD;
    for (int i = 0; i < Q; i++) {
        cin >> tempI >> tempD;
        query.push_back({ tempI, tempD });        // 그냥 노드 구조체 재활용해서 썼다
    }
}

// bfs로 미는데 포함되는 기사들 체크
bool check(int curNum, int dir) {

    // 해당 체크에서 사용하는것들 초기화
    memset(pushList, 0, sizeof(pushList));
    memset(visited, 0, sizeof(visited));
    pushList[curNum] = 1;

    // 큐 시작
    queue <Node> q;
    q.push({ knightList[curNum].r, knightList[curNum].c });
    visited[knightList[curNum].r][knightList[curNum].c] = 1;

    while (!q.empty()) {
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (i == dir) {
                if (ny < 0 || nx < 0 || ny >= L || nx >= L)            // 맵 바깥이면 푸시 못해
                    return false;
                if (MAP[ny][nx] == 2)                                // 다음이 벽이면 푸시 못해
                    return false;
                if (visited[ny][nx] == 1 || knightMAP[ny][nx] == 0)    // 방문했거나 기사가 없으면 안 담아
                    continue;
            }

            else {
                if (ny < 0 || nx < 0 || ny >= L || nx >= L)
                    continue;
                if (visited[ny][nx] == 1 || knightMAP[ny][nx] == 0)    // 방문했거나 기사가 없으면 안 담아
                    continue;
                if (knightMAP[now.y][now.x] != knightMAP[ny][nx])    // 다른 기사면 안 담아 
                    continue;
            }

            pushList[knightMAP[ny][nx]] = 1;
            q.push({ ny, nx });
            visited[ny][nx] = 1;
        }
    }
    return true;
}

void push(int curNum, int dir) {

    if (check(curNum, dir) == 0)    // 못 미는 상황이면..
        return;
    
    // 밀어지는 기사들 체크
    for (int i = 1; i <= N ; i++){
        if (pushList[i] == 0)
            continue;

        // 밀어지는 기사일때, 일단 밀기 위해 기존에 나이트맵에 저장된 기사 삭제
        for (int j = knightList[i].r; j < knightList[i].r + knightList[i].h; j++) {       
            for (int k = knightList[i].c; k < knightList[i].c + knightList[i].w; k++) {
                knightMAP[j][k] = 0;
            }
        }
    }

    // 일단 푸시해서 이동했다 가정했을때, 함정 개수 파악하고, 살 수 있으면 색칠하기 
    for (int i = 1; i <= N; i++) {
        if (pushList[i] == 0)       
            continue;

        int curTrabCnt = 0;
        knightList[i].r = knightList[i].r + dy[dir];
        knightList[i].c = knightList[i].c + dx[dir];
        for (int j = knightList[i].r; j < knightList[i].r + knightList[i].h; j++) {        
            for (int k = knightList[i].c; k < knightList[i].c + knightList[i].w; k++) {
                if (MAP[j][k] == 1)
                    curTrabCnt++;
            }
        }
        
        // 미는 기사 말고, 밀리는 기사면 데미지 감소 -> 체력보다 높은 데미지를 받으면 목록에서 삭제한다
        if (i != curNum){                   
            damaged[i] += curTrabCnt;
            knightList[i].k -= curTrabCnt;
            if (knightList[i].k <= 0) {   
                isDead[i] = 1;
                pushList[i] = 0;
            }
        }
        
        // 살아있는 기사들 기사 맵에 색칠하기
        if (isDead[i] == 0) {                                           
            for (int j = knightList[i].r; j < knightList[i].r + knightList[i].h; j++) {
                for (int k = knightList[i].c; k < knightList[i].c + knightList[i].w; k++) {
                    knightMAP[j][k] = i;
                }
            }
        }
    }
}

void solve() {

    for (int i = 0; i < query.size(); i++) {
        int curNum = query[i].y;
        int dir = query[i].x;

        if (isDead[curNum] == 1)        // 만약 죽은 기사라면 넘어감
            continue;

        push(curNum, dir);
    }
}


int main() {
    //freopen("sample_input.txt", "r", stdin);
    cin.tie(NULL); cout.tie(NULL); ios::sync_with_stdio(false);
    init();
    input();
    solve();

    for (int i = 1; i <= N; i++){
        if (isDead[i] == 0) {
            answer += damaged[i];
        }
    }
    cout << answer;

    return 0;
}
