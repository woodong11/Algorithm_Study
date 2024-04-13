#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;




int main() {
    int a, b, c;

    while (1) {
        cin >> a >> b >> c;

        if (a == 0 && b == 0 && c == 0) {
            return 0;
        }

        if (a >= b && a >= c) {
            if (a < b + c) {
                if (a == b && b == c) {
                    cout << "Equilateral\n";
                    continue;
                }
                if (a == b || a == c || b == c) {
                    cout << "Isosceles\n";
                    continue;
                }
                else {
                    cout << "Scalene\n";
                    continue;
                }
            }
        }
        if (b >= a && b >= c) {
            if (b < a + c) {
                if (a == b && b == c) {
                    cout << "Equilateral\n";
                    continue;
                }
                if (a == b || a == c || b == c) {
                    cout << "Isosceles\n";
                    continue;
                }
                else {
                    cout << "Scalene\n";
                    continue;
                }
            }
        }
        if (c >= a && c >= b) {
            if (c < a + b) {
                if (a == b && b == c) {
                    cout << "Equilateral\n";
                    continue;
                }
                if (a == b || a == c || b == c) {
                    cout << "Isosceles\n";
                    continue;
                }
                else {
                    cout << "Scalene\n";
                    continue;
                }
            }
        }
        cout << "Invalid\n";
    }

    return 0;
}
