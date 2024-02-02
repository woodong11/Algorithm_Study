#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct coor {
    int x;
    int y;
};

struct answers {
    int processor;
    int wire;
};

int T, N;
int MAP[13][13];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int wireCount;
vector <coor> processors;
vector <answers> answerList;
int connectedProcessors;
int connectedProcessorsMax;

bool compare(answers a, answers b) {
    if (a.processor == b.processor)
        return a.wire < b.wire;
    return a.processor > b.processor;
}

void init() {
    memset(MAP, 0, sizeof(MAP));
    processors.clear();
    answerList.clear();
    wireCount = 0;
    connectedProcessors = 0;
    connectedProcessorsMax = 0;
}

void dfs(int level) {

    // 모두 시도해봤으면 return, vector에 넣기
    if (level == processors.size()) {

        if (connectedProcessors >= connectedProcessorsMax) {
            connectedProcessorsMax = connectedProcessors;
            answerList.push_back({ connectedProcessors, wireCount });
        }
        return;
    }

    // level번재 프로세서 하나 꺼내서 길 만들 수 있으면 전선 만들기


    for (int k = 0; k < 4; k++)
    {
        int curX = processors[level].x;
        int curY = processors[level].y;
        vector<coor> temp;
        bool canConnect = false;
        int curWire = 0;

        // 해당 방향으로 테스트해보기
        while (1)
        {
            int nx = curX + dx[k];
            int ny = curY + dy[k];

            // 전선이 다른 전선에 닿거나 또다른 프로세서에 닿는 경우
            if (MAP[nx][ny] == 2 || MAP[nx][ny] == 1) {
                break;
            }

            // 벗어나면 브레이크
            if ((nx < 0 || ny < 0 || nx >= N || ny >= N)) {
                canConnect = true;
                break;
            }

            temp.push_back({ nx, ny });        // 빈칸일경우, wire만들 곳 담기
            curX = nx;
            curY = ny;

        }

        // 해당 방향으로 길을 만들 수 있다면 dfs 돌리기, 복구하기
        if (canConnect == true) {
            for (int path = 0; path < temp.size(); path++){
                coor curWire = temp[path];
                MAP[curWire.x][curWire.y] = 2;
            }
            wireCount += temp.size();
            connectedProcessors++;

            dfs(level + 1);

            for (int path = 0; path < temp.size(); path++)
            {
                coor curWire = temp[path];
                MAP[curWire.x][curWire.y] = 0;
            }

            wireCount -= temp.size();
            connectedProcessors--;
        }
    }

    dfs(level+1);
    
}

void solve() {
    dfs(0);
    sort(answerList.begin(), answerList.end(), compare);
}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        init();

        cin >> N;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> MAP[i][j];
                if (MAP[i][j] == 1) {

                    // 만약 가장자리에 있다면 카운트해주기
                    if (i == 0 || j == 0 || i == N - 1 || j == N - 1)
                        connectedProcessors++;

                    // 가장자리에 없는 프로세서는 벡터에 넣어주기
                    else
                        processors.push_back({ i, j });
                }

            }
        }

        solve();
        cout << "#" << tc << " " << answerList[0].wire << "\n";
    }
    return 0;
}
