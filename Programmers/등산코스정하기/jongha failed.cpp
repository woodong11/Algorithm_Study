#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <climits>

using namespace std;

struct Point {
    int end;
    int depth;

    bool operator<(Point right) const {
        return depth < right.depth;
    }
};

bool compare(Point& a, Point& b) {
    return a.depth < b.depth;
}

int start, end, dat[50001];
int from, e, depth;
priority_queue<Point> pq;


vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<vector<Point>> myanswer(n + 1, vector<Point>(n + 1, { INT_MAX, INT_MAX }));
    vector<vector<Point>> mypath(n + 1);

    for (vector<int> a : paths) {
        from = a[0];
        e = a[1];
        depth = a[2];

        mypath[from].push_back({ e, depth });
    }

    for (int i = 0; i < gates.size(); i++) {
        Point now, next;
        pq.push({ gates[i], 0 });

        while (!pq.empty()) {
            now.end = pq.top().end;
            now.depth = pq.top().depth;
            pq.pop();

            for (int j = 0; j < mypath[now.end].size(); j++) {
                int tempd = mypath[now.end][j].depth;
                int tempe = mypath[now.end][j].end;
                if (tempd >= myanswer[now.end][tempe].depth) {
                    continue;
                }

                myanswer[now.end][tempe] = { tempe, tempd };
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int h = 0; h < 10; h++) {
            cout << myanswer[i][h].end << " " << myanswer[i][h].depth;
        }
        cout << "\n";
    }

    return answer;
}
