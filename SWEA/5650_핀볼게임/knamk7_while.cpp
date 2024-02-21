#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

struct Point {
    int y;
    int x;
};

int N;
int map[102][102];
int dy[] = { 1,0,-1,0 };
int dx[] = { 0,-1,0,1 };
int score;
int result;
Point start;
vector<Point> wormholes[11];

void init()
{
    memset(map, 11, sizeof(map));
    result = 0;
    for (int i = 6; i <= 10; i++)
    {
        wormholes[i].clear();
    }
}

void input()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cin >> map[i][j];
            if (map[i][j] > 5)
            {
                wormholes[map[i][j]].push_back({ i,j });
            }
        }
    }
}

void move(int y, int x, int direction)
{
    int ny = y + dy[direction];
    int nx = x + dx[direction];
    while (ny != y || nx != x)
    {
        int next = map[ny][nx];
        if (next == -1)
        {
            break;
        }
        else if (next == 0)
        {
            ny += dy[direction];
            nx += dx[direction];
        }
        else if (next < 5)
        {
            score++;
            if (direction == next % 4)
            {
                direction = (direction + 1) % 4;
            }
            else if (direction == (next + 3) % 4)
            {
                direction = (direction + 3) % 4;
            }
            else
            {
                direction = (direction + 2) % 4;
            }
            ny += dy[direction];
            nx += dx[direction];
        }
        else if (next == 5 || next > 10)
        {
            score++;
            direction = (direction + 2) % 4;
            ny += dy[direction];
            nx += dx[direction];
        }
        else
        {
            if (ny == wormholes[next][0].y && nx == wormholes[next][0].x)
            {
                ny = wormholes[next][1].y + dy[direction];
                nx = wormholes[next][1].x + dx[direction];
            }
            else
            {
                ny = wormholes[next][0].y + dy[direction];
                nx = wormholes[next][0].x + dx[direction];
            }
        }
    }
}

int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        init();
        input();
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    score = 0;
                    if (map[i][j] != 0)
                        continue;
                    move(i, j, k);
                    result = max(result, score);
                }
            }
        }
        cout << '#' << test_case << ' ' << result << endl;
    }
    return 0;
}
