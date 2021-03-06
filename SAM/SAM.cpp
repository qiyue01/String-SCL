// SAM.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

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
#include<cstdio>
#define For(n) for(int i=0;i<n;++i)
using namespace std;
const int N = 300010;
namespace string_tool
{
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
		double ans;
		int firstpos;
		bool end;
		set<int> position;
		void clear()
		{
			end = false;
			position.clear();
			ans = 0;
			sum = 0;
			cnt = 0;
			cnt3 = 0;
			child = -1;
			next2_sum = 0;
			pre = 0;
			step = 0;
			cur_long = -1;
			max_long = 1001000;
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
		long tot; //tot为所有不同子串的和
		long tot2;
		long k;
		long length;
		void init()
		{
			cur = SAM_Pool;  
			root = last = cur++;
			root->clear();
			tot = 0;
			length = 0;
		}
		void Insert(int w,int pp)
		{
			length++;
			SAM_node *p = last;
			SAM_node *np = cur++;
			np->clear();
			np->step = p->step + 1;
			np->firstpos = np->step - 1; //确定原串初始位置
			while (p && !p->next[w])
			{
				//p->next2[p->next2_sum++] = w;
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
					//memcpy(nq->next2, q->next2, sizeof(q->next2));
					nq->step = p->step + 1;
					nq->pre = q->pre;
					q->pre = nq;
					np->pre = nq;
					while (p&&p->next[w] == q)
					{
						//p->next2[p->next2_sum++] = w;
						p->next[w] = nq, p = p->pre;
					}
				}
			}
			//np->cnt = 1;
			//SAM_node *part = np->pre;
			//while (part != NULL && part != root)
			//{
				//part->cnt++;
				//part = part->pre;
			//}
			tot += (np->step - np->pre->step);
			last = np;
			last->end = true;
		}
		void build(string &s)
		{
			tot2 = 0;
			init();
			for (int i = 0; i < s.size(); ++i)
				Insert(s[i] - 'a',i+1);
		}
		string LCS(string &b)     //返回最长公共子串，线性复杂度
		{
			int lenmax = 0, len2 = 0, sign = 0;
			SAM_node *find_point = root;
			string interim;
			for (long i = 0; i < b.size(); ++i)
			{
				if (find_point->next[b[i] - 'a'] != NULL)
				{
					len2++;
					find_point = find_point = find_point->next[b[i] - 'a'];    //向前匹配
				}
				else
				{
					while (find_point->next[b[i] - 'a'] == NULL && find_point != root) //回溯
						find_point = find_point->pre;
					if (find_point->next[b[i] - 'a'] == NULL)
						len2 = 0;
					else
					{
						len2 = find_point->step + 1;
						find_point = find_point->next[b[i] - 'a'];
					}
				}
				if (len2 > lenmax)
				{
					sign = i - len2;
					lenmax = len2;
				}
			}
			interim = b.substr(sign + 1, lenmax);
			return interim;
		}
		void clear_count(SAM_node *count)
		{
			if (count->child == -1 || count == last)
				return;
			else
			{
				count->child = -1;
				for (int i = 0; i < 26; ++i)
					if (count->next[i] != NULL)
						clear_count(count->next[i]);
			}
		}
		long count_substring(SAM_node *count) //输入开始位置指针统计不同子串个数，记忆化深搜
		{
			if (count == last)
			{
				count->child = 1;
				return 1;
			}
			if (count->child > 0)
				return count->child;
			count->child = 1;
			for (int i = 0; i < 26; ++i)
				if (count->next[i] != NULL)
					count->child += count_substring(count->next[i]);
			return count->child;
		}
		unsigned long long count_substring2(SAM_node *count) //dfs
		{
			if (count->ans > 0)
				return count->ans;
			unsigned long long ans = 1;
			for (int i = 0; i < 26; ++i)
				if (count->next[i] != NULL)
					ans += count_substring2(count->next[i]);
				else
				{
					if (part2[i] != 0)
						ans += part2[i];
				}
			count->ans=ans;
			return ans;
		}
		long LCS_2(vector<string> &part)
		{
			topo();
			for (int i = 0; i < part.size(); ++i)
			{
				SAM_node *find_point = root;
				long len = 0;
				for (int j = 0; j < part[i].size(); ++j)
				{
					if (find_point->next[part[i][j] - 'a'] != NULL)
					{
						len++;
						find_point = find_point = find_point->next[part[i][j] - 'a'];    //向前匹配
					}
					else
					{
						while (find_point->next[part[i][j] - 'a'] == NULL && find_point != root) //回溯
							find_point = find_point->pre;
						if (find_point->next[part[i][j] - 'a'] == NULL)
							len = 0;
						else
						{
							len = find_point->step + 1;
							find_point = find_point->next[part[i][j] - 'a'];
						}
					}
					if (len > find_point->cur_long)
						find_point->cur_long = len;
				}
				int cnt = cur - SAM_Pool;
				for (int i = cnt - 1; i >= 1; i--)
					if (pool[i]->cur_long >= 0 && pool[i]->pre != root)
						if (pool[i]->cur_long > pool[i]->pre->step)
							pool[i]->pre->cur_long = pool[i]->pre->step;
						else
							pool[i]->pre->cur_long = pool[i]->cur_long;
				SAM_node *part3 = SAM_Pool;
				while (part3 != cur)
				{
					if (part3->cur_long > 0)
					{
						part3->max_long = min(part3->cur_long, part3->max_long);
						part3->_time++;
						part3->cur_long = -1;
					}
					part3++;
				}
			}

			SAM_node *part3 = SAM_Pool;
			long ans = 0;
			while (part3 != cur)
			{
				if (part3->max_long != 1001000 && part3->_time == part.size())
					ans = max(ans, part3->max_long);
				part3++;
			}
			return ans;
		}
		void count_k_pre(string &s)
		{
			topo();
			int cnt = cur - SAM_Pool;
			SAM_node *p = SAM_Pool;
			for (int i = 0; i < s.size(); ++i)
			{
				p = p->next[s[i] - 'a'];
				p->cnt = 1;
			}
			for (int i = cnt - 1; i >= 1; i--)
				if (pool[i]->cnt != 0)
					pool[i]->pre->cnt += pool[i]->cnt;
		}
		long long count_k(long k)
		{
			SAM_node *part = SAM_Pool;
			long long sum = 0;
			while (part != cur)
			{
				sum += part->cnt*part->step;
				part++;
			}
			return sum;
		}
		void topo()
		{
			// 求出parent树的拓扑序
			int cnt = cur - SAM_Pool;
			int maxVal = 0;
			memset(d, 0, sizeof(d));
			for (int i = 1; i < cnt; i++)
				maxVal = max(maxVal, SAM_Pool[i].step), d[SAM_Pool[i].step]++;
			for (int i = 1; i <= maxVal; i++)
				d[i] += d[i - 1];
			for (int i = 1; i < cnt; i++)
				pool[d[SAM_Pool[i].step]--] = &SAM_Pool[i];
			pool[0] = root;
		}
		long  mod_str(long mod)
		{
			long sum = 0;
			topo();
			pool[0]->cnt3 = 1;
			int cnt = cur - SAM_Pool;
			for (int i = 0; i < cnt; ++i)
			{
				pool[i]->sum = pool[i]->sum % 2012;
				if (i == 0)
				{
					for (int j = 1; j < 10; ++j)
						if (pool[i]->next[j] != NULL)
						{
							pool[i]->next[j]->cnt3 += pool[i]->cnt3;
							pool[i]->next[j]->sum += pool[i]->sum * 10 + pool[i]->cnt3*j;
						}
				}
				else
				{
					for (int j = 0; j < 10; ++j)
						if (pool[i]->next[j] != NULL)
						{
							pool[i]->next[j]->cnt3 += pool[i]->cnt3;
							pool[i]->next[j]->sum += pool[i]->sum * 10 + pool[i]->cnt3*j;
						}
				}
			}
			for (int i = 0; i < cnt; ++i)
				sum += pool[i]->sum;
			return sum;
		}
		void print_kth(int k,SAM_node *part)
		{
			if (k != 0)
			{
				for (int i = 0; i < 26; ++i)
				{
					if (part->next[i] != NULL)
						if (part->next[i]->child < k)
						{
							k -= part->next[i]->child;
						}
						else
						{
							k--;
							cout << char('a' + i);
							print_kth(k, part->next[i]);
							break;
						}
					
				}
			}
		}
	};
}
using namespace string_tool;
namespace SAM
{
	struct SAM_node_map
	{
		SAM_node_map *pre;
		unordered_map<int, SAM_node_map *> next;
		int step;
		long long ans;
		void clear()
		{
			pre = 0;
			ans = 0;
			step = 0;
			next.clear();
		}
	};
	SAM_node_map SAM_Pool_map[N * 2];
	struct SAM_map //后缀自动机 Suffix_Automaton
	{
		SAM_node_map *root, *last;
		SAM_node_map  *cur;
		void init()
		{
			cur = SAM_Pool_map;  //cur=当前弧
			root = last = cur++;
			root->clear();
		}
		void topo()
		{
			// 求出parent树的拓扑序
			int cnt = cur - SAM_Pool;
			int maxVal = 0;
			memset(d, 0, sizeof(d));
			for (int i = 1; i < cnt; i++)
				maxVal = max(maxVal, SAM_Pool[i].step), d[SAM_Pool[i].step]++;
			for (int i = 1; i <= maxVal; i++)
				d[i] += d[i - 1];
			for (int i = 1; i < cnt; i++)
				pool[d[SAM_Pool[i].step]--] = &SAM_Pool[i];
			pool[0] = root;
		}
		void Insert(int w, int k)
		{
			SAM_node_map *p = last;
			SAM_node_map *np = cur++;
			np->clear();
			np->step = p->step + 1;
			while (p && p->next.find(w) == p->next.end())
				p->next[w] = np, p = p->pre;
			if (p == 0)
				np->pre = root;
			else
			{
				SAM_node_map *q = p->next[w];
				if (p->step + 1 == q->step)
					np->pre = q;
				else
				{
					SAM_node_map *nq = cur++;
					nq->clear();
					nq->next = q->next;
					nq->step = p->step + 1;
					nq->pre = q->pre;
					q->pre = nq;
					np->pre = nq;
					while (p&&p->next[w] == q)
						p->next[w] = nq, p = p->pre;
				}
			}
			last = np;
		}
	};
}
using namespace SAM;

