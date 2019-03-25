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

using namespace std;
const long long N = 1e5 + 5;
const long long inf = 1e18;
const long long base = 9973;

char s[N];
long long lcp[N], ans, prio[N];
long long root, tag[N], ch[N][2];
long long n, tot, Size[N];; unsigned long long hsh[N], pw[N];

bool cmp(long long x, long long y) {
	return s[x] < s[y] or s[x] == s[y] and tag[x - 1] < tag[y - 1];
}

void dfs(long long x, long long l, long long r) {
	if (!x) return;
	long long mid = l + r >> 1;
	tag[x] = mid;
	dfs(ch[x][0], l, mid - 1), dfs(ch[x][1], mid + 1, r);
	Size[x] = Size[ch[x][0]] + Size[ch[x][1]] + 1;
}

void rotate(long long &x, long long d, long long l, long long r) {
	long long y = ch[x][d], z = ch[y][d ^ 1];
	ch[y][d ^ 1] = x; ch[x][d] = z;
	x = y; dfs(x, l, r);
}

void insert(long long &x, long long l, long long r) {
	if (!x) {
		x = tot; tag[x] = l + r >> 1;
		Size[x] = 1; ch[x][0] = ch[x][1] = 0;
		prio[x] = rand(); return;
	} long long d = cmp(x, tot), mid = l + r >> 1;
	Size[x]++;
	if (d) insert(ch[x][d], mid + 1, r);
	else insert(ch[x][d], l, mid - 1);
	if (prio[ch[x][d]] < prio[x]) rotate(x, d, l, r);
}

long long find(long long x, long long now) { //²éÑ¯SA
	if (x == now) return Size[ch[x][0]] + 1;
	long long d = cmp(x, now);
	if (d) return Size[ch[x][0]] + 1 + find(ch[x][1], now);
	else return find(ch[x][0], now);
}

long long kth(long long x, long long k) { //²éÑ¯rank
	if (!x) return 0;
	if (Size[ch[x][0]] == k - 1) return x;
	if (Size[ch[x][0]] >= k) return kth(ch[x][0], k);
	return kth(ch[x][1], k - Size[ch[x][0]] - 1);
}

bool eq(long long l1, long long l2, long long len) {
	unsigned long long a = hsh[l1 + len - 1] - hsh[l1 - 1] * pw[len], b = hsh[l2 + len - 1] - hsh[l2 - 1] * pw[len];
	return a == b;
}

long long getlcp(long long a, long long b) {
	long long l = 1, r = min(a, b), ans = 0;
	while (l <= r) {
		long long mid = l + r >> 1;
		if (eq(a - mid + 1, b - mid + 1, mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	} return ans;
}

void insert(long long x) {
	s[++tot] = s[x]; hsh[tot] = hsh[tot - 1] * base + s[x] - 'a';
	insert(root, 1, inf);
	long long a = find(root, tot), b = kth(root, a - 1), c = kth(root, a + 1);
	ans -= lcp[c];
	lcp[tot] = getlcp(b, tot), lcp[c] = getlcp(tot, c);
	ans += lcp[tot] + lcp[c];
}

long long merge(long long x, long long y) {
	if (!x or !y) return x + y;
	if (prio[x] < prio[y]) {
		ch[x][1] = merge(ch[x][1], y);
		return x;
	}
	else {
		ch[y][0] = merge(x, ch[y][0]);
		return y;
	}
}

void remove(long long &x, long long l, long long r) {
	if (x == tot) {
		x = merge(ch[x][0], ch[x][1]);
		dfs(x, l, r); return;
	}
	else {
		Size[x]--;
		long long mid = l + r >> 1, d = cmp(x, tot);
		if (d) remove(ch[x][d], mid + 1, r);
		else remove(ch[x][d], l, mid - 1);
	}
}

void del() {
	long long rk = find(root, tot);
	long long b = kth(root, rk - 1), c = kth(root, rk + 1);
	ans -= lcp[tot] + lcp[c];
	lcp[c] = getlcp(b, c);
	ans += lcp[c];
	remove(root, 1, inf);
	tot--;
}
void init()
{
	srand(19990120);
	pw[0] = 1; for (long long i = 1; i <= n; i++) pw[i] = pw[i - 1] * base;
}
