/* 带权并查集 */
#include <iostream>
using namespace std;

#define MAXN 100010

struct node
{
	int par;
	int rank;
	int d;
};

int n, m;
node crime[MAXN];

int find(int x, int& d)
{
	if (crime[x].par == x)
	{
		d = 0;
		return x;
	}
	crime[x].par = find(crime[x].par, d);
	d = (d + crime[x].d) & 1;
	return crime[x].par;
}

int same(int x, int y)
{
	int d1, d2;
	x = find(x, d1);
	y = find(y, d2);
	if (x == y)
	{
		if (d1 == d2)
			return 1;
		else
			return 0;
	}
	return -1;
}

void unit(int x, int y, int diff)
{
	int d1, d2;
	x = find(x, d1);
	y = find(y, d2);
	if (x == y)
		return;
	int dis = (d1 + d2 + diff) & 1;
	if (crime[x].rank >= crime[y].rank)
	{
		crime[y].par = x;
		crime[y].d = dis;
		crime[x].rank += crime[y].rank;
	}
	else
	{
		crime[x].par = y;
		crime[x].d = dis;
		crime[y].rank += crime[x].rank;
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
		{
			crime[i].par = i;
			crime[i].rank = 1;
			crime[i].d = 0;
		}
		char ins[2];
		int x, y;
		for (int i = 0; i < m; i++)
		{
			scanf("%s%d%d", ins, &x, &y);
			if (ins[0] == 'D')
				unit(x, y, 1);
			else
			{
				int diff = same(x, y);
				switch (diff)
				{
				case -1:
					printf("Not sure yet.\n");
					break;
				case 0:
					printf("In different gangs.\n");
					break;
				case 1:
					printf("In the same gang.\n");
				}
			}
		}
	}
	return 0;
}