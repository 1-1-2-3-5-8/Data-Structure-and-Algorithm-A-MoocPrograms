#include <iostream>
#include <memory.h>
using namespace std;

#define MAXN (10 + (1L << 16))

int lst[MAXN];
int front[MAXN];
int mid[MAXN];
int back[MAXN];
int n;

int bp;
//把中序序列从start到end放到前序序列从fp开始的地方
void mb2f(int start, int end, int fp)
{
	if (end - start < 0)
		return;
	int root = back[bp];
	bp--;
	int midpos = lst[root];
	front[fp] = root;
	int leftn = midpos - start;
	mb2f(midpos + 1, end, fp + 1 + leftn);
	mb2f(start, midpos - 1, fp + 1);
}

int main()
{
	memset(lst, -1, sizeof(lst));
	n = 0;
	while (scanf("%d", mid + n) && lst[mid[n]] < 0)
	{
		lst[mid[n]] = n;
		n++;
	}
	back[0] = mid[n];
	for (int i = 1; i < n; i++)
	{
		scanf("%d", back + i);
	}
	bp = n - 1;
	mb2f(0, n - 1, 0);
	for (int i = 0; i < n - 1; i++)
		printf("%d ", front[i]);
	printf("%d\n", front[n - 1]);
	return 0;
}