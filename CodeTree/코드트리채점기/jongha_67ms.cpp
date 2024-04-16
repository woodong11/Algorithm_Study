// 시간 단축을 위해서 한 일.
// 1. string 을 Key값으로 하는 um 을 3개 만듦
// 1-1. priority_queue<Test> 를 value로 갖는 unable_url 은 grader_waiting에서 우선순위로 꺼냈을 때, 해당 url 이 작업 중일 경우 저장
// 1-2. Url_check 를 value로 갖는 url_time 은 해당 url 이 t(현재시간) - grid[idx](시간시간) + gap * 2 또는 채점 중인지를 저장
// 1-3. waiting_url 은 해당 url(url_id까지 있는) 이 중복돼서 들어왔는지 확인해주기 위한 bool 저장

// 2. grader_waiting 에서 우선순위로 나왔으나 해당 url 이 채점 중일 경우를 처리해주는 법
// 2-1. url_time 에서 해당 url 을 탐색해서 time과 is_grading(채점 중) 인지를 체크
// 2-2. 가능할 경우 채점기에 넣기
// 2-3. 채점 중이라서 불가능할 경우 unable_url에 저장(pq로 저장되기 때문에 나중에 해당 url이 채점 완료 처리됐을 때 하나씩 꺼내서 grader_waiting 에 다시 넣어주면됨.
// 2-4. 시간이 경과하지 않아서 불가능한 경우 time_waiting에 저장 (pair<int, Test> 로 first=time, second=Test로 저장해서 time이 낮은 순으로 정렬되게끔 함.) 
// 2-5. 여기서 결과를 출력할 때 unable_url 의 pq 요소의 개수 + grader_waiting 의 개수 + time_waiting의 개수를 합해야 하는데 unable_url 의 경우 u_m 타입이라 전체 탐색하지 않고, 따로 int cnt를 둬서 추가될때 +, 빠질 때 -로 해결함.

// 3. 채점기의 개수
// 3-1. 채점기의 개수 N 만큼 for문을 돌려서 grader 에 저장해주고, int 가 낮은 순으로 정렬되도록 함.
// 3-2. 해당 채점기를 사용할 때 Grid grid 에 인덱스로 접근 후 시간과 해당 url 을 저장해줌.
// 3-3. 채점이 완료되면 해당 인덱스를 비워주고, grader에 다시 저장해줌.

// 그 외.
// 1. url를 find('/') 를 통해 해당 idx 를 저장해줌 (바로 '\0' 로 바꿔주고 처리하려 했으나 url 이 완전 똑같은 경우를 처리해줘야 돼서 이렇게 함. 또한 '\0' 로 바꿔줄 경우 해시에서 그 뒤 문자열까지 읽어버려서 포기.)
// 2. substr 로 새로운 string 변수에 저장해주고 해시 처리함. ( 이유는 1번 이유때문 )

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
