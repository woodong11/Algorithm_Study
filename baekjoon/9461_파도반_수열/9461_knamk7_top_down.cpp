#include<iostream>
#include<vector>
using namespace std;

long long arr[101] = {0, 1, 1, 1};

long long p(int n)
{
    if (arr[n] == 0)
    {
        arr[n] = p(n - 3) + p(n - 2);
    }
    return arr[n];
}

int main()
{
    int n;
    
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        cout << p(a) << '\n';
    }
    return 0;
}
