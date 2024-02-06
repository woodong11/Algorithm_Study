// This code is for the problem of programmers.co.kr
// https://school.programmers.co.kr/learn/courses/30/lessons/43163
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(string begin, string target, vector<string> words) {
    int en = -1;               // index of target
    vector<int> v[50];         // graph
    int visited[50] = {0,};    // array to check if the node has been visited
    queue<int> q;              // queue for BFS

    // Search target and save its index
    for (int i = 0; i < words.size(); i++) {
        if (target == words[i]) {
            en = i;
            break;
        }
    }

    // If target does not exist, terminate the program
    if (en == -1) {
        return 0;
    }
    
    // Enqueue initial choices
    for (int i = 0; i < words.size(); i++) {
        int cnt = 0;
        for (int j = 0; j < begin.length(); j++) {
            if (begin[j] != words[i][j]) {
                cnt++;
            }
        }
        if (cnt == 1) {
            visited[i] = 1;
            q.push(i);
        }
    }
    
    // Build a graph among words
    for (int i = 0; i < words.size(); i++) {
        for (int j = i + 1; j < words.size(); j++) {
            int cnt = 0;
            for (int k = 0; k < begin.length(); k++) {
                if (words[i][k] != words[j][k]) {
                    cnt++;
                }
            }
            if (cnt == 1) {
                v[i].push_back(j);
                v[j].push_back(i);
            }
        }
    }
    
    // start BFS
    while(!q.empty()) {
        int now = q.front();
        if (now == en) {
            break;
        }
        q.pop();
        for (int i = 0; i < v[now].size(); i++) {
            int next = v[now][i];
            if (visited[next] > 0) {
                continue;
            }
            visited[next] = visited[now] + 1;
            q.push(next);
        }
    }

    return visited[en];
}
