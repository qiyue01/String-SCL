/*
* EXSAM维护信息还是用set或者可持久化线段树比较好 
* 实时更新信息的话要注意nq到q的信息拷贝 比较麻烦
*
*
*
*
*
*
*/

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
#include<unordered_map>

#define For(n) for(int i=0;i<n;++i)
using namespace std;
const int N = 100010;
struct EXSAM_node
{
	EXSAM_node *next[26],*pre;
	//bitset<10> part;//属于哪个主串
	int step;
	int bel;
	int size;
	int visit;
	bool vis;
	map<int,int> cnt;
	bitset<100> cnt2;
	void clear()
	{
		cnt2.reset();

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
		cur = EXSAM_Pool;  
		root = last = cur++;
		root->clear();
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
	void Insert(int w,int i)//第i个子串的字符,每插入新串时last应设置为root
	{  
		EXSAM_node *p = last;
		if (p->next[w] && p->next[w]->step == p->step + 1)
		{
			last = p->next[w];
			last->cnt[i]++;
			last->size++;
			return;
		}
		EXSAM_node *np = cur++;
		np->clear();
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
					nq->clear();
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
};
namespace trie_EXSAM
{
	EXSAM part;
	string p[100100];
	list<int> edge[100100];
	bool vis[100100];
	void add(int u, int v)
	{
		edge[u].push_back(v);
	}
	/*
	void trie_build(int cur, EXSAM_node *cur2)
	{
		queue<pair<int, EXSAM_node *>> que;
		pair<int, EXSAM_node *> pp;
		que.push(make_pair(cur, cur2));
		while (!que.empty())
		{
			pp = que.front();
			que.pop();
			for (auto &s : edge[pp.first])
			{
				part.last = pp.second;
				for (auto L : p[s])
					part.Insert(L - 'a');
				que.push(make_pair(s, part.last));
			}
		}
	}
	*/
}





