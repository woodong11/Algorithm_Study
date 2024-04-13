#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;




int h, w, n, m;

int main() {
    cin >> h >> w >> n >> m;

    int result = 0;
    int  a = 1, b = 1, c = 1, d = 1;

    if (a > h || b > w) {
        cout << result;
        return 0;
    }

    while (1) {
        if (a + n + 1 <= h) {
            a += (n + 1);
            c++;
        }
        if (b + m + 1 <= w) {
            b += (m + 1);
            d++;
        }
        if (a + n + 1 > h && b + m + 1 > w) {
            cout << c * d;
            return 0;
        }
    }

    return 0;
}
