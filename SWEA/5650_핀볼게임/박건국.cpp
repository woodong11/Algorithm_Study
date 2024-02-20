#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
 
int T, N, map[101][101], maxval = 0, cnt, step_cnt, flag;
int dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 }; //next = now + dy[now.way]
struct point {
    int y;
    int x;
    int way;
};
struct tele {
    int hole_num;
    int y;
    int x;
};
vector<tele> all_telehole;
point temp = { -1 };
void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] >= 6 && map[i][j] <= 10) {
                all_telehole.push_back({ map[i][j],i,j });
            }
        }
    }
}
int check_block(int from, int block_num) // 여기서 1~5번 블럭으로 들어갔을 때 들어가는 방향과 해당 블럭의 넘버
{
    if (block_num == 1) {
        if (from == 0) return 2;
        if (from == 1) return 3;
        if (from == 2) return 1;
        if (from == 3) return 0;
    }
    else if (block_num == 2) {
        if (from == 0) return 1;
        if (from == 1) return 3;
        if (from == 2) return 0;
        if (from == 3) return 2;
    }
    else if (block_num == 3) {
        if (from == 0) return 3;
        if (from == 1) return 2;
        if (from == 2) return 0;
        if (from == 3) return 1;
    }
    else if (block_num == 4) {
        if (from == 0) return 2;
        if (from == 1) return 0;
        if (from == 2) return 3;
        if (from == 3) return 1;
    }
    else if (block_num == 5) {
        if (from == 0) return 2;
        if (from == 1) return 3;
        if (from == 2) return 0;
        if (from == 3) return 1;
    }
}
void check_hall(point tel, int tel_num) //만약 웜홀에 들어가면 전체 웜홀 모아놓은 벡터에서 웜홀 번호만 같은거중에 좌표 다른거를 temp에 넣어놓고, 그 temp를 next에 다시 넣어줌;
{
    for (int i = 0; i < all_telehole.size(); i++) {
        if (all_telehole[i].hole_num == tel_num && (all_telehole[i].y != tel.y || all_telehole[i].x != tel.x)) {
            temp.way = tel.way, temp.y = all_telehole[i].y, temp.x = all_telehole[i].x;
            flag = 1;
            break;
        }
    }
}
void start(point st) {
    for (int i = 0; i < 4; i++) {
        point now = st;
        now.way = i; //i는 방향성으로 먼저 st로 입력된 좌표에서 모든 방향으로 출발하려고
        point next = now;
        while (1) {
            step_cnt++;
            next.y = next.y + dy[next.way], next.x = next.x + dx[next.way]; //now.way 방향이 가르키는 곳으로 한칸 이동
            if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N) {   // 1.먼저 벽을 만났을 경우, 해당 방향에서 정 반대방향으로 방향 바꿔주기
                next.y = next.y - dy[next.way], next.x = next.x - dx[next.way];
                next.way = (next.way + 2) % 4, cnt++;
            }
            //cout << "test1" << endl;
            if (map[next.y][next.x] <= 5 && map[next.y][next.x] >= 1) {   //2.블록을 만난경우 블럭 숫자에 맞는 값으로 이동하기
                next.way = check_block(next.way, map[next.y][next.x]), cnt++;
            }
            if (temp.y != next.y || temp.x != next.x || temp.way != next.way) // 웜홀에서 한칸이상 이동한 경우or 방향이 바뀐경우에는 다시 웜홀을 탈 수 있게
                flag = 0;
            if (flag == 0) {
                if (map[next.y][next.x] <= 10 && map[next.y][next.x] >= 6) {//3.웜홀을 만난경우 방향은 유지해주면서 한칸씩 갈준비
                    check_hall(next, map[next.y][next.x]);
                    next = temp;
                }
            }
            //cout << "test2" << endl;
            if (map[next.y][next.x] == -1) { //4. 블랙홀 을 만난경우 break
                break;
            }
            //cout << "test3" << endl;
            if (/*step_cnt >= 2 &&*/ next.y == now.y && next.x == now.x) { //5. 두칸이상 이동한 경우 자기좌표로 오면 끝내기
                break;
            }
            //cout << now.y << "--" << now.x << "---" << now.way << endl;
            //cout << "test4" << endl;
            //cout << next.y << "--" << next.x << "---" << next.way << "---" << cnt << endl;
        }
        step_cnt = 0;
        if (maxval < cnt) {
            maxval = cnt;
        }
        cnt = 0;
    }
}
void init() {
    memset(map, 0, sizeof(map));
    maxval = 0;
    flag = 0;
    temp = { -1,-1,-1 };
    all_telehole = {};
}
 
int main() {
    cin >> T;
    for (int x = 1; x <= T; x++) {
        //cout << "test5" << endl;
        input();
        //cout << "test6" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (map[i][j] == 0) { //0인 지점에서만 출발좌표를 넣어줄거임
                    point st;
                    st.y = i, st.x = j;
                    start(st);
                }
            }
        }
        cout << '#' << x << ' ' << maxval << endl;
        init();
    }
}
