#include<iostream>
using namespace std;

int arr[1000001] = { 1, 1, 2 };

int main()
{
	int n;
	cin >> n;
	for (int i = 3; i <= n; i++)
	{
		arr[i] = (arr[i - 2] + arr[i - 1]) % 15746;
	}
	cout << arr[n];
	return 0;
}
