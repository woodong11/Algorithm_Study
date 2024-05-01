#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <cmath>
#include <climits>

using namespace std;

struct Grid {
    int q, time, x, sushi_cnt, guest_cnt;
};

struct Point {
    int time, x, n;
};

struct Sushi {
    int time, x;
    string name;
};

struct SSU {
    int time;
    string name;

    bool operator<(SSU other) const {
        return time > other.time;
    }
};

int L, Q, t, x, n;
string name;
Grid grid[100000];
unordered_map<string, Point> guest;
queue<Sushi> q;
priority_queue<SSU> pq;
int sushi_cnt, guest_cnt, sushi_m, guest_m;

int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> L >> Q;

    int a;
    for (int i = 0; i < Q; i++) {
        cin >> a;

        if (a == 100) {
            cin >> t >> x >> name;
            sushi_cnt++;

            q.push({ t, x, name });
        }
        else if (a == 200) {
            cin >> t >> x >> name >> n;
            guest_cnt++;

            guest[name] = { t, x, n };
        }
        else {
            cin >> t;
            grid[i] = { a, t, 0, sushi_cnt, guest_cnt};
        }
    }

    while (!q.empty()) {
        Sushi now = q.front();
        q.pop();

        int t_gap = guest[now.name].time - now.time;

        if (t_gap > 0) {
            now.time += t_gap;
            now.x = (now.x + t_gap) % L;
        }

        int eated = guest[now.name].x - now.x;

        if (eated < 0) {
            eated += L;
        }
        
        eated += now.time;
        pq.push({ eated, now.name });
    }

    for (int i = 0; i < Q; i++) {
        if (grid[i].q != 300) continue;

        while (!pq.empty()) {
            SSU now = pq.top();

            if (now.time <= grid[i].time) {
                pq.pop();
                sushi_m++;
                guest[now.name].n--;
                if (guest[now.name].n == 0) guest_m++;
            }
            else {
                break;
            }
        }

        cout << grid[i].guest_cnt - guest_m << " " << grid[i].sushi_cnt - sushi_m << "\n";
    }


    return 0;
}
