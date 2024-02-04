	#define _CRT_SECURE_NO_WARNINGS
	#include <iostream>
	#include <vector>
	using namespace std;

	int T, n, m, quest_num;  // n은 샘플종류, m은 일의 총 개수, quest_num은 compare에서 dfs돌릴 횟수(?의 개수)
	vector<vector<int>>visited(10001, vector<int>(10001, 0));
	struct sample
	{
		int a;
		int b;
		int w;
	};
	struct cmp
	{
		int small;
		int big;
	};
	vector<sample> known; //!인애들
	vector<cmp> quest;  // ?인애들
	void add_dfs();

	void seper(int testnum) //이건 !랑 ? 구분해서 샘플이랑 비교해야할 대상 구분
	{
		for (int i = 0; i < testnum; i++)
		{
			char first;
			cin >> first;
			if (first == '!')
			{
				int a_input, b_input, w_input;
				cin >> a_input >> b_input >> w_input;
				known.push_back({ a_input,b_input,w_input });
				visited[a_input][b_input] = 1;
				known.push_back({ b_input,a_input,-1 * w_input });
				visited[b_input][a_input] = 1;
				add_dfs();
			}
			else if (first == '?')
			{
				cmp quest;
				int small_input, big_input;
				cin >> small_input >> big_input;
				quest = { small_input, big_input };
				int flag = 0;
				for (int j = 0; j < known.size(); j++)
				{
					if (quest.small == known[j].a && quest.big == known[j].b)
					{
						flag = 1;
						cout << known[j].w << " ";
						break;
					}
				}
				if (flag == 0)
					cout << "UNKNOWN" << " ";
			}
		}
	}

	void add_dfs()
	{
		int flag = 0;

		for (int i = 0; i < known.size() - 1; i++)
		{
			for (int j = 1; j < known.size(); j++)
			{
				if (visited[known[i].a][known[j].b] == 1)
					continue;
				if (known[i].b == known[j].a)
				{
					known.push_back({ known[i].a,known[j].b,known[i].w + known[j].w });
					visited[known[i].a][known[j].b] = 1;
					flag = 1;
				}
			}
		}
		if (flag == 1)
		{
			add_dfs();
		}
		else
		{
			return;
		}
	}
	void init()
	{
		for (int i = 0; i < visited.size(); i++)
		{
			for (int j = 0; j < visited.size(); j++)
			{
				visited[i][j] = 0;
			}
		}
		known = {};
		quest = {};

	}


	int main()
	{
		freopen("sample_input.txt", "r", stdin);

		cin >> T;
		for (int x = 1; x <= T; x++)
		{
			cin >> n >> m;
			cout << '#' << x << " ";
			seper(m);
			cout << endl;
			init();
		}
		return 0;
	}
