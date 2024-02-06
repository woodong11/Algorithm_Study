#include <string>
#include <vector>
#include <iostream>


using namespace std;

vector<string> v;
int result;

// begin 이랑 v 랑 비교해서 2개 이상 다르면 return 아니면 dfs
void dfs(string s, string target, int level, int count) {
    int cnt = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != target[i]) {
            cnt++;
        }
    }
    if (cnt == 1) {
        result = count + 1;
        return;
    }

    cnt = 0;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] != v[level][i]) cnt++;
        if (cnt > 1) break;
    }
    if (cnt == 1) {
        s = v[level];
        count++;
    }
    else {
        level++;
    }

    dfs(s, target, level, count);
}

int main() {
    vector<string> words;
    int answer = 0;
    int target_in_words = 0;
    string beg = "hit";
    string target = "cog";
    words.push_back("hot");
    words.push_back("dot");
    words.push_back("dog");
    words.push_back("lot");
    words.push_back("log");
    words.push_back("cog");

    // words 를 확인해서 target 이랑 같은게 하나라도 있으면 v 에 푸쉬백
    for (int i = 0; i < words.size(); i++) {
        int cnt = 0;
        if (target == words[i]) {
            target_in_words++;
        }
        for (int j = 0; j < target.length(); j++) {
            if (target[j] == words[i][j]) cnt++;
            if (cnt > 0) break;
        }
        if (cnt != 0) v.push_back(words[i]);

    }

    if (target_in_words == 0) {
        return answer;
    }
    else {
        dfs(beg, target, 0, 0);
        cout << result;
    }

    
}
