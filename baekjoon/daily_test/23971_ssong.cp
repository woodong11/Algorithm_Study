#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int H, W, N, M; // y, x, y, x
int row, col;

int main() {
    freopen("sample_input.txt", "r", stdin);
    cin >> H >> W >> N >> M;
    int needy = N + 1;
    int needx = M + 1;
    int poy = H / needy;
    int pox = W / needx;

    if (H % needy != 0) {
        poy += 1;
    }
    if (W % needx != 0) {
        pox += 1;
    }
    cout << poy * pox;
    return 0;
}
