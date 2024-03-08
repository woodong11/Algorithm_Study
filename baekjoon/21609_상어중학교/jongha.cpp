#include <algorithm>
#include <vector>
#include <climits>
#include <iostream>
#include <queue>
#include <unordered_set>
#include<cmath>

using namespace std;

struct Point {
    int y;
    int x;
};

int N, M, visited[21][21], cnt, result, zeronum;
int dat[6];
int dx[4] = { 0, 0, -1, 1 }, dy[4] = { 1, -1, 0, 0 };
vector<vector<int>> grid(21, vector<int>(21, -2));



void gravity(vector<vector<int>>& v) {
    for (int i = 0; i < N; i++) {
        int start = N - 1;
        int end = start;
        while (start >= 0) {
            if (v[start][i] == -2) {
                end--;

                if (end < 0) break;
                if (v[end][i] >= 0) {
                    v[start][i] = v[end][i];
                    v[end][i] = -2;
                    start--;
                    end = start;
                    continue;
                }
                if (v[end][i] == -1) {
                    start = end - 1;
                    end = start;
                    continue;
                }
            }
            else {
                start--;
                end = start;
            }
        }
    }
}

void rotate(vector<vector<int>>& v) {
    int tempgrid[21][21];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tempgrid[N - 1 - j][i] = v[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            v[i][j] = tempgrid[i][j];
        }
    }
}

void search(vector<vector<int>>& v) {
    vector<Point> resultv;

    while (1) {
        Point standardBlock = {-1, -1}, tempBlock;
        for (int i = 0; i < N; i++) {
            int num = 0;
            priority_queue<pair<int, int>> pq;
            for (int j = 0; j < N; j++) {
                if (visited[i][j] == 1 || v[i][j] == -2 || v[i][j] == -1 || v[i][j] == 0) continue;

                tempBlock = { i, j };
                vector<Point> tempv;
                vector<Point> zerov;
                Point now;
                num = v[i][j];
                int tempcnt = 1;
                visited[i][j] = 1;
                pq.push({ i, j });
                tempv.push_back({ i, j });
                while (!pq.empty()) {
                    now.y = pq.top().first;
                    now.x = pq.top().second;
                    pq.pop();

                    for (int z = 0; z < 4; z++) {
                        int ny = now.y + dy[z];
                        int nx = now.x + dx[z];

                        if (ny < 0 || ny >= N || nx < 0 || nx >= N || visited[ny][nx] == 1) continue;
                        if (v[ny][nx] != 0 && v[ny][nx] != num) {
                            continue;
                        }

                        visited[ny][nx] = 1;
                        if (v[ny][nx] == 0) {
                            zerov.push_back({ ny, nx });
                        }

                        tempv.push_back({ ny, nx });
                        pq.push({ ny, nx });
                        tempcnt++;
                    }
                }

                for (int z = 0; z < zerov.size(); z++) {
                    visited[zerov[z].y][zerov[z].x] = 0;
                }

                if (cnt <= tempcnt) {
                    if (cnt == tempcnt && zerov.size() < zeronum) continue;
                    if (zeronum == zerov.size() && standardBlock.y > tempBlock.y) continue;
                    if (standardBlock.y == tempBlock.y && standardBlock.x > tempBlock.x) continue;
                    resultv = tempv;
                    standardBlock = tempBlock;
                    cnt = tempcnt;
                    zeronum = zerov.size();
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                visited[i][j] = 0;
            }
        }

        if (cnt > 1) {
            result += pow(cnt, 2);
            cnt = 0;
            zeronum = 0;

            for (int i = 0; i < resultv.size(); i++) {
                v[resultv[i].y][resultv[i].x] = -2;
            }

        }
        else {
            return;
        }

        cnt = 0;

        gravity(v);
        rotate(v);
        gravity(v);

    }
}

int main() {
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    search(grid);

    cout << result;


    return 0;
}
