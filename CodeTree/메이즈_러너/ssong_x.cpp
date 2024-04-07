#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<queue>
#include<cmath>


using namespace std;

int N, M, K;
int map[11][11];
int map_print[11][11]; // print 위한 것

//상하좌우
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

struct pos {
    int y, x;
};

queue<pos>p; // 참가자 위치
pos EX; // 출구 위치



void init() {

}



void input() {
    cin >> N >> M >> K; // 미로의 크기, 참가자 수, 게임 시간
    int c = 0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cin >> c;
            map[i][j] = c;
            map_print[i][j] = c;
        }
    }
    int a = 0, b = 0;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        p.push({ a, b });
        map[a][b] = -1;
        map_print[a][b] = -1; // 참가자 수
    }
    cin >> a >> b;
    EX = { a, b };
}

void print() {
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++) {
            if (i == EX.y && j == EX.x) printf("E ");
            else if (map[i][j] == -1) printf("P ");
            else if (map[i][j] != 0) printf("# ");
            else printf("_ ");
        }
        printf("\n");
    }
    printf("\n");

}


int ans_move_cnt;

void moveP() {
    // 모든 참가자 한 칸씩 이동
    // 벽이 있는곳 이동x
    // 현재 머물러 있던 칸보다 출구까지의 최단거리가 가까워야함
    // 움직일 수 있는 칸 2개 이상이라면 상하 우선시

    // 움직일 수 없는 상황이라면 움직이지X
    // 한 칸에 2명 이상의 참가자 있을 수 있음
    // 벽만 피해용

    // 1. 현재 참가자와 출구와의 거리 dist
    // 2. for 4 // 상하좌우 움직이지
    //// 1. 벽이면 continue;
    //// 2. if (newdist < dist) >> 이동할 위치 update, 이동거리++
    //// 이동하지 않았을 때 이동거리 ++하면 X
    // 3. 탈출조건! if (출구 위치 == 이동할 위치)
    //        else queue.push(이동할위치)
    
    int pp_cnt = p.size();
    int now_dist = 0, next_dist = 0;
    int ny = 0, nx = 0;

    pos nowP;
    pos nextP;
    
    int end_flag = 0;
    for (int i = 0; i < pp_cnt; i++) {
        end_flag = 0; // 탈출했을 때
        nowP = p.front(); // 현재 참가자 위치
        nextP = nowP; // 이동할 참가자의 위치
        p.pop();

        now_dist = abs(EX.y - nowP.y) + abs(EX.x - nowP.x);

        for (int i = 0; i < 4; i++)
        {
            ny = nowP.y + dy[i];
            nx = nowP.x + dx[i];

            // 외곽일 경우 + 벽인 경우
            if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
            else if (map[ny][nx] >= 1 && map[ny][nx] <= 9) continue;

            // 움직였는데 출구인 경우
            else if (ny == EX.y && nx == EX.x) {
                map[nowP.y][nowP.x] += 0;
                ans_move_cnt++;
                end_flag = 1;
                break;
            }

            next_dist = abs(EX.y - ny) + abs(EX.x - nx);
            if (next_dist < now_dist) {
                
                nextP = { ny, nx }; // 이동할 위치
                ans_move_cnt++; // 이동한 거리
            }        
        }
        if (end_flag == 1) continue;
        p.push(nextP);
        map[nowP.y][nowP.x] += 0;    // 이동한 참가자의 위치 업데이트
        map[nextP.y][nextP.x] -= 1;
    }
}

void find_square() {
    // 1. <queue>에 추가하면서 P 찾기
    //// r과 c가 작은 P로 업데이트
    // 2. P 선택 후 좌상단 좌표 구하기
    //// y = max(py, ey) - level // x = max(px - ex) - level


}


void rotation() {
    //
    // 1. 참가자와 출구를 포함한 가장 작은 정사각형 구하기 >> 정사각형의 좌상단 좌표 구하기
    //// 1. y가 작은것, x가 작은 사각형 우선
    // 2. 시계방향으로 90도 회전(사람도 출구도 함께 움직임)
    //// 1. 내구도 감소 >> 
    // // 1. map 업데이트 >> map에 따른 참가자 p도 업데이트
    //

    // 출구 위치 기반으로 8방향 확인 >> y, x 가 작은 참가자 우선시
    // 좌상,좌중, 좌우, 중상, 중중, 중우, ... 순서로 dy[8] 구성
    // 
     
    find_square();
}


void process() {
    for (int i = 0; i < K; i++) {

        moveP(); // 참가자 이동
        print();
        // 회전
        rotation(); // 미로 회전

        //// if 모든 참가자 미로 탈출 시 
        //if () {

        //    break;
        //}



    }

}

int main() {
    freopen("sample_input.txt", "r", stdin);
    init();
    input();
    print();
    process();
}

