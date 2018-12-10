#include <iostream>
#include <queue>
using namespace std;

#define MAXN 6000
#define MAXBILL 1000005
typedef long long ll;

ll cost;
int num[MAXBILL];
priority_queue<int> maxque;
priority_queue<int, vector<int>, greater<int> > minque;

int main()
{
	int n;
	scanf("%d", &n);
	while (n--)
	{
		int k;
		scanf("%d", &k);
		int bill;
		while (k--)
		{
			scanf("%d", &bill);
			num[bill]++;
			maxque.push(bill);
			minque.push(bill);
		}
		while (!num[maxque.top()])
			maxque.pop();
		num[maxque.top()]--;
		cost += maxque.top();
		maxque.pop();
		while (!num[minque.top()])
			minque.pop();
		num[minque.top()]--;
		cost -= minque.top();
		minque.pop();
	}
	printf("%lld", cost);
	return 0;
}