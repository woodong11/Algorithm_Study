#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;


int N, M;
char how;
int a, b, gap;
int result;
bool escape = false;

struct Point {
    int first;
    int second;
    int gap;
};

vector<Point> v;
queue<int>  q;

void init() {
    v.clear();
    q = queue<int>();
}

void check(int targetA, int temp, int targetB, int gap) {
    if (a == temp) {
        escape = true;
        return;
    }
    for (int i = 0; i < v.size(); i++) {
        if (result != 0 || escape) return;
        if (v[i].first == targetA) {
            if (v[i].second == targetB) {
                result = gap + v[i].gap;
                return;
            }

            if (q.empty()) {
                q.push(targetA);
            }
            else {
                q.push(v[i].second);
                q.pop();
            }
            check(temp, v[i].second, targetB, gap + v[i].gap);
        }

    }
}

void input(int t_c) {
    cin >> N >> M;
    cout << "#" << t_c << " ";
    for (int i = 0; i < M; i++) {
        cin >> how;

        if (how == '!') {
            cin >> a >> b >> gap;
            v.push_back({ a, b, gap });
            v.push_back({ b, a, -gap });
        }
        else if (how == '?') {
            cin >> a >> b;

            check(a, 0, b, 0);

            if (escape || result == 0) {
                cout << "UNKNOWN" << " ";
                escape = false;
            }
            else {
                cout << result << " ";
                result = 0;
            }
        }
    }
    init();
    cout << "\n";
}


int main() {
    int T;

    cin >> T;

    for (int t_c = 1; t_c <= T; t_c++) {

        input(t_c);

    }


    return 0;
}
