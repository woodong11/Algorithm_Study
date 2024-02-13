#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int N, W, H;
int map[17][14];
int temp_map[5][17][14];
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };
int initial_brick_cnt;
int result;

void init()
{
    memset(map, -1, sizeof(map));
    memset(temp_map, -1, sizeof(temp_map));
    initial_brick_cnt = 0;
}

void input()
{
    cin >> N >> W >> H;
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            cin >> map[i][j];
            if (map[i][j] != 0)
            {
                initial_brick_cnt++;
            }
        }
    }
    result = initial_brick_cnt;
}

void break_brick(int y, int x, int level)
{
    if (temp_map[level][y][x] == 0)
    {
        return;
    }
    int iter_limit = temp_map[level][y][x];
    temp_map[level][y][x] = 0;
    for (int i = 0; i < 4; i++)
    {
        int ny = y;
        int nx = x;
        for (int j = 1; j < temp_map[level][y][x]; j++)
        {
            ny += dy[i];
            nx += dx[i];
            if (temp_map[level][ny][nx] == 0)
            {
                continue;
            }
            if (temp_map[level][ny][nx] == -1)
            {
                break;
            }
            break_brick(ny, nx, level);
        }

    }
}

void brick_fall(int level)
{
    for (int j = 1; j <= W; j++)
    {
        int index = H;

        for (int i = H; i > 0; i--)
        {
            if (temp_map[level][i][j] == 0)
            {
                continue;
            }

            temp_map[level][index][j] = temp_map[level][i][j];
            temp_map[level][i][j] = 0;
            index--;
        }
    }
}

void dfs(int x, int level)
{
    if (level == N)
    {
        int bricks_left = 0;
        for (int i = 1; i <= H; i++)
        {
            for (int j = 1; j <= W; j++)
            {
                if (temp_map[N - 1][i][j] != 0)
                {
                    bricks_left++;
                }
            }
        }
        result = min(result, bricks_left);
        return;
    }

    int y = 0;
    for (int j = 1; j <= W; j++)
    {
        for (int i = 1; i <= H; i++)
        {
            for (int j = 1; j <= W; j++)
            {
                temp_map[level + 1][i][j] = temp_map[level][i][j];
            }
        }
        for (int i = 1; i <= H; i++)
        {
            if (temp_map[level + 1][i][j] != 0)
            {
                y = i;
            }
        }
    }

    break_brick(y, x, level + 1);
    brick_fall(level + 1);

    

    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {

        }
    }

    for (int j = 1; j <= W; j++)
    {
        dfs(j, level + 1);
        if (level > 0)
        {
            for (int i = 1; i <= H; i++)
            {
                for (int j = 1; j <= W; j++)
                {
                    temp_map[level][i][j] = temp_map[level - 1][i][j];
                }
            }
        }
        else
        {
            for (int i = 1; i <= H; i++)
            {
                for (int j = 1; j <= W; j++)
                {
                    temp_map[level][i][j] = map[i][j];
                }
            }
        }
    }
}

void run()
{
    // copy map to temp_map
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            temp_map[0][i][j] = map[i][j];
        }
    }

    // run dfs to find minimum
    for (int j = 1; j <= W; j++)
    {
        dfs(j, 0);
    }
}

int main(int argc, char** argv)
{
    int test_case;
    int T;
    //freopen("input.txt", "r", stdin);
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        init();
        input();
        run();

        // print
        cout << "#" << test_case << " " << result << endl;
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
