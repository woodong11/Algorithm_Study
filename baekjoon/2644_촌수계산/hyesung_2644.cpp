#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	int people_num;
	cin >> people_num;

	int target1, target2;
	cin >> target1 >> target2;

	int relation_num;
	cin >> relation_num;
	
	vector<vector<int>> family_tree(people_num + 1, vector<int>());

	int target1_parent, target2_parent;
	for (int i = 0; i < relation_num; i++) {
		int parent, child;
		cin >> parent >> child;

		family_tree[parent].push_back(child);
		family_tree[child].push_back(parent);
		
	}

	queue<int> level_relation;
	vector<int> min_dist(people_num + 1, -1);
	
	int dist = 0;
	level_relation.push(target1);
	min_dist[target1] = dist;
	while (!level_relation.empty()) {
		dist++;
		                          
		int this_level_relation_size = level_relation.size();
		for (int i = 0; i < this_level_relation_size; i++) {
			int person = level_relation.front();
			level_relation.pop();

			vector<int> relations = family_tree[person];
			for (int j = 0; j < relations.size(); j++) {
				int relation = relations[j];
				if (min_dist[relation] == -1) {
					min_dist[relation] = dist;
					level_relation.push(relation);
				}
			}
		}
		
		if (min_dist[target2] != -1) break;
	}

	cout << min_dist[target2];

	return 0;
}
