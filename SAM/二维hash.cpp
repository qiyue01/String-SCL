// 草稿12.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
