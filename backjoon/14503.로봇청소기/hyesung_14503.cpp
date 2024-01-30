#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> pos;
typedef pair<int, int> direction;

int main() {
	int height, width;
	cin >> height >> width;

	pos crt_pos;
	int crt_direction;
	cin >> crt_pos.first >> crt_pos.second >> crt_direction; // direction : (0, N), (1, E), (2, S), (3, W)

	vector<vector<int>> map(height, vector<int>(width, 1));
	 
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cin >> map[i][j];
		}
	}

	vector<direction> move_directions = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

	int clean_room_count = 0;
	while (true) {
		if (map[crt_pos.first][crt_pos.second] == 0) {
			map[crt_pos.first][crt_pos.second] = -1;
			clean_room_count++;
		}

		bool connected_not_clean =  false;
		for (int i = 1; i <= 4; i++) {
			int direction_index = (crt_direction - i + 4) % 4;
			direction dir = move_directions[direction_index];
			if (connected_not_clean = (map[crt_pos.first + dir.first][crt_pos.second + dir.second] == 0)) {
				crt_pos = { crt_pos.first + dir.first, crt_pos.second + dir.second };
				crt_direction = direction_index;
				break;
			}
		}

		if (!connected_not_clean) {
			direction dir = move_directions[(crt_direction + 2) % 4];

			if (map[crt_pos.first + dir.first][crt_pos.second + dir.second] == 1) {
				break;
			}
			crt_pos = { crt_pos.first + dir.first, crt_pos.second + dir.second };
		}
	}

	cout << clean_room_count;

	return 0;
}