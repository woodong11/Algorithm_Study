#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>

using namespace std;

struct Point {
    int y, x;
};


int n;
int realh, xw, yh, height;
int visited[45][15];
int dy[4] = { 0, 0, 1, -1 }, dx[4] = { 1, -1, 0, 0 };
long long result;
vector<vector<long long>> v(45, vector<long long>(15, 0));

void dfs(vector<vector<long long>> tempv, int level, long long tempresult) {
    if (level == 3) {
        result = result < tempresult ? tempresult : result;
        for (int i = realh; i < height; i++) {
            for (int j = 0; j < n; j++) {
                if (visited[i][j] == 1) visited[i][j] = 0;
            }
        }
        return;
    }

    if (level != 0) {
        for (int i = height - 1; i >= realh; i--) {
            for (int j = 0; j < n; j++) {
                if (visited[i][j] == 1) {
                    visited[i][j] = 0;
                    int a = 1;
                    int b = 0;
                    int end; int start;
                    while (1) {
                        end = i - a;
                        if (end < 0) break;
                        if (visited[end][j] == 1) {
                            visited[end][j] = 0;
                            a++;
                            continue;
                        }
                        start = i - b;
                        tempv[start][j] = tempv[end][j];
                        tempv[end][j] = 0;
                        b++;
                        a++;
                    }
                }
            }
        }
    }

    Point lu, rd;
    queue<Point> q;
    int nowvisited[45][15];

    for (int i = realh; i < height; i++) {
        for (int j = 0; j < n; j++) {
            nowvisited[i][j] = 0;
        }
    }

    for (int i = realh; i < height; i++) {
        for (int j = 0; j < n; j++) {
            int cnt = 1;
            int y = i;
            int x = j;
            lu = { y, x };
            rd = { y, x };
            if (nowvisited[i][j] == 1) continue;
            nowvisited[i][j] = 1;
            visited[y][x] = 1;
            q.push({ y, x });
            xw = 1;
            yh = 1;

            while (!q.empty()) {
                Point now = q.front();
                q.pop();
                int ny, nx;
                for (int z = 0; z < 4; z++) {
                    ny = now.y + dy[z];
                    nx = now.x + dx[z];

                    if (ny < realh || ny >= height || nx < 0 || nx >= n) continue;
                    if (tempv[ny][nx] != tempv[y][x]) continue;
                    if (visited[ny][nx] == 1) continue;

                    q.push({ ny, nx });
                    lu.y = lu.y > ny ? ny : lu.y;
                    lu.x = lu.x > nx ? nx : lu.x;
                    rd.y = rd.y < ny ? ny : rd.y;
                    rd.x = rd.x < nx ? nx : rd.x; 
                    cnt++;
                    visited[ny][nx] = 1;
                    nowvisited[ny][nx] = 1;
                }
            }

            dfs(tempv, level + 1, tempresult + ((rd.y - lu.y + 1) * (rd.x - lu.x + 1) + cnt));
        }
    }
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    height = n * 3;
    realh = n * 2;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < n; j++) {
            cin >> v[i][j];
        }
    }

    dfs(v, 0, 0);

    cout << result;
    return 0;
}
