// 어거지로 해결한 것 같음...
// 재귀 어떻게 탈지 고민하다 2시간 반 날렸음. - 제대로 공부할것
// 복구 똑바로 안 해서 1시간 날렸음.
// 기저조건 없엤음. 이유는 아직 모르겠음 (인터넷에 다른 사람이 기저조건 안 썼길래 나도 안 쓰니깐 통과는 됨) 1시간 날렸음
// 물고기 다 이동 후 상어가 빈칸으로 못 움직이나? 문제에서 물고기 있는 칸으로만 움직일 수 있다고 명시된 것도 아닌데..
// 주석처리를 했다. 다른 사람 코드 안 봤으면 절대 못 풀었다 
// 확인할것: 기저조건 왜 없는지, 빈칸으로는 왜 상어가 못 움직이는지, 재귀탈때 전역배열 복구하는 것


/*
반례
7 6 2 6 15 7 9 3

3 5 1 4 14 1 10 6

6 4 13 3 4 6 11 1

16 5 8 7 5 2 12 2

답 88
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int answer;

struct fish {
    int num;
    int direction;
};

struct fishInfo {
    int y;
    int x;
    int num;
    int direction;
};

fish MAP[4][4];
fishInfo fishList[17];

// 배열을 매개변수로 전달해도 함수 내부에서 내용 변경시 원본이 바뀌길래 temp배열 만들었음. 근데 큐는 내용 바꿔도 원본은 그대로 있음.
// 왜그런지 나중에 꼭 물어보기
void move(int sharkY, int sharkX, int fishSum) {

    // 맵 변경하기 전에 상어 이동여부부터 먼저 체크
    int sharkDirection = MAP[sharkY][sharkX].direction;
    answer = max(answer, fishSum);
    //int newY = sharkY + dy[sharkDirection];
    //int newX = sharkX + dx[sharkDirection];
    //if (newY < 0 || newX < 0 || newY >= 4 || newX >= 4) {     // 범위 벗어날때 상어 집 돌아가고 재귀 종료
    //    answer = max(answer, fishSum);
    //    return;
    //}

    // 미리 저장하기
    fish tempMap[4][4];
    fishInfo tempList[17];
    memcpy(tempMap, MAP, sizeof(MAP));
    memcpy(tempList, fishList, sizeof(fishList));
    
    // 물고기 이동하기
    for (int i = 0; i < 17; i++)
    {
        fishInfo now = fishList[i];
        if (now.num == 0)               // 이미 잡아먹혀서 없는 물고기인 경우
            continue;
        if (now.y == sharkY && now.x == sharkX)
            continue;

        int curDirection = now.direction;
        for (int k = 0; k < 8; k++)
        {
            int ny = now.y + dy[curDirection];
            int nx = now.x + dx[curDirection];

            if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) {        // 범위 벗어났을때
                curDirection = (curDirection + 1) % 8;
                continue;
            }
            if (ny == sharkY && nx == sharkX) {                    // 상어 만났을때
                curDirection = (curDirection + 1) % 8;
                continue;
            }
            if (MAP[ny][nx].num == 0) {                             // 빈칸이었을때
                MAP[ny][nx] = { now.num, curDirection };
                MAP[now.y][now.x] = { 0, 0 };
                fishList[i].y = ny;
                fishList[i].x = nx;
                fishList[i].direction = curDirection;
                break;
            }
            else {                                              // 물고기가 있었을때
                fish tempFish;
                int tempNum = MAP[ny][nx].num;
                tempFish = { now.num, curDirection };
                MAP[now.y][now.x] = MAP[ny][nx];
                MAP[ny][nx] = tempFish;
                fishList[now.num].y = ny;
                fishList[now.num].x = nx;
                fishList[now.num].direction = curDirection;
                fishList[tempNum].y = now.y;
                fishList[tempNum].x = now.x;
                break;
            }
        }
    }


    // 상어 이동하기
    for (int i = 1; i < 4; i++){
        MAP[sharkY][sharkX].num = 0; MAP[sharkY][sharkX].direction = 0;

        int ny = sharkY + dy[sharkDirection] * i;
        int nx = sharkX + dx[sharkDirection] * i;

        if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4)
            break;

        int tempNum = MAP[ny][nx].num;
        int tempDirection = MAP[ny][nx].direction;

        // 이동하려는 칸이 빈칸인 경우
        /*if (MAP[ny][nx].num == 0) {
            MAP[ny][nx].num = -1; MAP[ny][nx].direction = sharkDirection;
            move(ny, nx, fishSum);
            MAP[ny][nx].num = 0;
            MAP[ny][nx].direction = 0;
        }*/

        // 물고기가 있는 경우
       if (MAP[ny][nx].num > 0){
            int eatenFish = MAP[ny][nx].num;
            MAP[ny][nx].num = -1;
            fishInfo tempfish = fishList[eatenFish];
            fishList[eatenFish] = {0, 0, 0, 0};
            move(ny, nx, fishSum + eatenFish);
            MAP[ny][nx].num = tempNum;
            fishList[eatenFish] = tempfish;
        }
    }

    // 맵, 리스트 복구하기
    memcpy(MAP, tempMap, sizeof(MAP));
    memcpy(fishList, tempList, sizeof(fishList));

}


int main() {
    // freopen("sample_input.txt", "r", stdin);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int a, b;
            cin >> a >> b;
            MAP[i][j] = { a, b - 1 };
            //tempMap[i][j] = { a, b - 1 };

            fishList[a] = { i, j, a, b - 1 };
            //tempList[a] = { i, j, a, b - 1 };
        }
    }

    int eatenFish = MAP[0][0].num;
    MAP[0][0].num = -1;             // 상어
    fishList[eatenFish].y = 0; fishList[eatenFish].x = 0;  fishList[eatenFish].num = 0;  fishList[eatenFish].direction = 0;
    move(0, 0, eatenFish);            // 재귀 타기


    cout << answer;

    return 0;
}
