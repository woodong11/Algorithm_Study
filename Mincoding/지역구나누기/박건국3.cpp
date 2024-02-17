#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <cstdlib>

using namespace std;

int cnt, visited[8], map[11][11], T, N, total_sum, result, used[8], flag, result_answer;
int visit[8];
struct value {
    vector<int> yx;
    int sum;
};
struct cmp { //pq를 써서 sum의 최소 순대로 나열
    bool operator () (value a, value b) {
        return a.sum > b.sum;
    }
};
priority_queue<value, vector<value>, cmp> pq;
vector<int> city, temp;

void dfs(int now, int level, int goal) {
    if (level == goal) {
        result = 1;
        flag = 1;
        return;
    }
    for (int i = 0; i < 11; i++)
    {
        if (map[now][i] == 0)
            continue;
        if (used[i] == 0)
            continue;
        if (visit[i] == 1)
            continue;
        visit[i] = 1;
        level++;
        dfs(i, level, goal);
        if (flag == 1)
            return;
    }

}
void check() { //여기서 test조합이 (0)이 들어왔으면 먼저 확인 후 나머지가 서로간에 연결 가능한지 확인하는 곳
    int pq_size = pq.size();
    for (int i = 0; i < pq_size; i++) {
        value team1 = pq.top();
        pq.pop();
        memset(used, 0, sizeof(used));
        for (int i = 0; i < team1.yx.size(); i++)
        {
            used[team1.yx[i]] = 1;
        }
        for (int i = 0; i < team1.yx.size(); i++) {
            visit[team1.yx[i]] = 1;
            dfs(team1.yx[i], 1, team1.yx.size());
            memset(visit, 0, sizeof(visit));
            if (result == 1) {
                flag = 0;
                break;
            }
        }
        if (result == 1) {
            result = 0;
            value team2 = {};
            for (int i = 0; i < N; i++)
            {
                if (used[i] == 0)
                {
                    team2.yx.push_back(i);
                }
            }
            memset(used, 0, sizeof(used));
            for (int i = 0; i < team2.yx.size(); i++)
            {
                used[team2.yx[i]] = 1;
            }
            for (int i = 0; i < team2.yx.size(); i++)
            {
                visit[team2.yx[i]] = 1;
                dfs(team2.yx[i], 1, team2.yx.size());
                memset(visit, 0, sizeof(visit));
                if (result == 1) {
                    flag = 0;
                    break;
                }
            }
            if (result == 1) {
                result_answer = team1.sum;
                result = 0;
                break;
            }
        }
    }
}
void make(int level) {
    if (cnt == level) { //cnt가 level이 되면 마을 조합이 하나 완성 된거임
        int temp_sum = 0;
        int result_sum = 0;
        for (int i = 0; i < temp.size(); i++) { //temp는 마을 조합인데(0) ,(1, 2, 3)일 경우 각 마을의 유권자수 구하려고
            temp_sum += city[temp[i]];
        }
        result_sum = abs(total_sum - temp_sum * 2); // 지역구a - 지역구b = 지역구a -(총유권자-지역구a)
        pq.push({ temp,result_sum });
        return;
    }
    for (int i = 0; i < N; i++) { //여기서 마을의 조합을 짜기
        if (visited[i] == 1)
            continue;
        visited[i] = 1;
        cnt++;
        temp.push_back(i);
        make(level);
        visited[i] = 0;
        temp.pop_back();
        cnt--;
    }

}
void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        city.push_back(x);
        total_sum += x;
    }
}
void init()
{
    for (int i = 0; i < 8; i++) {
        visited[i] = 0;
        used[i] = 0;
    }
    total_sum = 0, result = 0;
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            map[i][j] = 0;
        }
    }
    pq = {}, city = {};
}
int main() {
    cin >> T;
    for (int i = 1; i <= T; i++) {
        input();
        for (int i = 1; i < N; i++) {
            cnt = 0;
            make(i);
        }

        int de = 1;
        check();
        init();
        cout << '#' << i << ' ' << result_answer << endl;
    }
    return 0;
}
