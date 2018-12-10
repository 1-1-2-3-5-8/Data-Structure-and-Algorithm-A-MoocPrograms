#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1010
#define INF 200000

int n;
struct coordinate
{
	int x;
	int y;
	coordinate() {}
	coordinate(int _x, int _y) :x(_x), y(_y) {}
	friend bool operator< (coordinate a, coordinate b)
	{
		if (a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	}
	friend bool operator== (coordinate a, coordinate b)
	{
		return (a.x == b.x) && (a.y == b.y);
	}
} v[MAXN];

bool binary_search(coordinate p)
{
	int l = -1, r = n;//v[l]<p,v[r]>=p
	while (r - l > 1)
	{
		int mid = (l + r) / 2;
		if (v[mid] < p)
			l = mid;
		else
			r = mid;
	}
	return v[r] == p;
}

int main()
{
	while (scanf("%d", &n) && n)
	{
		int res = 0;
		for (int i = 0; i < n; i++)
			scanf("%d%d", &v[i].x, &v[i].y);
		v[n].x = v[n].y = INF;
		sort(v, v + n);
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
			{
				int dx = v[j].x - v[i].x;
				int dy = v[j].y - v[i].y;
				if (binary_search(coordinate(v[i].x + dy, v[i].y - dx)))
				{
					if (binary_search(coordinate(v[j].x + dy, v[j].y - dx)))
						res++;
				}
				if (binary_search(coordinate(v[i].x - dy, v[i].y + dx)))
				{
					if (binary_search(coordinate(v[j].x - dy, v[j].y + dx)))
						res++;
				}
			}
		printf("%d\n", res / 4);
	}
	return 0;
}