#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int map[3];

int main() {
	freopen("sample_input.txt", "r", stdin);
	int maxlen = 0;
	int sum=0;
	while (true){
		unordered_map<int, int> um;
		cin >> map[0] >> map[1] >> map[2];
		if (map[0] == 0 && map[1] == 0 && map[2] == 0) break;
		maxlen = max(max(map[0], map[1]), map[2]);
		sum = map[0]+ map[1]+ map[2] - maxlen;
		if (sum <= maxlen) {
			cout << "Invalid \n";
			continue;
		}
		for (int i = 0; i < 3; i++) {
			um[map[i]] += 1;
		}
		if (um.size() == 3) cout << "Scalene \n";
		else if (um.size() == 2) cout << "Isosceles \n";
		else cout << "Equilateral \n";
	}
	return 0;
}
