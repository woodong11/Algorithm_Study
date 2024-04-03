#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

void init() {
    // visited 0으로 초기화
}

int N, M, P, C, D;

struct pos {
    int y, x;
};

struct st_info {
    int y, x, sleep, death, score;
};

vector<st_info> santa[31]; // 산타 번호별 정보
pos rudol; // 루돌프 위치

int visited[52][52]; // 산타 방문(1~) + 루돌 방문(-1) // 빈공간(0)

struct santaTarget {
    int num, dist, y, x;
} santarget;

struct GoDol {
    int y, x, dist;
};

GoDol nextdol;
GoDol nextsan;

int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int dy_san[4] = { -1, 0, 1, 0 };
int dx_san[4] = { 0, 1, 0, -1 };

void input() {
    cin >> N >> M >> P >> C >> D; // 게임판 크기, 게임 턴 수, 산타 수, 루돌프 힘, 산타 힘
    cin >> rudol.y >> rudol.x;
    visited[rudol.y][rudol.x] = -1; // 루돌프 방문 여부

    int num, y, x = 0;
    for (int i = 0; i < P; i++) {
        cin >> num >> y >> x;
        visited[y][x] = num; // 산타 방문 여부
        santa[num].push_back({ y, x, 0, 0, 0 });
    }
}


void targetSanta() {

    santarget = { 0,1000000,0,0 }; // min(산타num, 산타와의 거리, y, x 좌표) >> 여기부터
    int dist = 0;

    for (int i = 1; i <= P; i++) {
        if (santa[i][0].death == 1) continue;

        dist = pow((santa[i][0].y - rudol.y), 2) + pow((santa[i][0].x - rudol.x), 2); // 산타와의 거리

        if (dist < santarget.dist) {
            santarget = { i, dist, santa[i][0].y, santa[i][0].x };
        }
        else if (dist == santarget.dist) { // 가까운 산타 2명 이상일 경우
            // y가 큰 걸로 update
            if (santa[i][0].y > santarget.y)
            {
                santarget = { i, dist, santa[i][0].y, santa[i][0].x };
            }
            else if (santa[i][0].y == santarget.y) {
                if (santa[i][0].x > santarget.x)
                {
                    santarget = { i, dist, santa[i][0].y, santa[i][0].x };
                }
            }
        }
    }
}



void interaction(int y, int x, int d, int nowSant, int nextSant) {
    if (visited[y][x] == 0) {
        visited[y][x] = nowSant;
        visited[santa[nowSant][0].y][santa[nowSant][0].x] = 0;
        santa[nowSant][0].y = y;
        santa[nowSant][0].x = x;
        return;
    }
    else if (y<=0 || x<=0 || y>N || x>N) {
        // 밀려난 산타 죽이기
        santa[nowSant][0].death = 1;
        return;
    }
    int ny = y + dy_san[d];
    int nx = x + dx_san[d];

    interaction(ny, nx, d, nextSant, visited[ny][nx]);
    visited[santa[nowSant][0].y][santa[nowSant][0].x] = 0;
    santa[nowSant][0].y = y;
    santa[nowSant][0].x = x;

    visited[y][x] = nowSant;
}


void crushByDol(int doly, int dolx, int stnum, int dirD) {
    //루돌프가 움직여서 충돌이 일어난 경우, 해당 산타는 C만큼의 점수를 얻게 됩니다. 
    //이와 동시에 산타는 루돌프가 이동해온 방향으로 C 칸 만큼 밀려나게 됩니다.
    santa[stnum][0].score += C;

    int ny = doly + C * dy[dirD];
    int nx = dolx + C * dx[dirD];

    if (ny <= 0 || nx <= 0 || ny > N || nx > N) {
        santa[stnum][0].death = 1;
        visited[santa[stnum][0].y][santa[stnum][0].x] = -1;
        return;
    }
    else if (visited[ny][nx] != 0) {
        // 상호작용 발생
        interaction(ny, nx, dirD, stnum, visited[ny][nx]);
        visited[doly][dolx] = 0;
        return;
    }

    visited[doly][dolx] = -1;
    santa[stnum][0].y = ny;
    santa[stnum][0].x = nx;
    visited[ny][nx] = stnum;
    santa[stnum][0].sleep = 1;

}


void goDol() {

    int ny, nx, dist = 0;
    nextdol = { 0, 0, 1000000 };
    int dir = -1;
    for (int i = 0; i < 8; i++)
    {
        ny = rudol.y + dy[i];
        nx = rudol.x + dx[i];

        if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
        dist = pow((ny - santarget.y), 2) + pow((nx - santarget.x), 2);

        if (dist < nextdol.dist) {
            nextdol = { ny, nx, dist };
            dir = i;
        }
    }

    visited[rudol.y][rudol.x] = 0; // 빈공간
    rudol = { nextdol.y, nextdol.x }; // 루돌프 돌진~!


    // crush
    if (visited[rudol.y][rudol.x] != 0) {
        crushByDol(rudol.y, rudol.x, visited[rudol.y][rudol.x], dir);
    }
    else {
        visited[rudol.y][rudol.x] = -1;
    }
}


void moveDol() {

    targetSanta(); //>> santarget
    goDol(); // >>nextdol
}


void crushBySan(int sany, int sanx, int stnum, int dirD) {
    //산타가 움직여서 충돌이 일어난 경우, 해당 산타는 D만큼의 점수를 얻게 됩니다. 
    // 이와 동시에 산타는 자신이 이동해온 반대 방향으로 D 칸 만큼 밀려나게 됩니다
    santa[stnum][0].score += D;

    int ny = sany + D * dy_san[dirD];
    int nx = sanx + D * dx_san[dirD];

    if (ny <= 0 || nx <= 0 || ny > N || nx > N) {
        santa[stnum][0].death = 1;
        visited[santa[stnum][0].y][santa[stnum][0].x] = 0;
        return;
    }
    else if (visited[ny][nx] != 0) {
        // 상호작용 발생
        interaction(ny, nx, dirD, stnum, visited[ny][nx]);
        santa[stnum][0].sleep = 1;
        visited[sany][sanx] = 0;
        return;
    }

    visited[sany][sanx] = -1;
    santa[stnum][0].y = ny;
    santa[stnum][0].x = nx;
    visited[ny][nx] = stnum;
    santa[stnum][0].sleep = 1;

}


void moveSan() {
    int ny =0, nx = 0;
    int dist = 0;

    for (int i = 1; i <= P; i++) {
        if (i == 3) {
            cout << "d"; // 여기
        }
        int cFlag = 0;
        if (santa[i][0].sleep == 1) {
            santa[i][0].sleep = 0;
            continue;
        }

        int now_dist = pow((santa[i][0].y - rudol.y), 2) + pow((santa[i][0].x - rudol.x), 2);
        nextsan = { santa[i][0].y, santa[i][0].x, now_dist }; // y, x, dist
        if (santa[i][0].death == 1) continue;
        // 산타 움직이기
        // rudol >> 현재 루돌프 위치

        for (int j = 0; j < 4; j++) {
            ny = santa[i][0].y + dy_san[j];
            nx = santa[i][0].x + dx_san[j];

            if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;

            // 루돌프랑 충돌할 경우
            else if (visited[ny][nx] == -1) {
                //int sany, int sanx, int stnum, int dirD
                crushBySan(ny, nx, i, (j + 2) % 4); // 여기
                cFlag = 1;
                break;
                // continue 추가?
            }

            // 다른 산타가 존재할 경우 >> 상호작용
            else if (visited[ny][nx] > 0 && visited[ny][nx] <= 31) continue;
            // 루돌프한테 걸어갈 경우 추가해야함 + 위에도 범위 수정

            dist = pow((ny - rudol.y), 2) + pow((nx - rudol.x), 2);

            if (dist < nextsan.dist) {
                nextsan = { ny, nx, dist };
            }
        }
        if (cFlag == 1) continue;

        visited[santa[i][0].y][santa[i][0].x] = 0;
        santa[i][0] = { nextsan.y, nextsan.x, santa[i][0].sleep, santa[i][0].death, santa[i][0].score };
        visited[santa[i][0].y][santa[i][0].x] = i;
        
    }

}

int endF;

void scoreP() {
    int endflag = 0;
    for (int i = 1; i <= P; i++)
    {
        if (santa[i][0].death == 1) {
            endflag++;
            continue;
        }
        santa[i][0].score += 1;
    }
    if (endflag == P) {
        endF = 1;
    }
}

int k = 0;

void process() {
    for (int i = 0; i < M; i++)
    {
        k = i;
        if (i == 1) {
            cout << "i";
        }
        moveDol();
        moveSan();   // 여기
        scoreP();

        if (endF == 1) break;
    }
}

void printscore() {
    // 각 산타가 얻은 최종 점수 cout
    for (int i = 1; i <= P; i++)
    {
        cout << santa[i][0].score << " ";
    }
}
int main() {
    freopen("sample_input.txt", "r", stdin);
    init();
    input();
    process();
    printscore();
}
