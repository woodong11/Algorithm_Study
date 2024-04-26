#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int N;
long long B;
int arr[100000];

int main(int argc, char** argv)
{
    cin >> N >> B;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + N);
    long long left = arr[0];
    long long right = arr[N - 1] + (int)sqrt(B);
    long long now = (left + right) / 2;
    long long answer = 0;
    while (left <= right) {
        long long cost = 0;
        for (int i = 0; i < N; i++) {
            if (arr[i] >= now) break;
            cost += pow(now - arr[i], 2);
            if (cost > B) {
                right = now - 1;
                break;
            }
        }
        if (cost <= B) {
            left = now + 1;
            answer = now;
        }
        now = (left + right) / 2;
    }
    cout << answer;
   return 0;
}
