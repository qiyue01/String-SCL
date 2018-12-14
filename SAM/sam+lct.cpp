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
const int N = 200100;
const int maxn = 400000;
namespace sam_lct
{
	struct LCT {
		int son[maxn][2], size[maxn], f[maxn], tag[maxn];
#define root(x) (son[f[x]][0]!=x&&son[f[x]][1]!=x)

		void push_down(int x) {
			if (tag[x] == 0)return;
			size[son[x][0]] += tag[x];
			tag[son[x][0]] += tag[x];
			size[son[x][1]] += tag[x];
			tag[son[x][1]] += tag[x];
			tag[x] = 0;
		}
		void push_up(int x) {
			if (!root(x))push_up(f[x]);
			push_down(x);
		}
		void rt(int x, int k) {
			int y = f[x], z = f[y];
			son[y][k ^ 1] = son[x][k];
			f[son[x][k]] = y;
			son[x][k] = y;
			f[y] = x; f[x] = z;
			if (son[z][0] == y)son[z][0] = x;
			else if (son[z][1] == y)son[z][1] = x;
			push_down(y);
			push_down(x);
		}
		void splay(int x) {
			push_up(x);
			while (!root(x)) {
				int y = f[x], z = f[y];
				if (root(y) && son[y][0] == x)rt(x, 1);
				else if (root(y) && son[y][1] == x)rt(x, 0);
				else if (son[z][0] == y && son[y][0] == x)rt(y, 1), rt(x, 1);
				else if (son[z][0] == y && son[y][1] == x)rt(x, 0), rt(x, 1);
				else if (son[z][1] == y && son[y][0] == x)rt(x, 1), rt(x, 0);
				else rt(y, 0), rt(x, 0);
			}
		}
		void access(int x) {
			for (int y = 0; x; x = f[x]) {
				splay(x);
				son[x][1] = y;
				push_down(x);
				y = x;
			}
		}
		void link(int x, int y) {
			access(y); splay(y); f[x] = y;
			size[y] += size[x]; tag[y] += size[x];
		}
		void cut(int x, int y) {
			access(y); splay(x); f[x] = 0;
			size[y] -= size[x]; tag[y] -= size[x];
		}
	}t;
	struct SAM_node
	{
		SAM_node *pre, *next[26];
		//int next2[26];//记录子节点位置，空间换时间，卡空间时可以去掉
		int next2_sum;
		int step;
		long child;
		long max_long;
		long cur_long;
		int _time;
		int sum;//求字符串不同整数和
		int cnt3;//求字符串不同整数和
		int cnt;
		unsigned long long ans;
		int firstpos;
		void clear()
		{
			ans = 0;
			sum = 0;
			cnt = 0;
			cnt3 = 0;
			child = -1;
			next2_sum = 0;
			pre = 0;
			step = 0;
			cur_long = -1;
			max_long = 101000;
			_time = 0;
			firstpos = 0;
			memset(next, 0, sizeof(next));
		}
	};
	long d[N * 2];
	SAM_node *pool[N * 2];
	SAM_node SAM_Pool[N * 2];
	int part2[26];
	struct SAM //后缀自动机 Suffix_Automaton
	{
		SAM_node *root, *last;
		SAM_node  *cur;
		long tot2;
		long k;
		long length;
		void init()
		{
			cur = SAM_Pool;  //cur=当前弧
			root = last = cur++;
			root->clear();
			length = 0;
		}
		void Insert(int w)
		{
			length++;
			SAM_node *p = last;
			SAM_node *np = cur++;
			np->clear();
			np->step = p->step + 1;
			np->firstpos = np->step - 1; //确定原串初始位置
			while (p && !p->next[w])
			{
				p->next[w] = np, p = p->pre;
			}
			if (p == 0)
				np->pre = root;
			else
			{
				SAM_node *q = p->next[w];
				if (p->step + 1 == q->step)
					np->pre = q;
				else
				{
					SAM_node *nq = cur++;
					nq->clear();
					memcpy(nq->next, q->next, sizeof(q->next));
					nq->firstpos = q->firstpos;
					nq->cnt = q->cnt;
					nq->step = p->step + 1;
					nq->pre = q->pre;
					t.link(nq - SAM_Pool, q->pre - SAM_Pool);
					t.cut(q - SAM_Pool, q->pre - SAM_Pool);
					t.link(q - SAM_Pool, nq - SAM_Pool);
					q->pre = nq;
					np->pre = nq;
					while (p&&p->next[w] == q)
					{
						p->next[w] = nq, p = p->pre;
					}
				}
			}
			last = np;
			t.link(last-SAM_Pool, last->pre - SAM_Pool);
		}
	};
}