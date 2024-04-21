#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;

    long long arr[1000] = { 0 };
    arr[1] = arr[2] = arr[3] = 1;
    arr[4] = arr[5] = 2;
    int maxval = 5; 
    for (int t = 0; t < N; t++) {
        int n;
        cin >> n;

        if (n <= maxval) { 
            cout << arr[n] << endl;
        }
        else { 
            for (int i = maxval + 1; i <= n; i++) {
                arr[i] = arr[i - 1] + arr[i - 5];
            }
            maxval = n; 
            cout << arr[n] << endl;
        }
    }

    return 0;
}
