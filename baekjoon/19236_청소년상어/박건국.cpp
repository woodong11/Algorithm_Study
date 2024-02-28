#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct point_fish {
    int y, x, num, dir, live;
};
struct point_shark {
    int y, x, dir;
};
struct temp_fish_point {
    int y, x, num;
};
struct cmp {
    bool operator () (point_fish a, point_fish b) {
        return a.num > b.num;
    }
};
int dy[] = { -1,-1,0,1,1,1,0,-1 }, dx[] = { 0,-1,-1,-1,0,1,1,1 };
int maxval;
//생선 방향성 정해주기

//디버깅용
vector<int> visited;

point_fish dir_check(point_fish now, int(&map)[4][4]) {
    for (int i = 0; i < 8; i++) {
        point_fish next = now;
        next.y = now.y + dy[now.dir];
        next.x = now.x + dx[now.dir];

        if (next.y < 0 || next.x < 0 || next.y >= 4 || next.x >= 4) { //맵 밖으로 나가면
            now.dir = (now.dir + 1) % 8;
            continue;
        }
        if (map[next.y][next.x] == -1) { // 다음칸에 상어가 있으면
            now.dir = (now.dir + 1) % 8;
            continue;
        }
        return next;
    }
    return now;
}

void dfs(point_shark now_shark, vector<point_fish> vec_fish, int(&map)[4][4], int sum) {
    int temp_map[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp_map[i][j] = map[i][j];
        }
    }
    vector<point_fish> temp_vec_fish = vec_fish;
    //생선들의 위치 바꿔주기
    //끝나는 조건으로 상어가 다음에 갈 곳이 없을때
    for (int i = 1; i <= 16; i++) {
        if (temp_vec_fish[i].live == 0)
            continue;


        point_fish tmp_now = temp_vec_fish[i];//움직일 생선
        point_fish tmp_next = { 0 }; // 움직임 당할 생선

        //아래에서 기존의 now가 x,y좌표가 next로 이동해있음
        //now에는 ㄹㅇ now의 xy좌표
        temp_vec_fish[i] = dir_check(temp_vec_fish[i], temp_map);
        //next에는 now에서 xy좌표만 next된거임
        tmp_next.num = temp_vec_fish[temp_map[temp_vec_fish[i].y][temp_vec_fish[i].x]].num;
        temp_vec_fish[tmp_next.num].y = tmp_now.y, temp_vec_fish[tmp_next.num].x = tmp_now.x;
        temp_map[temp_vec_fish[tmp_next.num].y][temp_vec_fish[tmp_next.num].x] = temp_vec_fish[tmp_next.num].num;
        temp_map[temp_vec_fish[i].y][temp_vec_fish[i].x] = temp_vec_fish[i].num;        
    }
    for (int t = 1; t <= 3; t++) {
        point_shark next_shark = now_shark;
        next_shark.y = next_shark.y + dy[now_shark.dir] * t;
        next_shark.x = next_shark.x + dx[now_shark.dir] * t;
        if (temp_map[next_shark.y][next_shark.x] == 0 || (next_shark.y < 0 || next_shark.x < 0 || next_shark.y >= 4 || next_shark.x >= 4)) {
            maxval = max(sum, maxval);
            continue;
        }
        //temp_num에 다음좌표의 생선인덱스를 담아놓을거임
        int temp_num = temp_map[next_shark.y][next_shark.x];

        //순서대로 상어.dir에 상어가 먹은 방향넣기, sum에 먹은상어값 넣기,
        // 먹은 상어live = 0, 먹은생선자리로 이동, 이동전 자리는 0,
        next_shark.dir = temp_vec_fish[temp_num].dir;
        sum += temp_num;
        temp_vec_fish[temp_num].live = 0;
        temp_map[next_shark.y][next_shark.x] = -1;
        temp_map[now_shark.y][now_shark.x] = 0;

        dfs(next_shark, temp_vec_fish, temp_map, sum);

        sum -= temp_num;
        temp_vec_fish[temp_num].live = 1;
        temp_map[next_shark.y][next_shark.x] = temp_num;
        temp_map[now_shark.y][now_shark.x] = -1;
    }
}


int main() {
    priority_queue<point_fish, vector<point_fish>, cmp> pq;

    int map[4][4];

    //맵 입력
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int y, x, num, dir;
            cin >> num >> dir;
            map[i][j] = num;
            y = i, x = j;
            pq.push({ y, x, num, dir - 1, 1 });
        }
    }
    vector<point_fish> vec_fish;
    vec_fish.push_back({ 0,0,0,0,0 });

    while (!pq.empty()) {
        point_fish temp_fish = pq.top();
        pq.pop();
        vec_fish.push_back(temp_fish); // num 순서대로 저장된 fish를 vec에 인덱스처럼
    }
    point_shark shark_now = { 0,0,vec_fish[map[0][0]].dir };
    int result = map[0][0];
    vec_fish[map[0][0]].live = 0;
    map[0][0] = -1;

    dfs(shark_now, vec_fish, map, result); //맵에는 상어 위치에 -1, 먹힌 생선은 live가 0

    cout << maxval;


    return 0;

}


