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
template<typename T>
vector<long> compute_prefix(const T &pattern)
{
	vector<long> prefix_function(pattern.size() + 2, 0);
	long k = -1;
	prefix_function[0] = -1;
	int q = 0;
	while (q < pattern.size())
	{
		while (k != -1 && pattern[k] != pattern[q])
			k = prefix_function[k];
		q++;
		prefix_function[q] = ++k;
	}
	return prefix_function;
}
template<typename T>
void KMP(T &file, T &pattern, int &a)
{
	long n = file.size(), m = pattern.size();
	vector<long> prefix_function = compute_prefix(pattern);
	long part = 0;
	for (int q = 0; q < n; ++q)
	{
		while (part != -1 && pattern[part] != file[q])
			part = prefix_function[part];
		part++;
		if (m == part)
		{
			a++;
			part = prefix_function[part];
		}
	}
}
vector<long> GETNEXT(string &str) //预处理计算next数组  
{
	vector<long> Next(str.size() + 5, -1);
	int i = 0, j, po, len = str.size();
	Next[0] = len;//初始化Next[0]  
	while (str[i] == str[i + 1] && i + 1 < len)//计算Next[1]  
		i++;
	Next[1] = i;
	po = 1;//初始化po的位置  
	for (i = 2; i < len; i++)
	{
		if (Next[i - po] + i < Next[po] + po)//第一种情况，可以直接得到Next[i]的值  
			Next[i] = Next[i - po];
		else//第二种情况，要继续匹配才能得到Next[i]的值  
		{
			j = Next[po] + po - i;
			if (j < 0)j = 0;//如果i>po+Next[po],则要从头开始匹配  
			while (i + j < len&&str[j] == str[j + i])//计算Next[i]  
				j++;
			Next[i] = j;
			po = i;//更新po的位置  
		}
	}
	return Next;
}
//计算extend数组
vector<long> EXKMP(string &s1, string &s2)
{
	int i = 0, j, po, len = s1.size(), l2 = s2.size();
	vector<long> next1=GETNEXT(s2);//计算子串的next数组
	vector<long> extend(max(s1.size(), s2.size()) + 1, -1);
	while (s1[i] == s2[i] && i < l2&&i < len)//计算ex[0]
		i++;
	extend[0] = i;
	po = 0;//初始化po的位置
	for (i = 1; i < len; i++)
	{
		if (next1[i - po] + i < extend[po] + po)//第一种情况，直接可以得到ex[i]的值
			extend[i] = next1[i - po];
		else//第二种情况，要继续匹配才能得到ex[i]的值
		{
			j = extend[po] + po - i;
			if (j < 0)j = 0;//如果i>ex[po]+po则要从头开始匹配
			while (i + j < len&&j < l2&&s1[j + i] == s2[j])//计算ex[i]
				j++;
			extend[i] = j;
			po = i;//更新po的位置
		}
	}
	return extend;
}

int MINR(string &p, int l) {        //s是原串（未加倍过），l是原串长   最小表示法，可以处理10e5
	string s = p + p;
	int i = 0, j = 1;                    //利用i，j指针移动
	while (i < l&&j < l) {
		int k = 0;
		while (s[i + k] == s[j + k] && k < l)++k;    //不断比较直到比较完长度为l的串或两个子串不相等
		if (k == l)return min(i, j);        //若比较出长度为l则直接返回靠前的那个串的开始位置
		if (s[i + k] > s[j + k])i = max(i + k + 1, j + 1);    //i串比j串大，那么i到i+k中的串都比j串大，i可以直接移动到i+k+1位置，而起始位置比j小的肯定都在j移动过程中比较过，所以i可以直接移动到j+1位置，因此取这两值的最大值
		else j = max(j + k + 1, i + 1);    //同上
	}
	return min(i, j);            //返回位置靠前的下标
}

int MAXR(string &p, int l) {   //最大表示法
	string s = p + p;
	int i = 0, j = 1;
	while (i < l&&j < l) {
		int k = 0;
		while (s[i + k] == s[j + k] && k < l)++k;
		if (k == l)return min(i, j);
		if (s[i + k] < s[j + k])i = max(i + k + 1, j + 1);
		else j = max(j + k + 1, i + 1);
	}
	return min(i, j);
}
void print(vector<long> &part,long k)
{
	if (k == 0)
		return;
	else
	{
		print(part, part[k]);
		cout << k << " ";
	}
}

