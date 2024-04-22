#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N;
int grid[1000][3], visited[1000][3];

int main() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
        visited[N - 1][i] = grid[N - 1][i];
    }

    for (int i = N - 2; i >= 0; i--) {
        for (int j = 0; j < 3; j++) {
            for (int z = 0; z < 3; z++) {
                if (j == z) continue;
                if (visited[i][j] == 0) visited[i][j] = grid[i][j] + visited[i + 1][z];
                else {
                    visited[i][j] = visited[i][j] > grid[i][j] + visited[i + 1][z] ? grid[i][j] + visited[i + 1][z] : visited[i][j];
                }
                
            }
        }
    }

    int result = 99999999;
    for (int i = 0; i < 3; i++) {
        result = visited[0][i] < result ? visited[0][i] : result;
    }

    cout << result;

    return 0;
}
