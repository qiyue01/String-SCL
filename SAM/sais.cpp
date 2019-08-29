#include "pch.h"
/*
namespace SuffixArray {

	const int MAXN =1001000;
	// sa下标范围[1,n]，和rk映射出的字符串位置从0数起 ht的下标从2开始有实用意义
int sa[MAXN], rk[MAXN], ht[MAXN];
bool t[MAXN << 1];

inline bool islms(const int i, const bool *t) {
	return i > 0 && t[i] && !t[i - 1];
}
template<typename T>
inline void sort(T s, int *sa, const int len, const int sz, const int sigma,
	bool *t, int *b, int *cb, int *p) {
	memset(b, 0, sizeof(int) * sigma);
	memset(sa, -1, sizeof(int) * len);
	for (int i = 0; i < len; i++) b[s[i]]++;
	cb[0] = b[0];
	for (int i = 1; i < sigma; i++)
		cb[i] = cb[i - 1] + b[i];
	for (int i = sz - 1; i >= 0; i--)
		sa[--cb[s[p[i]]]] = p[i];
	for (int i = 1; i < sigma; i++)
		cb[i] = cb[i - 1] + b[i - 1];
	for (int i = 0; i < len; i++)
		if (sa[i] > 0 && !t[sa[i] - 1])
			sa[cb[s[sa[i] - 1]]++] = sa[i] - 1;
	cb[0] = b[0];
	for (int i = 1; i < sigma; i++)
		cb[i] = cb[i - 1] + b[i];
	for (int i = len - 1; i >= 0; i--)
		if (sa[i] > 0 && t[sa[i] - 1])
			sa[--cb[s[sa[i] - 1]]] = sa[i] - 1;
}
template<typename T>
inline void sais(T s, int *sa, const int len, bool *t, int *b, int *b1,
	const int sigma) {
	int i, j, x, p = -1, cnt = 0, sz = 0, *cb = b + sigma;
	for (t[len - 1] = 1, i = len - 2; i >= 0; i--)
		t[i] = s[i] < s[i + 1] || (s[i] == s[i + 1] && t[i + 1]);
	for (i = 1; i < len; i++)
		if (t[i] && !t[i - 1])
			b1[sz++] = i;
	sort(s, sa, len, sz, sigma, t, b, cb, b1);
	for (i = sz = 0; i < len; i++)
		if (islms(sa[i], t))
			sa[sz++] = sa[i];
	for (i = sz; i < len; i++)
		sa[i] = -1;
	for (i = 0; i < sz; i++) {
		for (x = sa[i], j = 0; j < len; j++) {
			if (p == -1 || s[x + j] != s[p + j] || t[x + j] != t[p + j]) {
				p = x, cnt++;
				break;
			}
			else if (j > 0 && (islms(x + j, t) || islms(p + j, t))) {
				break;
			}
		}
		sa[sz + (x >>= 1)] = cnt - 1;
	}
	for (i = j = len - 1; i >= sz; i--)
		if (sa[i] >= 0)
			sa[j--] = sa[i];
	int *s1 = sa + len - sz, *b2 = b1 + sz;
	if (cnt < sz)
		sais(s1, sa, sz, t + len, b, b1 + sz, cnt);
	else for (i = 0; i < sz; i++)
		sa[s1[i]] = i;
	for (i = 0; i < sz; i++)
		b2[i] = b1[sa[i]];
	sort(s, sa, len, sz, sigma, t, b, cb, b2);
}

template<typename T>
inline void getHeight(T s, const int n) {
	for (int i = 1; i <= n; i++)
		rk[sa[i]] = i;
	for (int i = 0, j = 0, k = 0; i < n; ht[rk[i++]] = k)
		for (k ? k-- : 0, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; k++);

}

template<typename T>
inline void init(T s, const int n, const int sigma) {
	sais(s, sa, n, t, rk, ht, sigma), rk[0] = 0;
	getHeight(s, n - 1);
}
}
using namespace SuffixArray;
#define maxn 1010010
#define M 20
const int BSZ = 25, BNUM = maxn / BSZ + 10;
struct ST
{
	long long n, m;
	array<long long, maxn> s, Lmax, Rmax, bel;
	array<long long, BNUM> L, R, LG, ST[M + 1];
private:
	inline long long query(int l, int r) {
		if (l >= r)
			return LLONG_MIN;
		static int t;
		t = LG[r - l];
		return max(ST[t][l], ST[t][r - (1 << t)]);
	}
public:
	void init(int k)
	{
		n = k;
		for (int i = 1; i <= n; ++i)
			bel[i] = i / BSZ + 1;
		const int B = bel[n];
		LG[0] = -1;
		for (int i = 1; i <= B; ++i)
			LG[i] = LG[i >> 1] + 1;
		for (int i = 1; i <= B; ++i) {
			L[i] = (i - 1) * BSZ;
			R[i] = L[i] + BSZ - 1;
		}
		L[1] = 1, R[B] = n;
		long long last = LLONG_MIN;
		for (int i = 1, now = 1; i <= n; ++i) {
			Lmax[i] = last = std::max(s[i], last);
			if (i >= R[now])
				ST[0][now] = Lmax[i], last = LLONG_MIN, ++now;
		}
		last = LLONG_MIN;
		for (int i = n, now = B; i; --i)
		{
			Rmax[i] = last = max(s[i], last);
			if (i <= L[now])
				last = LLONG_MIN, --now;
		}
		for (int i = 1, pw = 1; i <= M; ++i, pw <<= 1)
		{
			for (int j = 1; j <= B; ++j)
				ST[i][j] = std::max(ST[i - 1][j], ST[i - 1][std::min(j + pw, B)]);
		}
	}
	long long query1(int l, int r)
	{
		if (l > r)
			swap(l, r);
		const int lb = bel[l], rb = bel[r];
		if (lb != rb)
			return max(max(Rmax[l], Lmax[r]), query(lb + 1, rb));
		else
		{
			static long long res;
			res = LLONG_MIN;
			for (int i = l; i <= r; ++i)
				res = max(res, s[i]);
			return res;
		}
	}
};
struct LCP
{
	ST p;
	array<int, MAXN> rk;
	void init(int *a, int *r, int n)
	{
		for (int i = 0; i <= n; ++i)
		{
			p.s[i] = -a[i];
			rk[i] = r[i];
		}
		p.init(n);
	}
	int lcp(int a, int b)
	{
		if (a == b)
			return p.n - a + 1;
		a = rk[a - 1], b = rk[b - 1];
		if (a > b)
			swap(a, b);
		return -p.query1(a + 1, b);
	}
	int lcp(int L1, int R1, int L2, int R2)
	{
		int res = lcp(L1, L2);
		return min(res, min((R1 - L1 + 1), (R2 - L2 + 1)));
	}
};
LCP lcp;
*/
