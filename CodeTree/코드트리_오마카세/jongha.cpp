#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <cmath>
#include <climits>

using namespace std;

struct t_x {
    int t, x, next_t;
};

struct Point {
    queue<t_x> q;
};

struct Guest {
    int x, n, now_time;
    string name;
};

int L, Q;
int timer, x, n;
int cnt = 0;
string name;
queue<Guest> guest;
unordered_map<string, Point> sushi;

int main() {
    // 여기에 코드를 작성해주세요.
    int a = 0;

    cin >> L >> Q;

    for (int i = 0; i < Q; i++) {
        cin >> a;

        // 회전

        // 입력 처리
        if (a == 100) {
            cin >> timer >> x >> name;

            sushi[name].q.push({ timer, x, INT_MAX });
            cnt++;
        }
        else if (a == 200) {
            cin >> timer >> x >> name >> n;

            guest.push({ x, n, timer, name });
        }
        else if (a == 300) {
            cin >> timer;

            int guest_size = guest.size();
            if(cnt == 0 || guest.size() == 0) {
                cout << guest.size() << " " << cnt << "\n";
                continue;
            }

            for (int i = 0; i < guest_size; i++) {
                Guest now = guest.front();
                int for_size = sushi[now.name].q.size();
                if(for_size == 0) {
                    guest.pop();
                    guest.push(now);
                    continue;
                }
                guest.pop();

                for(int i = 0; i < for_size; i++) {
                    t_x now_sushi = sushi[now.name].q.front();
                    sushi[now.name].q.pop();

                    if(now_sushi.next_t != INT_MAX) {
                        if(now_sushi.next_t <= timer) {
                            now.n--;
                            cnt--;
                        } else {
                            sushi[now.name].q.push(now_sushi);
                        }
                        continue;
                    }

                    if(now.now_time > now_sushi.t) {
                        now_sushi.x = (now.now_time + now_sushi.x - now_sushi.t) % L;
                        now_sushi.t = now.now_time;
                    }
                    int now_position = (timer + now_sushi.x - now_sushi.t);

                    if((now_sushi.x <= now.x && now_position >= now.x) || (now_sushi.x > now.x && now_position >= now.x + L)){
                        now.n--;
                        cnt--;
                        continue;
                    }

                    int next_t = INT_MAX;
                    if(now_sushi.x <= now.x) {
                        next_t = timer + now.x - now_position;
                    } else {
                        next_t = timer + now.x + L - now_position;
                    }
                    now_sushi = {timer, now_position, next_t};
                    sushi[now.name].q.push(now_sushi);
                }

                if (now.n == 0) continue;
                now.now_time = timer;
                guest.push(now);
            }

            cout << guest.size() << " " << cnt << "\n";
        }
        else {
            cout << "error\n";
            return 0;
        }

    }

    return 0;
}
