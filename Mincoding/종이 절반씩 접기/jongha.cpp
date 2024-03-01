#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>

using namespace std;


struct Point {
    int max;
    int min;
};

int cnt;
int grid[201][201];
int H, W;
int temph, tempw;
queue<Point> q;


void halfH() {

    for (int i = 0; i < temph; i++) {
        if (i < temph / 2) {
            for (int z = 0; z < tempw; z++) {
                grid[i][z] += grid[temph - i - 1][z];
            }
        }
        else {
            for (int z = 0; z < tempw; z++) {
                grid[i][z] = 0;
            }
        }
    }

    temph = temph / 2;

}

void halfW() {

    for (int j = 0; j < temph; j++) {
        for (int i = 0; i < tempw / 2; i++) {
            grid[j][i] += grid[j][tempw - i - 1];
        }
        // 원래 아래 코드였는데 배열 범위를 벗어나면서 grid 초반을 0으로 초기화 해버린듯 함..
        //for (int i = tempw / 2; i < tempw; i++) {
        //    grid[j][i + tempw / 2] = 0;
        //}
        for (int i = tempw / 2; i < tempw; i++) {
            grid[j][i] = 0;
        }
    }

    tempw = tempw / 2;
}

int main() {
    int max = 0; int min = 999999999;
    cin >> H >> W;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
        }
    }

    temph = H;
    tempw = W;

    while (temph % 2 == 0 || tempw % 2 == 0) {
        if (temph % 2 == 0 && tempw % 2 == 0) {
            if (temph > tempw) {
                halfH();
            }
            else {
                halfW();
            }
        }
        else if (temph % 2 == 0) {
            halfH();
        }
        else {
            halfW();
        }

        for (int i = 0; i < temph; i++) {
            for (int z = 0; z < tempw; z++) {
                max = max > grid[i][z] ? max : grid[i][z];
                min = min > grid[i][z] ? grid[i][z] : min;
            }
        }


        cnt++;

        q.push({ max, min });
        min = 9999999;

    }


    cout << cnt << "\n";

    while (!q.empty()) {
        cout << q.front().max << " " << q.front().min << "\n";
        q.pop();
    }


    return 0;
}
