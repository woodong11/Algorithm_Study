#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;

int cnt, visited[8], map[11][11];
int T, N, total_sum;

struct value{
    vector<int> yx;
    int sum;
};
struct cmp { //pq를 써서 sum의 최소 순대로 나열
    bool operator () (value a, value b)
    {
        return a.sum > b.sum;
    }
};
priority_queue<value, vector<value>, cmp> pq;
vector<int> city, temp;

int dfs(){

}
int check(vector<int> test) { //여기서 test조합이 (0)이 들어왔으면 먼저 확인 후 나머지가 서로간에 연결 가능한지 확인하는 곳
    int flag = 0, used[8]; //여기서 먼저 test로 확인하면서 used에 1 때려놓은 후 i<N 해고,dfs로 나머지 구간을 확인
    

    if (flag == 1)
    {

        return 1;
    }
    return 0;
}
void make(int level){
    if (cnt == level){ //cnt가 level이 되면 마을 조합이 하나 완성 된거임
        int result = check(temp); //그럼 여기서 해당 마을 조합이 서로 이동 가능여부 확인
        if(result == 1){    //가능이면 1반환해서 pq에 해당 조합과 sum값 반환 (사실 그냥 sum만 반환해도 될듯)
            int temp_sum = 0;
            int result_sum = 0;
            for (int i = 0; i < temp.size(); i++){ //temp는 마을 조합인데(0) ,(1, 2, 3)일 경우 각 마을의 유권자수 구하려고
                temp_sum += city[temp[i]];
            }
            result_sum = abs(total_sum - temp_sum * 2); // 지역구a - 지역구b = 지역구a -(총유권자-지역구a)
            pq.push({ temp,result_sum });
        }
        return;
    }

    for (int i = 0; i < N; i++){ //여기서 마을의 조합을 짜기
        if (visited[i] == 1)
            continue;
        visited[i] = 1;
        cnt++;
        temp.push_back(i);
        make(level);
        visited[i] = 0;
        temp.pop_back();
        cnt--;
    }

}
void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < N; i++){
        int x;
        cin >> x;
        city.push_back(x);
        total_sum += x;
    }
}
int main(){
    cin >> T;
    for (int i = 1; i <= T; i++){
        input();
        for (int i = 1; i < N; i++){
            cnt = 0;
            make(i);
        }
        int de = 1;
    }
}
