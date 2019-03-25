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
using namespace std;
namespace string_tool2
{
	const int N = 150000;
	bool DEL[N * 2];
	struct SAM_node
	{
		SAM_node *pre, *next[26];
		int step, Del;
		int firstpos, maxend;
		bool *del, endd;
		void clear(int n)
		{
			endd = false;
			maxend = 0;
			Del = n;
			pre = 0;
			step = 0;
			firstpos = 0;
			del = &DEL[n];
			*del = false;
			memset(next, 0, sizeof(next));
		}
	};
	SAM_node SAM_Pool[N * 2];
	SAM_node *last_pool[N * 2];
	struct SAM //后缀自动机 Suffix_Automaton
	{
		SAM_node *root, *last;
		SAM_node  *cur;
		int length, Del;
		void init()
		{
			cur = SAM_Pool;
			root = last = cur++;
			root->clear(0);
			length = 0;
			Del = 1;
			last_pool[0] = root;
		}
		void Insert(int w)
		{
			SAM_node *p = last;

			SAM_node *np = cur++;
			Del++;
			np->clear(Del);
			np->step = p->step + 1;
			np->firstpos = np->step;
			while (p && (p->next[w] == NULL || *(p->next[w]->del) == true))
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
					nq->clear(q->Del);
					memcpy(nq->next, q->next, sizeof(q->next));
					//memcpy(nq->next2, q->next2, sizeof(q->next2));
					nq->del = q->del;
					nq->firstpos = q->firstpos;
					nq->step = p->step + 1;
					nq->pre = q->pre;
					q->pre = nq;
					np->pre = nq;
					while (p && p->next[w] == q)
					{
						p->next[w] = nq, p = p->pre;
					}
				}
			}
			last = np;
			last_pool[++length] = last;
		}
		void pop_back()
		{
			DEL[last->Del] = true;
			--length;
			last = last_pool[length];
		}
		void get_suf()
		{
			SAM_node *pp = last;
			while (pp != root)
			{
				pp->maxend = length;
				pp->endd = true;
				pp = pp->pre;
			}
		}
		void clear_suf()
		{
			SAM_node *pp = last;
			while (pp != root)
			{
				pp->maxend = length;
				pp->endd = false;
				pp = pp->pre;
			}
		}
		void print_min(int x)
		{
			get_suf();
			SAM_node *p = root;
			bool flag = 0;
			int len = 0;
			for (int i = 0; i < x; ++i)
			{
				len++;
				for (int j = 0; j < 26; ++j)
					if (p->next[j] != NULL && *p->next[j]->del == false)
					{
						p = p->next[j];
						flag = 1;
						break;
					}
				if (p->endd)
					break;
			}
			if (p->endd && len != x)
			{
				cout << p->maxend - len + 1 << endl;
			}
			else
			{
				cout << p->firstpos - len + 1 << endl;
			}
			clear_suf();
		}
	};
}