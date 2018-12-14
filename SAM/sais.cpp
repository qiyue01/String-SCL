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

namespace SuffixArray {

	const int MAXN = 500010;

	int sa[MAXN], rk[MAXN], ht[MAXN];
	bool t[MAXN << 1];

	inline bool islms(const int i, const bool *t) {
		return i > 0 && t[i] && !t[i - 1];
	}

	template<class T>
	inline void sort(T s, int *sa, const int len, const int sz, const int sigma,
		bool *t, int *b, int *cb, int *p) {
		memset(b, 0, sizeof(int) * sigma);
		memset(sa, -1, sizeof(int) * len);
		for (register int i = 0; i < len; i++) b[s[i]]++;
		cb[0] = b[0];
		for (register int i = 1; i < sigma; i++) cb[i] = cb[i - 1] + b[i];
		for (register int i = sz - 1; i >= 0; i--) sa[--cb[s[p[i]]]] = p[i];
		for (register int i = 1; i < sigma; i++) cb[i] = cb[i - 1] + b[i - 1];
		for (register int i = 0; i < len; i++) if (sa[i] > 0 && !t[sa[i] - 1])
			sa[cb[s[sa[i] - 1]]++] = sa[i] - 1;
		cb[0] = b[0];
		for (register int i = 1; i < sigma; i++) cb[i] = cb[i - 1] + b[i];
		for (register int i = len - 1; i >= 0; i--) if (sa[i] > 0 && t[sa[i] - 1])
			sa[--cb[s[sa[i] - 1]]] = sa[i] - 1;
	}

	template<class T>
	inline void sais(T s, int *sa, const int len, bool *t, int *b, int *b1, const int sigma) {
		register int i, j, x, p = -1, cnt = 0, sz = 0, *cb = b + sigma;
		for (t[len - 1] = 1, i = len - 2; i >= 0; i--) t[i] = s[i] < s[i + 1] ||
			(s[i] == s[i + 1] && t[i + 1]);
		for (i = 1; i < len; i++) if (t[i] && !t[i - 1]) b1[sz++] = i;
		sort(s, sa, len, sz, sigma, t, b, cb, b1);
		for (i = sz = 0; i < len; i++) if (islms(sa[i], t)) sa[sz++] = sa[i];
		for (i = sz; i < len; i++) sa[i] = -1;
		for (i = 0; i < sz; i++) {
			for (x = sa[i], j = 0; j < len; j++) {
				if (p == -1 || s[x + j] != s[p + j] || t[x + j] != t[p + j]) {
					cnt++, p = x;
					break;
				}
				else if (j > 0 && (islms(x + j, t) || islms(p + j, t))) {
					break;
				}
			}
			sa[sz + (x >>= 1)] = cnt - 1;
		}
		for (i = j = len - 1; i >= sz; i--) if (sa[i] >= 0) sa[j--] = sa[i];
		register int *s1 = sa + len - sz, *b2 = b1 + sz;
		if (cnt < sz) sais(s1, sa, sz, t + len, b, b1 + sz, cnt);
		else for (i = 0; i < sz; i++) sa[s1[i]] = i;
		for (i = 0; i < sz; i++) b2[i] = b1[sa[i]];
		sort(s, sa, len, sz, sigma, t, b, cb, b2);
	}

	template<class T>
	inline void getHeight(T s, int n) {
		for (register int i = 1; i <= n; i++) rk[sa[i]] = i;
		register int j = 0, k = 0;
		for (register int i = 0; i < n; ht[rk[i++]] = k)
			for (k ? k-- : 0, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; k++);
	}

	template<class T>
	inline void init(T s, const int len, const int sigma) {
		sais(s, sa, len, t, rk, ht, sigma);
	}
}
using namespace SuffixArray;
