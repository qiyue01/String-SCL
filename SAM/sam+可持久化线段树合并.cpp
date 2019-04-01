#include"pch.h"
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
#include<unordered_map>
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
#include<cstdio>
#include<tuple>
using namespace std;
#define  G(x,y) get<y>(x)
namespace tree //函数式线段树 动态开点
{
	const int N1 = 16000000;
	struct node
	{
		node *L, *R;
		int l, r, val;
		void clear()
		{
			L = R = NULL;
			l = r = val = 0;
		}
	};
	node pool[N1], *cur;
	void clear()
	{
		cur = pool;
		cur->clear();
	}
	node *new_node(int L, int R, int val)
	{
		cur->l = L, cur->r = R, cur->val = val;
		return cur++;
	}
	void push_down(node *a) //创建合适的子节点
	{
		if ((a->L != NULL && a->R != NULL) || (a->l == a->r))
			return;
		int mid = (a->l + a->r) / 2;
		a->L = new_node(a->l, mid, 0);
		a->R = new_node(mid + 1, a->r, 0);
	}
	void update(node *x) //权值线段树清空区间后的维护
	{
		x->val = 0;
		if (x->L != NULL) x->val += x->L->val;
		if (x->R != NULL) x->val += x->R->val;
	}
	node* insert(node *old_version, int k)//单点插入 从旧版本生成新版本 权值线段树
	{
		push_down(old_version);
		int l = old_version->l, r = old_version->r;
		node * new_version = new_node(l, r, old_version->val + 1);
		if (l != r)
		{
			int mid = (l + r) / 2;
			if (k >= mid + 1)
			{
				new_version->R = insert(old_version->R, k);
				new_version->L = old_version->L;
			}
			else
			{
				new_version->L = insert(old_version->L, k);
				new_version->R = old_version->R;
			}
		}
		return new_version;
	}
	void insert_cur(node *cur_version, int k)//单点插入 插入某个版本 权值线段树
	{
		push_down(cur_version);
		int l = cur_version->l, r = cur_version->r;
		int mid = (l + r) / 2;
		cur_version->val++;
		if (l != r)
		{
			if (k >= mid + 1)
				insert_cur(cur_version->R, k);
			else
				insert_cur(cur_version->L, k);
		}
	}
	void insert_cur_n(node *cur_version, int k, int data)//单点+ 插入某个版本 普通线段树 
	{
		push_down(cur_version);
		int l = cur_version->l, r = cur_version->r;
		int mid = (l + r) / 2;
		cur_version->val += data;
		if (l != r)
		{
			if (k >= mid + 1)
				insert_cur_n(cur_version->R, k, data);
			else
				insert_cur_n(cur_version->L, k, data);
		}
	}
	node* insert_n(node *old_version, int k, int data)//单点+ 从旧版本生成新版本 普通线段树 
	{
		push_down(old_version);
		int l = old_version->l, r = old_version->r;
		node * new_version = new_node(l, r, old_version->val + data);
		if (l != r)
		{
			int mid = (l + r) / 2;
			if (k >= mid + 1)
			{
				new_version->R = insert_n(old_version->R, k, data);
				new_version->L = old_version->L;
			}
			else
			{
				new_version->L = insert_n(old_version->L, k, data);
				new_version->R = old_version->R;
			}
		}
		return new_version;
	}
	node *merge(node *x, node *y) //合并x,y,返回合并后的根
	{
		if (x == NULL) return y;
		if (y == NULL) return x;
		node *merge_version = new_node(x->l, x->r, y->val + x->val);
		merge_version->L = merge(x->L, y->L);
		merge_version->R = merge(x->R, y->R);
		return merge_version;
	}
	void merge_all(node *x, node *y) // 将x全树合并到y上
	{
		y->val += x->val;
		y->L = merge(x->L, y->L);
		y->R = merge(x->R, y->R);
	}
	int query_sum(node *x, int L, int R) //区间求和 可以直接用来代替单点查询
	{
		if (x == NULL) return 0;
		int sum = 0;
		int mid = (x->l + x->r) / 2;
		if (x->l == L && x->r == R)
			return x->val;
		else
		{
			if (L <= mid && R > mid)
				return query_sum(x->L, L, mid) + query_sum(x->R, mid + 1, R);
			else if (R <= mid)
				return query_sum(x->L, L, R);
			else if (L >= mid + 1)
				return query_sum(x->R, L, R);
		}
	}
	int query_max(node *x, int L, int R) //区间求和 可以直接用来代替单点查询
	{
		if (x == NULL) return 0;
		int sum = 0;
		int mid = (x->l + x->r) / 2;
		if (x->l == L && x->r == R)
			return x->val;
		else
		{
			if (L <= mid && R > mid)
				return max(query_max(x->L, L, mid), query_max(x->R, mid + 1, R));
			else if (R <= mid)
				return query_max(x->L, L, R);
			else if (L >= mid + 1)
				return query_max(x->R, L, R);
		}
	}
	void merge(int L, int R, node *x, node *y) //将x的区间合并到y上
	{
		if (x == NULL) return;
		int mid = (x->l + x->r) / 2;
		if (x->l == L && x->r == R)
		{
			y->val += x->val;
			y->L = merge(x->L, y->L);
			y->R = merge(x->R, y->R);
			//x->L = NULL, x->R = NULL; //是否清空原区间 可选
		}
		else
		{
			push_down(y);
			if (L <= mid && R > mid)
				merge(L, mid, x->L, y->L), merge(mid + 1, R, x->R, y->R);
			else if (R <= mid)
				merge(L, R, x->L, y->L);
			else if (L >= mid + 1)
				merge(L, R, x->R, y->R);
		}
		update(x);
	}
}
using namespace tree;

#define For(n) for(int i=0;i<n;++i)
using namespace std;
const int N = 300010;
struct EXSAM_node
{
	EXSAM_node *next[26], *pre;
	node *segment;
	int step;
	int bel;
	int size;
	int visit;
	bool vis;
	int pos;
	void clear(int p)
	{
		segment = new_node(1, 200000, 0);
		pos = p;
		vis = 0;
		pre = NULL;
		step = 0;
		size = 0;
		visit = 0;
		memset(next, 0, sizeof(next));
		//memset(cnt, 0, sizeof(cnt));
	}
};
EXSAM_node EXSAM_Pool[N * 2];
EXSAM_node *EXpool[N * 2];
long d[N * 2];
struct EXSAM
{
	EXSAM_node *root, *last;
	EXSAM_node  *cur;
	void init()
	{
		cur = EXSAM_Pool;  //cur=当前弧
		root = last = cur++;
		root->clear(1);
		root->visit = 0;
	}
	void update(EXSAM_node *np, int i)
	{
		while (np&& np->visit != i)
		{
			np->visit = i;
			np->size++;
			np = np->pre;
		}
	}
	void Insert(int w, int i)//第i个子串的字符,每插入新串时last应设置为root
	{
		EXSAM_node *p = last;
		if (p->next[w] && p->next[w]->step == p->step + 1)
		{
			last = p->next[w];
			last->size++;
			return;
		}
		EXSAM_node *np = cur++;
		np->clear(cur - EXSAM_Pool - 1);
		np->step = p->step + 1;
		while (p && !p->next[w])
		{
			p->next[w] = np, p = p->pre;
		}
		if (p == 0)
			np->pre = root;
		else
		{
			EXSAM_node *q = p->next[w];
			if (p->step + 1 == q->step)
				np->pre = q;
			else
			{
				EXSAM_node *nq = cur++;
				nq->clear(cur - EXSAM_Pool - 1);
				nq->step = p->step + 1;
				memcpy(nq->next, q->next, sizeof(q->next));
				nq->pre = q->pre;
				//nq->size = q->size;
				//nq->visit = q->visit;
				q->pre = nq;
				np->pre = nq;
				while (p&&p->next[w] == q)
				{
					p->next[w] = nq, p = p->pre;
				}
			}
		}
		last = np;
		insert_cur(last->segment, i);
	}
	void topo()
	{
		// 求出parent树的拓扑序
		int cnt = cur - EXSAM_Pool;
		int maxVal = 0;
		memset(d, 0, sizeof(d));
		for (int i = 1; i < cnt; i++)
		{
			maxVal = max(maxVal, EXSAM_Pool[i].step), d[EXSAM_Pool[i].step]++;
		}
		for (int i = 1; i <= maxVal; i++)
			d[i] += d[i - 1];
		for (int i = 1; i < cnt; i++)
			EXpool[d[EXSAM_Pool[i].step]--] = &EXSAM_Pool[i];
		EXpool[0] = root;
	}
}part;
stack<tuple<EXSAM_node*, int, int> > st;
list<char> solve(int l, int r, string &s)
{
	list<char> ans;
	while (!st.empty())
		st.pop();
	EXSAM_node *p = part.root;
	for (int i = 0; i < s.size(); ++i)
	{
		int k = s[i] - 'a';
		for (int j = 25; j > k; --j)
			if (p->next[j] != NULL)
				st.push(make_tuple(p->next[j], i, j));
		if (p->next[k] != NULL)
			p = p->next[k];
		else
		{
			p = NULL;
			break;
		}
	}
	if (p)
		for (int i = 25; i >= 0; --i)
			if (p->next[i])
				st.push(make_tuple(p->next[i], s.size(), i));
	bool flag = false;
	while (!st.empty())
	{
		auto p = st.top();
		st.pop();
		if (l + G(p, 1) <= r && query_sum(G(p, 0)->segment, l + G(p, 1), r) != 0)
		{
			flag = true;
			for (int i = 0; i < G(p, 1); ++i)
				ans.push_back(s[i]);
			ans.push_back(char(G(p, 2) + 'a'));
		}
		if (flag) break;
	}
	if (flag)
		return ans;
	else
	{
		ans.clear();
		return ans;
	}
}
