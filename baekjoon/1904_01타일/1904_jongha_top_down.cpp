#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N;
long long memo[15746];

long long dp(int level) {
    if (memo[level] != 0) return memo[level];

    long long a = dp(level - 2);
    long long b = dp(level - 1);
    
    memo[level] = a + b;

    return memo[level];
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin >> N;

    memo[1] = 1;
    memo[2] = 2;

    cout << dp(N) % 15746;


    return 0;
}
