#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int distance;
};

struct cmp {
    bool operator()(Edge a, Edge b) {
        if (a. distance == b.distance) {
            return a.to > b.to;
        }
        return a.distance > b.distance;
    }
};

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer;
    
    sort(summits.begin(), summits.end());

    vector<vector<Edge>>v(n + 1);
    for (vector<int> i : paths) {
        v[i[0]].push_back({ i[1], i[2] });
        v[i[1]].push_back({ i[0], i[2] });
    }

    vector<int> gate(n + 1);
    vector<int> summit(n + 1);

    for (int i : gates) {
        gate[i] = 1;
    }

    for (int i : summits) {
        summit[i] = 1;
    }

    int ans_n = 21e8;
    int ans_i = 21e8;
    for (int i : summits) {
        vector<int> visited(n + 1);
        int currentIntensity = 0;
        int end = 21e8;
        priority_queue<Edge, vector<Edge>, cmp> pq;
        for (Edge j : v[i]) {
            pq.push(j);
        }
        visited[i] = 1;
        while (!pq.empty()) {
            Edge now = pq.top();
            pq.pop();
            if (visited[now.to] == 1 || summit[now.to] == 1) continue;
            visited[now.to] = 1;
            currentIntensity = max(currentIntensity, now.distance);
            if (gate[now.to] == 1) {
                if (currentIntensity < ans_i) {
                    ans_n = i;
                    ans_i = currentIntensity;
                }
                break;
            }
            for (Edge j : v[now.to]) {
                pq.push(j);
            }
        }
    }

    answer.push_back(ans_n);
    answer.push_back(ans_i);
    return answer;
}
