#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

bool is_valid_regions(vector<vector<int>>& connected, vector<bool> unioned) {
	for (int i = 0; i < unioned.size(); i++) {
		if (!unioned[i]) {
			queue<int> q;
			q.push(i);
			while (!q.empty()) {
				int city = q.front();
				q.pop();
				if (unioned[city]) continue;
				unioned[city] = true;

				for (int next_city : connected[city]) {
					if(!unioned[next_city]) q.push(next_city);
				}
			}
			break;
		}
	}

	for (int i = 0; i < unioned.size(); i++) {
		if (!unioned[i]) return false;
	}
	return true;
}

void union_region(vector<vector<int>> &connected, vector<int> &cities_voter, vector<bool> &unioned, int crt_city, int total_voter_num, int crt_voter_num, int &min_diff) {
	unioned[crt_city] = true;

	if (abs((total_voter_num - crt_voter_num) - crt_voter_num) < min_diff) {
		if (is_valid_regions(connected, unioned)) {
			
			min_diff = abs((total_voter_num - crt_voter_num) - crt_voter_num);
		}
	}

	for (int city : connected[crt_city]) {
		if (!unioned[city]) {
			union_region(connected, cities_voter, unioned, city, total_voter_num, crt_voter_num + cities_voter[city], min_diff);
		}
	}
	unioned[crt_city] = false;
}

void solve(int test_case) {
	int city_num;
	cin >> city_num;

	vector<vector<int>> map(city_num, vector<int>(city_num));

	vector<vector<int>> connected(city_num);
	vector<int> cities_voter(city_num);
	vector<bool> unioned(city_num, false);

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				connected[i].push_back(j);
			}
		}
	}
	
	int total_voters = 0;
	for (int i = 0; i < cities_voter.size(); i++) {
		cin >> cities_voter[i];
		total_voters += cities_voter[i];
	}

	
	int min_diff = INT_MAX;
	
	for (int i = 0; i < unioned.size(); i++) {
		union_region(connected, cities_voter, unioned, i, total_voters, cities_voter[i], min_diff);
	}
	
	cout << "#" << test_case << " " << min_diff << endl;
}

int main() {
	int test_num;
	cin >> test_num;

	for (int test_case = 1; test_case <= test_num; test_case++) {
		solve(test_case);
	}

	return 0;
}
