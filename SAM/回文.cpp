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
	const int sigma = 29;
	const int N = 550000;

	class Palindromic_Tree
	{
	public:
		int len[N];//�Խڵ�iΪ��β�Ļ��Ĵ��ĳ���
		int str[N];//��i����ӵ��ַ�
		int last;
		int point;
		int n;
		int Next[N][sigma];
		//map<int, int> Next[100015];
		int fail[N];//������AC�Զ�����failָ�룬ָ��ʧ�����Ҫ��ת���Ľڵ㣨��Ϊi������ĺ�׺�Ҳ�Ϊi��
		int count1[N];//�ڵ�i��ʾ�Ļ��Ĵ���S�г��ֵĴ���������ʱ����Ĳ�����ȫ�ģ�count()�����ӽڵ��Ժ������ȷ�ģ�
		int num[N];//�Խڵ�i���Ĵ���ĩβ�ַ���β�ĵ�����������·���ϵĻ��Ĵ�����Ŀ��(Ҳ����failָ��·�������)
		int trans[N];//ÿ���ַ�i��Ӧ��lastָ��
		int half[N];//ÿ���ڵ��Ӧ�Ļ��ļ����ָ��
		int newnode(int l)
		{
			for (int i = 0; i < sigma; ++i)
				Next[point][i] = 0;
			//Next[point].clear();
			count1[point] = 0;
			num[point] = 0;
			len[point] = l;
			half[point] = 0;
			return point++;
		}
		void init()
		{
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
		void add(int c)
		{
			c = c - 'a' + 1;
			str[++n] = c;
			int cur = get_fail(last);
			if (!Next[cur][c])//(Next[cur].find(c) == Next[cur].end())
			{
				int now = newnode(len[cur] + 2);
				fail[now] = Next[get_fail(fail[cur])][c];
				Next[cur][c] = now;
				num[now] = num[fail[now]] + 1;
				if (len[now] <= 2)  //��halfָ���
				{
					half[now] = fail[now];
				}
				else
				{
					int tmp = half[cur];
					while (str[n - len[tmp] - 1] != str[n] || ((len[tmp] + 2) << 1) > len[now]) tmp = fail[tmp];
					//��չ��ĳ���Ϊlen[tmp]+2
					half[now] = Next[tmp][c];
				}
			}
			last = Next[cur][c];
			count1[last]++;
			trans[n] = last;
		}
		void build(string &s)
		{
			for (int i = 0; i < s.size(); ++i)
				add(s[i]);
		}
		void counting()//ͳ�Ʊ�����ͬ�Ļ��Ĵ��ĳ��ִ���
		{
			for (int i = point - 1; i >= 0; i--)//�����ۼӣ���֤ÿ���㶼������ĸ��׽ڵ������꣬���Ǹ��׽ڵ��ܼӵ���������
				count1[fail[i]] += count1[i];
		}
	} tree;
}
using namespace Palindromic;

namespace Palindromic2 //�ڴ�ѹ����
{
	const int sigma = 26;
	const int N = 2010000;
	int len[N];//�Խڵ�iΪ��β�Ļ��Ĵ��ĳ���
	int str[N];//��i����ӵ��ַ�
	int last;
	int point;
	int n;
	//int Next[N][sigma];
	vector<pair<int, int> > Next[N];
	int fail[N];//������AC�Զ�����failָ�룬ָ��ʧ�����Ҫ��ת���Ľڵ㣨��Ϊi������ĺ�׺�Ҳ�Ϊi��
	//int count1[N];//�ڵ�i��ʾ�Ļ��Ĵ���S�г��ֵĴ���������ʱ����Ĳ�����ȫ�ģ�count()�����ӽڵ��Ժ������ȷ�ģ�
	int num[N];//�Խڵ�i���Ĵ���ĩβ�ַ���β�ĵ�����������·���ϵĻ��Ĵ�����Ŀ��(Ҳ����failָ��·�������)
	//int trans[N];//ÿ���ַ�i��Ӧ��lastָ��
	class Palindromic_Tree
	{
	public:

		int newnode(int l)
		{
			//for (int i = 0; i < sigma; ++i)
				//Next[point][i] = 0;
			Next[point].clear();
			//count1[point] = 0;
			num[point] = 0;
			len[point] = l;
			return point++;
		}
		int find(int k, int c)
		{
			for (int i = 0; i < Next[k].size(); ++i)
				if (Next[k][i].first == c)
					return i;
			return -1;
		}
		void init2()
		{
			for (int i = 0; i <= point + 100; ++i)
				Next[i].clear();
			init();
		}
		void init()
		{
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
		void add(int c)
		{
			c -= 'a';
			str[++n] = c;
			int cur = get_fail(last);
			if (find(cur, c) == -1)//(!Next[cur][c])
			{
				int now = newnode(len[cur] + 2);
				int kk = get_fail(fail[cur]);
				if (find(kk, c) == -1)
					fail[now] = 0;
				else
					fail[now] = Next[kk][find(kk, c)].second;
				Next[cur].push_back(make_pair(c, now));
				num[now] = num[fail[now]] + 1;
			}
			last = Next[cur][find(cur, c)].second;
			//count1[last]++;
			//trans[n] = last;
		}
		void build(string &s)
		{
			for (int i = 0; i < s.size(); ++i)
				add(s[i]);
		}
		/*
		void counting()//ͳ�Ʊ�����ͬ�Ļ��Ĵ��ĳ��ִ���
		{
			for (int i = point - 1; i >= 0; i--)//�����ۼӣ���֤ÿ���㶼������ĸ��׽ڵ������꣬���Ǹ��׽ڵ��ܼӵ���������
				count1[fail[i]] += count1[i];
		}
		*/
	} tree;
}
using namespace Palindromic2;
namespace manacher1 { //��init������manacher
	const int N = 11000000 + 5;
	int cnt, len, ans = 0;
	char s[N], ss[N * 2];
	int p[N * 2];

	void init() {//��ÿ�����ַ��в���һ���ַ�
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