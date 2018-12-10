/* 普通并查集 */
#include <iostream>
#include <memory.h>
using namespace std;

int par[200010];
int rk[200010];

int find(int n)
{
	if (par[n] == n)
		return n;
	return par[n] = find(par[n]);
}

bool same(int x, int y)
{
	return find(x) == find(y);
}

void unit(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x == y)
		return;
	if (rk[x] > rk[y])
		par[y] = x;
	else
	{
		par[x] = y;
		if (rk[x] == rk[y])
			rk[y]++;
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	int i;
	while (t--)
	{
		memset(rk, 0, sizeof(rk));
		int n, m;
		scanf("%d%d", &n, &m);
		for (i = 1; i <= 2 * n; i++)
			par[i] = i;
		char message;
		int a, b;
		while (m--)
		{
			scanf("\n%c%d%d", &message, &a, &b);
			if (message == 'D')
			{
				unit(a, b + n);
				unit(a + n, b);
			}
			else
			{
				if (same(a, b))
					printf("In the same gang.\n");
				else
				{
					if (same(a, b + n))
						printf("In different gangs.\n");
					else
						printf("Not sure yet.\n");
				}
			}
		}
	}
	return 0;
}