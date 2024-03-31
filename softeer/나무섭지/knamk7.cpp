#include<iostream>
#include<algorithm>
#include<climits>
#include<string>
#include<queue>
#include<vector>


using namespace std;

struct Coord{
    int y;
    int x;
};

int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};

int main(int argc, char** argv)
{
    //input
    int n, m;
    cin >> n >> m;
    Coord D;
    vector<vector<char>> map(n + 2, vector<char>(m + 2, '#'));
    for (int i = 1; i <= n; i++) {
        string row;
        cin >> row;
        for (int j = 1; j <= m; j++) {
            map[i][j] = row[j - 1];
            if (row[j - 1] == 'D') {
                D = {i, j};
            }
        }
    }

    int N = INT_MAX;

    //bfs
    queue<Coord> q;
    vector<vector<int>> visited(n + 2, vector<int>(m + 2, -1));
    q.push(D);
    visited[D.y][D.x] = 0;
    while (!q.empty()) {
        Coord now = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];
            if (map[ny][nx] == '#' || visited[ny][nx] > -1) continue;
            q.push({ny, nx});
            visited[ny][nx] = visited[now.y][now.x] + 1;
            if (map[ny][nx] == 'N')
                {
                    N = visited[ny][nx];
                }
        }
    }

    //ghost
    int G = INT_MAX;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (map[i][j] == 'G') {
                G = min(G, abs(D.y - i) + abs(D.x - j));
            }
        }
    }

    if (N < G) {
        cout << "Yes";
    }
    else {
        cout << "No";
    }

   return 0;
}
