#include <stdio.h>
#include <memory.h>

#define MAXN 20010

int n;
int a[MAXN];
int temp[MAXN];
int cnt;

void merge(int l, int r, int m)
{
	for (int i = l; i <= r; i++)
		temp[i] = a[i];
	int lp = l, rp = m + 1;
	int ap = l;
	while (lp <= m && rp <= r)
	{
		if (temp[lp] <= temp[rp])
			a[ap++] = temp[lp++];
		else
		{
			a[ap++] = temp[rp++];
			cnt += m - lp + 1;
		}
	}
	while (lp <= m)
		a[ap++] = temp[lp++];
	while (rp <= r)
		a[ap++] = temp[rp++];
}

void mergesort(int l, int r)
{
	if (l >= r)
		return;
	int mid = (l + r) / 2;
	mergesort(l, mid);
	mergesort(mid + 1, r);
	merge(l, r, mid);
}

int main()
{
	while (scanf("%d", &n) && n)
	{
		for (int i = 0; i < n; i++)
			scanf("%d", a + i);
		cnt = 0;
		mergesort(0, n - 1);
		printf("%d\n", cnt);
	}
	return 0;
}