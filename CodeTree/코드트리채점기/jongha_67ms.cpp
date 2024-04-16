#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <unordered_map>

using namespace std;

// url = 도메인/번호 -> 도메인이 같으면 (start시간 + 채점에 걸린 시간 * 3)초까지 채점 불가
// url 이 같은 문제가 채점 대기큐에 있으면 추가되지 않음.

// 200 : 채점 추가
// 300 : 채점 시작
// 400 : 채점 종료
// 500 : 채점 대기 문제 수 출력

struct Test {
    int num, time, idx;
    string url;

    bool operator<(Test other) const {
        if (num != other.num) return num > other.num;
        return time > other.time;
    }
};

struct Url_check {
    int time;
    bool is_grading = false;
};

struct Grid {
    int time;
    string url;
};

// cnt 는 unable_url 에 있는 개수
int Q, N, cnt;
string u0;
Grid grid[50000];
priority_queue<Test> grader_waiting;
priority_queue<int, vector<int>, greater<int>> grader;
priority_queue<pair<int, Test>, vector<pair<int, Test>>, greater<pair<int, Test>>> time_waiting;
unordered_map<string, priority_queue<Test>> unable_url;
unordered_map<string, Url_check> url_time;
unordered_map<string, bool> waiting_url;

// 채점기 준비
void order1() {
    cin >> N >> u0;

    for (int i = 0; i < N; i++) {
        grader.push(i);
    }

    int idx = u0.find("/");

    grader_waiting.push({ 1, 0, idx, u0 });
    waiting_url[u0] = true;
}

// 채점추가 : 채점 우선순위 p의 번호가 작을 수록, 대기 큐에 들어온 시간이 빠를수록 높음.
void order2() {
    int t, p;
    cin >> t >> p >> u0;

    auto it = waiting_url.find(u0);
    if (it != waiting_url.end() && it->second) return;
    int idx = u0.find("/");

    grader_waiting.push({ p, t, idx, u0 });
    waiting_url[u0] = true;
}

// 채점 요청 :
void order3() {
    int t;
    cin >> t;
    if (grader.empty()) return;

    while (!time_waiting.empty()) {
        pair<int, Test> a = time_waiting.top();

        if (a.first <= t) {
            grader_waiting.push(a.second);
            time_waiting.pop();
        }
        else {
            break;
        }
    }

    Test test;
    string temp;
    string temp2;
    while (!grader_waiting.empty()) {
        test = grader_waiting.top();
        temp = test.url;
        string temp3 = temp.substr(0, test.idx);

        auto it = url_time.find(temp3);
        if (it != url_time.end()) {
            if (it->second.time > t) {
                time_waiting.push(make_pair(it->second.time, test));
                grader_waiting.pop();
            }
            else if (it->second.is_grading) {
                unable_url[temp3].push(test);
                cnt++;
                grader_waiting.pop();
            }
            else {
                temp2 = temp3;
                break;
            }
        }
        else {
            temp2 = temp3;
            break;
            
            return;
        }
    }

    if (grader_waiting.empty()) return;

    int a = grader.top();
    grader.pop();
    grader_waiting.pop();

    grid[a] = { t, temp2 };
    url_time[temp2].is_grading = true;
    waiting_url[test.url] = false;
}

// 채점 종료 :
void order4() {
    int t, j_id;

    cin >> t >> j_id;

    int t_id = j_id - 1;
    if (grid[t_id].time == 0) return;

    int gap = t - grid[t_id].time;
    url_time[grid[t_id].url] = { t + gap * 2, false };

    auto it = unable_url.find(grid[t_id].url);
    if (it != unable_url.end() && !it->second.empty()) {
        grader_waiting.push(it->second.top());
        it->second.pop();
        cnt--;
    }
    
    grid[t_id] = { 0, };
    grader.push(t_id);
}

// 채점 대기 큐 조회 :
void order5() {
    int t;
    cin >> t;
    cout << grader_waiting.size() + cnt + time_waiting.size() << "\n";
}

int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> Q;

    int a;
    for (int i = 0; i < Q; i++) {
        cin >> a;

        if (a == 400) {
            order4();
        }
        else if (a == 200) {
            order2();
        }
        else if (a == 300) {
            order3();
        }
        else if (a == 500) {
            order5();
        }
        else if (a == 100) {
            order1();
        }
        else {
            cout << i << "error\n";
        }
    }

    return 0;
}
