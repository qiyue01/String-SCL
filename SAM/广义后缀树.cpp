/*  ע���Ƿ����ĺ�׺��
*  ��֮ǰ��init()
*  �����Ҫ�������ֵ��� ��ô��Ҫ�ȷ�ת���봮
*  ÿ���ڵ��rank��ʾ��ÿ���ڵ�������ĺ�׺������
*  ����cntͳ�Ƴ��ֵ����� �����Ļ�ע����Ϣ����
*  build�����������󼴿ɵ���EXST���������׺��
*  ��ͨ�ĺ�׺���Լ�SAM��ΪEXSAM����������һ�����ػ���
*  trans2����ڵ��Լ����ȼ������EXST�ϴӸ����ýڵ���Ӵ�
*  ʱ������˵��������ϲ������������������Բ�������ʽ�ϲ���֤���Ӷ�
*/
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
#include<unordered_set>
#define For(n) for(int i=0;i<n;++i)
using namespace std;
const int N = 300010;
struct EXSAM_node
{
	EXSAM_node *next[26], *pre;
	int rank;
	int step;
	int sign;
	int belong;
	int firstpos;
	set<int> cnt;
	void clear(int k)
	{
		rank = 0;
		belong = 0;
		firstpos = 0;
		sign = k;
		pre = NULL;
		step = 0;
		memset(next, 0, sizeof(next));
	}

};
EXSAM_node EXSAM_Pool[N * 2];
EXSAM_node *EXpool[N * 2];
long d[N * 2];
string spool[N];
struct EXSAM
{
	EXSAM_node *root, *last;
	EXSAM_node  *cur;
	void init()
	{
		cur = EXSAM_Pool;
		root = last = cur++;
		root->clear(cur - EXSAM_Pool);
	}
	EXSAM_node *newnode()
	{
		cur->clear(cur - EXSAM_Pool + 1);
		return cur++;
	}
	void Insert(int w, int i, int j)//��i���Ӵ����ַ�,ÿ�����´�ʱlastӦ����Ϊroot
	{
		EXSAM_node *p = last;
		if (p->next[w] && p->next[w]->step == p->step + 1)
		{
			last = p->next[w];
			last->cnt.insert(i);
			return;
		}
		EXSAM_node *np = newnode();
		np->step = p->step + 1;
		np->firstpos = j; //ȷ��ԭ����ʼλ��
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
				EXSAM_node *nq = newnode();
				nq->step = p->step + 1;
				memcpy(nq->next, q->next, sizeof(q->next));
				nq->pre = q->pre;
				nq->belong = q->belong;
				nq->firstpos = q->firstpos;
				q->pre = nq;
				np->pre = nq;
				while (p&&p->next[w] == q)
				{
					p->next[w] = nq, p = p->pre;
				}
			}
		}
		last = np;
		last->belong = i;
		last->cnt.insert(i);
	}

	void topo()
	{
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
EXSAM_node *trans[N * 2];
void build(string &s, int i)
{
	for (int j = 0; j < s.size(); ++j)
		part.Insert(s[j] - 'a', i, j + 1);
	spool[i] = s;
	part.last = part.root;
}
vector<pair<int, int> > edge[N * 2];
void addedge(int u, int v, int w)
{
	edge[u].push_back({ w,v });
}
int dfslen;
void dfs(int a)
{
	trans[a]->rank = dfslen;
	for (auto &p : edge[a])
	{
		dfslen++;
		dfs(p.second);
	}
}
void EXST()
{
	EXSAM_node *p;
	p = part.root;
	trans[1] = p;
	p++;
	for (int i = 0; i < part.cur - EXSAM_Pool + 10; ++i)
		edge[i].clear();
	while (p != part.cur)
		addedge(p->pre->sign, p->sign, spool[p->belong][p->firstpos - p->pre->step - 1]), trans[p->sign] = p, p++;
	for (int i = 0; i < part.cur - EXSAM_Pool + 10; ++i)
		sort(edge[i].begin(), edge[i].end());
	dfslen = 0;
	dfs(1);
}
string trans2(EXSAM_node *p, int len)
{
	string p2;
	for (int i = p->firstpos - 1; i >= p->firstpos - len; --i)
		p2.append(1, spool[p->belong][i]);
	return p2;
}

