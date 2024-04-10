#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
using namespace std;

int P, N, M, Q, K, S, L, commandNum, pidT;
long long maxScore;

struct Node {
	int y;
	int x;
};

struct rabbit {
	int y;
	int x;
	int pid;
	int junpCnt;
};

// 전체토끼 중 뛰는 토끼 구하는 우선순위 함수 
struct compare {
	bool operator()(rabbit a, rabbit b) {
		if (a.junpCnt == b.junpCnt) {
			if ((a.y + a.x) == (b.y + b.x)) {
				if (a.y == b.y) {
					if (a.x == b.x) {
						return a.pid > b.pid;
					}
					return a.x > b.x;
				}
				return a.y > b.y;
			}
			return (a.y + a.x) > (b.y + b.x);
		}
		return a.junpCnt > b.junpCnt;
	}
};

// K번 중에 점수S를 더할 토끼 구하는 우선순위 함수
struct compare2 {
	bool operator()(rabbit a, rabbit b) {
		if ((a.y + a.x) == (b.y + b.x)) {
			if (a.y == b.y) {
				if (a.x == b.x) {
					return a.pid < b.pid;
				}
				return a.x < b.x;
			}
			return a.y < b.y;
		}
		return (a.y + a.x) < (b.y + b.x);
	}
};

// 상하좌우 네 방향 중 우선순위 구하는 함수
bool destCompare(Node a, Node b) {
	if (a.y + a.x == b.y + b.x) {
		if (a.y == b.y) {
			return a.x > b.x;
		}
		return a.y > b.y;
	}
	return a.y + a.x > b.y + b.x;
}

int command[4003][3];									// 커맨드 저장 배열
priority_queue <rabbit, vector<rabbit>, compare > pq;	// 토끼 저장 pq
unordered_map <int, int> distList;						// pid에 해당하는 토끼 이동거리 빠르게 접근을 위함
unordered_map <int, long long> scoreList;				// 나중에 maxScore에서 빼줄꺼임
unordered_map <int, long long> sList;					// 해당 토끼마다 받은 S점수 저장

void input() {
	cin >> Q;

	// 100 명령
	cin >> commandNum >> N >> M >> P;					
	int pid_i, d_i;
	for (int i = 1; i <= P; i++){					
		cin >> pid_i >> d_i;
		pq.push({ 0, 0, pid_i, 0 });
		distList[pid_i] = d_i;
		scoreList[pid_i] = 0;
		sList[pid_i] = 0;
	}

	// 200, 300 명령
	int temp1, temp2;						
	for (int i = 2; i <= Q-1; i++){						
		cin >> command[i][0] >> command[i][1] >> command[i][2];
	}

	// 400 명령
	cin >> command[Q][0];	
}

// 우선순위 토끼 도착지점 구하는 함수
Node findDestination(rabbit curRabbit, int nowDist) {
	vector <Node> destList;
	int nextY, nextX;
	int curY = curRabbit.y, curX = curRabbit.x;
	int posY = (nowDist) % (2*N - 2) , posX = (nowDist) % (2*M - 2);
	
	// 상
	if (posY <= curY)
		nextY = curY - posY;
	else if (posY <= curY + N - 1)
		nextY = posY - curY;
	else
		nextY = curY + (2 * N - 2) - (posY);
	destList.push_back({nextY, curX});

	// 하
	if (posY <= (N-1 - curY))
		nextY = curY + posY;
	else if (posY <= (N-1) - curY + (N-1))
		nextY = (N-1) - (posY - ((N-1)-curY));
	else
		nextY = posY - ((N - 1) - curY + (N - 1));
	destList.push_back({ nextY, curX });

	// 우
	if (posX <= curX)
		nextX = curX - posX;
	else if (posX <= curX + M - 1)
		nextX = posX - curX;
	else
		nextX = curX + (2 * M - 2) - (posX);
	destList.push_back({ curY, nextX });

	// 좌
	if (posX <= (M - 1 - curX))
		nextX = curX + posX;
	else if (posX <= (M - 1) - curX + (M - 1))
		nextX = (M - 1) - (posX - ((M - 1) - curX));
	else
		nextX = posX - ((M - 1) - curX + (M - 1));
	destList.push_back({ curY, nextX });

	sort(destList.begin(), destList.end(), destCompare);

	return { destList[0].y, destList[0].x };
}

// 경주 진행 
void move() {
	unordered_map <int, rabbit> jumpedRabbit;	// 점프한 토끼들 담음

	for (int i = 0; i < K; i++){				// K만큼 걸림
		rabbit moveRabbit = pq.top();
		pq.pop();

		int nowDist = distList[moveRabbit.pid];
		Node destPos = findDestination(moveRabbit, nowDist);

		long long addScore = destPos.y + destPos.x + 2;			// 나중에 깎을 점수 업데이트
		maxScore += (destPos.y + destPos.x) + 2;				// 최고 점수 업데이트

		// 점프한 토끼 위치 pq에 다시 저장하고 점수 업데이트
		moveRabbit = { destPos.y, destPos.x, moveRabbit.pid, moveRabbit.junpCnt+1};			// logP만큼 걸림
		pq.push(moveRabbit);
		jumpedRabbit[moveRabbit.pid] = moveRabbit;
		scoreList[moveRabbit.pid] = scoreList[moveRabbit.pid] + addScore;
	}

	// jumpedRabbit 중 우선순위 높은 토끼 S 더하기
	priority_queue <rabbit, vector<rabbit>, compare2> jumpedRabbitLIst;
	for (const auto &i : jumpedRabbit){
		jumpedRabbitLIst.push(i.second);
	}
	rabbit scoreRabbit = jumpedRabbitLIst.top();
	sList[scoreRabbit.pid] = sList[scoreRabbit.pid] + S;
}

// 이동거리 변경
void changeDist() {
	distList[pidT] = distList[pidT] * L;
}

void solve() {
	for (int i = 2; i <= Q-1; i++){
		if (command[i][0] == 200) {
			K = command[i][1];
			S = command[i][2];
			move();
		}

		else {
			pidT = command[i][1];
			L = command[i][2];
			changeDist();
		}
	}

	// 최고의 토끼 선정
	long long answer = 0;
	for (auto i : scoreList){
		int curPid = i.first;
		long long curScore = maxScore - i.second + sList[curPid];
		answer = max(answer, curScore);
	}
	cout << answer;
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	input();
	solve();
	return 0;
}
