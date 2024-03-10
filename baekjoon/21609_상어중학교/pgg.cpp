//이거 처음에 풀다 만거
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
    int y, x;
};
struct block {
    int y, x, num;
};

int map[20][20], dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
int N, M, score;
vector<point> max_loca;
void input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
}


block find(int idx, int(&abc)[20][20]) {
    int arr[20][20];
    block findmax = {21,21, 0};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = abc[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i][j] == idx) {
                vector<point> temp_loca = {};
                block ab = { 21,21,1 }; //대표 블록
                queue<point> tmp;
                tmp.push({ i,j });
                temp_loca.push_back({ i,j });
                arr[i][j] = 6;
                

                while (!tmp.empty()) {
                    point now = tmp.front();
                    tmp.pop();
                    for (int x = 0; x < 4; x++) {
                        point next = { 0 };
                        next.y = now.y + dy[x];
                        next.x = now.x + dx[x];
                        if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N)
                            continue;
                        if (arr[next.y][next.x] == idx || arr[next.y][next.x] == 0) {
                            temp_loca.push_back({ next.y,next.x });
                            ab.num++;
                            arr[next.y][next.x] = 6;
                            if (ab.y > next.y)
                                ab.y = next.y, ab.x = next.x;
                            if (ab.y == next.y && ab.x > next.x)
                                ab.y = next.y, ab.x = next.x;                            
                        }
                    }
                }
                if (ab.num > findmax.num ||(ab.num == findmax.num && ab.y < findmax.y)) {
                    max_loca = {};
                    max_loca = temp_loca;
                    findmax = ab;           
                }
            }
        }
    }
    return findmax;
}
int func(block now, int idx) {
    queue<point> q;
    int cnt = 0;
    q.push({ now.y,now.x });
    int abc = map[now.y][now.x];
    map[now.y][now.x] = 10;
    while (!q.empty()) {
        point now = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            point next = { 0 };
            next.y = now.y + dy[i];
            next.x = now.x + dx[i];
            if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N)
                continue;
            if (map[next.y][next.x] == abc || map[next.y][next.x] == 0) {
                map[next.y][next.x] = 10;
                cnt++;
            }
        }
    }
    return cnt * cnt;
}

void gravi() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 10) {
                if()
            }
        }
    }
}

int main() {
    input();
    while (1) {
        block now = { 0 };
        int maxidx = 0;
        for (int i = 1; i <= M; i++) {
            block tmp = { 0 };
            tmp = find(i, map);
            if (tmp.num > now.num ||(tmp.num == now.num && tmp.y < now.y)) {
                now = tmp;
                maxidx = i;
            }
        }
        score += func(now, maxidx);
        gravi();


        if (now.num < 2)
            break;
    }

}
