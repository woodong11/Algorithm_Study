13 ~ 16, 18 FAILED

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

vector<string> spl;
unordered_map<string, unordered_set<int>> um;
unordered_map<int, string> findmap;
unordered_set<int> temp;
string sstr;

vector<vector<int>> mergev(2602);
int visited[2602];

int find(int a) {
    if (a == visited[a]) return a;
    int tar = find(visited[a]);
    visited[a] = tar;
    return tar;
}

// 병합
void merge(int a, int b) {
    int tar1 = find(a);
    int tar2 = find(b);
    if (a == b) return;
    // 같은 부모이면 RETURN 시간초과가 나고 나서 추가해줬는데
    // 시간초과는 풀림. 근데 13 ~ 16, 18 실패 뜸
    if (tar1 == tar2) return;
    visited[tar2] = tar1;
    // tar1 엔 값이 없고, tar2 에 값이 있을 때 tar1에 덮어주기
    if (findmap.count(tar1) == 0 && findmap.count(tar2) > 0) {
        findmap[tar1] = findmap[tar2];
    }
    // tar2가 이미 병합되어 있는 상태라면 그 요소들을 tar1 에 저장
    if (mergev[tar2].size() > 0) {
        visited[tar2] = tar1;
        mergev[tar1].push_back(tar2);
        if (findmap.count(tar2) > 0) {
            // findmap[tar2] = findmap[tar1]; 하단으로 바꿈. 결과는 똑같음.
            findmap.erase(tar2);
        }
        for (int i = 0; i < mergev[tar2].size(); i++) {
            int val = mergev[tar2][i];
            mergev[tar1].push_back(val);
            visited[val] = tar1;
            if (findmap.count(val) > 0) {
                // findmap[val] = findmap[tar2];
                findmap.erase(val);
            }
        }
    }
    else {
        mergev[tar1].push_back(tar2);
        visited[tar2] = tar1;
        if (findmap.count(tar2) > 0) {
            // findmap[tar2] = findmap[tar1];
            findmap.erase(tar2);
        }
    }
    mergev[tar2].clear();
}

void unmerge(int a) {
    int tar = find(a);
    // 병합이 없으면 return
    if (mergev[tar].size() == 0) return;
    // 부모의 값을 a로 이동 (UNMERGE 조건 때문)
    findmap[a] = findmap[tar];
    // 부모 기준으로 병합됐던 애들을 해체하는 작업.
    for (int i = 0; i < mergev[tar].size(); i++) {
        int val = mergev[tar][i];
        if (val == a) {
            findmap.erase(tar);
            visited[val] = val;
            continue;
        }
        findmap.erase(val);
        visited[val] = val;
    }
    mergev[tar].clear();
}

char c[10], d[10];

void split(string s) {
    stringstream ss(s);
    string mys;

    while (ss >> mys) {
        spl.push_back(mys);
    }
}



vector<string> solution(vector<string> commands) {
    vector<string> answer;
    int a;
    int idx, idx2;
    string val1, val2;

    // visited 인덱스로 초기화
    for (int i = 0; i < 2602; i++) {
        visited[i] = i;
    }
    // 인덱스 접근을 2차원을 1차원으로 변환해서 접근함.
    for (int i = 0; i < commands.size(); i++) {
        spl.clear();

        split(commands[i]);

        if (spl[0] == "UPDATE" && spl.size() == 4) {
            idx = find(stoi(spl[1]) * 50 + stoi(spl[2]));
            val1 = spl[3];
            um[val1].insert(idx);
            findmap[idx] = val1;
        }
        else if (spl[0] == "UPDATE") {
            val1 = (spl[1]);
            val2 = spl[2];

            if (um.find(val1) != um.end()) {
                temp = um[val1];
                um.erase(val1);

                for (int tp : temp) {
                    um[val2].insert(tp);
                    int tpidx = find(tp);
                    findmap[tpidx] = val2;
                }
            }
        }
        else if (spl[0] == "MERGE") {
            idx = stoi(spl[1]) * 50 + stoi(spl[2]);
            idx2 = stoi(spl[3]) * 50 + stoi(spl[4]);

            merge(idx, idx2);
        }
        else if (spl[0] == "UNMERGE") {
            idx = stoi(spl[1]) * 50 + stoi(spl[2]);

            unmerge(idx);
        }
        else if (spl[0] == "PRINT") {
            int resultidx = find(stoi(spl[1]) * 50 + stoi(spl[2]));
            //idx = mergev[find(resultidx)];

            if (findmap.count(resultidx) > 0) {
                answer.push_back(findmap[resultidx]);
            }
            else {
                answer.push_back("EMPTY");
            }
        }
    }
    return answer;
}

int main() {
    vector<string> inputv = { "UPDATE 50 50 ERRR", "UPDATE 50 47 GGR", "MERGE 50 50 47 47", "MERGE 48 49 49 50", "MERGE 49 50 47 47", "MERGE 50 50 50 50", "UPDATE ERRR CCCVV", "PRINT 50 50", "PRINT  49 50", "PRINT 47 47", "PRINT 1 4", "UNMERGE 49 50", "PRINT 49 50", "PRINT 48 49"};
    vector<string> resultt = solution(inputv);

    for (int i = 0; i < resultt.size(); i++) {
        cout << resultt[i] << "\n";
    }

    return 0;
}
