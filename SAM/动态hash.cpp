#include "pch.h"
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<array>
#define ll unsigned long long
using namespace std;
const int M = 2e5 + 3;
int n, m;
string s;
ll hash1[M] = { 1 };
namespace FHQTreap //动态维护hash 插入删除query lcp 修改即可
{
	int root, tot, top, stk[M], son[M][2];
	ll w[M];
	array<int, M> siz, pos, ch;
	inline int Rand()
	{
		static int seed = 131; return seed = int(seed * 48271ll % (~0ull >> 1));
	}
	inline int newnode(int x)
	{
		int a = ++tot; son[a][0] = son[a][1] = 0;
		return siz[a] = 1, w[a] = ch[a] = x, pos[a] = Rand(), a;
	}
	inline void pushup(int x)
	{
		siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
		w[x] = w[son[x][0]] * hash1[siz[son[x][1]] + 1] + ch[x] * hash1[siz[son[x][1]]] + w[son[x][1]];
	}
	inline void build(string& s)
	{
		int a, b, c; b = stk[top = 1] = newnode(s[0] - 'a' + 1);
		for (int i = 1; i < s.size(); ++i)
		{
			c = newnode(s[i] - 'a' + 1), a = 0;
			for (; top&&pos[stk[top]] > pos[c]; a = stk[top--], pushup(a));
			if (top) son[stk[top]][1] = c; son[c][0] = a;
			stk[++top] = c; if (top == 1) b = c;
		} for (; top; --top) pushup(stk[top]); root = b;
	}
	int merge(int x, int y)
	{
		if (!x || !y) return x | y;
		if (pos[x] < pos[y]) return son[x][1] = merge(son[x][1], y), pushup(x), x;
		else return son[y][0] = merge(x, son[y][0]), pushup(y), y;
	}
	void split(int u, int k, int& x, int& y)
	{
		if (!u)
		{
			x = y = 0;
			return;
		}
		if (siz[son[u][0]] >= k)
		{
			return split(son[y = u][0], k, x, son[u][0]), pushup(u), void();
		}
		else
		{
			split(son[x = u][1], k - siz[son[u][0]] - 1, son[u][1], y), pushup(u);
			return;
		}
	}
	inline void Insert(int x, int ch) //在rank x后位置插入
	{
		int a, b = newnode(ch), c;
		split(root, x, a, c), root = merge(a, merge(b, c));
	}
	int all_len;//维护全局序列长度
	inline void Delete(int x) //删除rank x的元素
	{
		all_len--;
		int a, b, c;
		split(root, x - 1, a, b), split(b, 1, b, c), root = merge(a, c);
	}
	inline ll ask(int l, int r) //询问区间【l,r】之间的hash值
	{
		int a, b, c;
		split(root, r, a, c), split(a, l - 1, a, b); ll ans = w[b];
		return root = merge(a, merge(b, c)), ans;
	}
	inline bool query(int x, int y, int len)
	{
		//cout << "hash" << " " << ask(x, x + len - 1) << " " << ask(y, y + len - 1) << endl;
		return ask(x, x + len - 1) == ask(y, y + len - 1);
	}

	void init(string &s)
	{
		all_len = s.size();
		for (int i = 1; i < M; ++i)
			hash1[i] = hash1[i - 1] * 131;
		build(s);
	}
	inline int Min(int a, int b) { return a < b ? a : b; }
	int lcp(int x, int y)//二分求后缀lcp 
	{
		int l, r, mid;
		//cout << all_len << endl;
		for (l = 1, r = Min(all_len - x, all_len - y) + 1; l <= r;)
		{
			mid = (l + r) >> 1,
				query(x, y, mid) ? l = mid + 1 : r = mid - 1;
			//cout << l << " " << r << endl;
		}
		return r;
	}
	void insert(int x, int y)
	{
		int  ch = y - 'a' + 1;
		all_len++;
		Insert(x, ch);
	}
}
using namespace FHQTreap;