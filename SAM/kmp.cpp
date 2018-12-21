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
vector<long> GETNEXT(string &str) //Ԥ�������next����  
{
	vector<long> Next(str.size() + 5, -1);
	int i = 0, j, po, len = str.size();
	Next[0] = len;//��ʼ��Next[0]  
	while (str[i] == str[i + 1] && i + 1 < len)//����Next[1]  
		i++;
	Next[1] = i;
	po = 1;//��ʼ��po��λ��  
	for (i = 2; i < len; i++)
	{
		if (Next[i - po] + i < Next[po] + po)//��һ�����������ֱ�ӵõ�Next[i]��ֵ  
			Next[i] = Next[i - po];
		else//�ڶ��������Ҫ����ƥ����ܵõ�Next[i]��ֵ  
		{
			j = Next[po] + po - i;
			if (j < 0)j = 0;//���i>po+Next[po],��Ҫ��ͷ��ʼƥ��  
			while (i + j < len&&str[j] == str[j + i])//����Next[i]  
				j++;
			Next[i] = j;
			po = i;//����po��λ��  
		}
	}
	return Next;
}
//����extend����
vector<long> EXKMP(string &s1, string &s2)
{
	int i = 0, j, po, len = s1.size(), l2 = s2.size();
	vector<long> next1=GETNEXT(s2);//�����Ӵ���next����
	vector<long> extend(max(s1.size(), s2.size()) + 1, -1);
	while (s1[i] == s2[i] && i < l2&&i < len)//����ex[0]
		i++;
	extend[0] = i;
	po = 0;//��ʼ��po��λ��
	for (i = 1; i < len; i++)
	{
		if (next1[i - po] + i < extend[po] + po)//��һ�������ֱ�ӿ��Եõ�ex[i]��ֵ
			extend[i] = next1[i - po];
		else//�ڶ��������Ҫ����ƥ����ܵõ�ex[i]��ֵ
		{
			j = extend[po] + po - i;
			if (j < 0)j = 0;//���i>ex[po]+po��Ҫ��ͷ��ʼƥ��
			while (i + j < len&&j < l2&&s1[j + i] == s2[j])//����ex[i]
				j++;
			extend[i] = j;
			po = i;//����po��λ��
		}
	}
	return extend;
}

int MINR(string &p, int l) {        //s��ԭ����δ�ӱ�������l��ԭ����   ��С��ʾ�������Դ���10e5
	string s = p + p;
	int i = 0, j = 1;                    //����i��jָ���ƶ�
	while (i < l&&j < l) {
		int k = 0;
		while (s[i + k] == s[j + k] && k < l)++k;    //���ϱȽ�ֱ���Ƚ��곤��Ϊl�Ĵ��������Ӵ������
		if (k == l)return min(i, j);        //���Ƚϳ�����Ϊl��ֱ�ӷ��ؿ�ǰ���Ǹ����Ŀ�ʼλ��
		if (s[i + k] > s[j + k])i = max(i + k + 1, j + 1);    //i����j������ôi��i+k�еĴ�����j����i����ֱ���ƶ���i+k+1λ�ã�����ʼλ�ñ�jС�Ŀ϶�����j�ƶ������бȽϹ�������i����ֱ���ƶ���j+1λ�ã����ȡ����ֵ�����ֵ
		else j = max(j + k + 1, i + 1);    //ͬ��
	}
	return min(i, j);            //����λ�ÿ�ǰ���±�
}

int MAXR(string &p, int l) {   //����ʾ��
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

