namespace trie01
{
	const int sigma = 20;
	long long base = 1;
	struct node
	{
		node *child[2];
		int times;
		int element;
		bool lazy;
		void clear()
		{
			lazy = times = element = 0;
		}
	};
	node *history[200000];
	node _pool[5000000];
	node *root, *cur = _pool, *null;
	node *new_()
	{
		cur->clear();
		cur->child[0] = cur->child[1] = null;
		return cur++;
	}
	void init()
	{
		null = new node();
		null->times = null->element = null->lazy = 0;
		null->child[0] = null->child[1] = null;
		cur = _pool;
		root = new_();
		history[0] = new_();
	}
	void insert(node *ver_s, int pos, int element, int add)
	{
		node *found = ver_s;
		bitset<sigma + 1> kkk = pos;
		found->times += add;
		for (int i = sigma; i >= 0; --i)
		{
			if (found->child[kkk[i]] == null)
			{
				found->child[kkk[i]] = new_();
				found = found->child[kkk[i]];
			}
			else
				found = found->child[kkk[i]];
			found->times += add;
		}
		found->element = element;
	}
	node *insert_new(int pos, int element, node *old, int add)
	{
		node *found = old, *_new = new_(), *_new2;
		bitset<sigma + 1> kkk = pos;
		_new2 = _new;
		for (int i = sigma; i >= 0; --i)
		{
			_new->times += add;
			_new->child[kkk[i]] = new_();
			if (found == null)
				_new = _new->child[kkk[i]];
			else
			{
				_new->times += found->times;
				_new->child[!kkk[i]] = found->child[!kkk[i]];
				_new = _new->child[kkk[i]];
				found = found->child[kkk[i]];
			}
		}
		_new->times += found->times;
		_new->times += add;
		_new->element = element;
		return _new2;
	}
	int rank(node *p, int pos)
	{
		bitset<sigma + 1> kkk = pos;
		int rk = 1;
		for (int i = sigma; i >= 0; --i)
		{
			if (kkk[i])
				rk += p->child[0]->times;
			p = p->child[kkk[i]];
		}
		return rk;
	}
	int find(node *p, int pos)
	{
		bitset<sigma + 1> kkk = pos;
		for (int i = sigma; i >= 0; --i)
			p = p->child[kkk[i]];
		return p->times;
	}
	int kth(node *p, int s)
	{
		bitset<sigma + 1> ans;
		for (int i = sigma; i >= 0; --i)
			if (p->child[0]->times < s)
			{
				s -= p->child[0]->times;
				ans[i] = 1;
				p = p->child[1];
			}
			else
				p = p->child[0], ans[i] = 0;
		return ans.to_ulong();
	}
	int rank(int L, int R, int pos)
	{
		node* PL = history[L - 1], *PR = history[R];
		bitset<sigma + 1> kkk = pos;
		int rk = 1;
		for (int i = sigma; i >= 0; --i)
		{
			if (kkk[i])
				rk += PR->child[0]->times - PL->child[0]->times;
			PL = PL->child[kkk[i]];
			PR = PR->child[kkk[i]];
		}
		return rk;
	}
	int prefix(node *p, int pos)
	{
		bitset<sigma + 1> kkk = pos;
		int rk = 0;
		for (int i = sigma; i >= 0; --i)
		{
			if (kkk[i])
				rk += p->child[0]->times;
			p = p->child[kkk[i]];
		}
		rk += p->times;
		return rk;
	}
	int querysum(node *p, int L, int R)
	{
		return prefix(p, R) - prefix(p, L - 1);
	}
	int kth(int L, int R, int s)
	{
		node* PL = history[L - 1], *PR = history[R];
		int rk;
		for (int i = sigma; i >= 0; --i)
		{
			rk = PR->child[0]->times - PL->child[0]->times;
			if (rk < s)
			{
				s -= rk;
				PL = PL->child[1];
				PR = PR->child[1];
			}
			else
			{
				PL = PL->child[0];
				PR = PR->child[0];
			}
		}
		return rk;
	}
	void merge(node *a, node *b)
	{
		b->times += a->times;
		for (int i = 0; i < 2; ++i)
		{
			if (a->child[i] != null && b->child[i] != null)
				merge(a->child[i], b->child[i]);
			else if (b->child[i] == null)
				b->child[i] = a->child[i];
		}
	}
	node *merge2(node *a, node *b) {
		node *p = new_();
		p->times += a->times + b->times;
		for (int i = 0; i < 2; ++i) {
			if (a->child[i] != null || b->child[i] != null)
				p->child[i] = merge2(a->child[i], b->child[i]);
			else if (a->child[i] == null)
				p->child[i] = b->child[i];
			else
				p->child[i] = a->child[i];
		}
		return p;
	}
}
using namespace trie01;
using namespace std;
const int N = 200010;
struct EXSAM_node
{
	EXSAM_node *next[26], *pre;
	int rank;
	int step;
	int sign;
	int belong;
	int firstpos;
	node *cnt;
	void clear(int k)
	{
		cnt = new_();
		rank = 0;
		belong = 0;
		firstpos = 0;
		sign = k;
		pre = NULL;
		step = 0;
		memset(next, 0, sizeof(next));
	}

};
EXSAM_node EXSAM_Pool[N * 2];
EXSAM_node *EXpool[N * 2];
long d[N * 2];
string spool[N];
struct EXSAM
{
	EXSAM_node *root, *last;
	EXSAM_node  *cur;
	void init()
	{
		cur = EXSAM_Pool;
		root = last = cur++;
		root->clear(cur - EXSAM_Pool);
	}
	EXSAM_node *newnode()
	{
		cur->clear(cur - EXSAM_Pool + 1);
		return cur++;
	}
	void Insert(int w, int i, int j)//第i个子串的字符,每插入新串时last应设置为root
	{
		EXSAM_node *p = last;
		if (p->next[w] && p->next[w]->step == p->step + 1)
		{
			last = p->next[w];
			insert(last->cnt, j, j, 1);
			return;
		}
		EXSAM_node *np = newnode();
		np->step = p->step + 1;
		np->firstpos = j; //确定原串初始位置
		while (p && !p->next[w])
		{
			p->next[w] = np, p = p->pre;
		}
		if (p == 0)
			np->pre = root;
		else
		{
			EXSAM_node *q = p->next[w];
			if (p->step + 1 == q->step)
				np->pre = q;
			else
			{
				EXSAM_node *nq = newnode();
				nq->step = p->step + 1;
				memcpy(nq->next, q->next, sizeof(q->next));
				nq->pre = q->pre;
				nq->belong = q->belong;
				nq->firstpos = q->firstpos;
				q->pre = nq;
				np->pre = nq;
				while (p&&p->next[w] == q)
				{
					p->next[w] = nq, p = p->pre;
				}
			}
		}
		last = np;
		last->belong = i;
		insert(last->cnt, j, j, 1);
	}

	void topo()
	{
		int cnt = cur - EXSAM_Pool;
		int maxVal = 0;
		memset(d, 0, sizeof(d));
		for (int i = 1; i < cnt; i++)
		{
			maxVal = max(maxVal, EXSAM_Pool[i].step), d[EXSAM_Pool[i].step]++;
		}
		for (int i = 1; i <= maxVal; i++)
			d[i] += d[i - 1];
		for (int i = 1; i < cnt; i++)
			EXpool[d[EXSAM_Pool[i].step]--] = &EXSAM_Pool[i];
		EXpool[0] = root;
	}
}part;
EXSAM_node *trans[N * 2];
EXSAM_node *Last[N * 2];
void build(string &s, int i)
{
	for (int j = 0; j < s.size(); ++j)
	{
		part.Insert(s[j] - 'a', i, j + 1);
	}
	EXSAM_node *r = part.root;
	for (int j = 0; j < s.size(); ++j)
	{
		r = r->next[s[j] - 'a'];
		Last[j + 1] = r;
	}
	spool[i] = s;
	part.last = part.root;
}
vector<pair<int, int> > edge[N * 2];
void addedge(int u, int v, int w)
{
	edge[u].push_back({ w,v });
}
int dfslen;
void dfs(int a)
{
	trans[a]->rank = dfslen;
	for (auto &p : edge[a])
	{
		dfslen++;
		dfs(p.second);
	}
}
void EXST()
{
	EXSAM_node *p;
	p = part.root;
	trans[1] = p;
	p++;
	for (int i = 0; i < part.cur - EXSAM_Pool + 10; ++i)
		edge[i].clear();
	while (p != part.cur)
		addedge(p->pre->sign, p->sign, spool[p->belong][p->firstpos - p->pre->step - 1]), trans[p->sign] = p, p++;
	for (int i = 0; i < part.cur - EXSAM_Pool + 10; ++i)
		sort(edge[i].begin(), edge[i].end());
	dfslen = 0;
	dfs(1);
}
void EXST2()
{
	EXSAM_node *p;
	p = part.root;
	trans[1] = p;
	p++;
	for (int i = 0; i < part.cur - EXSAM_Pool + 10; ++i)
		edge[i].clear();
	while (p != part.cur)
		addedge(p->pre->sign, p->sign, spool[p->belong][p->firstpos - p->pre->step - 1]), trans[p->sign] = p, p++;
}
string trans2(EXSAM_node *p, int len)
{
	string p2;
	for (int i = p->firstpos - 1; i >= p->firstpos - len; --i)
		p2.append(1, spool[p->belong][i]);
	return p2;
}
const int maxn = 230000;
const int max2 = 20;
int father[max2][maxn];
void init(int n)
{
	memset(father, 0, sizeof(father));
	int Max = N * 2;
	for (int i = 0; i < Max; ++i)
		edge[i].clear();
}
void dfs2(int x)
{
	for (auto &s : edge[x])
	{
		if (father[0][x] != s.second)
		{
			father[0][s.second] = x;
			dfs2(s.second);
		}
	}
}
void  build(int root, int n)
{
	dfs2(root);
	for (int k = 0; k < max2; k++)  //预处理father
		for (int i = 1; i <= n; i++)
			if (father[k][i])
				father[k + 1][i] = father[k][father[k][i]];
}
EXSAM_node *substring(int L, int R)
{
	int len = R - L + 1;
	int p = Last[R]->sign;
	for (int k = max2 - 1; k >= 0; k--)
	{
		if (father[k][p] == 0)
			continue;
		if (trans[father[k][p]]->step >= len)
			p = father[k][p];
	}
	return trans[p];
}
void single(string &s)
{
	int n = s.size();
	init();
	init(n);
	part.init();
	build(s, 1);
	EXST2();
	int cnt = part.cur - EXSAM_Pool - 1;
	build(1, cnt + 100);
	part.topo();
	for (int i = cnt; i > 0; --i)
		EXpool[i]->pre->cnt = merge2(EXpool[i]->cnt, EXpool[i]->pre->cnt);
}
int ansss[120000];