#include <iostream>
#include <queue>
#include <vector>

using namespace std;



int grid[9], population[9], DAT[9], CDAT[9];
int K, N, M, T, result = 99999, cnt, sum;
vector<int> v[9];
vector<int> cv;
queue<int> q;

void init() {
    result = 99999;
    sum = 0;
    for (int i = 0; i < 9; i++) {
        v[i].clear();
    }
    for (int i = 0; i < 9; i++) {
        DAT[i] = 0;
    }
}

void DATinit() {
    for (int i = 0; i < 9; i++) {
        DAT[i] = 0;
    }
    cv.clear();
}

// checknsort 보조 함수
void checkdfs(int a, int color) {
    DAT[a] = 1;

    for (int i = 0; i < v[a].size(); i++) {
        if (DAT[v[a][i]] == 1) {
            continue;
        }
        if (grid[v[a][i]] == color) {
            q.push(v[a][i]);
            cv.back() += population[v[a][i]];
            checkdfs(v[a][i], color);
        }
    }
}

// 같은 색이고, 연결되어 있으면 합치기
void checknsort() {
    int temp;
    for (int i = 0; i < N; i++) {
        if (DAT[i] != 0) continue;
        cv.push_back(population[i]);
        DAT[i] = 1;
        
        checkdfs(i, grid[i]);

        while (!q.empty()) {
            temp = q.front();
            q.pop();
            if (DAT[temp] == 1) {
                if (q.empty()) break;
                else {
                    continue;
                }
            }

            if (grid[temp] == grid[i]) {
                DAT[temp] = 1;
                cv.back() += population[temp];
            }
        }
    }
}

// 색칠하기
void randomdrawing(int level) {
    if (level == N) {
        checknsort();
        if (cv.size() == 2) {
            if (cv[0] > cv[1]) {
                result = result > cv[0] - cv[1] ? cv[0] - cv[1] : result;
            }
            else {
                result = result > cv[1] - cv[0] ? cv[1] - cv[0] : result;
            }
        }
        DATinit();
        return;
    }
    for (int i = 1; i <= 2; i++) {
        grid[level] = i;
        randomdrawing(level + 1);
    }
}

int main() {
    int a;

    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cin >> N;
        init();
        for (int i = 0; i < N; i++) {
            for (int z = 0; z < N; z++) {
                cin >> a;
                if (a == 1) {
                    v[i].push_back(z);
                }
            }
        }

        for (int i = 0; i < N; i++) {
            cin >> population[i];
            sum += population[i];
        }

        randomdrawing(0);

        cout << "#" << tc << " " << result << "\n";
    }

    return 0;
}
