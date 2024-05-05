#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

vector<int> answer;
vector<vector<int>> diceMAP;    // 주사위들 전역변수로 저장
int diceCnt, maxWinCnt;         // 주사위 개수 (2~ 10), A가 해당 조합에서 최대 이긴 횟수
vector <int> aPath, bPath;      // A에 해당하는 조합 저장
vector <int> aCase, bCase;
int aSelected[10];
int aDAT[501];
int bDAT[501];

// A 또는 B 해당 path(조합) 마다 굴러서 주사위 합 저장하기
void roll(int level, int sum, int isA, vector <int> path ){
    if (level == diceCnt/2){
        if (isA == 0){
            aDAT[sum] ++;
            aCase.push_back(sum);
        }
        else{
            bDAT[sum]++;
            bCase.push_back(sum);
        }
        return;
    }

    for (int i=0; i<6; i++){   
        roll(level + 1, sum + diceMAP[path[level]][i], isA, path);
    }
}


void check(){

    // 초기화
    memset(aDAT, 0, sizeof(aDAT));
    memset(bDAT, 0, sizeof(bDAT));
    aCase.clear();
    bCase.clear();

    // A가 가져감에 따라 자동으로 선택되는 B 주사위 path 만들기 
    bPath.clear();
    for (int i=0; i<diceCnt; i++){
        if (aSelected[i] == 0) bPath.push_back(i);
    }

    // DAT, Case에 값 저장
    roll(0, 0, 0, aPath);    
    roll(0, 0, 1, bPath);    

    // aCase, bCase에 정렬, 중복 제거
    sort(aCase.begin(),aCase.end());
    aCase.erase(unique(aCase.begin(),aCase.end()),aCase.end());
    sort(bCase.begin(),bCase.end());
    bCase.erase(unique(bCase.begin(),bCase.end()),bCase.end());

    // 경우의 수 계산
    int curWinCnt = 0, bCnt = 0;
    for (int i = 0; i < aCase.size(); i++) {
        int curCnt = 0;
        // 현재 aCase 원소보다 작은 bCase 원소 개수를 센다.
        while (bCnt < bCase.size() && bCase[bCnt] < aCase[i]) {
            bCnt++;
        }

        // 현재 aCase 원소 DAT x bCase 원소 DAT 
        for (int j=0; j< bCnt; j++){
            curWinCnt += (aDAT[aCase[i]] * bDAT[bCase[j]]);
        }    
    }


    // 정답 업데이트
    if (curWinCnt > maxWinCnt){
        maxWinCnt = curWinCnt;
        answer.clear();
        for(int i=0; i<aPath.size(); i++){
            answer.push_back(aPath[i] + 1);
        }
    }

}


// 조합 만들기 함수 -> path에 저장
void makePath(int level, int pre){
    if (level == diceCnt/2){
        check();
        return;
    }

    for (int i=pre+1; i < diceCnt; i++){
        aPath.push_back(i);
        aSelected[i] = 1;
        makePath(level+1, i);
        aSelected[i] = 0;
        aPath.pop_back();
    }   
}

vector<int> solution(vector<vector<int>> dice) {

    diceMAP = dice;
    diceCnt = dice.size();
    makePath(0, -1);
    return answer;
}
