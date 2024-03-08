// 프로그래머스에 작성된 코드 아래에 붙이면 기본 코드 테스트 가능

int main()
{
    int n = 6;
    vector<vector<int>> paths = { {1, 2, 3}, {2, 3, 5}, {2, 4, 2}, {2, 5, 4}, {3, 4, 4}, {4, 5, 3}, {4, 6, 1}, {5, 6, 1} };
    vector<int> gates = { 1, 3 };
    vector<int> summits = { 5 };
    vector<int> answer = solution(n, paths, gates, summits);
    for (int i : answer)
    {
        cout << i << " ";
    }
    cout << endl;

    n = 7;
    paths = { {1, 4, 4}, {1, 6, 1}, {1, 7, 3}, {2, 5, 2}, {3, 7, 4}, {5, 6, 6} };
    gates = { 1 };
    summits = { 2, 3, 4 };
    answer = solution(n, paths, gates, summits);
    for (int i : answer)
    {
        cout << i << " ";
    }
    cout << endl;

    n = 7;
    paths = { {1, 2, 5}, {1, 4, 1}, {2, 3, 1}, {2, 6, 7}, {4, 5, 1}, {5, 6, 1}, {6, 7, 1} };
    gates = { 3, 7 };
    summits = { 1, 5 };
    answer = solution(n, paths, gates, summits);
    for (int i : answer)
    {
        cout << i << " ";
    }
    cout << endl;

    n = 5;
    paths = { {1, 3, 10}, {1, 4, 20}, {2, 3, 4}, {2, 4, 6}, {3, 5, 20}, {4, 5, 6} };
    gates = { 1, 2 };
    summits = { 5 };
    answer = solution(n, paths, gates, summits);
    for (int i : answer)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
