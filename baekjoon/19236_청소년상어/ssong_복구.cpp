// 1. temploca: loca (정보담는 리스트) - 필요하긴 하다. 대신 재귀 타면서 넘겨주고 복구해야하기 때문에 (전역으로 설정했으므로) 지역에 이걸 백업해두는 temploca가 필요함.
// 2. 상어가 먹을 수 있는 환경에서 추가 복구 필요: 상어가 먹으면 map이랑 loca가 추가로 변경되므로, 이에 해당할때만 추가로 복구를 또 시켜야 한다
// 3. 맨 처음 상어는 0,0 위치의 물고기를 먹고 시작해야하므로, process 들어갈때 0,0위치의 물고기 넘버를 보내주고 시작해야함
  
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int map[4][4][2]; // 물고기 num, 방향 저장
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int startFish;
int eatScore = 0;
int edflag = 0;
int newScore = 0;
int maxVal = 0;
int nextcur;

struct Point {
    int y, x;
};

vector<vector<Point>> loca(17);

void input() {
    int a, b;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> a >> b;
            if (i == 0 && j == 0) {
                startFish = a;
                map[i][j][0] = 0; // 상어 num = 0
                map[i][j][1] = b - 1;
                loca[0].push_back({ i, j });
                continue;
            }
            map[i][j][0] = a; // 물고기 번호
            map[i][j][1] = b - 1; // 물고기 방향
            loca[a].push_back({ i, j });
        }
    }
}

void moveFish() {
    int nowFishnum = 0;

    for (size_t i = 1; i < 17; i++)
    {
        if (loca[i].size() == 0) continue;

        nowFishnum = i; // 이동할 물고기 num

        int nowy = loca[nowFishnum][0].y;
        int nowx = loca[nowFishnum][0].x;
        int nowdir = map[nowy][nowx][1];
        int flag = 0;
        int nexty, nextx = 0;

        for (int i = 0; i < 8; i++)
        {
            flag = 0;
            nowdir = (map[nowy][nowx][1] + i) % 8;
            nexty = nowy + dy[nowdir];
            nextx = nowx + dx[nowdir];
            
            // 벽, 상어, 못가용 => 45도 돌려야햄
            if (nexty < 0 || nextx < 0 || nexty >= 4 || nextx >= 4) continue;
            nextcur = map[nexty][nextx][0]; // 이동하려는 곳에 있는 물고기의 번호or 빈곳인지 아닌지?

            if (nextcur == 0) continue; // 상어 num = 0
            flag = 1;
            break; // 갈 수 있다면 for문 out
        }

        if (flag == 0) continue; //8방향 다 돌았는데 갈 곳이 없을 경우 > 움직이지 않음 > 다음 물고기로

        // 다른 물고기 만났을 때 + // 아무것도 없을 때
        if (nextcur > 0 || nextcur == -1) {
            int tempNum = map[nexty][nextx][0]; // 이동할 위치에 있는 물고기 num
            int tempDir = map[nexty][nextx][1];

            map[nexty][nextx][0] = map[nowy][nowx][0];
            map[nexty][nextx][1] = nowdir;

            // nextcur / tempNum == -1인경우 
            map[nowy][nowx][0] = tempNum;
            map[nowy][nowx][1] = tempDir;

            // loca 변경
            loca[nowFishnum].pop_back();
            loca[nowFishnum].push_back({ nexty, nextx });

            // 빈 공간일 때
            if (tempNum == -1) continue;

            loca[tempNum].pop_back();
            loca[tempNum].push_back({ nowy, nowx });
        }
    }
}

void process(int score) {
    vector<vector<Point>> temploca(17);
    int tempmap[4][4][2];
    // 복구를 위함함
    memcpy(tempmap, map, sizeof(map));
    temploca = loca;

    moveFish();

    for (int i = 1; i <= 3; i++)
    {
        edflag = 0;

        // 상어의 위치 loca[0]에저장되어있음
        int sharky = loca[0][0].y;
        int sharkx = loca[0][0].x;
        int sharkdir = map[sharky][sharkx][1];

        int nextSy = sharky + i * dy[sharkdir];
        int nextSx = sharkx + i * dx[sharkdir];

        // 벽이면 out >> 집으로가 
        if (nextSy < 0 || nextSx < 0 || nextSy >= 4 || nextSx >= 4) {
            edflag = 1;
            maxVal = max(maxVal, score);
            continue;
        }

        nextcur = map[nextSy][nextSx][0]; // 이동하려는 곳에 있는 물고기의 번호or 빈곳인지 아닌지?

        if (nextcur > 0) {
            int tempDir = map[nextSy][nextSx][1]; // 이동할 위치에 있는 물고기의 방향
            int tempNum = map[nextSy][nextSx][0]; // 이동할 위치에 있는 물고기 번호

            map[nextSy][nextSx][0] = 0;
            map[nextSy][nextSx][1] = tempDir;

            map[sharky][sharkx][0] = -1;
            map[sharky][sharkx][1] = -1;

            Point a = loca[tempNum][0]; // 이동할 위치에 있는 물고기의 좌표
            Point b = loca[0][0]; // 상어 좌표

            loca[tempNum].pop_back(); // 물고기 먹힘
            loca[0].pop_back(); //상어 이동해용
            loca[0].push_back({ nextSy, nextSx });

            process(score + tempNum);

            // 복구

            map[sharky][sharkx][0] = 0;
            map[sharky][sharkx][1] = sharkdir;

            map[nextSy][nextSx][0] = tempNum;
            map[nextSy][nextSx][1] = tempDir;

            loca[tempNum].push_back(a);
            loca[0].pop_back();
            loca[0].push_back(b);
        }

        // 2. 빈 칸 >> 집으로 가
        else if (nextcur == -1) {
            edflag = 1;
            maxVal = max(maxVal, score);
            continue;
        }
    }
    
    memcpy(map, tempmap, sizeof(map));
    loca = temploca;
}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    input();
    process(startFish);
    cout << maxVal;
    return 0;
}
