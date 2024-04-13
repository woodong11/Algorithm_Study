#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int n, m, k;
struct info {
    int y, x, dir, fscore, gun;
};

int score[31]; // id에 따른 플레이어 점수
info pp[31]; // id에 따른 플레이어 정보
vector<int> map_gun[21][21]; // 맵에 총 저장 
int map_pp[21][21]; // 맵에 플레이어 id 저장

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

bool cmp(int a, int b) {
    return a > b;
}

void init() {
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            map_pp[i][j] = -1;
        }
    }
}

void input() {
    cin >> n >> m >> k;
    int a;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a;
            if (a == 0)continue;
            map_gun[i][j].push_back(a);
        }
    }
    int y, x, d, s;
    for (int i = 0; i < m; i++)
    {
        cin >> y >> x >> d >> s;
        pp[i] = { y - 1, x - 1, d, s, 0 };
        map_pp[y - 1][x - 1] = i;
    }
}

void moveP() {
    // 플레이어 한 칸 이동
        // 1. 격자 벗어나는 경우 >> 방향 바꾸기
        // 2. 플레이어가 있다면 >> 싸움
        // 3. 플레이어가 없다면, 총 확인 >> 총 get
        //

    info nowplayer, nextplayer;
    info* winplayer, * loseplayer;
    int ny, nx = 0;
    int sumscore_now, sumscore_next;
    for (int i = 0; i < m; i++)
    {
        nowplayer = pp[i];

        ny = nowplayer.y + dy[nowplayer.dir];
        nx = nowplayer.x + dx[nowplayer.dir];
        // 정반대 방향으로 방향을 바꾸어서 1만큼 이동
        if (ny < 0 || nx < 0 || ny >= n || nx >= n) {
            nowplayer.dir = (nowplayer.dir + 2) % 4;
            ny = nowplayer.y + dy[nowplayer.dir];
            nx = nowplayer.x + dx[nowplayer.dir];
        }
        // 플레이어가 있다면 >> 싸움
        if (map_pp[ny][nx] != 0) {
            nextplayer = pp[map_pp[ny][nx]];
            sumscore_now = nowplayer.fscore + nowplayer.gun;
            sumscore_next = nextplayer.fscore + nextplayer.gun;

            if (sumscore_next < sumscore_now) {
                winplayer = &nowplayer;
                loseplayer = &nextplayer;
            }
            else if (sumscore_next == sumscore_now) {
                if (nowplayer.fscore > nextplayer.fscore) {
                    winplayer = &nowplayer;
                    loseplayer = &nextplayer;
                }
                else if (nowplayer.fscore < nextplayer.fscore) {
                    winplayer = &nextplayer;
                    loseplayer = &nowplayer;
                }
            }
            else {
                winplayer = &nextplayer;
                loseplayer = &nowplayer;
            }
            score[i] += abs(sumscore_now - sumscore_next);


            map_gun[ny][nx].push_back((*loseplayer).gun);
            (*loseplayer).gun = 0;

            // 
        // 4. 진 플레이어는 본인이 가지고 있는 총을 해당 격자에 내려놓고
        // //  해당 플레이어가 원래 가지고 있던 방향대로 한 칸 이동
        // // 만약 이동하려는 칸에 다른 플레이어가 있거나 격자 범위 밖인 경우
        // //// 오른쪽으로 90도씩 회전하여 빈 칸이 보이는 순간 이동
        // /// 만약 해당 칸에 총이 있다면, 
        // ////해당 플레이어는 가장 공격력이 높은 총을 획득하고 나머지 총들은 해당 격자에 내려 놓습니다.
        // // 이긴 플레이어는 승리한 칸에 떨어져 있는 총들과 원래 들고 있던 총 중 가장 공격력이 높은 총을 획득하고, 
        // 나머지 총들은 해당 격자에 내려 놓습니다.
        // 
        // 
            // pp[i] 업데이트
            //map_pp 업데이트
            // 한판 끝나고 해도 될것같기도?
            /*pp[i].y = ny;
            pp[i].x = nx;
            pp[i].dir = nowplayer.dir;
            map_pp[nowplayer.y][nowplayer.x] = 0;
            map_pp[ny][nx] = i;*/
        }
        // 플레이어가 없는 경우 >> 총확인
        else {
            // 3. 이동한 방향에 플레이어가 없다면 해당 칸에 총이 있는지 확인
            // 총이 있는 경우, 해당 플레이어는 총을 획득합니다. 
            // 플레이어가 이미 총을 가지고 있는 경우에는 
            // 놓여있는 총들과 플레이어가 가지고 있는 총 가운데 공격력이 더 쎈 총을 획득하고, 
            // 나머지 총들은 해당 격자에 둡니다.
            int getgun = nowplayer.gun;
            int temp;
            if (map_gun[ny][nx].size() == 0) continue; // 총이 없다면 

            sort(map_gun[ny][nx].begin(), map_gun[ny][nx].end(), cmp);
            if (getgun < map_gun[ny][nx][0]) {
                temp = getgun;
                getgun = map_gun[ny][nx][0];
                if (getgun == 0) map_gun[ny][nx].erase(map_gun[ny][nx].begin());
                else map_gun[ny][nx][0] = temp;
            }
            pp[i].gun = getgun;
        }

    }
}

void process() {
    for (int i = 0; i < k; i++)
    {
        moveP();

    }

}

int main() {
    freopen("sample_input.txt", "r", stdin);
    init();
    input();
    process();

    return 0;
}
