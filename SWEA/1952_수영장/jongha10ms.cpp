#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

struct Point {
    int startidx;
    int sum;
};

int T, day, month, quarter, year;
int visited[12];
int grid[12];
vector<int> monthv;
vector<Point> quarterv;

bool compare(Point& a, Point& b) {
    return a.sum > b.sum;
}

void init() {
    for (int i = 0; i < 12; i++) {
        visited[i] = 0;
    }

    monthv.clear();
    quarterv.clear();
}

int main() {
    int a;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        init();
        cin >> day >> month >> quarter >> year;
        
        for (int i = 0; i < 12; i++)
        {
            cin >> a;
            grid[i] = a * day;
            if (grid[i] >= month) {
                monthv.push_back(month);
            }
            else {
                monthv.push_back(grid[i]);
            }
        }

        int start = 0, mid = start + 1, end = start + 2;
        int sum = monthv[start] + monthv[start + 1] + monthv[end];
        for (int i = 0; i < 10; i++) {
            if (sum >= quarter) {
                quarterv.push_back({ start , sum - quarter });
            }
            if (i == 9) break;
            sum -= monthv[start];
            start++;
            end++;
            sum += monthv[end];
        }

        sort(quarterv.begin(), quarterv.end(), compare);
        sum = 0;

        int cnt = 0;
        if (quarterv.size() == 10) {
            for (int i = 0; i < 10; i++) {
                if (quarterv[i].sum < 0) break;
                cnt++;
            }
        }

        if (cnt == 10) {
            sum += quarter * 4;
        }
        else if (cnt != 10) {
            for (int i = 0; i < quarterv.size(); i++) {
                start = quarterv[i].startidx;
                if (visited[start] == 1 || visited[start + 1] == 1 || visited[start + 2] == 1) continue;
                if (quarterv[i].sum >= 0) {
                    sum += quarter;
                    visited[quarterv[i].startidx] = 1;
                    visited[quarterv[i].startidx + 1] = 1;
                    visited[quarterv[i].startidx + 2] = 1;
                }
            }

            for (int i = 0; i < 12; i++) {
                if (grid[i] == 0 || visited[i] == 1) continue;
                sum += monthv[i];
            }
        }

        if (sum >= year) {
            cout << "#" << tc << " " << year << "\n";
        }
        else {
            cout << "#" << tc << " " << sum << "\n";
        }
    }



    return 0;
}
