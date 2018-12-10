#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXN 2018
int m, n;
int res[MAXN], in[MAXN];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		priority_queue<int> que;
		scanf("%d%d", &m, &n);
		for (int i = 0; i < n; i++)
			scanf("%d", res + i);
		sort(res, res + n);
		m--;
		while (m--)
		{
			for (int i = 0; i < n; i++)
				scanf("%d", in + i);
			sort(in, in + n);
			for (int i = 0; i < n; i++)
				que.push(res[i] + in[0]);
			for (int i = 1; i < n; i++)
			{
				int j;
				for (j = 0; j < n; j++)
				{
					if (que.top() > res[j] + in[i])
					{
						que.pop();
						que.push(res[j] + in[i]);
					}
					else
						break;
				}
				if (j == 0)
					break;
			}
			for (int i = n - 1; i >= 0; i--)
			{
				res[i] = que.top();
				que.pop();
			}
		}
		bool out = 0;
		for (int i = 0; i < n; i++)
		{
			if (out)
				printf(" ");
			else
				out = 1;
			printf("%d", res[i]);
		}
		printf("\n");
	}
	return 0;
}