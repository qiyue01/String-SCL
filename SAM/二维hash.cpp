// �ݸ�12.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include "pch.h"
/*
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
typedef bool boolean;

const unsigned int hash1 = 131, hash2 = 233;
const int N = 1005, M = 105;

int p1[N], p2[N];
int m, n, x, y;
char S[N][N], T[M][M];
unsigned int hs[N][N];

inline void prepare() {
	p1[0] = 1, p2[0] = 1;
	for (int i = 1; i < N; i++)
		p1[i] = p1[i - 1] * hash1;
	for (int i = 1; i < N; i++)
		p2[i] = p2[i - 1] * hash2;
}

inline void solve() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			hs[i][j] = hs[i - 1][j - 1] * hash1 * hash2 + (hs[i - 1][j] - hs[i - 1][j - 1] * hash2) * hash1 + (hs[i][j - 1] - hs[i - 1][j - 1] * hash1) * hash2 + S[i][j];
		}


	int rt = 0;
	unsigned int s = 0, c;
	for (int i = 1; i <= x; i++)
		for (int j = 1; j <= y; j++)
			s += T[i][j] * p1[x - i] * p2[y - j];
	for (int i = x; i <= n; i++)
		for (int j = y; j <= m; j++) {
			c = hs[i][j] - hs[i - x][j - y] * p1[x] * p2[y] - (hs[i][j - y] - hs[i - x][j - y] * p1[x]) * p2[y] - (hs[i - x][j] - hs[i - x][j - y] * p2[y]) * p1[x];
			if (s == c)
				rt++;
		}
	cout << rt << endl;
}

int kase;
int main() {
	prepare();
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				cin >> S[i][j];
		cin >> x >> y;
		for (int i = 1; i <= x; ++i)
			for (int j = 1; j <= y; ++j)
				cin >> T[i][j];
		solve();
	}
	return 0;
}*/

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ������ʾ: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
