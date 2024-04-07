#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

enum Side {
	U,
	B,
	R,
	D,
	F,
	L
};

enum Direction {
	right,
	left
};

int T, n;
string cube[6][3] = {
	{{"www"}, {"www"}, {"www"}},
	{{"yyy"}, {"yyy"}, {"yyy"}},
	{{"rrr"}, {"rrr"}, {"rrr"}},
	{{"ooo"}, {"ooo"}, {"ooo"}},
	{{"ggg"}, {"ggg"}, {"ggg"}},
	{{"bbb"}, {"bbb"}, {"bbb"}}
};
queue<char> q;

Side convertToEnumS(char a) {
	if (a == 'U') return Side::U;
	else if (a == 'D') return Side::D;
	else if (a == 'F') return Side::F;
	else if (a == 'B') return Side::B;
	else if (a == 'L') return Side::L;
	else if (a == 'R') return Side::R;
	else {
		cout << "ErrorS" << endl;
		return Side::U; // 기본값으로 Sunday를 반환
	}
}

Direction convertToEnumD(char a) {
	if (a == '+') return Direction::right;
	else if (a == '-') return Direction::left;
	else {
		cout << "ErrorD" << endl;
		return Direction::right;
	}
}

void rotateSide(int d, int side) {
	if (d == 0) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				q.push(cube[side][i][j]);
			}
		}
		
		for (int i = 2; i >= 0; i--) {
			for (int j = 0; j < 3; j++) {
				cube[side][j][i] = q.front();
				q.pop();
			}
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				q.push(cube[side][i][j]);
			}
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 2; j >= 0; j--) {
				cube[side][j][i] = q.front();
				q.pop();
			}
		}
	}
}

void rotateOutside(int d, int side) {
	// right
	if (d == 0) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				q.push(cube[side][i][j]);
			}
		}
	} // left
	else {

	}

}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;

	for (int i = 0; i < T; i++) {
		cin >> n;

		string a;
		for (int j = 0; j < n; j++) {
			cin >> a;
			
			Side side = convertToEnumS(a[0]);
			Direction direct = convertToEnumD(a[1]);
		}
	}

	return 0;
}
