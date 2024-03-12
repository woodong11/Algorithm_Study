#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<climits>

using namespace std;



int T;
int a, b, c;


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> a >> b >> c;

		int cnt = 0;

		if (c < 3 || b < 2 || a < 1) {
			cout << "#" << tc << " -1\n";
			continue;
		}
		if (a < b && b < c) {
			cout << "#" << tc << " 0\n";
			continue;
		}

		cnt += abs(c - b) + 1;
		b -= cnt;

		if (a < b) {
			cout << "#" << tc << " " << cnt << "\n";
			continue;
		}

		cnt += abs(b - a) + 1;

		cout << "#" << tc << " " << cnt << "\n";
	}





	return 0;
}
