#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int answer;
int minCnt = 21e8;
string targetStr;
int visited[51];
vector <string> wordList;

// a와 b는 틀린 str이라고 가정
bool check(string a, string b){
    int diffCnt = 0;
    for(int i=0; i<a.length(); i++){
        if (a[i] != b[i])
            diffCnt+=1;
        if (diffCnt > 1)
            return false;
    }
    
    return true;
}

// 재귀함수
void func(string node, int cnt){
    if (node == targetStr){
        if (minCnt > cnt)
            minCnt = cnt;
        return;
    }
    
    for(int i=0; i<wordList.size(); i++){
        if ((visited[i] == 0) && (check(node, wordList[i]))){
            visited[i] = 1;
            func(wordList[i], cnt+1);
            visited[i] = 0;
        } 
    }  
}

int solution(string begin, string target, vector<string> words) {

    // 모든 단어의 길이는 같다
    // 전역변수로 넘겨주기
    bool canAnswer = false;
    
    targetStr = target;
    for(int i=0; i<words.size(); i++){       
        wordList.push_back(words[i]);
        if (targetStr == words[i])
            canAnswer = true;
    }
    
    if (canAnswer)
        func(begin, 0);
    else
        return 0;
    
    return max(minCnt, 0);
}
