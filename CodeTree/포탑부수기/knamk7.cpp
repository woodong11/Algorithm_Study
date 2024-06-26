#include<iostream>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
using namespace std;

struct Node
{
    int y;
    int x;
};

int N, M, K;
bool flag = 0;
vector<vector<int>> map;
vector<vector<int>> latest_attack;
vector<vector<Node>> visited;
vector<vector<bool>> related;
Node attacker;
Node target;
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int by[8] = { -1,-1,-1,0,0,1,1,1 };
int bx[8] = { -1,0,1,-1,1,-1,0,1 };
vector<Node> path;
vector<Node> lasertrace;

void laser(Node attacker, Node target);
void bomb(Node attacker, Node target);
void init();

void dfs(Node now)
{
    if (visited[now.y][now.x].y == 0)
    {
        return;
    }
    if (now.y == attacker.y && now.x == attacker.x)
    {
        return;
    }
    lasertrace.push_back(visited[now.y][now.x]);
    dfs(visited[now.y][now.x]);
}

void bfs()
{
    bool breakflag = 0;
    queue<Node> q;
    q.push(attacker);
    visited[attacker.y][attacker.x] = attacker;
    while (!q.empty())
    {
        Node now = q.front();
        if (now.y == target.y && now.x == target.x) break;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];
            if (ny < 1) ny = N;
            else if (ny > N) ny = 1;
            if (nx < 1) nx = M;
            else if (nx > M) nx = 1;
            if (map[ny][nx] <= 0) continue;
            if (visited[ny][nx].y != 0) continue;
            visited[ny][nx] = now;
            if (ny == target.y && nx == target.x)
            {
                breakflag = 1;
                break;
            }
            q.push({ ny, nx });
        }
        if (breakflag)
        {
            break;
        }
    }
    dfs(target);
}

void input()
{
    cin >> N >> M >> K;
    init();
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            cin >> map[i][j];
        }
    }
}

void init()
{
    map = vector<vector<int>>(N + 2, vector<int>(M + 2));
    latest_attack = vector<vector<int>>(N + 2, vector<int>(M + 2));
    related = vector<vector<bool>>(N + 2, vector<bool>(M + 2));
    visited = vector<vector<Node>>(N + 2, vector<Node>(M + 2));
}

void start_turn()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            related[i][j] = 0;
            visited[i][j] = { 0,0 };
        }
    }
    lasertrace.clear();
    path.clear();
}

void select()
{
    int minVal = INT_MAX;
    int latest = 0;
    Node a = { INT_MAX, INT_MAX };
    // select attacker
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            if (map[i][j] <= 0) continue;
            else if (map[i][j] < minVal)
            {
                minVal = map[i][j];
                a = { i,j };
                latest = latest_attack[i][j];
            }
            else if (map[i][j] == minVal)
            {
                if (latest_attack[i][j] > latest)
                {
                    a = { i,j };
                    latest = latest_attack[i][j];
                }
                else if (latest_attack[i][j] < latest)
                {
                    continue;
                }
                else if ((i + j) > (a.y + a.x))
                {
                    a = { i,j };
                }
                else if ((i + j) == (a.y + a.x))
                {
                    if (j > a.x)
                    {
                        a = { i,j };
                    }
                }
            }
        }
    }
    // select target
    int maxVal = 0;
    latest = INT_MAX;
    Node t = { INT_MAX, INT_MAX };
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            if (map[i][j] <= 0) continue;
            if (i == a.y && j == a.x) continue;
            else if (map[i][j] > maxVal)
            {
                maxVal = map[i][j];
                t = { i,j };
                latest = latest_attack[i][j];
            }
            else if (map[i][j] == maxVal)
            {
                if (latest_attack[i][j] < latest)
                {
                    t = { i,j };
                    latest = latest_attack[i][j];
                }
                else if (latest_attack[i][j] > latest)
                {
                    continue;
                }
                else if ((i + j) < (t.y + t.x))
                {
                    t = { i,j };
                }
                else if ((i + j) == (t.y + t.x))
                {
                    if (j < t.x)
                    {
                        t = { i,j };
                    }
                }
            }
        }
    }
    if (t.y == INT_MAX && t.x == INT_MAX)
    {
        flag = 1;
        return;
    }
    attacker = a;
    map[attacker.y][attacker.x] += N + M;
    target = t;
}

void attack(int turn)
{
    latest_attack[attacker.y][attacker.x] = turn;
    bfs();
    if (!lasertrace.empty())
    {
        laser(attacker, target);
    }
    else
    {
        bomb(attacker, target);
    }
}

void laser(Node attacker, Node target)
{
    lasertrace.pop_back();
    for (Node i : lasertrace)
    {
        map[i.y][i.x] -= map[attacker.y][attacker.x] / 2;
        related[i.y][i.x] = 1;
    }
    map[target.y][target.x] -= map[attacker.y][attacker.x];
    related[attacker.y][attacker.x] = 1;
    related[target.y][target.x] = 1;
}

void bomb(Node attacker, Node target)
{
    for (int i = 0; i < 8; i++)
    {
        int ny = target.y + by[i];
        int nx = target.x + bx[i];
        if (ny < 1) ny = N;
        else if (ny > N) ny = 1;
        if (nx < 1) nx = M;
        else if (nx > M) nx = 1;
        if (ny == attacker.y && nx == attacker.x) continue;
        if (map[ny][nx] > 0)
        {
            map[ny][nx] -= map[attacker.y][attacker.x] / 2;
            related[ny][nx] = 1;
        }
    }
    map[target.y][target.x] -= map[attacker.y][attacker.x];
    related[attacker.y][attacker.x] = 1;
    related[target.y][target.x] = 1;
}

void repair()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            if (map[i][j] <= 0) continue;
            if (related[i][j]) continue;
            map[i][j] += 1;
        }
    }
}

void result()
{
    int maxVal = 0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            maxVal = max(maxVal, map[i][j]);
        }
    }
    cout << maxVal;
}

int main()
{
    input();
    for (int i = 1; i <= K; i++)
    {
        start_turn();
        select();
        if (flag) 
            break;
        attack(i);
        repair();
    }
    result();
    return 0;
}
