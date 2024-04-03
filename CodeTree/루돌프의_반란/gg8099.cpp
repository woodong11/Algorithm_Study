#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct point {
    int y, x, dir;
};
struct tp { //산타를 위한 구조체로 yx는 좌표, live는 생사유무 0이면죽1이면 살, score는 점수, t는 기절시간
    int y, x, live, score, t;
};
struct di {
    int num, dis, y, x, dir;
};
struct cmp {
    bool operator() (di a, di b) {
        return a.dis > b.dis;
        return a.dir > b.dir;
    }
};
vector<tp> vec[31]; //산타들 정보
point deer;

int map[51][51], dy[] = { -1,0,1,0,-1,1,1,-1 }, dx[] = { 0,1,0,-1,1,1,-1,-1 };
int N, M, P, C, D;

di dist_mv() {
    di val = { 0,999999,0,0 };
    point yx = deer;
    int tmp = 0;
    for (int i = 1; i <= P; i++) {
        if (vec[i][0].live == 0) {
            continue;
        }
        tmp = (deer.y - vec[i][0].y) * (deer.y - vec[i][0].y) + (deer.x - vec[i][0].x) * (deer.x - vec[i][0].x);
        if (val.dis > tmp) {
            val.dis = tmp;
            val.num = i;
            val.y = vec[i][0].y;
            val.x = vec[i][0].x;
        }
        if (val.dis == tmp) {
            if (val.y > vec[i][0].y)
                continue;
            if (val.y == vec[i][0].y && val.x > vec[i][0].x)
                continue;
            val.dis = tmp;
            val.num = i;
            val.y = vec[i][0].y;
            val.x = vec[i][0].x;
        }
    }
    int dir = 0;
    if (yx.y > vec[val.num][0].y) {
        if (yx.x > vec[val.num][0].x)
            dir = 7;
        else if (yx.x == vec[val.num][0].x)
            dir = 0;
        else if (yx.x < vec[val.num][0].x)
            dir = 4;
    }
    else if (yx.y == vec[val.num][0].y) {
        if (yx.x > vec[val.num][0].x)
            dir = 3;
        else if (yx.x < vec[val.num][0].x)
            dir = 1;
    }
    else if (yx.y < vec[val.num][0].y) {
        if (yx.x > vec[val.num][0].x)
            dir = 6;
        else if (yx.x == vec[val.num][0].x)
            dir = 2;
        else if (yx.x < vec[val.num][0].x)
            dir = 5;
    }
    val.y = yx.y + dy[dir];
    val.x = yx.x + dx[dir];
    val.dir = dir;
    return val;
}
void deer_crash(point now) { //충돌하면 산타는 점수를 얻고, 밀려나며, 기절한다. 그리고 연쇄작용
    point next = { 0 };
    if (map[now.y][now.x] == 0) //만약 빈칸이면 그냥 리턴
        return;
    int num = map[now.y][now.x]; //루돌프가 이동한 자리에 산타가 있으면 해당 산타의 번호를 저장
    vec[num][0].score += C;   //점수얻는부분
    vec[num][0].t = M + 2;    //기절 시간 정하기 현재가 M이면 산타가 이동할때 시간이 M>t가 되어야 이동가능
    map[vec[num][0].y][vec[num][0].x] = 0; //어차피 num아니까 기존 산타자리 0처리하고
    vec[num][0].y += dy[now.dir] * C; //충돌 후 산타 좌표 등록
    vec[num][0].x += dx[now.dir] * C;
    next = { vec[num][0].y ,vec[num][0].x , now.dir };
    if (next.y <= 0 || next.x <= 0 || next.y > N || next.x > N) {
        vec[num][0].live = 0;
        return;
    }
    //여기서부터 연쇄작용
    while (1) {
        if (map[next.y][next.x] == 0) {
            map[next.y][next.x] = num;
            break;
        }
        int tmp_num = map[next.y][next.x];
        map[next.y][next.x] = num;
        num = tmp_num;
        //vec[num][0].t = M + 1; //산타끼리 충돌하고 기절시간 조절인데 산타끼리 부딪히고 기절하는지 모르겟음
        vec[num][0].y += dy[now.dir]; //상호작용에서는 한칸만 이동
        vec[num][0].x += dx[now.dir];
        next = { vec[num][0].y ,vec[num][0].x , now.dir }; //이동후 좌표 조절
        if (next.y <= 0 || next.x <= 0 || next.y > N || next.x > N) {
            vec[num][0].live = 0;
            return;
        }
    }

}
void santa_crush(point now, int num) { // now는 부딪친 직후의 산타(지금 방향도 부디칠때의 반대방향)
    point next = { 0 };
    vec[num][0].score += D;
    vec[num][0].t = M + 2;
    vec[num][0].y += dy[now.dir] * D, vec[num][0].x += dx[now.dir] * D;
    next = { vec[num][0].y ,vec[num][0].x , now.dir };
    if (next.y <= 0 || next.x <= 0 || next.y > N || next.x > N) {
        vec[num][0].live = 0;
        return ;
    }
    while (1) {
        if (map[next.y][next.x] == 0) {
            map[next.y][next.x] = num;
            break;
        }
        int tmp_num = map[next.y][next.x];
        map[next.y][next.x] = num;
        num = tmp_num;
        //vec[num][0].t = M + 1;
        vec[num][0].y += dy[now.dir];
        vec[num][0].x += dx[now.dir];
        next = { vec[num][0].y ,vec[num][0].x , now.dir };
        if (next.y <= 0 || next.x <= 0 || next.y > N || next.x > N) {
            vec[num][0].live = 0;
            return;
        }
    }
}
point cal_dist(point now) { //now는 산타좌표
    point up, ri, dw, le;
    point result = { 0,0, };
    up = { now.y + dy[0],now.x + dx[0] }, ri = { now.y + dy[1],now.x + dx[1] }, dw = { now.y + dy[2],now.x + dx[2] }, le = { now.y + dy[3],now.x + dx[3] };
    int rlwns_dist = (deer.y - now.y) * (deer.y - now.y) + (deer.x - now.x) * (deer.x - now.x); //기준거리 << 이거리보다 길어지는애들은 고려 x
    int up_dist = (deer.y - up.y) * (deer.y - up.y) + (deer.x - up.x) * (deer.x - up.x);
    int ri_dist = (deer.y - ri.y) * (deer.y - ri.y) + (deer.x - ri.x) * (deer.x - ri.x);
    int dw_dist = (deer.y - dw.y) * (deer.y - dw.y) + (deer.x - dw.x) * (deer.x - dw.x);
    int le_dist = (deer.y - le.y) * (deer.y - le.y) + (deer.x - le.x) * (deer.x - le.x);
    priority_queue<di, vector<di>, cmp> pq; //int num, dis, y, x, dir;
    pq.push({ 0,up_dist,0,0,0 });
    pq.push({ 0,ri_dist,0,0,1 });
    pq.push({ 0,dw_dist,0,0,2 });
    pq.push({ 0,le_dist,0,0,3 });
    while (!pq.empty()) {
        di tmp = pq.top();
        pq.pop();
        if (rlwns_dist <= tmp.dis)
            continue;
        point next = { 0 };
        next.y = now.y + dy[tmp.dir], next.x = now.x + dx[tmp.dir];
        next.dir = tmp.dir;
        if (map[next.y][next.x] >= 1)
            continue;
        else if (map[next.y][next.x] == 0) {
            next.dir = 6;
            return next;
        }
        else if (map[next.y][next.x] == -1) {
            next.dir = (next.dir + 2) % 4;
            return next;
        }
    }
    point x = { 0,0,5 };
    return x;

}
void santa_mv() {//temp.dir이 -1이면 산타가 루돌프랑 부디침, 5이면 안착
    for (int i = 1; i <= P; i++) {//산타 이동
        if (vec[i][0].live == 0 || vec[i][0].t > M)
            continue;
        point temp = cal_dist({ vec[i][0].y, vec[i][0].x, 0 });
        if (temp.dir == 5)
            continue;
        else if (temp.dir <= 3) {
            map[vec[i][0].y][vec[i][0].x] = 0;
            vec[i][0].y = temp.y, vec[i][0].x = temp.x;
            santa_crush(temp, i);
        }
        else {
            map[vec[i][0].y][vec[i][0].x] = 0;
            vec[i][0].y = temp.y, vec[i][0].x = temp.x;
            map[vec[i][0].y][vec[i][0].x] = i;
        }
    }
}
int T; //T가 M대신해줄거
void input() { //입력 부분
    cin >> N >> T >> P >> C >> D;
    int a, b;  //사슴 좌표
    cin >> a >> b;
    deer = { a,b,0 };
    map[a][b] = -1; //루돌프 위치는 -1로 표현
    for (int i = 0; i < P; i++) { //산타들 위치 받기
        int num, y, x;
        cin >> num >> y >> x;
        tp tmp = { y,x,1,0,-1 };
        vec[num].push_back(tmp);
        map[y][x] = num;
    }
}

int main() {
    input();
    while (1) { //동작 부분으로 live가 1인게 하나도 없을때까지 동작
        int flag = 0; //live표현하려고 하나라도 있으면 while문 동작
        M++; //M은 0부터 시작해서 1번게임이 끝나기 전에 점수 받기
        di goal = dist_mv();//루돌프랑 산타 거리측정 휴 루돌프가 이동한 좌표.
        map[deer.y][deer.x] = 0;//움직이기전 deer에 움직인 후 goal을 넣어주기전 기존 자리에 0처리
        deer = { goal.y,goal.x, goal.dir }; //움직인 후 좌표를 deer에
        deer_crash(deer); // 루돌프 이동했는데 산타 있는지 없는지하고 있으면 충돌
        map[deer.y][deer.x] = -1; // 루돌프 위치는 -1
        santa_mv();
        //산타가 움직였는데 루돌프 있으면 충돌 + 충돌 후 이동 + 연쇄작용 + 기절
        for (int i = 1; i <= P; i++) {
            if (vec[i][0].live != 1)
                continue;
            vec[i][0].score++;
            if (vec[i][0].live == 1)
                flag = 1;
        }
        if (flag == 0)
            break;
        if (T == M) {
            break;
        }
    }

    for (int i = 1; i <= P; i++) {
        cout << vec[i][0].score << " ";
    }

    return 0;
}
