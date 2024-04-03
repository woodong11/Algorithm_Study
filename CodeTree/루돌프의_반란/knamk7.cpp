#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

struct Node
{
    int r;
    int c;
};

int N, M, P, C, D;
Node R;
Node S[30];
vector<vector<int>> map;
int status[30];
int score[30];
int santaleft;

void input()
{
    int nousage;
    cin >> N >> M >> P >> C >> D;
    map = vector<vector<int>>(N + 2, vector<int>(N + 2));
    cin >> R.r >> R.c;
    for (int i = 0; i < P; i++)
    {
        cin >> nousage >> S[i].r >> S[i].c;
        map[S[i].r][S[i].c] = 1;
    }
}

void santa()
{
    int minVal = 5000;
    Node priority = { 0,0 };
    int santanum = 0;
    for (int i = 0; i < P; i++)
    {
        if (status[i])
        {
            continue;
        }
        int yy = R.r - S[i].r;
        int xx = R.c - S[i].c;
        int d = yy * yy + xx * xx;
        if (d < minVal)
        {
            priority = S[i];
        }
        else if (d == minVal)
        {
            if (priority.r <= S[i].r)
            {
                priority.r = S[i].r;
                if (priority.c >= S[i].c)
                {
                    santanum = i;
                    continue;
                }
                priority.c = S[i].c;
            }
        }
        santanum = i;
    }
    int dr[8] = { -1,-1,-1,0,0,1,1,1 };
    int dc[8] = { -1,0,1,-1,1,-1,0,1 };
    int mindistance = 5000;
    int dir_num;
    for (int i = 0; i < 8; i++)
    {
        int nr = R.r + dr[i];
        int nc = R.c + dc[i];
        int distance = (nr - S[santanum].r) * (nr - S[santanum].r) + (nc - S[santanum].c) * (nc - S[santanum].c);
        if (distance < mindistance)
        {
            mindistance = distance;
            dir_num = i;
        }
    }
    R.r += dr[dir_num];
    R.c += dc[dir_num];
    if (mindistance == 0)
    {
        map[S[santanum].r][S[santanum].c] = 0;
        S[santanum].r += dr[dir_num] * C;
        S[santanum].c += dc[dir_num] * C;
        if (S[santanum].r < 1 || S[santanum].c < 1 || S[santanum].r > N || S[santanum].c > N)
        {
            if (--santaleft == 0)
            {
                score[santaleft] += C;
                return;
            }
            status[santanum] = -1;
        }
        else
        {
            map[S[santanum].r][S[santanum].c] = 1;
            status[santanum] = 1;
        }
        score[santanum] += C;
    }
}

void print()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (i == R.r && j == R.c)
            {
                printf("R ");
            }
            else if (map[i][j] == 1)
            {
                printf("S ");
            }
            else
            {
                printf("O ");
            }
        }
        printf("\n");
    }
    printf("\n");
}


int main()
{
    input();
    santaleft = P;
    for (int t = 1; t <= M; t++)
    {
        print();
        santa();
        if (santaleft == 0) break;

    }
    for (int i = 0; i < P; i++)
    {
        printf("%d ", score[i]);
    }
    return 0;
}
