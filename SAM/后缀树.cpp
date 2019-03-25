#include "pch.h"
// luogu-judger-enable-o2

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
namespace Suffix_Tree
{
	/*
	*每个节点start为出现最早的后缀位置
	*
	*
	*
	*/
	const int maxn = 200010;
	const int maxc = 29;
	struct ST {
		const static int inf = 1e9;
		int last[maxn];
		int t[maxn][maxc], len[maxn], start[maxn], link[maxn], s[maxn], tot, n, rem, now, pool[maxn];
		int cnt;
		int ans[maxn], calc[maxn], pre[maxn];
		int cur_len;
		ST() :tot(1), n(0), rem(0), now(1) { len[0] = inf; }
		void init()
		{
			memset(t, 0, sizeof(t));
			memset(start, 0, sizeof(start));
			memset(len, 0, sizeof(len));
			memset(last, 0, sizeof(last));
			tot = 1;
			n = 0;
			rem = 0;
			now = 1;
			len[0] = inf;
		}
		int node(int sta, int l) {
			start[++tot] = sta, len[tot] = l, link[tot] = 1;
			return tot;
		}
		void add(int x) {
			s[++n] = x, ++rem;
			for (int last = 1; rem;) {
				while (rem > len[t[now][s[n - rem + 1]]]) rem -= len[now = t[now][s[n - rem + 1]]];
				int ed = s[n - rem + 1];
				int &v = t[now][ed];
				int c = s[start[v] + rem - 1];
				if (!v) {
					v = node(n - rem + 1, inf);
					link[last] = now;
					last = now;
				}
				else if (x == c) {
					link[last] = now;
					last = now;
					break;
				}
				else {
					int u = node(start[v], rem - 1);
					t[u][x] = node(n, inf);
					t[u][c] = v, start[v] += rem - 1, len[v] -= rem - 1;
					link[last] = v = u, last = v;
				}
				if (now == 1) --rem; else now = link[now];
			}
		}
		void dfs(int cur) //深搜处理信息，需要先初始化
		{
			if (len[cur] > 2e8)
			{
				ans[cur] += n - start[cur];
				return;
			}
			ans[cur] += len[cur];
			for (int i = 1; i <= 26; ++i)
				if (t[cur][i])
				{
					ans[t[cur][i]] += ans[cur];
					dfs(t[cur][i]);
					pre[t[cur][i]] = cur;
				}
		}
		void get_last()
		{
			for (int i = 1; i <= tot; ++i)
				if (t[i][27] || len[i] > 2e8)
					last[cur_len - ans[i] + 1] = i;
		}
		void topo() //广搜+剪枝处理信息，能同时递推出拓扑序
		{
			cnt = 0;
			memset(ans, 0, sizeof(ans));
			memset(calc, 0, sizeof(calc));
			queue<int> que;
			que.push(1);
			int cur;
			while (!que.empty())
			{
				cur = que.front();
				que.pop();
				pool[cnt++] = cur;
				if (len[cur] > 2e8)
					ans[cur] += n - start[cur];
				else
					ans[cur] += len[cur];
				if (t[cur][27])
					calc[cur] = 1;
				else if (len[cur] > 2e8)
				{
					calc[cur] = 1;
					continue;
				}
				for (int i = 1; i < 27; ++i)
					if (t[cur][i])
					{
						que.push(t[cur][i]);
						ans[t[cur][i]] += ans[cur];
						pre[t[cur][i]] = cur;
					}
			}
		}
	} st;
}
using namespace Suffix_Tree;

