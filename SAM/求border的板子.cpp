const int N = 450005;
char s[N];
int pos[N], Ans[N], m;

struct Node {
	int id, l, r;
}; vector<Node> q[N];

struct SegmentTree {
	int val[N * 25], lc[N * 25], rc[N * 25], rt[N * 10], size;
	inline SegmentTree() { memset(val, 127, sizeof(val)); }
	inline void ins(int &u, int l, int r, int pos, int x) {
		if (!u) u = ++size;
		if (l == r) return (void)(val[u] = min(val[u], x));
		int mid = l + r >> 1;
		if (pos <= mid) ins(lc[u], l, mid, pos, x);
		else ins(rc[u], mid + 1, r, pos, x);
		val[u] = min(val[lc[u]], val[rc[u]]);
	}
	inline int query(int u, int l, int r, int pos, int lim) {
		if (!u) return 0;
		if (l == r) return val[u] < lim ? l : 0;
		int mid = l + r >> 1, res = 0;
		if (mid + 1 >= pos) return query(lc[u], l, mid, pos, lim);
		if (val[rc[u]] < lim) res = query(rc[u], mid + 1, r, pos, lim);
		if (!res) return query(lc[u], l, mid, pos, lim); else return res;
	}
	inline int merge(int x, int y, int l, int r) {
		if (!x || !y) return x + y;
		int o = ++size, mid = l + r >> 1;
		if (l == r) val[o] = min(val[x], val[y]);
		else {
			lc[o] = merge(lc[x], lc[y], l, mid);
			rc[o] = merge(rc[x], rc[y], mid + 1, r);
			val[o] = min(val[lc[o]], val[rc[o]]);
		}
		return o;
	}
}T1, T2;

namespace Sam {
	vector<int> g[N];
	vector< pair<int, int> > s[N];
	int sz[N], top[N], ms[N];
	int ch[N][26], len[N], fa[N], id[N], size = 1, tail = 1;

	inline int newnode(int x) { return len[++size] = x, size; }
	inline void ins(int c, int x) {
		int p = tail, np = newnode(len[p] + 1);
		pos[x] = np, id[np] = x;
		for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
		if (!p) return (void)(fa[np] = 1, tail = np);
		int q = ch[p][c];
		if (len[q] == len[p] + 1) fa[np] = q;
		else {
			int nq = newnode(len[p] + 1);
			fa[nq] = fa[q], fa[q] = fa[np] = nq;
			for (int i = 0; i < 26; i++) ch[nq][i] = ch[q][i];
			for (; p && ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
		}tail = np;
	}
	inline void addedge() {
		for (int i = 2; i <= size; i++) g[fa[i]].push_back(i);
	}
	inline void Buildtree(int u) {
		if (id[u]) T1.ins(T1.rt[u], 1, size, id[u], id[u]);
		sz[u] = 1;
		for (int i = 0; i < (int)g[u].size(); i++) {
			int v = g[u][i]; Buildtree(v);
			T1.rt[u] = T1.merge(T1.rt[u], T1.rt[v], 1, size);
			sz[u] += sz[v];
			if (sz[v] > sz[ms[u]]) ms[u] = v;
		}
	}
	inline void prework(int u, int x) {
		if (id[u]) s[x].push_back({ id[u], id[u] - len[x] });
		for (int i = 0; i < (int)g[u].size(); i++) prework(g[u][i], x);
	}
	inline void dfs(int u, int chain) {
		top[u] = chain;
		if (id[u]) s[u].push_back({ id[u], id[u] - len[u] });
		if (ms[u]) dfs(ms[u], chain);
		for (int i = 0; i < (int)g[u].size(); i++) {
			int v = g[u][i];
			if (v != ms[u]) dfs(v, v), prework(v, u);
		}
	}
	inline void Doit() { addedge(), Buildtree(1), dfs(1, 1); }//³õÊ¼»¯½¨Ê÷
	inline int query(int u, int l, int r, Node Query) {
		int res = T1.query(T1.rt[u], 1, size, r, l + len[u]);
		while (u) {
			q[u].push_back(Query), u = fa[top[u]];
			if (!u) break;
			res = max(res, T1.query(T1.rt[u], 1, size, r, l + len[u]));
		}
		return res < l ? 0 : res - l + 1;
	}
	inline void solve(int u) {
		for (int i = 0; i < (int)s[u].size(); i++)
			T2.ins(T2.rt[top[u]], 1, size, s[u][i].first, s[u][i].second);
		for (int i = 0; i < (int)q[u].size(); i++) {
			int l = q[u][i].l, r = q[u][i].r;
			int now = T2.query(T2.rt[top[u]], 1, size, r, l);
			Ans[q[u][i].id] = max(Ans[q[u][i].id], (now < l ? 0 : now - l + 1));
		}
		for (int i = 0; i < (int)g[u].size(); i++) solve(g[u][i]);
	}
}
void addquery(int i, int l, int r)
{
	Node p;
	p.id = i, p.l = l, p.r = r;
	Ans[i] = Sam::query(pos[r], l, r, p);
}