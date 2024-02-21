#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

int dy[4] = { -1, 1, 0, 0 };        // 상하좌우
int dx[4] = { 0, 0, -1, 1 };
int changeDir[4] = { 1, 0, 3, 2 };  

int T, N, M, K, answer;

struct microbe {
    int y;
    int x;
    int population;
    int direction;
};

vector <vector< vector <microbe>>> MAP;
queue <microbe> microbes;

void init() {
    MAP.clear();
    for (int i = 0; i < microbes.size(); i++) {
        microbes.pop();
    }
    answer = 0;
}

void input() {
    cin >> N >> M >> K;
    MAP.resize(N, vector <vector<microbe>>(N, vector<microbe>()));

    int row, col, microNum, dir;
    for (int i = 0; i < K; i++)
    {
        cin >> row >> col >> microNum >> dir;
        microbes.push({ row, col, microNum, dir-1 });       // 입력은 1,2,3,4로 주어지므로 
    }
}

void move() {

    // 현재 있는 미생물들 이동해서 배치하기
    int curSize = microbes.size();
    for (int i = 0; i < curSize; i++)
    {
        microbe now = microbes.front();
        microbes.pop();

        int ny = now.y + dy[now.direction];
        int nx = now.x + dx[now.direction];
        int newDirection = now.direction;
        int newPopulation = now.population;
        if (ny == 0 || nx == 0 || ny == N - 1 || nx == N - 1) {
            newDirection = changeDir[now.direction];
            newPopulation = (int)(newPopulation / 2);
        }

        MAP[ny][nx].push_back({ ny, nx, newPopulation, newDirection });
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (MAP[i][j].size() == 0)
                continue;

            else if (MAP[i][j].size() == 1) {
                microbes.push(MAP[i][j][0]);
                MAP[i][j].clear();
            }

            else {
                int maxPopulation = 0;
                int maxPopDir;
                int populationSum = 0;
                for (int k = 0; k < MAP[i][j].size(); k++)
                {
                    populationSum += MAP[i][j][k].population;
                    if (maxPopulation < MAP[i][j][k].population) {
                        maxPopulation = MAP[i][j][k].population;
                        maxPopDir = MAP[i][j][k].direction;
                    }
                }
                microbes.push({ i, j, populationSum, maxPopDir });
                MAP[i][j].clear();
            }

        }
    }

    int de = -1;
}


void solve() {
    for (int i = 0; i < M; i++)
    {
        move();
    }

    while (!microbes.empty()){
        microbe now = microbes.front();
        microbes.pop();
        answer += now.population;
    }
}


int main() {
    freopen("sample_input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        init();
        input();
        solve();

        cout << "#" << tc << " " << answer << "\n";
    }
    

    int de = -1;

    return 0;
}
