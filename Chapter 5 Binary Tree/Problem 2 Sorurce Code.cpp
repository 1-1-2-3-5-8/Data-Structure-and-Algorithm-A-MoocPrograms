#include <stdio.h>
#include <string.h>
#include <math.h>
#include <memory.h>

#define MAXN 1000

template <class T>
struct stack
{
	int size;
	T arr[MAXN];
	stack() :size(-1) {}
	bool empty()
	{
		return size < 0;
	}
	void push(T t)
	{
		arr[++size] = t;
	}
	T top()
	{
		return arr[size];
	}
	T pop()
	{
		return arr[size--];
	}
};

template <class T>
struct queue
{
	int fp, ep;
	T arr[MAXN];
	queue() :fp(0), ep(-1) {}
	bool empty()
	{
		return ep < fp;
	}
	void push(T t)
	{
		arr[++ep] = t;
	}
	T front()
	{
		return arr[fp];
	}
	T pop()
	{
		return arr[fp++];
	}
};

struct node
{
	node *left, *right;
	int level;
	char data;
	node(char _c) :data(_c), level(0), left(0), right(0) {}
};

int n;
char eq[MAXN];
int val[200];
char rev[MAXN];
int maxlevel;

int power(int x, int n)
{
	int res = 1;
	while (n--)
		res *= x;
	return res;
}

//single calculation
int cal(int vala, int valb, char c)
{
	switch (c)
	{
	case '+':
		return vala + valb;
	case '-':
		return vala - valb;
	case '*':
		return vala * valb;
	default://case '/':
		return vala / valb;
	}
}

//calculate by post-order seq
int res()
{
	stack<int> ob;
	int len = strlen(rev);
	for (int i = 0; i < len; i++)
	{
		if (rev[i] >= 'a'&&rev[i] <= 'z')
			ob.push(val[rev[i]]);
		else if (rev[i] >= 'A'&&rev[i] <= 'Z')
			ob.push(val[rev[i]]);
		else
		{
			int vala = ob.pop(), valb = ob.pop();
			ob.push(cal(valb, vala, rev[i]));
		}
	}
	return ob.pop();
}

stack<node *> op;
stack<node *> ob;
//build sub-tree
inline void bd()
{
	node *valb = ob.pop();
	node *vala = ob.pop();
	node *ope = op.pop();
	ope->left = vala;
	ope->right = valb;
	ob.push(ope);
	return;
}

//build up binary tree
node *build()
{
	op.push(new node('('));
	int len = strlen(eq);
	char c;
	for (int i = 0; i < len; i++)
	{
		switch (eq[i])
		{
		case ')':
			while (op.top()->data != '(')
				bd();
			op.pop();//pop '('
			break;
		case '(':
			op.push(new node('('));
			break;
		case '*'://fall through
		case '/':
			while (op.top()->data == '*' || op.top()->data == '/')
				bd();
			op.push(new node(eq[i]));
			break;
		case '+':
		case '-':
			while (op.top()->data != '(')
				bd();
			op.push(new node(eq[i]));
			break;
		default:
			ob.push(new node(eq[i]));
		}
	}
	while (op.top()->data != '(')
		bd();
	return ob.pop();
}

//restore & output post-order seq
void postout(node *root)
{
	memset(rev, 0, sizeof(rev));
	typedef enum { L, R } tag;
	struct tagnode
	{
		node *data;
		tag t;
		tagnode() :data(0), t(L) {}
		tagnode(node *n, tag _t) :data(n), t(_t) {}
	};
	stack<tagnode> s;
	maxlevel = 0;
	node *mov = root;
	int level;
	int pos = 0;
	while (!s.empty() || mov)
	{
		if (mov)
		{
			s.push(tagnode(mov, L));
			level = mov->level;
			mov = mov->left;
			if (mov)
			{
				mov->level = ++level;
				if (level > maxlevel)
					maxlevel = level;
			}
		}
		else
		{
			tagnode top = s.pop();
			if (top.t == L)
			{
				top.t = R;
				s.push(top);
				level = top.data->level;
				mov = top.data->right;
				if (mov)
				{
					mov->level = ++level;
					if (level > maxlevel)
						maxlevel = level;
				}
			}
			else
			{
				rev[pos++] = top.data->data;
				printf("%c", top.data->data);
				mov = NULL;
			}
		}
	}
	printf("\n");
}


char mid[MAXN];
//output tree
void print(node *root)
{
	struct nd
	{
		node *data;
		int p;
		nd() :data(0), p(0) {}
		nd(node *d, int _p) :data(d), p(_p) {}
	};
	queue<nd> que;
	int dis = power(2, maxlevel);
	que.push(nd(root, dis));
	int level = 0;
	nd mov = que.pop();
	while (level <= maxlevel)
	{
		int prev = 1;
		dis /= 2;
		int rightmost = 0;
		memset(mid, ' ', sizeof(mid));
		while (mov.data->level <= level)
		{
			for (int i = prev; i < mov.p; i++)
				printf(" ");
			printf("%c", mov.data->data);
			prev = mov.p + 1;
			if (mov.data->left)
			{
				que.push(nd(mov.data->left, mov.p - dis));
				mid[mov.p - 2] = '/';
				rightmost = mov.p - 2;
			}
			if (mov.data->right)
			{
				que.push(nd(mov.data->right, mov.p + dis));
				mid[mov.p] = '\\';
				rightmost = mov.p;
			}
			if (que.empty())
				break;
			mov = que.pop();
		}
		printf("\n");
		level++;
		if (que.empty())
			break;
		if (level <= maxlevel)
		{
			mid[rightmost + 1] = '\0';
			printf("%s\n", mid);
		}
	}
}

int main()
{
	scanf("%s%d", eq, &n);
	char c[2];
	int v;
	for (int i = 0; i < n; i++)
	{
		scanf("%s%d", c, &v);
		val[c[0]] = v;
	}
	node *root = build();
	postout(root);
	print(root);
	printf("%d\n", res());
	return 0;
}