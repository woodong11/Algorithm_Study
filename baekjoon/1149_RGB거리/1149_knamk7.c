#include<stdio.h>
#define min(a, b) (a) > (b) ? (b) : (a)

int main()
{
	int n;
	int a, b, c;
	int x, y, z;
	scanf("%d", &n);
	scanf("%d %d %d", &a, &b, &c);
	for (int i = 1; i < n; i++)
	{
		scanf("%d %d %d", &x, &y, &z);
		x += min(b, c);
		y += min(a, c);
		z += min(a, b);
		a = x;
		b = y;
		c = z;
	}
	printf("%d",min(a, min(b, c)));
	return 0;
}
