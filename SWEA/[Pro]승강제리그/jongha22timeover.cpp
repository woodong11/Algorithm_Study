// 리그의 개수 L, id 는 0 ~ L -1  - > id 가 낮을 수록 우수한 리그
// N명의 선수, id 는 0 ~ N - 1 -> 능력이 높을수록, ID 가 작을수록 우수한 선수

// 초기에 N/L 명씩 차례대로 배치
// N은 L의 배수, N/L 은 홀수 값을 가짐.

// 리그 승강제
// 능력이 가장 좋은 선수와 상위 리그의 능력이 가장 안 좋은 선수와 교체
// 0번 리그의 능력이 가장 좋은 선수와 L - 1번 리그의 능력이 가장 좋지 않은 선수는 이동하지 않음.

// 트레이드 제도
// 능력이 가장 좋은 선수를 상위 리그의 중간급 능력의 선수와 맞교환하는 제도
// (M+1)/ 2 번째 선수가 중간급 선수
// 0번 리그의 능력이 가장 좋은 선수와 L - 1 번 리그의 중간급 능력의 선수는 이동하지 않음.

// N : 9 ~ 39990, L : 3 ~ 10, mAbility[] : 1 ~ 10000, N / L : 3 ~ 3999



#include <set>
#include <queue>
#include <iterator>
#include <iostream>

using namespace std;

set<long long> s[4000];
// 각 리그 인원수
int nl, middlePlayer;
int largen, largel;

void init(int N, int L, int mAbility[])
{
    nl = N / L;
    largen = N, largel = L;

    for (int i = 0; i < L; i++) {
        s[i].clear();
    }

    int idx = -1;
    for (int i = 0; i < N; i++) {
        if (i % nl == 0) idx++;
        long long val = mAbility[i] * 40000 - i;
        s[idx].insert(val);
    }
}

// 전체리그에서 이동한 선수들의 ID값의 합을 반환 ( 최대 500회 )
int move()
{
    queue<int> q;
    int a, b;
    long long result = 0;
    for (int i = 1; i < largel; i++) {
        auto it = s[i].end();
        advance(it, -1);
        q.push(*it);
        q.push(*s[i - 1].begin());
    }
    for (int i = 0; i < largel - 1; i++) {
        a = q.front();
        q.pop();
        b = a % 40000 == 0 ? 0 : 40000 - a % 40000;
        result += (b);
        s[i].insert(a);
        s[i + 1].erase(a);

        a = q.front();
        q.pop();
        b = a % 40000 == 0 ? 0 : 40000 - a % 40000;
        result += (b);
        s[i + 1].insert(a);
        s[i].erase(a);
    }
    return result;
}

// 전체 리그에서 이동한 선수들의 ID 값의 합을 반환 ( 최대 1000회 )
int trade()
{
    queue<int> q;
    long long result = 0, a, b;
    middlePlayer = (nl + 1) / 2 - 1;
    for (int i = 1; i < largel; i++) {
        auto it = s[i].end();
        advance(it, -1);
        q.push(*it);
        it = s[i - 1].begin();
        advance(it, middlePlayer);
        q.push(*it);
    }
    for (int i = 0; i < largel - 1; i++) {
        a = q.front();
        q.pop();
        b = a % 40000 == 0 ? 0 : 40000 - a % 40000;
        result += (b);
        s[i].insert(a);
        s[i + 1].erase(a);
        a = q.front();
        q.pop();
        b = a % 40000 == 0 ? 0 : 40000 - a % 40000;
        result += (b);
        s[i + 1].insert(a);
        s[i].erase(a);
    }
    return result;
}
