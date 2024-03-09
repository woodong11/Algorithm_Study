// 주의: 백준 서버에선 사용하지 않는 변수가 있으면 컴파일 에러가 난다.
// 주의1: 특정 함수를 사용할려면 무조건 해당 라이브러리를 불러와야 한다. ex) max -> algorithm, pow -> cmath

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

struct Node {
    int y;
    int x;
};

// pq에서 쓰기 위함
struct group {
    int groupSize;
    int rainbowCnt;
    int baseY;
    int baseX;
    int color;
};

// pq 내 정렬을 위한 compare - 좀 더 빠른 정렬을 위해 벡터 대신 pq를 사용했음음
struct compare {
    bool operator()(group a, group b) {
        if (a.groupSize == b.groupSize) {
            if (a.rainbowCnt == b.rainbowCnt) {
                if (a.baseY == b.baseY) {
                    return a.baseX < b.baseX;
                }
                else
                    return a.baseY < b.baseY;
            }
            else
                return a.rainbowCnt < b.rainbowCnt;
        }
        else
            return a.groupSize < b.groupSize;
    }
};

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int N, M, answer;
int MAP[21][21];
int visited[21][21];


// bfs에서 구해야 할 것: 총 크기, 무지개블록 개수, 기준블록 행, 기준블록
group bfs(int startY, int startX, int color) {

    // bfs 돌릴때 초기화
    int groupSize = 1, rainbowCnt = 0;
    int baseY = 21e8, baseX = 21e8;
    memset(visited, 0, sizeof(visited));    

    // bfs 시작
    queue <Node> q;
    q.push({ startY, startX });
    visited[startY][startX] = 1;

    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        // 기준블록 업데이트 - 무지개 블록이 아닌 블록이 기준블록!!!!!!!!!!! 문제 잘 읽기
        if (MAP[now.y][now.x] != 0 && now.y < baseY) {
            baseY = now.y;
            if (now.x < baseX)
                baseX = now.x;
        }
        
        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                continue;

            if (visited[ny][nx] == 1)
                continue;

            if (MAP[ny][nx] == color || MAP[ny][nx] == 0) {
                q.push({ ny, nx });
                visited[ny][nx] = 1;
                groupSize++;

                if (MAP[ny][nx] == 0)
                    rainbowCnt++;
            }
        }
    }

    group ret = { groupSize ,rainbowCnt, baseY, baseX , color};
    return ret;
}

// 제거하는 함수. bfs로 구현. 제거된 블록은 -2로 만들었음.
void remove(int startY, int startX, int color) {
    queue <Node> q;
    q.push({ startY, startX });
    MAP[startY][startX] = -2;

    while (!q.empty())
    {
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                continue;

            if (MAP[ny][nx] == color || MAP[ny][nx] == 0) {
                q.push({ ny, nx });
                MAP[ny][nx] = -2;
            }
        }
    }
}

// 중력작용 - 좀 더 멋진 중력 구현 생각해보기기
void gravity() {
    for (int i = 0; i < N; i++) {    // 각 열

        int startRow = N - 1;
        int endRow = N - 1;

        while (true) {
            while (true) {       // -1 찾기 or 끝날때 찾기
                if (endRow == -1 || MAP[endRow][i] == -1)
                    break;
                endRow--;
            }

            // start부터 endRow 이전까지 큐에 담기
            queue <int> q;
            for (int j = startRow; j > endRow; j--){
                if (MAP[j][i] >= 0) {
                    q.push(MAP[j][i]);
                    MAP[j][i] = -2;
                }

            }
            while (!q.empty()){
                int color = q.front();
                q.pop();
                MAP[startRow][i] = color;
                startRow--;
            }

            if (endRow == -1)
                break;

            startRow = endRow - 1;
            endRow = startRow;
        }
    }
}

// 반시계로 90도 돌리는 함수수
void rotate() {
    int tempMAP[21][21] = { 0, };
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            tempMAP[N - 1 - j][i] = MAP[i][j];
        }
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            MAP[i][j] = tempMAP[i][j];
        }
    }
}


int main() {
    //freopen("sample_input.txt", "r", stdin);

    // 입력받기
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
        }
    }

    // 실행 - 이거대로 하면 중복되는게 많음. 다른 풀이 생각해보기
    while (true)
    {
        priority_queue <group, vector<group>, compare> pq;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (MAP[i][j] > 0) {        // 기본블록일때 bfs (그룹엔 기본블록이 무조건 하나 이상 있어야 하니깐)
                    group ret = bfs(i, j, MAP[i][j]);

                    if (ret.groupSize > 1) {
                        pq.push(ret);
                    }
                }
            }
        }

        if (pq.size() == 0)     // pq에 아무것도 안 담길때 == 블록을 만들 수 없을 때
            break;

        group maxGroup = pq.top();
        int color = maxGroup.color;
       
        remove(maxGroup.baseY, maxGroup.baseX, color);      // 블록제거
        answer += pow(maxGroup.groupSize, 2);               // 점수 업데이트 
            
        gravity();
        rotate();
        gravity();
    }
    
    cout << answer;

    return 0;
}
