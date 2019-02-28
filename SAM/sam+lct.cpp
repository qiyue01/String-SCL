
#include "pch.h"
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<deque>
#include<iomanip>
#include<sstream>
#include<stack>
#include<iostream>
#include<limits>
#include<bitset>
#include<list>
#include<queue>
#include<memory>
#include<functional>
#define For(n) for(int i=0;i<n;++i)
using namespace std;

namespace sam_lct
{
	const int N = 1200100;
	const int maxn = 2400000;
	struct lct
	{
		int top;
		int fa[N], c[N][2], w[N], tag[N], q[N];
		bool rev[N];
		void add(int x, int y) {
			if (x)
			{
				w[x] += y; tag[x] += y;
			}
		}
		void pushdown(int x) {
			int l = c[x][0], r = c[x][1];
			if (tag[x])
			{
				add(l, tag[x]); add(r, tag[x]);
				tag[x] = 0;
			}
		}
		bool isroot(int x) {
			return c[fa[x]][0] != x && c[fa[x]][1] != x;
		}
		void rotate(int x) {
			int y = fa[x], z = fa[y], l, r;
			if (c[y][0] == x)l = 0; else l = 1; r = l ^ 1;
			if (!isroot(y))
			{
				if (c[z][0] == y)c[z][0] = x;
				else c[z][1] = x;
			}
			fa[c[x][r]] = y; fa[y] = x; fa[x] = z;
			c[y][l] = c[x][r]; c[x][r] = y;
		}
		void splay(int x) {
			top = 0; q[++top] = x;
			for (int i = x; !isroot(i); i = fa[i])
				q[++top] = fa[i];
			for (int i = top; i; i--)
				pushdown(q[i]);
			while (!isroot(x))
			{
				int y = fa[x], z = fa[y];
				if (!isroot(y))
				{
					if (c[y][0] == x ^ c[z][0] == y)rotate(x);
					else rotate(y);
				}
				rotate(x);
			}
		}
		void access(int x) {
			for (int t = 0; x; t = x, x = fa[x])
				splay(x), c[x][1] = t;
		}
		void link(int x, int f) {
			fa[x] = f; access(f); splay(f); add(f, w[x]);
		}
		void cut(int x) {
			access(x); splay(x); add(c[x][0], -w[x]);
			fa[c[x][0]] = 0; c[x][0] = 0;
		}
	}t;
	struct SAM_node
	{
		SAM_node *pre, *next[26];
		int step;
		int cnt;
		int sign;
		int firstpos;
		void clear(int cur)
		{
			sign = cur;
			cnt = 0;
			pre = 0;
			step = 0;
			firstpos = 0;
			memset(next, 0, sizeof(next));
		}
	};
	long d[N * 2];
	SAM_node *pool[N * 2];
	SAM_node SAM_Pool[N * 2];
	struct SAM //后缀自动机 Suffix_Automaton
	{
		SAM_node *root, *last;
		SAM_node  *cur;
		long tot2;
		long k;
		long length;
		void init()
		{
			cur = SAM_Pool;
			root = last = cur++;
			root->clear(cur - SAM_Pool);
			length = 0;
		}
		void Insert(int w)
		{
			length++;
			SAM_node *p = last;
			SAM_node *np = cur++;
			np->clear(cur - SAM_Pool);
			np->step = p->step + 1;
			np->firstpos = np->step - 1; //确定原串初始位置
			t.w[np->sign] = 1;
			while (p && !p->next[w])
			{
				p->next[w] = np, p = p->pre;
			}
			if (p == 0)
			{
				np->pre = root;
				t.link(np->sign, root->sign);
			}
			else
			{
				SAM_node *q = p->next[w];
				if (p->step + 1 == q->step)
				{
					np->pre = q;
					t.link(np->sign, q->sign);
				}
				else
				{
					SAM_node *nq = cur++;
					nq->clear(cur - SAM_Pool);
					memcpy(nq->next, q->next, sizeof(q->next));
					nq->firstpos = q->firstpos;
					nq->cnt = q->cnt;
					nq->step = p->step + 1;
					nq->pre = q->pre;
					t.link(nq->sign, q->pre->sign);
					t.cut(q->sign);
					t.link(q->sign, nq->sign);
					t.link(np->sign, nq->sign);
					q->pre = nq;
					np->pre = nq;
					while (p&&p->next[w] == q)
					{
						p->next[w] = nq, p = p->pre;
					}
				}
			}
			last = np;
		}
	};
}
using namespace sam_lct;