#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
using namespace std;

int dy[4] = { 1,-1,0,0 };
int dx[4] = {0,0,1,-1};
int N, W, H;
int map[15][12];
int minval;
int cnt;

void sort_down(int col) {    //1줄씩 밑으로 내리기
    int idx1 = H - 1;
    int idx2 = H - 2;
    while (idx1 > 0 && idx2 > 0) {
        while (map[idx1][col] != 0 && idx1 > 0) {
            idx1--;
        }
        if (idx1 == 0) break;
        idx2 = idx1 - 1;
        while (map[idx2][col] == 0 && idx2 > 0) {
            idx2--;
        }
        swap(map[idx1][col], map[idx2][col]);
    }
}

void move_down() {    //전부 밑으로 내리기 (0을 위로 올리기)
    for (int i = 0; i < W; i++) {
        sort_down(i);
    }
}

void boom(int y, int x) {    

    if (map[y][x] == 0) return;    //0이면무시

    int t = map[y][x];
    map[y][x] = 0;// 해당 벽돌 파괴
    cnt--;//벽돌개수 차감

    for (int k=1; k < t; k++) { //1이면 실행 x
        for (int i = 0; i < 4; i++)    //벽돌 숫자 만큼 주변 파괴
        {
            int ny = y + dy[i] * k;
            int nx = x + dx[i] * k;
            if (ny < 0 || ny >= H || nx < 0 || nx >= W || map[ny][nx] == 0) continue;
            boom(ny, nx);    

        }
    }

}
void shoot(int x) {    //한줄씩 구슬쏘기

    for (int y = 0; y < H; y++)
    {
        if (map[y][x] != 0) {
            boom(y, x);
            return;
        }
    }
}
void dfs(int level) {
    int temp[15][12]; //임시저장
    int tempcnt = cnt;

    //기저조건 N번 재귀
    if (level == N) 
    {
        minval = min(minval, cnt);
        return;
    }

    //임시 저장
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            temp[y][x] = map[y][x];
        }
    }

    for (int i = 0; i < W; i++)
    {
        shoot(i);    //구슬쏘기
        move_down();    //밑으로 내리기


        dfs(level + 1);

        //복구
        cnt = tempcnt;
        for (int y = 0; y < H; y++)
        {
            for (int x = 0; x < W; x++)
            {
                map[y][x] = temp[y][x];
            }
        }
    }
}
int main(int argc, char** argv)
{
    int test_case;
    int T;

    freopen("input.txt", "r", stdin);
    cin >> T;
    
    for (test_case = 1; test_case <= T; ++test_case)
    {    
        minval = 500;
        cnt = 0;
        cin >> N >> W >> H;

        //입력
        for (int y = 0; y < H; y++)
        {
            for (int x = 0; x < W; x++)
            {
                cin >> map[y][x];
                if (map[y][x] != 0) cnt++;    //벽돌개수 카운트
            }
        }
        dfs(0);

        cout <<"#"<<test_case<<" " << minval<<"\n";
    }
    return 0;
}
