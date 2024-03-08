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
        if (a.distance == b.distance) {
            return a.to > b.to;
        }
        return a.distance > b.distance;
    }
};

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer;

    sort(summits.begin(), summits.end());

    vector<vector<Edge>>v(n + 1); // 인접 리스트
    for (vector<int> i : paths) {
        v[i[0]].push_back({ i[1], i[2] });
        v[i[1]].push_back({ i[0], i[2] });
    }

    vector<int> gate(n + 1); // DAT for gates
    vector<int> summit(n + 1); // DAT for summits

    for (int i : gates) {
        gate[i] = 1;
    }

    for (int i : summits) {
        summit[i] = 1;
    }

    int ans_n = 21e8;
    int ans_i = 21e8;
    for (int i : summits) { // Prim's Algorithm 변형, 봉우리 기준으로 탐색
        int currentIntensity = 0;
        priority_queue<Edge, vector<Edge>, cmp> pq;
        vector<int> visited(n + 1);
        for (Edge j : v[i]) {
            pq.push(j);
        }
        visited[i] = 1;
        while (!pq.empty()) {
            Edge now = pq.top();
            pq.pop();
            if (now.distance > ans_i) { // pq에 의해 가장 짧은 거리가 선택됨, 아직 입구 도착을 못했는데 현재보다 intensity가 크다면 가지치기
                break;
            }
            if (visited[now.to] == 1 || summit[now.to] == 1) { // 이미 간 곳, 다른 봉우리는 가지 않는다
                continue;
            }
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
