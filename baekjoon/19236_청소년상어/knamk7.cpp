#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct Fish
{
    int id;
    int direction;
    int y;
    int x;
};

struct Shark
{
    int y;
    int x;
    int direction;
};

bool cmp(Fish a, Fish b)
{
    return a.id < b.id;
}

int dy[] = { -1,-1,0,1,1,1,0,-1 };
int dx[] = { 0,-1,-1,-1,0,1,1,1 };

int map[4][4];

Shark shark;
Fish fish[16];

void move_fish()
{
    for (int i = 0; i < 16; i++)
    {
        if (fish[i].id == -1)
            continue;
        int ny = fish[i].y + dy[fish[i].direction];
        int nx = fish[i].x + dx[fish[i].direction];
        while (ny < 0 || nx < 0 || ny >= 4 || nx >= 4 || (ny == shark.y && nx == shark.x))
        {
            fish[i].direction = (fish[i].direction + 1) % 4;
            ny = fish[i].y + dy[fish[i].direction];
            nx = fish[i].x + dx[fish[i].direction];
        }

    }
}

int main()
{
    // input
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int id, d;
            map[i][j] = id;
            fish[i * 4 + j + 1] = { id, d - 1, i, j };
        }
    }
    sort(fish + 1, fish + 17, cmp);

    // moves
    shark = { fish[map[0][0]].y, fish[map[0][0]].x, fish[map[0][0]].direction };
    fish[map[0][0]]
        while (true)
        {

        }

    return 0;
}
