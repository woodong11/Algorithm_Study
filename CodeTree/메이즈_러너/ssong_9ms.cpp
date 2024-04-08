#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<queue>
#include<cmath>


using namespace std;

int N, M, K;
int map[11][11];
int map_print[11][11]; // print 위한 것
int ans_move_cnt;
int min_level;
pos left_point;
int level;
int temp[11][11];

//상하좌우
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

struct pos {
    int y, x;
};

queue<pos>p; // 참가자 위치
pos EX; // 출구 위치
queue<pos>find_p; // 참가자 찾기 위한

void input() {
    cin >> N >> M >> K; // 미로의 크기, 참가자 수, 게임 시간
    int c = 0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cin >> c;
            map[i][j] = c;
            map_print[i][j] = c;
        }
    }
    int a = 0, b = 0;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        p.push({ a, b });
        map[a][b] -= 1;
        map_print[a][b] -= 1; // 참가자 수
    }
    cin >> a >> b;
    EX = { a, b };
}

void print() {
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++) {
            if (i == EX.y && j == EX.x) printf("E ");
            else if (map[i][j] <= -1) printf("P ");
            else if (map[i][j] != 0) printf("# ");
            //else if (map[i][j] != 0) printf("%d ", map[i][j]);
            else printf("_ ");
        }
        printf("\n");
    }
    printf("\n");
}

void moveP() {

    int pp_cnt = p.size();
    int now_dist = 0, next_dist = 0;
    int ny = 0, nx = 0;
    pos nowP;
    pos nextP;
    int end_flag = 0;

    for (int i = 0; i < pp_cnt; i++) {
        end_flag = 0; // 탈출했을 때
        nowP = p.front(); // 현재 참가자 위치
        nextP = nowP; // 이동할 참가자의 위치
        p.pop();

        now_dist = abs(EX.y - nowP.y) + abs(EX.x - nowP.x);

        for (int i = 0; i < 4; i++)
        {
            ny = nowP.y + dy[i];
            nx = nowP.x + dx[i];

            // 외곽일 경우 + 벽인 경우
            if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
            else if (map[ny][nx] >= 1 && map[ny][nx] <= 9) continue;

            // 움직였는데 출구인 경우
            else if (ny == EX.y && nx == EX.x) {
                map[nowP.y][nowP.x] += 1;
                ans_move_cnt++;
                end_flag = 1;
                break;
            }

            next_dist = abs(EX.y - ny) + abs(EX.x - nx);
            if (next_dist < now_dist) {
                now_dist = next_dist;
                nextP = { ny, nx }; // 이동할 위치
                // 이동한 거리
            }
        }

        if (end_flag == 1) continue;
        if (nowP.y == nextP.y && nowP.x == nextP.x) {
            p.push(nextP);
            continue;
        }

        map[nowP.y][nowP.x] += 1;    // 이동한 참가자의 위치 업데이트
        map[nextP.y][nextP.x] -= 1;
        ans_move_cnt++;
        p.push(nextP);
    }
}

void find_square() {

    left_point = { 11,11 };
    pos check_p; // 현재 체크할 p
    level = 0;
    min_level = 11;
    find_p = p;
    int lp_y = 0, lp_x = 0;

    for (int i = 0; i < p.size(); i++) {
        check_p = find_p.front();
        find_p.pop();
        level = max(abs(check_p.y - EX.y), abs(check_p.x - EX.x));
        // 해당 p와의 좌상단 좌표

        lp_y = max(max(EX.y, check_p.y) - level, 1);
        lp_x = max(max(EX.x, check_p.x) - level, 1);
        if (level < min_level) {
            left_point = { lp_y, lp_x }; // 좌상단
            min_level = level; // r-1
        }
        else if (level == min_level) {
            if ((lp_y <= left_point.y) && (lp_x <= left_point.x)) {
                left_point = { lp_y, lp_x }; // 좌상단
            }
        }
    }
    level = min_level;
}

void rotation() {

    int ex_flag = 0;
    for (int i = left_point.y; i <= left_point.y + level; i++)
    {
        for (int j = left_point.x; j <= left_point.x + level; j++) {
            temp[i - left_point.y][j - left_point.x] = map[i][j];
        }
    }

    for (int i = 0; i <= level; i++)
    {
        for (int j = 0; j <= level; j++) {
            if (temp[level - j][i] >= 1 && temp[level - j][i] <= 9) {
                map[i + left_point.y][j + left_point.x] = temp[level - j][i] - 1;
            }
            else {
                map[i + left_point.y][j + left_point.x] = temp[level - j][i];
            }

            if (map[i + left_point.y][j + left_point.x] < 0) {
                for (int i = 0; i < abs(map[i + left_point.y][j + left_point.x]); i++) {
                    p.push({ i + left_point.y, j + left_point.x });
                }
            }
            // EX 업데이트
            if (ex_flag == 1) continue;
            if (i + left_point.y == EX.y && j + left_point.x == EX.x) {
                EX = { j + left_point.y, level - i + left_point.x };
                ex_flag = 1;
            }
        }
    }

    while (!p.empty()) {
        p.pop();
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (map[i][j] < 0) {
                for (int pp = 0; pp < abs(map[i][j]); pp++)
                {
                    p.push({ i,j });
                }
            }
        }
    }
}


void moveM() {
    find_square();
    rotation();
}


void process() {
    for (int i = 0; i < K; i++) {
        moveP(); // 참가자 이동
        // if 모든 참가자 미로 탈출 시 
        if (p.size() == 0) break;
        moveM(); // 미로 회전
    }
    cout << ans_move_cnt << '\n';
    cout << EX.y << " " << EX.x << '\n';
}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    input();
    process();
}
