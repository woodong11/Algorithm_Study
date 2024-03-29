#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

// N <= 100만, S, F <= 1000억
// 실패한 이유 : 
// 1. 강의 시작은 느린데 강의가 빨리 끝나는 경우를 따져주지 않아 failed
// 2. map 이 O(NlogN)으로 정렬되다보니 100만 * 1000 이라서 시간초과 나는 듯 함.
int N;

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    map<int, int> m;
    int a, b;
    int lastTime =0 ;
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> a >> b;
        lastTime = lastTime >= b ? lastTime : b;
        m.insert({a, b});
    }

    int t = 1;
    int result = 0;
    while(1) {
        if(t >= lastTime) break;
        if(m.find(t) == m.end()) {
            t++;
            continue;
        }
        t = m[t];
        result ++;
    }
    cout << result;
   return 0;
}
