#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>

using namespace std;

struct Point {
    int start;
    int end;

    bool operator<(Point right) const {
        if (end != right.end) return end > right.end;
        return start > right.start;
    }
};


// N <= 100만, S, F <= 1000억
int N;

priority_queue<Point> pq;

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    map<int, int> m;
    int a, b;
    int lastTime = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        pq.push({ a, b });
    }

    int t = 0;
    int result = 0;
    while (!pq.empty()) {
        Point now = pq.top();
        pq.pop();
        if (t > now.start) {
            continue;
        }
        t = now.end;

        result++;
    }
    cout << result;
    return 0;
}
