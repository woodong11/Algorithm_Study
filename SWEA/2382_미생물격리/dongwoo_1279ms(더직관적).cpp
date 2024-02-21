#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

int dy[4] = { -1, 1, 0, 0 };        // 상하좌우
int dx[4] = { 0, 0, -1, 1 };
int changeDir[4] = { 1, 0, 3, 2 };  // 해당 위치에 들어갔을때 방향 바꿔주는 함수 ex) 0 -> 1
int T, N, M, K, curTime, answer;

struct Node {
    int y;
    int x;
};

struct microbe {
    int population;
    int direction;
    int time;
};

vector <vector< vector <microbe>>> MAP;

void init() {
    MAP.clear();
    answer = 0;
}

void input() {
    cin >> N >> M >> K;
    MAP.resize(N, vector <vector<microbe>>(N, vector<microbe>()));

    int row, col, microNum, dir;
    for (int i = 0; i < K; i++)
    {
        cin >> row >> col >> microNum >> dir;
        MAP[row][col].push_back({microNum, dir - 1, curTime});       // 입력은 1,2,3,4로 주어지므로 
    }
}

void move() {

    // 현재 있는 미생물들 이동해서 배치하기
    vector <Node> v;                            // 개수가 2보다 큰 위치 저장하는 벡터          
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if ((MAP[i][j].size() > 0) && (MAP[i][j][0].time == curTime)) {

                microbe now = MAP[i][j][0];             
                MAP[i][j].erase(MAP[i][j].begin());

                int ny = i + dy[now.direction];
                int nx = j + dx[now.direction];
                int newDirection = now.direction;
                int newPopulation = now.population;
                if (ny == 0 || nx == 0 || ny == N - 1 || nx == N - 1) {
                    newDirection = changeDir[now.direction];
                    newPopulation = (int)(newPopulation / 2);
                }
                MAP[ny][nx].push_back({newPopulation, newDirection, curTime + 1 });

                if (MAP[ny][nx].size() >= 2)
                    v.push_back({ ny, nx });
            }
        }
    }

    // 개수가 2보다 큰 칸 미생물들 하나로 합치기
    for (int i = 0; i < v.size(); i++){
        Node now = v[i];
        if (MAP[now.y][now.x].size() == 1)
            continue;

        int maxPopulation = 0;
        int maxPopDir;
        int populationSum = 0;
        for (int k = 0; k < MAP[now.y][now.x].size(); k++)
        {
            populationSum += MAP[now.y][now.x][k].population;
            if (maxPopulation < MAP[now.y][now.x][k].population) {
                maxPopulation = MAP[now.y][now.x][k].population;
                maxPopDir = MAP[now.y][now.x][k].direction;
            }
        }
        MAP[now.y][now.x].clear();
        MAP[now.y][now.x].push_back({ populationSum, maxPopDir, curTime + 1 });
    }
}


void solve() {
    for (int i = 0; i < M; i++)
    {
        move();
        curTime++;
    }

    // 마지막 미생물 개수 세기
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (MAP[i][j].size() > 0)
                answer += MAP[i][j][0].population;
        }
    }
}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        init();
        input();
        solve();
        cout << "#" << tc << " " << answer << "\n";
    }
    return 0;
}
