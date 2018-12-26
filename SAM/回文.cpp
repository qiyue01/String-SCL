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
#define For(n) for(int i=0;i<n;++i)
using namespace std;

namespace Palindromic
{
	int len[1000005];
	int str[1000005];
	int last;
	int point;
	int n;
	int Next[1000005][26];
	//map<int, int> Next[100015];
	int fail[1000005];
	int count1[1000005];
	int num[1000005];
	class Palindromic_Tree
	{
	public:

		int newnode(int l)
		{
			for (int i = 0; i < 26; ++i)
				Next[point][i] = 0;
			//Next[point].clear();
			count1[point] = 0;
			num[point] = 0;
			len[point] = l;
			return point++;
		}
		void init()
		{
			memset(len, 0, sizeof(len));
			memset(num, 0, sizeof(num));
			memset(fail, 0, sizeof(fail));
			memset(count1, 0, sizeof(count1));
			memset(str, 0, sizeof(str));
			memset(Next, 0, sizeof(Next));//
			point = 0;
			newnode(0);
			newnode(-1);
			last = 0;
			n = 0;
			str[n] = -1;
			fail[0] = 1;
		}
		int get_fail(int x)
		{
			while (str[n - len[x] - 1] != str[n])
				x = fail[x];
			return x;
		}
		int add(int c)
		{
			c -= 'a';
			str[++n] = c;
			int cur = get_fail(last);
			if (!Next[cur][c])//(Next[cur].find(c) == Next[cur].end())
			{
				int now = newnode(len[cur] + 2);
				fail[now] = Next[get_fail(fail[cur])][c];
				Next[cur][c] = now;
				num[now] = num[fail[now]] + 1;
			}
			last = Next[cur][c];
			count1[last]++;
			return num[last];
		}
		void build(string &s)
		{
			for (int i = 0; i < s.size(); ++i)
				add(s[i]);
		}
		void counting()//统计本质相同的回文串的出现次数
		{
			for (int i = point - 1; i >= 0; i--)//逆序累加，保证每个点都会比它的父亲节点先算完，于是父亲节点能加到所有子孙
				count1[fail[i]] += count1[i];
		}
	};
	int pa[1000005];
}
namespace manacher1 { //先init（）再manacher
	const int N = 11000000 + 5;
	int cnt, len, ans = 0;
	char s[N], ss[N * 2];
	int p[N * 2];

	void init() {//将每两个字符中插入一个字符
		len = strlen(s), cnt = 1;
		ss[0] = '!'; ss[cnt] = '#';
		for (int i = 0; i < len; i++)
			ss[++cnt] = s[i], ss[++cnt] = '#';
		ans = 0;
	}

	void manacher() {
		int pos = 0, mx = 0;
		for (int i = 1; i <= cnt; i++) {
			if (i < mx) p[i] = min(p[pos * 2 - i], mx - i);
			else p[i] = 1;
			while (ss[i + p[i]] == ss[i - p[i]]) p[i]++;
			if (mx < i + p[i]) mx = i + p[i], pos = i;
			ans = max(ans, p[i] - 1);
		}
	}
}
using namespace Palindromic;