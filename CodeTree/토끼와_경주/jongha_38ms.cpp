#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>

using namespace std;

struct Point {
    int y;
    int x;
};

struct Rabbit {
    int y, x, jump_c;
    long long other_score;
    int my_score, num, jump_p;
};

// 좌표 우선순위
struct compareP {
    bool operator()(const Point a, const Point b) {
        if (a.y + a.x != b.y + b.x) return a.y + a.x < b.y + b.x;
        else if (a.y != b.y) return a.y < b.y;
        else return a.x < b.x;
    }
};

// 토끼 이동 우선순위
struct compareR {
    bool operator()(const Rabbit* a, const Rabbit* b) {
        if (a->jump_c != b->jump_c) return a->jump_c > b->jump_c;
        else if (a->y + a->x != b->y + b->x) return a->y + a->x > b->y + b->x;
        else if (a->y != b->y) return a->y > b->y;
        else if (a->x != b->x) return a->x > b->x;
        else return a->num > b->num;
    }
};

// 턴이 끝난 후 S 점수를 받을 우선순위
struct compareS {
    bool operator()(const Rabbit* a, const Rabbit* b) {
        if (a->y + a->x != b->y + b->x) return a->y + a->x < b->y + b->x;
        else if (a->y != b->y) return a->y < b->y;
        else if (a->x != b->x) return a->x < b->x;
        else return a->num < b->num;
    }
};

// Q : 명령, N, M : 맵크기, K : 이벤트 턴, S : 이벤트 턴이 끝난 후 보너스 점수, L : 이동거리 변경, P : 토끼 대가리수
int N, M, K, Q, S, L, P;
// pidi : 토끼 인덱스, di : 이동거리, pidt : 토끼 인덱스
int pidi, pidt, di;
//priority_queue<Point, vector<Point>, compareP> p_pq;
priority_queue<Rabbit*, vector<Rabbit*>, compareR> r_pq;
priority_queue<Rabbit*, vector<Rabbit*>, compareS> s_pq;
unordered_map<int, Rabbit> um;

Point next_p(Point now, int d) {
    int m_m = M - 1, n_m = N - 1;

    //p_pq = priority_queue<Point, vector<Point>, compareP>();
    Point result = { -1, -1 };

    for (int i = 0; i < 4; i++) {
        Point next = now;
        // x++
        if (i == 0) {
            int td = d %( 2 * n_m);

            if (td >= N - next.y) {
                td -= N - next.y;
                next.y = N;
            }
            else {
                next.y += td;
                td = 0;
            }

            if (td >= next.y - 1) {
                td -= (next.y - 1);
                next.y = 1;
            }
            else {
                next.y -= td;
                td = 0;
            }

            next.y += td;
        }
        // y++
        else if (i == 1) {
            int td = d % (2 * n_m);

            if (td >= next.y - 1) {
                td -= (next.y - 1);
                next.y = 1;
            }
            else {
                next.y -= td;
                td = 0;
            }

            if (td >= N - next.y) {
                td -= (N - next.y);
                next.y = N;
            }
            else {
                next.y += td;
                td = 0;
            }

            next.y -= td;
        }
        // x--
        else if (i == 2) {
            int td = d % (2 * m_m);

            if (td >= M - next.x) {
                td -= M - next.x;
                next.x = M;
            }
            else {
                next.x += td;
                td = 0;
            }

            if (td >= next.x - 1) {
                td -= (next.x - 1);
                next.x = 1;
            }
            else {
                next.x -= td;
                td = 0;
            }

            next.x += td;
        }
        // y--
        else {
            int td = d % (2 * m_m);

            if (td >= next.x - 1) {
                td -= (next.x - 1);
                next.x = 1;
            }
            else {
                next.x -= td;
                td = 0;
            }

            if (td >= M - next.x) {
                td -= (M - next.x);
                next.x = M;
            }
            else {
                next.x += td;
                td = 0;
            }

            next.x -= td;
        }

        if (result.y + result.x < next.y + next.x) {
            result = next;
        }
        else if(result.y + result.x == next.y + next.x) {
            if (result.y < next.y) {
                result = next;
            }
            else if (result.y == next.y) {
                if (result.x < next.x) {
                    result = next;
                }
            }
        }
    }

    return result;
}

priority_queue<Rabbit*, vector<Rabbit*>, compareS> tmp_pq;
void turn() {
    s_pq = priority_queue<Rabbit*, vector<Rabbit*>, compareS>();
    tmp_pq = priority_queue<Rabbit*, vector<Rabbit*>, compareS>();

    for (int i = 0; i < K; i++) {
        Rabbit* now = r_pq.top();
        r_pq.pop();
        Point t_now = { now->y, now->x };
        Point t_next = next_p(t_now, now->jump_p);

        now->other_score += (t_next.y + t_next.x);
        now->jump_c++;
        now->y = t_next.y;
        now->x = t_next.x;
        r_pq.push(now);
        tmp_pq.push(now);
    }

    while (!tmp_pq.empty()) {
        s_pq.push(tmp_pq.top());
        tmp_pq.pop();
    }
    Rabbit* now = s_pq.top();
    now->my_score += S;
}

vector<pair<int, int>> v;
long long result() {
    Rabbit* now;

    long long sum = 0;
    while (!r_pq.empty()) {
        now = r_pq.top();
        r_pq.pop();
        v.push_back(make_pair(now->my_score, now->other_score));
        sum += now->other_score;
    }

    long long result = 0;

    for (int i = 0; i < v.size(); i++) {
        long long ab = sum - v[i].second + v[i].first;
        result = result >= ab ? result : ab;
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> Q;

    int a;
    for (int i = 0; i < Q; i++) {
        cin >> a;
        if (a == 200) {
            cin >> K >> S;

            turn();
        }
        else if (a == 300) {
            cin >> pidt >> L;
            um[pidt].jump_p *= L;
        }
        else if (a == 400) {
            cout << result();
        }
        else if (a == 100) {
            cin >> N >> M >> P;

            for (int j = 0; j < P; j++) {
                cin >> pidi >> di;

                Rabbit r = { 1, 1, 0, 0, 0, pidi, di };
                um[pidi] = r;

                r_pq.push(&um[pidi]);
            }
        }
    }



    return 0;
}
