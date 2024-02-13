#include <iostream>
#include <queue>
#include <vector>
#include <array>

using namespace std;
struct levelx {
    int fi;
    int se;
    int th;
    int fo;
};
struct point {
    int y;
    int x;
};
point noww;

int N, W, H, T, startnum, maxval;
int map[13][15], temp[13][15];
int dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
array<int, 4> now;
vector<array<int, 4>> vec;



void tempreset()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            temp[i][j] = map[i][j];
        }
    }
}
void input()
{
    cin >> N >> W >> H;
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < H; j++)
        {
            cin >> map[i][j];
            temp[i][j] = map[i][j];
            if (map[i][j] != 0)
                startnum++; // 이건 기존에 있던 벽돌 수로 startnum - cnt 가 max보다 크면 많은 벽돌 부순거
        }
    }
}
//check는 총 부신 벽돌의 수.
int check()
{
    int cnt = 0;
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < H; j++)
        {
            if (temp[i][j] != 0)
                cnt++;
        }
    }
    return cnt;
}

//(BFS)여기에서 구슬이 맞은 부분의 시작점으로 한다 << 그럼 이 함수에서 모든블럭을 터침.
void BFS(point st)
{
    queue<point> q;
    int k = map[st.y][st.x];
    if (k == 1) //만약에 시작 부분이 1이면 그 칸만 0으로 만들고 BFS는 끝
    {
        temp[st.y][st.x] = 0;
    }
    else    //1이 아니면 k-1번째 까지 블럭을 0으로 만든다. 이때 블럭이 0이면 그냥 넘어가고 0이 아니면 0으로 만든다. 
    {       //대신 k-1번째 에서는 0,1이 아닌지 확인 후 아니면 다시 BFS를 돌려서 반복
        temp[st.y][st.x] = 0; //k!=1이라 시작 지점은 0으로 바꾼 후 시작
        q.push(st);
        while (!q.empty())
        {
            noww = q.front();  //시작 좌표를 now에 넣는다.
            q.pop();

            for (int j = 0; j < 4; j++) //일단 방향먼저 정하고 2이면 한칸만, 3이상이면 해당 방향으로 그 이상 가도록 설정
            {
                point next = { 0 };
                int count = 1;    //이거는 k-1번째에 도착했을때 해당 지점의 좌표에 있는 숫자를 파악하여 BFS를 돌릴지 말지 결정하기 위해서 설정
                next.y = noww.y + dy[j];
                next.x = noww.x + dx[j];
                if (next.y < 0 || next.x < 0 || next.y >= W || next.x >= H)  //맵 벗어나면 그냥 다음 방향으로 바로 가기위한 가지치기
                    continue;
                if (k >= 2) {    //이거는 2 이상이면 한칸씩 더 가면서 해당 지점이 0,1 이 아니면 BFS들어가도록 설정
                    for (int i = 0; i < k - 1; i++)
                    {
                        next.y = next.y + dy[j];         //여기는 한칸씩 이동
                        next.x = next.x + dx[j];
                        count++;                        //count는 칸 이동한 수로 k와 같아지면 해당 지점 좌표를 탐색함.
                        if (next.y < 0 || next.x < 0 || next.y >= W || next.x >= H)
                            continue;
                        if (count == k)                    //이제 k칸 이동하면 해당 좌표 탐색
                        {
                            if (temp[next.y][next.x] == 1) //해당 좌표가 1이면 그냥 그 좌표 지점만 0으로 설정
                                temp[next.y][next.x] = 0;
                            else                              //1이 아니면 그 칸에서 해당 좌표 수만큼 이동해야 하니까 다시 BFS
                                BFS(next);
                        }
                        else
                        {
                            temp[next.y][next.x] = 0; // 이건 count가 k에 도달하기 전까지는 그냥 0으로 해버리기.
                        }
                    }
                }

            }
        }
    }
}

//(rearange)이건 BFS끝나면 블럭 내리기
void rearange()
{
    for (int i = W - 1; i >= 0; i--)
    {
        for (int j = 0; j < H; j++)
        {
            if (temp[i][j] == 0) //아랫칸부터 탐색하는데 0 발견시 해당열을 탐색 시작하여 0이 아닌 부분을 만나면 0발견한 부분의 숫자와 바꿈.
            {
                for (int a = i; a >= 0; a--)
                {
                    if (temp[a][j] != 0)
                    {
                        temp[i][j] = temp[a][j];
                        temp[a][j] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void arr(int level)
{
    if (level == N)
    {
        vec.push_back(now);
        return;
    }

    for (int i = 0; i < H; i++)
    {
        now[level] = i;
        arr(level + 1);
        now[level] = 0;
    }
}

void go(array<int, 4> arr1)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < W; j++)
        {
            if (temp[j][arr1[i]] != 0)
            {
                point st;
                st = { j,arr1[i] };
                BFS(st);
                rearange();
                break;
            }
        }
    }
}
void allreset()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            map[i][j] = 0;
        }
    }
    startnum = 0, maxval = 0;
    vec = {}, now = {}, noww = {};
    for (int i = 0; i < 4; i++)
    {
        now[i] = 0;
    }
}


int main()
{
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        input();
        arr(0);
        for (int j = 0; j < vec.size(); j++)
        {
            go(vec[j]);
            int cnt = check();
            if (maxval < startnum - cnt)
            {
                maxval = startnum - cnt;
            }
            tempreset();
        }
        cout << '# ' << i << maxval << endl;
        allreset();
    }
    return 0;
}
