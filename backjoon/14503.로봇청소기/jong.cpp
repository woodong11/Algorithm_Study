#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


int direction[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
int r, c, d, cnt, N, M;
int grid[51][51];

void back_move(int robot_x, int robot_y, int robot_direction);

// -1로 청소를 한다.
void clean(int robot_x, int robot_y) {
    grid[robot_y][robot_x] = -1;
    cnt++;
}

// 90도로 회전한다.
int rotate(int robot_direction) {
    int next_robot_direction;

    next_robot_direction = robot_direction - 1;
    if (next_robot_direction == -1) next_robot_direction = 3;

    return next_robot_direction;
}

// 주변을 확인한다.
bool surround_check(int robot_x, int robot_y) {
    for (int i = 0; i < 4; i++) {
        if (grid[robot_y + direction[i][1]][robot_x + direction[i][0]] == 0) return true;
    }
    return false;
}

bool front_check(int robot_next_x, int robot_next_y) {
    if (grid[robot_next_y][robot_next_x] == 0) {
        return true;
    }
    return false;
}

// 움직인다. 
void move(int robot_x, int robot_y, int robot_direction) {
    if (grid[robot_y][robot_x] == 0) clean(robot_x, robot_y);

    // 벽 확인
    // 다음 위치를 청소했거나 벽이라면 주변 확인
    if (surround_check(robot_x, robot_y)) {
        int robot_next_x, robot_next_y;

        // 회전하고 방향을 갱신한다.
        robot_direction = rotate(robot_direction);

        robot_next_x = robot_x + direction[robot_direction][0];
        robot_next_y = robot_y + direction[robot_direction][1];

        // 전방 체크 후 움직인다.
        if (front_check(robot_next_x, robot_next_y)) {
            move(robot_next_x, robot_next_y, robot_direction);
        }
        else {
            move(robot_x, robot_y, robot_direction);
        }
    }
    else {
        back_move(robot_x, robot_y, robot_direction);
    }
}

// 후진한다.
void back_move(int robot_x, int robot_y, int robot_direction) {
    int robot_next_x, robot_next_y;
    robot_next_x = robot_x - direction[robot_direction][0];
    robot_next_y = robot_y - direction[robot_direction][1];
    if (grid[robot_y - direction[robot_direction][1]][robot_x - direction[robot_direction][0]] == 1) {
        cout << cnt;
        return;
    }
    move(robot_next_x, robot_next_y,robot_direction);
}

int main() {
    cin >> N >> M;
    cin >> r >> c >> d;

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < M; k++) {
            cin >> grid[i][k];
        }
    }
    move(c, r, d);

    return 0;
 }
