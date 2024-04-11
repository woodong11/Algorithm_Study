/*
ny nx 쓸때 자나깨나 범위 초과 주의!!!!!!!!!!!!!!!!!!!! 이거때매 6시간 날림
최단경로로 -1 이동하는거에서 4방향 탐색으로 짰었는데 이때도 범위 벗어났을때 continue 조건을 해야 하는데 빠뜨렸다
-> visual studio에선 자동으로 continue하는 것 같은데, gcc에선 어림도 없음 
-> visual studio에선 정답이 제대로 나오는데 서버에선 런타임 에러 뜬다
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node {
    int y;
    int x;
};

struct Node1 {

    int y;
    int x;
    int dist;
};

int N, M, curTime = 1;
int dy[4] = { -1, 0, 0, 1 };
int dx[4] = { 0, -1, 1, 0 };
int campMAP[16][16];            // 방문 안 한 곳이면 1, 방문 한 곳이면 2
int visited[16][16];
int isOnMAP[31];                // 사람이 격자 위에 있고 움직여야 하면 1, 없거나 도착했으면 0
int arrivedCnt;                    // 이게 m이 되면 종료한다.
Node stores[31];
Node people[31];


bool compare(Node a, Node b) {
    if (a.y == b.y) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

vector <Node> targetCampList;

void input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> campMAP[i][j];
        }
    }

    int tempY, tempX;
    for (int i = 1; i <= M; i++) {
        cin >> tempY >> tempX;
        stores[i] = { tempY - 1, tempX - 1 };
    }
}

// 최단거리로 한칸 움직이는 함수
int bfs(int num) {
    Node person = people[num];
    Node targetStore = stores[num];
    int personDist = 21e8;

    memset(visited, 0, sizeof(visited));
    queue <Node> q;
    q.push({ targetStore.y, targetStore.x });
    visited[targetStore.y][targetStore.x] = 1;

    while (!q.empty()) {
        Node now = q.front();
        q.pop();

        //if (visited[now.y][now.x] >= personDist)        // 시간을 줄여주기 위해 썼다
        //    break;

        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)        // 격자 벗어나면 패스
                continue;

            if ((ny == person.y) && (nx == person.x)) {
                visited[ny][nx] = visited[now.y][now.x] + 1;
                personDist = visited[ny][nx];
                return personDist;
            }

            if (campMAP[ny][nx] == 2 || visited[ny][nx] != 0)    // 방문 못하는곳이거나 체크한 곳이면 패스
                continue;

            q.push({ ny, nx });
            visited[ny][nx] = visited[now.y][now.x] + 1;
        }
    }


    return visited[person.y][person.x];
}

void movePeople() {

    vector <int> moveList;
    vector <int> dontMove;            // 해당 함수 끝나고 움직이지 못하는 곳 업데이트하기 위해 씀
    for (int i = 1; i <= M; i++) {
        if (isOnMAP[i] == 1)
            moveList.push_back(i);
    }

    if (moveList.size() == 0)
        return;

    // 움직여야 할 사람들이 있다면 최단거리로 움직이기
    for (int i = 0; i < moveList.size(); i++) {
        int curPerson = moveList[i];

        // 최단거리까지 한칸 움직이기
        int personDist = bfs(curPerson);

        // 사람 한칸 이동
        for (int i = 0; i < 4; i++) {
            int ny = people[curPerson].y + dy[i];
            int nx = people[curPerson].x + dx[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)         // 이거때매 4시간 해맸음. 비주얼스튜디오 컴파일러는 맵 벗어낫을 때 자동으로 continue 하는 것 같은데, 서버 gcc는 안 그렇다
                continue;

            if (visited[ny][nx] == personDist - 1) {
                people[curPerson] = { ny, nx };
                break;
            }
        }

        // 만약 편의점에 도착했다면 dontmove에 넣기
        if ((people[curPerson].y == stores[curPerson].y) && (people[curPerson].x == stores[curPerson].x))
            dontMove.push_back(curPerson);
    }

    if (dontMove.size() == 0)
        return;

    for (int i = 0; i < dontMove.size(); i++) {
        int stopPerson = dontMove[i];
        arrivedCnt += 1;
        isOnMAP[stopPerson] = 0;
        campMAP[people[stopPerson].y][people[stopPerson].x] = 2;
    }
}

// 빈 캠프에 사람 집어넣는 함수
void insertPerson(int num) {
    Node targetStore = stores[num];
    targetCampList.clear();

    // bfs 돌리기
    memset(visited, 0, sizeof(visited));
    queue <Node> qq;
    qq.push({ targetStore.y, targetStore.x });
    visited[targetStore.y][targetStore.x] = 1;
    int minDist = 21e8;
    int isFirst = 0;

    while (!qq.empty()) {
        Node now = qq.front();
        qq.pop();

        //if (visited[now.y][now.x] > minDist)        // 시간을 줄여주기 위해 썼다
        //    return;

        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)        // 격자 벗어나면 패스
                continue;

            if (campMAP[ny][nx] == 2 || visited[ny][nx] != 0)    // 방문 못하는곳이거나 체크한 곳이면 패스
                continue;

            if (campMAP[ny][nx] == 1) {                        // 캠프가 있으면 체크
                if (isFirst == 0) {
                    minDist = visited[now.y][now.x] + 1;
                    isFirst = 1;
                }
            }

            qq.push({ ny, nx });
            visited[ny][nx] = visited[now.y][now.x] + 1;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (campMAP[i][j] == 1 && visited[i][j] == minDist) {
                targetCampList.push_back({ i, j });
            }
        }
    }

    return;
}

void solve() {

    while (1) {
        if (arrivedCnt == M)
            break;

        movePeople();                // 1번, 2번

        if (curTime <= M) {            // 3번
            insertPerson(curTime);

            // 우선순위 높은 베이스캠프에 사람 넣고, 사람 위치와 보드 위에 있음, 다른 사람은 건너면 안됨


            sort(targetCampList.begin(), targetCampList.end(), compare);
            Node targetCamp = targetCampList[0];

            people[curTime] = { targetCamp.y, targetCamp.x };
            isOnMAP[curTime] = 1;
            campMAP[targetCamp.y][targetCamp.x] = 2;
        }

        curTime++;
    }

    cout << curTime - 1;
}


int main() {
    //freopen("sample_input.txt", "r", stdin);
    input();
    solve();

    return 0;
}
