#define _CRT_SECURE_NO_WARNINGS
// freopen("sample_input.txt","r",stdin);
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int T, map[13], price[13], ad, am, tm, ay;
int dif, total_price, visited[13];

void day_month() {
    for (int i = 1; i <= 12; i++) {
        if (map[i] >= dif)
            price[i] = am;
        else if (map[i] < dif)
            price[i] = map[i] * ad;
        total_price += price[i];
    }
}

void thmonth(int st, int tmp[13]) {
    if (st > 10) {
        int tmp_sum = 0;
        for (int i = 1; i <= 12; i++) {
            tmp_sum += tmp[i];
        }
        total_price = min(tmp_sum, total_price);
        return;
    }

    if (visited[st] == 1) {
        thmonth(st + 1, tmp);
        return;
    }

    int tmp_map[13];
    for (int i = 0; i < 13; i++) {
        tmp_map[i] = tmp[i];
    }

    int tmp1 = tmp_map[st], tmp2 = tmp_map[st + 1], tmp3 = tmp_map[st + 2];
    if (tm <= tmp1 + tmp2 + tmp3) {
        tmp_map[st] = tm, tmp_map[st + 1] = 0, tmp_map[st + 2] = 0;
    }
    visited[st] = 1;
    thmonth(st + 1, tmp_map);
    visited[st] = 0;

    //복구하고 dfs
    tmp_map[st] = tmp1, tmp_map[st + 1] = tmp2, tmp_map[st + 2] = tmp3;
    thmonth(st + 1, tmp_map);
}

int main() {
    freopen("sample_input.txt", "r", stdin);
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cin >> ad >> am >> tm >> ay;
        if (am % ad != 0)
            dif = am / ad + 1;
        else
            dif = am / ad;

        for (int i = 1; i <= 12; i++)
            cin >> map[i];

        day_month();
        thmonth(1, price);

        total_price = min(total_price, ay);
        cout << '#' << tc << ' ' << total_price << endl;

        memset(price, 0, sizeof(price));
        total_price = 0;
        memset(visited, 0, sizeof(visited));
    }
    return 0;
}
