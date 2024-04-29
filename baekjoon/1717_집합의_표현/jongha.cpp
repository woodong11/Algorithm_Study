#include<iostream>
#include<vector>
#include<map>
#include<cmath>
#include<queue>

using namespace std;

int N, arr[1000000];


int find(int a) {
    if (arr[a] == a) return a;
    int tar = find(arr[a]);
    arr[a] = tar;
    return tar;
}

void merge(int a, int b) {
    int tar1 = find(a);
    int tar2 = find(b);

    if (tar1 == tar2) return;
    arr[tar1] = tar2;
}

int n, m, a, b, c;
int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;

        if (a == 0) {
            if (find(b) != find(c)) {
                merge(b, c);
            }
        }
        else {
            if (find(b) == find(c)) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}
