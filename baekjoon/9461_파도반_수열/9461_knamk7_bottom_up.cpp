#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n;
    vector<long long> p = {0, 1, 1, 1};
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        if(a < p.size())
        {
            cout << p[a] << '\n';
        }
        else
        {
            while(a >= p.size())
            {
                p.push_back(p[p.size() - 2] + p[p.size() - 3]);
            }
            cout << p[a] << '\n';
        }
    }
    return 0;
}
