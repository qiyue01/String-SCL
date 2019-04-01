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
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <stdio.h>

using namespace std;
typedef long long int LL;
const int MAX = 1e5 + 5;
char str[MAX];
int n;
struct Tree //支持前向后向追加的回文树
{
	int next[2 * MAX][26];
	int fail[2 * MAX];
	int num[2 * MAX];
	int len[2 * MAX];
	int s[2 * MAX];
	int last[2];
	int tot[2];
	LL p;//p即为树上节点数
	int new_node(int x)
	{
		memset(next[p], 0, sizeof(next[p]));
		num[p] = 0;
		len[p] = x;
		return p++;
	}
	void init()
	{
		p = 0;
		new_node(0);
		new_node(-1);
		last[0] = 0;
		last[1] = 0;
		tot[0] = MAX - 5;
		tot[1] = MAX - 6;
		fail[0] = 1;
	}
	int get_fail(int x, int k)
	{
		s[tot[0] - 1] = -1; s[tot[1] + 1] = -1;
		while (s[tot[k]] != s[tot[k] + (k ? -1 : 1)*(len[x] + 1)])
			x = fail[x];
		return x;
	}
	int add(int x, int k) //k=0为前加 k=1为后+
	{
		x -= 'a';
		s[tot[k] += (k ? 1 : -1)] = x;
		int cur = get_fail(last[k], k);
		if (!(last[k] = next[cur][x]))
		{
			int now = new_node(len[cur] + 2);
			fail[now] = next[get_fail(fail[cur], k)][x];
			next[cur][x] = now;
			num[now] = num[fail[now]] + 1;
			last[k] = now;
			if (len[last[k]] == tot[1] - tot[0] + 1)  last[k ^ 1] = last[k];
		}
		return num[last[k]];
	}
}tree;
/*
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin.tie(NULL);
	int x, y;
	long long ans;
	char p;
	while (cin >> x)
	{
		tree.init();
		ans = 0;
		while (x--)
		{
			cin >> y;
			if (y == 1)
			{
				cin >> p;
				ans += tree.add(p, 0);
			}
			else if (y == 2)
			{
				cin >> p;
				ans += tree.add(p, 1);
			}
			else if (y == 3)
				cout << tree.p - 2 << '\n';
			else
				cout << ans << '\n';
		}
	}
	return 0;
}
*/