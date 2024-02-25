#include <iostream>
#include <vector>
#include <queue>
 
using namespace std;
 
typedef struct {
    int y;
    int x;
}s_pos;
 
typedef struct {
    int dy;
    int dx;
}s_dir;
 
s_pos operator+(s_pos& l, s_dir& r) {
    return { l.y + r.dy, l.x + r.dx };
}
 
typedef struct {
    s_pos pos;
    int microbe_num;
    int dir;
}s_group;
 
vector<int> replace_dirs = { -1, 0, 2, 3, 1 };
s_dir move_dirs[] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
 
void solve(int test_case) {
    int map_size, max_time, initial_group_num;
    cin >> map_size >> max_time >> initial_group_num;
 
    queue<s_group> groups;
    vector<vector<int>> map(map_size, vector<int>(map_size, -1));
    vector<vector<s_group>> microbes(map_size, vector<s_group>(map_size));
    vector<vector<int>> max_microbe(map_size, vector<int>(map_size, 0));
    for (int i = 1; i < map_size - 1; i++) {
        for (int j = 1; j < map_size - 1; j++) {
            map[i][j] = 0;
        }
    }
 
    for (int i = 0; i < initial_group_num; i++) {
        s_group group{};
        cin >> group.pos.y >> group.pos.x >> group.microbe_num >> group.dir;
        group.dir = replace_dirs[group.dir];
        groups.push(group);
    }
 
    queue<s_pos> next;
    for (int i = 0; i < max_time; i++) {
         
        while (!groups.empty()) {
            s_group group = groups.front();
            groups.pop();
            s_pos next_pos = group.pos + move_dirs[group.dir];
 
            if (map[next_pos.y][next_pos.x] != -1) {
                if (microbes[next_pos.y][next_pos.x].microbe_num == 0) {
                    next.push(next_pos);
                }
 
                microbes[next_pos.y][next_pos.x].microbe_num += group.microbe_num;
 
                if (max_microbe[next_pos.y][next_pos.x] < group.microbe_num) {
                    max_microbe[next_pos.y][next_pos.x] = group.microbe_num;
                    microbes[next_pos.y][next_pos.x].dir = group.dir;
                }
            } else {
                next.push(next_pos);
 
                microbes[next_pos.y][next_pos.x].microbe_num = group.microbe_num / 2;
 
                microbes[next_pos.y][next_pos.x].dir = (group.dir + 2) % 4;
            }
        }
 
        while (!next.empty()) {
            s_pos next_pos = next.front();
            next.pop();
            s_group group = microbes[next_pos.y][next_pos.x];
            groups.push({ next_pos, group.microbe_num, group.dir });
            microbes[next_pos.y][next_pos.x].microbe_num = 0;
            max_microbe[next_pos.y][next_pos.x] = 0;
        }
    }
 
    int count = 0;
    while (!groups.empty()) {
        s_group group = groups.front();
        groups.pop();
        count += group.microbe_num;
    }
 
    cout << "#" << test_case << " " << count << endl;
 
}
 
int main() {
    int test_num;
    cin >> test_num;
     
    for (int i = 1; i <= test_num; i++) {
        solve(i);
    }
 
    return 0;
}
