#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
 
struct point {
    int y, x, num, dir; //yx는 좌표에 num은 미생물 수 , dir 은 방향
};
struct temp_point {
    int index, num;
};
vector<point> mesang;
vector<temp_point> temp_mesang;
int T, N, M, K;
int map[101][101], parent[1001], dy[] = { 0,-1,1,0,0 }, dx[] = { 0,0,0,-1,1 };
 
int find(int tar) {
    if (tar == parent[tar])
        return tar;
    int ret = find(parent[tar]);
    parent[tar] = ret;
    return ret;
}
void setunion(int a, int b) { // 이게 a,b가 masnag에 인덱스 값
    int t1 = find(a);
    int t2 = find(b);
    if (t1 == t2)
        return;
    parent[t2] = t1;
    mesang[a].num += mesang[b].num;
    mesang[b].num = 0;
    mesang[b].dir = mesang[a].dir;
}
void mapset() {
    for (int i = 0; i < N; i++) {
        map[0][i] = -1, map[N - 1][i] = -1, map[i][0] = -1, map[i][N - 1] = -1;
    }
    //for (int i = 0; i < K; i++) {
    //  map[mesang[i].y][mesang[i].x] = mesang[i].num;
    //}
}
void parent_set() {
    for (int i = 0; i < K; i++) {
        parent[i] = i;
    }
}
void init() {
    memset(map, 0, sizeof(map));
    mesang = {};
    memset(parent, 0, sizeof(parent));
    temp_mesang = {};
}
int dir_func(int a) {
    if (a == 1 || a == 3)
        return a + 1;
    else if (a == 2 || a == 4)
        return a - 1;
}
void solve() {
    int temp[101][101] = { 0 };
    for (int i = 0; i < mesang.size(); i++) {
        mesang[i].y = mesang[i].y + dy[mesang[i].dir], mesang[i].x = mesang[i].x + dx[mesang[i].dir];
        temp[mesang[i].y][mesang[i].x]++;
        if (map[mesang[i].y][mesang[i].x] == -1) { // 미생물이 이동한 후 의 위치가 빨간약이면 (미생물 수)/2 에다가 방향 반대로
            mesang[i].num = mesang[i].num / 2, mesang[i].dir = dir_func(mesang[i].dir);
        }
    }
    for (int i = 0; i < N; i++) { //여기서 temp에 2이상인 값들은 temp_mesang에 넣어서 mesang 인덱스로 parent 값을 비교 후 다르다면
        //union해서  num값들을 비교해서 하나로 몰아주기 >> 이러면 다음번에 벡터 전체 찾을필요 없음 
        for (int j = 0; j < N; j++) {
            if (temp[i][j] >= 2) {//temo 돌면서 2 이상이면 temp_mesang에 인덱스,미생물 수, 미생물 방향 넣기. 
                for (int x = 0; x < mesang.size(); x++) { // 여기서 temp에 넣었음
                    if (mesang[x].y == i && mesang[x].x == j)
                        temp_mesang.push_back({ x,mesang[x].num });
 
                }
                int max_num = 0, max_index = 0;
                for (int x = 0; x < temp_mesang.size(); x++) { // 여기서 max_num에 에 해당하는 부분에 인덱스 저장;
                    if (temp_mesang[x].num > max_num)
                        max_num = temp_mesang[x].num, max_index = temp_mesang[x].index;
                }
                for (int x = 0; x < temp_mesang.size(); x++) { //이론상 여기까지 하면 이동하면서 곂쳐진 부분들에 대한 미생물 군집들이 가장 큰 개체에 속하고 방향성이 가장 큰 군집을 따르게 된다.
                    if (mesang[temp_mesang[x].index].num == 0)
                        continue;
                    if (find(max_index) == find(temp_mesang[x].index))
                        continue;
                    setunion(max_index, temp_mesang[x].index);
                }                                           //이제 이렇게 묶인 군집들은 전체 vec를 돌면서 숫자 비교를할 필요가 없음
                temp_mesang = {};
            }
        }
    }
}
int main() {
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cin >> N >> M >> K;
        for (int i = 0; i < K; i++) {
            parent_set();
            int diry, dirx, me_num, dir_yx;
            cin >> diry >> dirx >> me_num >> dir_yx;
            mesang.push_back({ diry,dirx,me_num,dir_yx }); // mesang에 미생물 정보 받기.
        }
        mapset(); // 맵 설정 (미생물들이랑 테두리 작)
        for (int i = 0; i < M; i++) { //시간M만큼 이동
            solve();
        }
        //마지막에 mesang 돌면서 result += mesang[i].num ; 로 누적합 구하기.
        int result = 0;
        for (int i = 0; i < mesang.size(); i++) {
            if (mesang[i].num != 0)
                result += mesang[i].num;
        }
        cout << '#' << tc << ' ' << result << endl;
        init();
    }
}
