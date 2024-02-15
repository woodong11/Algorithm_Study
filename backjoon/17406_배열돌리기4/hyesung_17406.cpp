#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef struct {
	int y;
	int x;
}s_pos;

typedef struct {
	int dy;
	int dx;
}s_dir;

s_pos operator+(s_pos &l, s_dir &r) {
	return { l.y + r.dy, l.x + r.dx };
}

typedef struct {
	s_pos center;
	int range;
}s_rotation;

vector<s_dir> rotate_dirs = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

void rotate(vector<vector<int>> &nums, s_rotation rotation) {
	s_pos center = rotation.center;

	for (int i = 1; i <= rotation.range; i++) {
		s_pos crt_pos = { center.y - i, center.x - i };
		s_pos next_pos = crt_pos;

		int dir = -1;
		int prev_data = nums[crt_pos.y][crt_pos.x];
		
		for (int j = 0; j < i * 8; j++) {

			if (j % (i * 2) == 0) {
				dir++;
			}

			next_pos = next_pos + rotate_dirs[dir];
			int temp = nums[next_pos.y][next_pos.x];
			nums[next_pos.y][next_pos.x] = prev_data;

			prev_data = temp;
		}
	}
}

int sum(vector<int> nums) {
	int sum = 0;
	for (int num : nums){
		sum += num;
	}
	return sum;
}

int main() {
	int height, width, rotate_num;
	cin >> height >> width >> rotate_num;

	vector<vector<int>> nums(height + 2, vector<int>(width + 2));
	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) {
			cin >> nums[i][j];
		}
	}

	vector<s_rotation> rotations;
	vector<int> indices;

	for (int i = 0; i < rotate_num; i++) {
		s_rotation rotation = {};
		cin >> rotation.center.y >> rotation.center.x >> rotation.range;
		rotations.push_back(rotation);
		indices.push_back(i);
	}

	int min_sum = INT_MAX;
	do {

		vector<vector<int>> temp_nums(nums);
		for (int index : indices) {
			rotate(temp_nums, rotations[index]);
		}

		for (int i = 1; i < temp_nums.size() - 1; i++) {
			min_sum = min(min_sum, sum(temp_nums[i]));
		}
	} while (next_permutation(indices.begin(), indices.end()));

	cout << min_sum;

	return 0;
}
