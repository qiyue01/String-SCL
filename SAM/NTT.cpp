
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
#include<array>
#include<memory>
#include<functional>
#include<unordered_map>
#include<complex>
typedef unsigned long long uLL;

const int MAXN = 1 << 21 | 1;
const int MOD = 998244353;
const int G = 3;

int k;

int n, m;
int a[MAXN], b[MAXN], w[MAXN];

inline int modPow(int a, int b) {
	int ret = 1;
	for (; b; b >>= 1, a = (uLL)a * a % MOD)
		if (b & 1) ret = (uLL)ret * a % MOD;
	return ret;
}

inline void init(int k) {
	int bn = k >> 1;
	w[bn + 0] = 1;
	w[bn + 1] = modPow(G, (MOD - 1) / k);
	for (int i = 2; i < bn; i++)
		w[bn + i] = (unsigned long long)w[bn + i - 1] * w[bn + 1] % MOD;
	for (int i = bn - 1; i > 0; i--) w[i] = w[i << 1];
}

inline void ntt(int *a, int n, int f) {
	for (int i = 0, j = 0; i < n; i++) {
		if (i > j) std::swap(a[i], a[j]);
		for (int k = n >> 1; (j ^= k) < k; k >>= 1)
			;
	}
	for (int i = 1; i < n; i <<= 1) {
		for (int j = 0; j < n; j += i << 1) {
			int *x = a + j, *y = a + i + j, *w = ::w + i;
			for (int k = 0, t; k < i; k++) {
				t = (uLL)w[k] * y[k] % MOD;
				y[k] = (x[k] - t <= 0 ? x[k] - t + MOD : x[k] - t);
				x[k] = (x[k] + t >= MOD ? x[k] + t - MOD : x[k] + t);
			}
		}
	}
	if (f == -1) {
		std::reverse(a + 1, a + n);
		const int inv = modPow(n, MOD - 2);
		for (int i = 0; i < n; i++) a[i] = (uLL)a[i] * inv % MOD;
	}
}
const int OUT_LEN = 13000000;

char obuf[OUT_LEN], *oh = obuf;
std::streambuf *fb;

inline void print(char c) {
	oh == obuf + OUT_LEN ? (fb->sputn(obuf, OUT_LEN), oh = obuf) : 0;
	*oh++ = c;
}

template <class T>
inline void print(T x) {
	static int buf[30], cnt;
	if (x == 0)
	{
		print('0');
		return;
	}
	for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
	while (cnt) print((char)buf[cnt--]);
}

inline void flush() { fb->sputn(obuf, oh - obuf); }
using namespace std;
/*
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	fb = std::cout.rdbuf();
	int n, m, mn;
	cin >> n >> m;
	k = 1;
	for (; k < n + m + 2;) k <<= 1;
	init(k);
	for (int i = 0; i <= n; ++i)
	{
		cin >> a[i];
	}
	ntt(a, k, 1);
	for (int i = 0; i <= m; ++i)
	{
		cin >> b[i];
	}
	ntt(b, k, 1);

	for (int i = 0; i < k; ++i)
	{
		b[i] = (uLL)a[i] * b[i] % MOD;
	}
	ntt(b, k, -1);
	for (int i = 0; i <= m + n; ++i)
		print(b[i]), print(' ');
	flush();
	return 0;
}
*/



