// 试验品1.cpp: 定义控制台应用程序的入口点。
//

#include"pch.h"
#include<string>
#include<vector>
#include<regex>
#include<algorithm>
#include<random>
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
#define EPS 1e-8
const int sigma = 26;
using namespace std;
struct Trie_node
{
	Trie_node *next[sigma];
	Trie_node *fail;
	int end, end2,ans,depth;
	Trie_node(Trie_node*a = NULL, bool b = 0)
	{
		memset(next, 0, sizeof(next));
		fail = a;
		end2 = 0;
		end = b;
		ans = 0;
		depth = 0;
	}
};

struct Trie
{
	Trie_node *root;
	Trie()
	{
		root = new Trie_node(NULL, 0);
	}
	void insert(string &l,int k)
	{
		Trie_node *found = root;
		for (auto &s : l)
		{
			if (found->next[s - 'a'] != NULL)
				found = found->next[s - 'a'];
			else
			{
				found->next[s - 'a'] = new Trie_node(NULL, 0);
				found = found->next[s - 'a'];
			}
		}
		found->end++;
		found->ans = k;
		found->depth = l.size();
	}
	void clear_fail(Trie_node *part)
	{
		part->fail = NULL;
		part->end2 = part->end;
		for (int i = 0; i < sigma; ++i)
			if (part->next[i] != NULL)
				clear_fail(part->next[i]);
	}
	void compute_fail()
	{
		queue<Trie_node *> part;
		part.push(root);
		while (!part.empty())
		{
			Trie_node *part2 = NULL;
			Trie_node *father = part.front();
			part.pop();
			for (int s = 0; s < sigma; ++s)
			{
				if (father->next[s] != NULL)
				{
					if (father == root)
						father->next[s]->fail = root;
					else
					{
						part2 = father->fail;
						while (part2 != NULL)
						{
							if (part2->next[s] != NULL)
							{
								father->next[s]->fail = part2->next[s];
								father->next[s]->end2 += part2->next[s]->end2;
								break;
							}
							part2 = part2->fail;
						}
						if (part2 == NULL)
							father->next[s]->fail = root;
					}
					part.push(father->next[s]);
				}
			}
		}
	}
	void clear()
	{
		root = new Trie_node(NULL, 0);
	}
};
/*
struct online_AC
{
	Trie part[20];
	int group[20], size1[20];
	int p2;
	set<string> part2[20];
	set<string> all;
	void clear()
	{
		all.clear();
		p2 = 0;
		for (int i = 0; i < 20; ++i)
		{
			part[i].clear();
			size1[i] = 0;
			part2[i].clear();
		}
	}
	online_AC()
	{

		for (int i = 0; i < 20; ++i)
			group[i] = (1 << i);
		p2 = 0;
		memset(size1, 0, sizeof(size1));
	};
	void add(string &s)
	{
		if (all.find(s) != all.end())
			return;
		all.insert(s);
		Trie_node *found = part[0].root;
		part2[0].insert(s);
		size1[0] += s.size();
		part[0].insert(s);
		if (size1[0] > group[0])
			rebuild(0);
		else
		{
			part[0].clear_fail(part[0].root);
			part[0].compute_fail();
		}
	}
	void Delete(string &s)
	{
		int flag = 1;
		for (int i = 0; i <= p2; ++i)
		{
			if (part2[i].find(s) != part2[i].end())
			{
				part2[i].erase(s);
				Trie_node *found = part[i].root;
				for (auto &p : s)
				{
					if (found->next[p - '0'] != NULL)
						found = found->next[p - '0'];
					else
					{
						flag = 0;
						break;
					}
				}
				if (flag)
				{
					found->end -= 1;
					part[i].clear_fail(part[i].root);
					part[i].compute_fail();
				}
				break;
			}
		}
	}
	long match(string &s)
	{
		long ans = 0;
		for (int i = 0; i <= p2; ++i)
		{
			Trie_node *found = part[i].root, *found2 = NULL;
			for (auto & p : s)
			{
				if (found->next[p - '0'] != NULL)
					found = found->next[p - '0'];
				else
				{
					while (found != part[i].root && found->next[p - '0'] == NULL)
						found = found->fail;
					if (found->next[p - '0'] != NULL)
						found = found->next[p - '0'];
				}
				ans += found->end2;
			}
		}
		return ans;
	}
	void rebuild(int s)
	{
		if (s + 1 > p2)
			p2 = s + 1;
		for (auto &p : part2[s])
			part2[s + 1].insert(p);
		size1[s + 1] += size1[s];
		size1[s] = 0;
		part2[s].clear();
		part[s].clear();
		if (size1[s + 1] > group[s + 1])
			rebuild(s + 1);
		else
		{
			part[s + 1].clear();
			for (auto p : part2[s + 1])
				part[s + 1].insert(p);
			part[s + 1].clear_fail(part[s + 1].root);
			part[s + 1].compute_fail();
		}
	}
};
*/
/*
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	string a, b;
	int c, d,cas=0;
	int ans[100005];
	while (cin>>a)
	{
		memset(ans, 0, sizeof(ans));
		cas++;
		Trie part,part2;
		cin >> c;
		for (int i = 0; i < c; ++i)
		{
			cin >> d >> b;
			if (d == 0)
				part.insert(b, i);
			else
				part2.insert(b, i);
		}
		Trie_node *p1=part.root, *p2=part2.root;
		for (auto &s : a)
		{
			if (p1->next[s - 'a'] != NULL)
				p1=p1->next[s - 'a'];
			else
			{
				while (p1 != part.root && p1->next[s - 'a'] != NULL)
					p1 = p1->fail;
				if (p1->next[s - 'a'] != NULL)
					p1 = p1->next[s - 'a'];
			}
			p1->ans++;
		}

		for (auto &s : a)
		{
			if (p2->next[s - 'a'] != NULL)
				p2 = p2->next[s - 'a'];
			else
			{
				while (p2 != part.root && p2->next[s - 'a'] != NULL)
					p2 = p2->fail;
				if (p2->next[s - 'a'] != NULL)
					p2 = p2->next[s - 'a'];
			}
			p2->ans++;
		}
	}
}*/