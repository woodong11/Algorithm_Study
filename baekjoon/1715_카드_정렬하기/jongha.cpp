#include<iostream>
#include<vector>
#include<map>
#include<cmath>
#include<queue>

using namespace std;

int N;
long long a;
priority_queue<long long, vector<long long>, greater<long long>> pq;

int main(int argc, char** argv)
{
    cin >> N;
    
    for (int i = 0; i < N; i++) {
        cin >> a;
        pq.push(a);
    }

    long long result = 0;
    while (!pq.empty()) {
        long long a = pq.top();
        pq.pop();

        if (!pq.empty()) {
            long long b = pq.top();
            pq.pop();
            pq.push(a + b);
            result += (a + b);
        }
    }

    cout << result;

    return 0;
}
