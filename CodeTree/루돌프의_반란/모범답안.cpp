#include <iostream>

using namespace std;

#define MAX_N 51
#define MAX_P 31

int n, m, p, c, d;
int points[MAX_P];
pair<int, int> pos[MAX_P];
pair<int, int> rudolf;

int board[MAX_N][MAX_N];
bool is_live[MAX_P];
int stun[MAX_P];

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

// (x, y)가 보드 내의 좌표인지 확인하는 함수입니다.
bool is_inrange(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

int main() {
    cin >> n >> m >> p >> c >> d;  // 변수들을 입력받습니다.
    cin >> rudolf.first >> rudolf.second;
    board[rudolf.first][rudolf.second] = -1;  // 루돌프의 위치를 보드에 표시합니다.

    for(int i = 1; i <= p; i++) {
        int id;
        cin >> id;
        cin >> pos[id].first >> pos[id].second;
        board[pos[id].first][pos[id].second] = id; // 각 산타의 위치를 보드에 표시합니다.
        is_live[id] = true;  // 산타가 살아있는지 여부를 표시합니다.
    }

    for(int t = 1; t <= m; t++) {
        int closestX = 10000, closestY = 10000, closestIdx = 0;

        // 살아있는 산타 중 루돌프에 가장 가까운 산타를 찾습니다.
        for(int i = 1; i <= p; i++) {
            if(!is_live[i]) continue;

            pair<int, pair<int, int>> currentBest = { (closestX - rudolf.first) * (closestX - rudolf.first) + (closestY - rudolf.second) * (closestY - rudolf.second), {-closestX, -closestY}};
            pair<int, pair<int, int>> currentValue = {(pos[i].first - rudolf.first) * (pos[i].first - rudolf.first) + (pos[i].second - rudolf.second) * (pos[i].second - rudolf.second), {-pos[i].first, -pos[i].second}};
            
            if(currentValue < currentBest) {
                closestX = pos[i].first;
                closestY = pos[i].second;
                closestIdx = i;
            }
        }

        // 가장 가까운 산타의 방향으로 루돌프가 이동합니다.
        if(closestIdx) {
            pair<int, int> prevRudolf = rudolf;
            int moveX = 0;
            if(closestX > rudolf.first) moveX = 1;
            else if(closestX < rudolf.first) moveX = -1;

            int moveY = 0;
            if(closestY > rudolf.second) moveY = 1;
            else if(closestY < rudolf.second) moveY = -1;

            rudolf.first += moveX;
            rudolf.second += moveY;
            board[prevRudolf.first][prevRudolf.second] = 0;

            // 루돌프의 이동으로 충돌한 경우, 산타를 이동시키고 처리를 합니다.
            if(rudolf.first == closestX && rudolf.second == closestY) {
                int firstX = closestX + moveX * c;
                int firstY = closestY + moveY * c;
                int lastX = firstX;
                int lastY = firstY;

                stun[closestIdx] = t + 1;

                // 만약 이동한 위치에 산타가 있을 경우, 연쇄적으로 이동이 일어납니다.
                while(is_inrange(lastX, lastY) and board[lastX][lastY] > 0) {
                    lastX += moveX;
                    lastY += moveY;
                }

                // 연쇄적으로 충돌이 일어난 가장 마지막 위치에서 시작해,
                // 순차적으로 보드판에 있는 산타를 한칸씩 이동시킵니다.
                while(!(lastX == firstX and lastY == firstY)) {
                    int beforeX = lastX - moveX;
                    int beforeY = lastY - moveY;

                    if(!is_inrange(beforeX, beforeY)) break;

                    int idx = board[beforeX][beforeY];

                    if(!is_inrange(lastX, lastY)) {
                        is_live[idx] = false;
                    }
                    else {
                        board[lastX][lastY] = board[beforeX][beforeY];
                        pos[idx] = {lastX, lastY};
                    }

                    lastX = beforeX;
                    lastY = beforeY;
                }

                points[closestIdx] += c;
                pos[closestIdx] = {firstX, firstY};
                if(is_inrange(firstX, firstY)) {
                    board[firstX][firstY] = closestIdx;
                }
                else {
                    is_live[closestIdx] = false;
                }
            }
        }

        board[rudolf.first][rudolf.second] = -1;

        // 각 산타들은 루돌프와 가장 가까운 방향으로 한칸 이동합니다.
        for(int i = 1; i <= p; i++) {
            if(!is_live[i] || stun[i] >= t) continue;

            int minDist = (pos[i].first - rudolf.first) * (pos[i].first - rudolf.first) + (pos[i].second - rudolf.second) * (pos[i].second - rudolf.second);
            int moveDir = -1;
            
            for(int dir = 0; dir < 4; dir++) {
                int nx = pos[i].first + dx[dir];
                int ny = pos[i].second + dy[dir];
                
                if(!is_inrange(nx, ny) || board[nx][ny] > 0) continue;

                int dist = (nx - rudolf.first) * (nx - rudolf.first) + (ny - rudolf.second) * (ny - rudolf.second);
                if(dist < minDist) {
                    minDist = dist;
                    moveDir = dir;
                }
            }

            if(moveDir != -1) {
                int nx = pos[i].first + dx[moveDir];
                int ny = pos[i].second + dy[moveDir];

                // 산타의 이동으로 충돌한 경우, 산타를 이동시키고 처리를 합니다.
                if(nx == rudolf.first && ny == rudolf.second) {
                    stun[i] = t + 1;

                    int moveX = -dx[moveDir];
                    int moveY = -dy[moveDir];

                    int firstX = nx + moveX * d;
                    int firstY = ny + moveY * d;
                    int lastX = firstX;
                    int lastY = firstY;

                    if(d == 1) {
                        points[i] += d;
                    }
                    else {
                        // 만약 이동한 위치에 산타가 있을 경우, 연쇄적으로 이동이 일어납니다.
                        while(is_inrange(lastX, lastY) and board[lastX][lastY] > 0) {
                            lastX += moveX;
                            lastY += moveY;
                        }

                        // 연쇄적으로 충돌이 일어난 가장 마지막 위치에서 시작해,
                        // 순차적으로 보드판에 있는 산타를 한칸씩 이동시킵니다.
                        while(!(lastX == firstX and lastY == firstY)) {
                            int beforeX = lastX - moveX;
                            int beforeY = lastY - moveY;

                            if(!is_inrange(beforeX, beforeY)) break;

                            int idx = board[beforeX][beforeY];

                            if(!is_inrange(lastX, lastY)) {
                                is_live[idx] = false;
                            }
                            else {
                                board[lastX][lastY] = board[beforeX][beforeY];
                                pos[idx] = {lastX, lastY};
                            }

                            lastX = beforeX;
                            lastY = beforeY;
                        }

                        points[i] += d;
                        board[pos[i].first][pos[i].second] = 0;
                        pos[i] = {firstX, firstY};
                        if(is_inrange(firstX, firstY)) {
                            board[firstX][firstY] = i;
                        }
                        else {
                            is_live[i] = false;
                        }
                    }
                }
                else {
                    board[pos[i].first][pos[i].second] = 0;
                    pos[i] = {nx, ny};
                    board[nx][ny] = i;
                }
            }
        }

        // 라운드가 끝나고 탈락하지 않은 산타들의 점수를 1 증가시킵니다.
        for(int i = 1; i <= p; i++) 
            if(is_live[i]) points[i]++;
    }

    for(int i = 1; i <= p; i++) 
        cout << points[i] << " ";
}
