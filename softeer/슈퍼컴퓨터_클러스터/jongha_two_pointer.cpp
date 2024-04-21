#include<iostream>
#include<vector>
#include<map>
#include<cmath>

using namespace std;

int N, ai;
long long B;
int tempsqrt;
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

    tempsqrt = (int)sqrt(B);

    int result = 0;
    int start = 0, end = tempsqrt + 1;
    long long sum = 0;
    while(start <= end) {
        sum = 0;
        int now = (start + end) * 0.5;

        auto it = mymap.begin();
        while(1) {
            if(it->first >= now || it == mymap.end()) break;
            sum += pow(now - it->first, 2) * it->second;
            ++it;

            if(sum > B) {
                end = now - 1;
                break;
            }
        }
        
        if(sum < B) {
            start = now + 1;
        } else if(sum == B) {
            cout << now;
            return 0;
        }
    }

    cout << (int)((start + end) * 0.5);
    
   return 0;
}
