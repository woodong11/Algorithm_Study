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
    string tmp;
    if (a == b) return;
    // 같은 부모이면 RETURN 시간초과가 나고 나서 추가해줬는데
    // 시간초과는 풀림. 근데 13 ~ 16, 18 실패 뜸
    if (tar1 == tar2) return;
    visited[tar2] = tar1;
    // tar1 엔 값이 없고, tar2 에 값이 있을 때 tar1에 덮어주기
    if (findmap.count(tar1) == 0 && findmap.count(tar2) > 0) {
        tmp = findmap[tar2];
    }
    else {
        um.erase(findmap[tar2]);
        findmap.erase(tar2);
    }
    // tar2가 이미 병합되어 있는 상태라면 그 요소들을 tar1 에 저장
    if (mergev[tar2].size() > 0) {
        visited[tar2] = tar1;
        mergev[tar1].push_back(tar2);
        if (findmap.count(tar2) > 0) {
            // findmap[tar2] = findmap[tar1]; 하단으로 바꿈. 결과는 똑같음.
            um.erase(findmap[tar2]);
            findmap.erase(tar2);
            findmap[tar1] = tmp;
            um[tmp].insert(tar1);
        }
        for (int i = 0; i < mergev[tar2].size(); i++) {
          // findmap 과 um의 동기화가 이루어지지 않아서 예외 케이스를 발견했는데 고쳐도 점수 더 틀림.
          // 
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
            um.erase(findmap[tar2]);
            findmap.erase(tar2);
            findmap[tar1] = tmp;
            um[tmp].insert(tar1);
        }
    }
    mergev[tar2].clear();
}

void unmerge(int a) {
    int tar = find(a);
    // 병합이 없으면 return
    if (mergev[tar].size() == 0) return;
    // 부모의 값을 a로 이동 (UNMERGE 조건 때문)
    string tem = findmap[tar];
    findmap[a] = tem;
    if (um.find(tem) != um.end()) {
        um[tem].clear();
        um[tem].insert(a);
    }
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

        if (commands[i] == "UPDATE CCCVV VVCC") {
            int addg = 0;
        }

        split(commands[i]);

        if (spl[0] == "UPDATE" && spl.size() == 4) {
            idx = find(stoi(spl[1]) * 50 + stoi(spl[2]));
            val1 = spl[3];
            if (findmap.count(idx) != 0) {
                string temps = findmap[idx];
                temp = um[temps];
                um.erase(temps);
                um[val1] = temp;
                for (int tp : temp) {
                    findmap[tp] = val1;
                }
            }
            else {
                findmap[idx] = val1;
                um[val1].insert(idx);
            }
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
    vector<string> com = { "MERGE 1 1 1 3", "MERGE 1 4 2 5", "MERGE 3 6 4 5", "MERGE 5 4 7 6", "MERGE 8 4 9 9", "PRINT 1 1", "UPDATE 1 1 A", "UPDATE 1 4 B", "UPDATE 5 4 C", "MERGE 7 6 2 5", "PRINT 2 5", "UPDATE B D", "PRINT 5 4", "MERGE 2 5 7 6", "PRINT 2 5", "UNMERGE 5 4", "PRINT 7 6"};
    vector<string> v = solution(com);

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << "\n";
    }

    return 0;
}
