#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    int arr[1000002];
    arr[1] = 1;
    arr[2] = 2;
    arr[3] = 3;
    arr[4] = 5;
    if (N <= 4) {
        cout << arr[N];
    }
    else {
        for (int i = 4; i <= N; i++) {
            arr[i] = (arr[i - 1] + arr[i - 2]) % 15746;
        }
        cout << arr[N];
    }


    return 0;
}
