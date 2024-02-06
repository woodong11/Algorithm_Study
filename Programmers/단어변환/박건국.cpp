#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;
int visited[51];
int flag = 0;
int cmp(string now, string next) {
    int cnt = 0;
    for (int i = 0; i < now.length(); i++)
    {
        if (now[i] != next[i])
            cnt++;
    }
    if (cnt <= 1)
        return 0;
    else
        return 1;

}

int bfs(int level, string begin, string target, vector<string> words) {
    queue<string> q;
    queue<int> p;
    q.push(begin);
    int cnt = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
        string now = q.front();
        if (!p.empty()) {
            visited[p.front()] = 1;
            p.pop();
        }
        if (now == target)
        {
            flag = 1;
            break;
        }
        q.pop();
        for (int i = 0; i < words.size(); i++) {
            int cmpnum = cmp(now, words[i]);
            if (visited[i] == 1)
                continue;
            if (cmpnum == 0)
            {
                p.push(i);
                q.push(words[i]);
            }
        }
        }
        if (flag==1)
        {
            break;
        }
        cnt++;
    }

    if (flag == 1)
        return cnt;
    else
        return 0;
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;

    answer = bfs(0, begin, target, words);
    return answer;
}
