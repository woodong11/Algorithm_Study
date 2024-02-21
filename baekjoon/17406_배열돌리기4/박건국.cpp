#include <iostream>
#include <vector>

using namespace std;
int N, M, K, map[51][51], temp1[51][51], temp2[51][51];
int dy[] = { 0, 1, 0, -1 }, dx[] = { 1, 0, -1, 0 }, minval = 21e8;;
int temp_value;
struct point {
    int y;
    int x;
};
struct arr {
    int r;
    int c;
    int s;
};
vector<arr> vec;
vector<int> order;
int visited[7];

void mapset()
{
    for (int i = 0; i < 51; i++)
    {
        for (int j = 0; j < 51; j++)
        {
            temp2[i][j] = temp1[i][j];
        }
    }
}
void turn(vector<int> st) { //now백터에는 st[0]=0,[1]=1이 들어가있음
    for (int x = 0; x < st.size(); x++) {//그럼 vec[st[i]]는 vec[st[0]] = (3 4 2) , vec[st[1]] = (4 2 1)
        arr test = vec[st[x]]; // now.r = 3 , now.c = 4, now.s = 2
        for (int y = test.s; y >= 1; y--)        {
            point yx = { test.r - y, test.c - y }; //이동시 시작좌표
            for (int i = 0; i < 4; i++){
                for (int j = 1; j <= 2 * y; j++){        
                    temp1[yx.y + dy[i]][yx.x + dx[i]] = temp2[yx.y][yx.x]; //한칸씩 이동하는거니까 그냥 맵을 temp해서 다음칸에 있는거 대입하는 느낌
                    yx.y += dy[i], yx.x += dx[i]; //여기서 좌표 한칸씩 앞으로
                }
            }
        }
        mapset(); // temp2를 temp1이랑 같게해서 다시 대입하려고
    }
}
void check() {
    for (int i = 1; i <= N; i++) {
        int sum = 0;
        for (int j = 1; j <= M; j++) {
            sum += temp1[i][j];
            temp2[i][j] = temp1[i][j] = map[i][j];
        }
        if (sum < minval)
            minval = sum;
    }
}
void dfs(int level) { //여기서 level이 회전체 갯수에 도달하면 회전시작
    if (level == K) {
        turn(order); //지금 turn에는 0,1이 들어감 그리고 다음 턴에는 1,0 들어감
        check();    //이건 최소 minval구하기 위한 행count
        return;
    }
    for (int i = 0; i < K; i++) {
        if (visited[i] == 1)
            continue;
        order.push_back(i); //여기서는 order백터에 012 021 102느낌으로 순서 정해줌
        visited[i] = 1;
        dfs(level + 1);
        order.pop_back();
        visited[i] = 0;
    }
}
void input() { //그냥 입력 n:행,m:열,k:회전체 개수
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> map[i][j];
            temp1[i][j] = temp2[i][j] = map[i][j]; //temp에 먼저 돌리고 리셋할때 map으로
        }
    }
}
int main() {
    input();
    for (int i = 0; i < K; i++) {
        arr now;//rcs를 받을 now구조체 선언 (3 4 2),(4 2 1)
        cin >> now.r >> now.c >> now.s;
        vec.push_back(now); //이 전역vec에 (3 4 2),(4 2 1)넣음
    }                        //회전할때 dfs에서 중복순열 느낌으로 넣어주려고
    dfs(0);
    cout << minval;
    return 0;
}
