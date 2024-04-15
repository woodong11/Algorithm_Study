#include<iostream>
#include<vector>


using namespace std;

int dy[] = {0,1,0,-1};
int dx[] = {1,0,-1,0};

vector<vector<int>> map;
vector<int> vy;
vector<int> vx;

int n, m;
int cnt = 0;

void dfs(int y, int x, int level) {
    if (level == m) {
        cnt++;
        return;
    }
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (map[ny][nx] == 1) continue;
        map[ny][nx] = 1;
        if (ny == vy[level] && nx == vx[level]) {
            dfs(ny, nx, level + 1);
        }
        else {
            dfs(ny, nx, level);
        }
        map[ny][nx] = 0;
    }
}

int main(int argc, char** argv)
{
    cin >> n >> m;
    map = vector<vector<int>>(n + 2, vector<int>(n + 2, 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> map[i][j];
        }
    }
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        vy.push_back(a);
        vx.push_back(b);
    }

    map[vy[0]][vx[0]] = 1;
    dfs(vy[0], vx[0], 1);

    cout << cnt;
    
   return 0;
}
