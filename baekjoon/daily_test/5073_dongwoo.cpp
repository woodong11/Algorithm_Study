#include <iostream>
#include <vector>
using namespace std;

vector <int> inputSide;

void findTriangle() {

	int maxSide = 0;
	int maxIdx;
	for (int i = 0; i < 3; i++) {
		if (inputSide[i] > maxSide) {
			maxSide = inputSide[i];
			maxIdx = i;
		}
	}

	// inputSide에는 2개만 남게 된다.
	inputSide.erase(inputSide.begin() + maxIdx);

	if (inputSide[0] + inputSide[1] <= maxSide) {
		cout << "Invalid" << "\n";
		return;
	}
	if ((inputSide[0] == inputSide[1]) && (inputSide[0] == maxSide) && (inputSide[1] == maxSide))
		cout << "Equilateral" << "\n";

	else if ((inputSide[0] != inputSide[1]) && (inputSide[0] != maxSide) && (inputSide[1] != maxSide))
		cout << "Scalene" << "\n";

	else
		cout << "Isosceles" << "\n";

	return;
}


int main() {

	while (true) {
		inputSide.clear();
		for (int i = 0; i < 3; i++){
			int temp;
			cin >> temp;
			inputSide.push_back(temp);
		}
		
		// 종료조건
		if (inputSide[0] == 0)
			break;

		// 삼각형 결과 출력
		findTriangle();
	}
	
	return 0;
}
