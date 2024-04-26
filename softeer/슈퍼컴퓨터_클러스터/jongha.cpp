#include<iostream>
#include<vector>
#include<map>
#include<cmath>

using namespace std;

int N, ai;
long long B;
int gap;
map<int, int> mymap;

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> B;

    int a;
    for(int i = 0; i < N; i++) {
        cin >> a;

        if(mymap.find(a) != mymap.end()) {
            mymap[a]++;
        } else {
            mymap[a] = 1;
        }
    }

    unsigned long long start = mymap.begin()->first, end = 3000000000;
    unsigned long long sum = 0;
    while(start <= end) {
        sum = 0;
        unsigned long long now = (start + end) >> 1;
        unsigned long long temp1 = 0;
        auto it = mymap.begin();
        while(1) {
            if(it->first >= now) break;
            temp1 = 0;
            unsigned long long temp = (now - it->first) * (now - it->first);
            for(int i = 0; i < it->second; i++) {
                temp1 += temp;

                if(temp1 > B) break;
            }
            sum += temp1;
            
            if(sum > B) {
                end = now - 1;
                break;
            }
            
            ++it;
            if(it == mymap.end()) break;
        }
        
        if(sum <= B) {
            start = now + 1;
        }
    }

    cout << (int)((start + end) * 0.5);
    
   return 0;
}
