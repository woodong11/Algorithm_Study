#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Rotation
{
    int r;
    int c;
    int s;
};

int N, M, K;
int matrix[51][51];
int matrix_copied[51][51];
Rotation rotations[6];
vector<vector<int>> permutation; // vector to save all possible orders of selections 모든 선택 순서 저장을 위한 이차원 벡터
vector<int> path; // temporary vector to save selection orders during recursion 재귀 돌릴 때 선택 순서 저장을 위한 벡터
int visited[6];

void rotate_matrix(int(*matrix)[51], Rotation rot);
void permute(int level);
int process();

int main()
{
    cin >> N >> M >> K;

    // get all permutations of selections
    // 모든 선택 순서
    permute(0);


    // input
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            cin >> matrix[i][j];
        }
    }
    for (int i = 0; i < K; i++)
    {
        cin >> rotations[i].r >> rotations[i].c >> rotations[i].s;
    }

    cout << process();

    return 0;
}

void rotate_matrix(int(*matrix)[51], Rotation rot)
{
    int r = rot.r;
    int c = rot.c;
    int s = rot.s;
    // rotation size of s
    for (int i = 1; i <= s; i++)
    {
        int temp = matrix[r + i][c + i];
        int y = r + i;
        int x = c + i;

        for (y = r + i; y > r - i; y--)
        {
            matrix[y][x] = matrix[y - 1][x];
        }

        for (x = c + i; x > c - i; x--)
        {
            matrix[y][x] = matrix[y][x - 1];
        }

        for (y = r - i; y < r + i; y++)
        {
            matrix[y][x] = matrix[y + 1][x];
        }

        for (x = c - i; x < c + i - 1; x++)
        {
            matrix[y][x] = matrix[y][x + 1];
        }

        matrix[r + i][c + i - 1] = temp;
    }
}

// get permutations by recursion
// 재귀를 통해 가능한 모든 경우의 수 저장
void permute(int level)
{
    if (level == K)
    {
        permutation.push_back(path);
        return;
    }
    for (int i = 0; i < K; i++)
    {
        if (visited[i])
        {
            continue;
        }
        path.push_back(i);
        visited[i] = 1;
        permute(level + 1);
        path.pop_back();
        visited[i] = 0;
    }
}

int process()
{
    int minVal = 5000;

    // copy matrix to matrix_copied
    for (int i = 0; i < permutation.size(); i++)
    {
        for (int y = 1; y <= N; y++)
        {
            for (int x = 1; x <= M; x++)
            {
                matrix_copied[y][x] = matrix[y][x];
            }
        }

        for (int j = 0; j < K; j++)
        {
            rotate_matrix(matrix_copied, rotations[permutation[i][j]]);
        }

        int tempVal = 5000;

        for (int y = 1; y <= N; y++)
        {
            int row_sum = 0;
            for (int x = 1; x <= M; x++)
            {
                row_sum += matrix_copied[y][x];
            }
            tempVal = min(tempVal, row_sum);
        }

        minVal = min(minVal, tempVal);
    }

    return minVal;
}
