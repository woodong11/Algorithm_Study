#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
using namespace std;

//청소년 상어는(0, 0)에 있는 물고기를 먹고, (0, 0)에 들어가게 된다.
// 상어의 방향은(0, 0)에 있던 물고기의 방향과 같다
// 
// 
// 이후 물고기 이동
// 물고기는 번호가 작은 물고기부터 순서대로 이동
// 한 칸을 이동
// 이동할 수 있는 칸은 빈 칸과 다른 물고기가 있는 칸
// 이동할 수 없는 칸은 상어가 있거나, 공간의 경계를 넘는 칸
// 각 물고기는 방향이 이동할 수 있는 칸을 향할 때까지 방향을 45도 반시계 회전
// 이동할 수 있는 칸이 없으면 이동을 하지 않는다.
// 물고기가 다른 물고기가 있는 칸으로 이동할 때는 서로의 위치를 바꾸는 방식으로 이동
// 
// 


// priority_queuq에 map에 존재하는 물고기 num 저장
// vector<vector<x, y>> >> index = 물고기 num 에 따른 y, x 위치 저장
// >> 위치 교환할 때 update
// map에 물고기 번호,, 방향 꼭 저장해야할까..?
// map의 역할: 이동 가능 여부 판단. 
// 방향을 map
// 


int map[4][4][2]; // 물고기 num, 방향 저장
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int tempmap[4][4][2];

struct compare
{
    bool operator()(int a, int b)
    {
        return a > b;
    }
};


struct Point {
    int y, x;
};

vector<vector<Point>> loca(17);//  , vector<Point>(1)); // 물고기 num에 따른 y, x 위치 
vector<vector<Point>> temploca(17);
int nextcur;



void input() {
    int a, b;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> a >> b;
            if (i == 0 && j == 0) {
                map[i][j][0] = 0; // 상어 num = 0
                map[i][j][1] = b - 1;
                loca[0].push_back({ i, j });
                continue;
            }

            map[i][j][0] = a; // 물고기 번호
            map[i][j][1] = b - 1; // 물고기 방향
            loca[a].push_back({ i, j });
            // pq.push(a);
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
            // map 변경
            //map[i][j][0] = a; // 물고기 번호
            //map[i][j][1] = b - 1; // 물고기 방향
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


int eatScore = 0;
int edflag = 0;

int moveShark(int dist, int eScore) {
    edflag = 0;

    // 상어의 위치 loca[0]에저장되어있음
    int sharky = loca[0][0].y;
    int sharkx = loca[0][0].x;
    int sharkdir = map[sharky][sharkx][1];

    int nextSy = sharky + dist* dy[sharkdir];
    int nextSx = sharkx + dist* dx[sharkdir];

    // 벽이면 out >> 집으로가 

    if (nextSy < 0 || nextSx < 0 || nextSy >= 4 || nextSx >= 4) {
        edflag = 1;
        return eScore;
    }

    nextcur = map[nextSy][nextSx][0]; // 이동하려는 곳에 있는 물고기의 번호or 빈곳인지 아닌지?

    if (nextcur > 0) {
        int tempDir = map[nextSy][nextSx][1];// 이동할 위치에 있는 물고기의 방향
        int tempNum = map[nextSy][nextSx][0]; // 이동할 위치에 있는 물고기 번호

        map[nextSy][nextSx][0] = 0;
        map[nextSy][nextSx][1] = tempDir;

        map[sharky][sharkx][0] = -1;
        map[sharky][sharkx][1] = -1;

        loca[tempNum].pop_back(); // 물고기 먹혔어~
        loca[0].pop_back(); //상어 이동해용
        loca[0].push_back({nextSy, nextSx});

        eScore += tempNum; // 상어가 먹은 물고기 점수
    }
    
    // 2. 빈 칸인가 >> 집으로 가
    else if (nextcur == -1) {
        edflag = 1;
    }
    return eScore;
}



int newScore = 0;
int maxVal = 0;

// map을 지역변수로? >>ㄱ..




void process(int score) {
    // 상어가 다음으로 못 가는 경우
    if (edflag ==1) {
        maxVal = max(maxVal, score);
        return;
    }
    memcpy(tempmap, map, sizeof(map));

    moveFish();
    


    for (int i = 1; i <= 3; i++)
    {
        newScore = moveShark(i, score);

        process(newScore);

        // 어휴.............
        memcpy(map, tempmap, sizeof(map));
        
    }
}

int main() {
    freopen("sample_input.txt", "r", stdin);
    input();
    // moveFish();
    process(0);
    cout << maxVal;


    return 0;
}
