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

using namespace std;
/*
const int sigma = 26;
struct Trie_node
{
	Trie_node *next[sigma];
	Trie_node *fail;
	int sign;
	void clear()
	{
		memset(next, 0, sizeof(next));
		fail = 0;
	}
};
Trie_node pool[1503000], *cur;
void init()
{
	cur = pool;
}
Trie_node *newnode()
{
	cur->clear();
	cur->sign = cur - pool + 1;
	return cur++;
}
vector<int> last;
Trie_node * queue1[1010000];
struct Trie
{
	Trie_node *root;
	Trie()
	{
		root = newnode();
	}
	void insert(string &l, int k)
	{
		Trie_node *found = root;
		for (auto &s : l)
		{
			if (found->next[s - 'a'] != NULL)
				found = found->next[s - 'a'];
			else
			{
				found->next[s - 'a'] = newnode();
				found = found->next[s - 'a'];
			}
		}
		last[k] = found->sign;
	}

	int head, tail;
	void compute_fail()
	{
		head = 1;
		tail = 2;
		queue1[1] = root;
		while (head != tail)
		{
			Trie_node *part2 = NULL;
			Trie_node *father = queue1[head];
			head++;
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
								break;
							}
							part2 = part2->fail;
						}
						if (part2 == NULL)
							father->next[s]->fail = root;
					}
					queue1[tail++] = (father->next[s]);
				}
			}
		}
	}
	void bfs()
	{
		for (int i = 0; i < sigma; ++i)
			if (!root->next[i])
				root->next[i] = root;
			else
				que1.push(root->next[i]);
		while (!que1.empty())
		{
			auto it = que1.front();
			que1.pop();
			for (int i = 0; i < sigma; ++i)
				if (!it->next[i])
					it->next[i] = it->fail->next[i];
				else
					que1.push(it->next[i]);
		}
	}
	void clear()
	{
		root = newnode();
	}
};
*/