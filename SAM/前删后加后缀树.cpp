#define sigma 26 // size of the alphabet
#define maxn 100010 // maximal size of the string
#define inf 1000000000 // *infinity*

struct node { // describes the node of the suffix tree
	int l, r, pr, link, depth, next[sigma], idx, e;
	// l and r are left and right bounds for the string that corresponds to the edge that ends in that node
	// sometimes r will be equal to inf, when the edge is "endless"
	// pr is the parent node or ancestor
	// link is the suffix link for the node, when it is not yet defined, it equals to zero (we use 1-indexation here)
	// depth is the length of the way that starts in the root and ends in this node
	// next correponds to the transitions by 26 letters (a to z) from this node. here we also use 1-indexation
	// e is the number of edges that starts in this node
}t[maxn * 2];
struct state { // describes the state (generally, the path from the root to some node)
	int v, j, depth;
	// v is the index of some node. we consider that the path ends somewhere between v and t[v].pr
	// j is the position at this edge. generally, j corresponds to the number of symbols till the end of the current edge
	// depth is the length of the string that ends in this state
	state() {}
	state(int v, int j, int depth) :v(v), j(j), depth(depth) {}
}ptr, ptr2;
long long LenSum, ans;
int n, i, N, sz, qL, qR, que[maxn], endless, idx, j;
int ch, s[maxn];

state follow(state ptr, char c) { // go from the state by a character
	if (ptr.j > 0) { // if the edge is not yet ended, there's an only option: follow this edge (it it's OK now, of course)
		if (s[t[ptr.v].r - ptr.j] == c)return state(ptr.v, ptr.j - 1, ptr.depth + 1); else return state(0, 0, 0);
	}
	else { // otherwise, there is a case when the edge is ended and now we have to make move from the vertex
		if (!t[ptr.v].next[c])return state(0, 0, 0); else return state(t[ptr.v].next[c], t[t[ptr.v].next[c]].r - t[t[ptr.v].next[c]].l - 1, ptr.depth + 1);
	}
}

state go(int k, int l, int r) { // yet another function to travel the tree: move by r-l symbols that correspond the substring [l; r) from the node k
	while (l < r) {
		k = t[k].next[s[l]];    // when we stay in the vertex, we just have to choose the edge, which we'll follow
		// next, we have two basic cases: when the remaining interval is too long, we just go further to another node. if not, we can say the required state
		if (t[k].r - t[k].l >= r - l)return state(k, t[k].r - t[k].l - r + l, t[k].depth - t[k].r + t[k].l + r - l); else l += t[k].r - t[k].l;
	}
	return state(k, 0, t[k].depth); // obviously, this line will be executed only in case when l == r initially. it's clear that we just have to stay in the current node
}

void change(int l, int r, int pr, int cc) { // this function updates fields l, r, pr for the node cc
	t[cc].l = l, t[cc].r = r, t[cc].pr = pr, // just set l, r and pr equal to the new values
		t[cc].depth = t[pr].depth + r - l; // as we could have changed pr, depth can be changed too
	t[pr].e += t[pr].next[s[l]] == 0; // now we're going to add an edge, so we update the number of outgoing edges
	t[pr].next[s[l]] = cc; // don't forget that edge corresponds to some substring. so, we add the edge from the parent by the first char of this string
	if (r == inf)t[cc].idx = inf - t[cc].depth, t[pr].idx = max(t[cc].idx, t[pr].idx);
}

int split(state ptr) { // split the edge t[ptr.v].pr -> ptr.v into two parts: before ptr and after ptr. returns the index of the new intermediate node between these two parts
	// in the following two cases we don't have to do the split because one of the parts will be equal to zero
	if (ptr.j == 0)return ptr.v;
	if (ptr.j == t[ptr.v].r - t[ptr.v].l)return t[ptr.v].pr;
	int leng = t[ptr.v].r - t[ptr.v].l; // length of the edge before split
	change(t[ptr.v].l, t[ptr.v].l + leng - ptr.j, t[ptr.v].pr, ++sz); // now we create new leaf vertex. it's parent edge corresponds to the first part (before ptr)
	t[ptr.v].pr = sz, // for the second part the parent was changed
		t[ptr.v].l += leng - ptr.j, // left bound of the interval was also changed
		t[sz].idx = t[ptr.v].idx,
		t[sz].e += t[sz].next[s[t[ptr.v].l]] == 0, // recalculate the number of edges, outgoing from the new vertex (upper one if we consider root the highest)
		t[sz].next[s[t[ptr.v].l]] = ptr.v; // now connect the first part of the old edge with the second through the intermediate vertex
	return sz;
}

int getlink(int k) { // finds the suffix link for the node k. even regardless we use split, new nodes will not be created
	if (t[k].link)return t[k].link; // if the link is already calculated, return it. this way we'll calculate something no more than O(N) times
	return t[k].link = split(go(getlink(t[k].pr), t[k].l + (t[k].pr == 1), t[k].r)); // find the largest suffix of the suffix that corresponds to the path to the node k
}

void plusquery(char cha) { // query denoted by "+" in the statement. adds char to the end of the string
	s[N++] = cha;
	while (1) {
		state nptr = follow(ptr, cha); // try to go by the current symbol
		if (nptr.v) { ptr = nptr; break; } // in case we have succeeded (ptr.v is nonzero) just stop, because we don't have to perform more splits
		// otherwise, we have found new edge that should be splitted
		// the case is as like this: root -(some letters)> (some vertex) -(edge where we have to go by this new char)> (some vertex) -(maybe again some letters)> (some vertex)
		// so now we need to split this edge into two parts to create the transition by the new char
		int mid = split(ptr), // mid is the index of the intermediate vertex of the edge where we have to go by this char
			leaf = ++sz; // we also create a node in which the edge from mid by the new char should end
		change(N - 1, inf, mid, leaf); // now we set left and right bounds for this edge. initially, it's endless
		// now just go further to another suffixes
		int new_mid = getlink(mid); // largest suffix of mid, smaller than mid
		ptr.v = new_mid, ptr.j = 0, ptr.depth = t[new_mid].depth;
		que[++qR] = leaf; // add the new leaf node to the queue
		LenSum += t[leaf].r - t[leaf].l; endless += t[leaf].r == inf; // maintain the amount of distinct substrings. it is generally equal to the sum of all edges' lenghts
		if (mid == 1)return; // if there are no another suffixes
	}
}

// function Get returns an answer to the problem: the sum of all edges' lengths
// we deal with endless edges' lengths by considering decreasing their length equally
inline long long Get() { return LenSum - endless * 1LL * (inf - N); }

void minusquery() { // query denoted by "-" in the statement. removes char from the end of the string
	int td = que[qL], // td is the deepest suffix. naturally, it will appear in the queue earlier
		j, cut, r, rr, new_son, nl;
	LenSum -= t[td].r - t[td].l; endless -= t[td].r == inf; // for a while, we don't consider this edge when we calculate the sum of edges' lengths
	// there are two cases: the case when the node to change corresponds to the current node in ptr (to which we try to append symbols) and when not
	if (td == ptr.v) { // when it corresponds
		ptr = go(getlink(t[ptr.v].pr), t[ptr.v].l + (t[ptr.v].pr == 1), t[ptr.v].r - ptr.j); // the suffix to which we append characters will be reduced ...
		rr = (t[ptr.v].r - t[ptr.v].l - ptr.j); // ... by the value of EdgeLength(t[ptr.v].pr -> ptr.v) - ptr.j, because only the part ptr.j -> end of the edge belongs to the largest suffix
		t[td].l = qR + t[t[td].pr].depth; // so now this edge's length and ranges should be changed to reduce only the part that belonged to the largest suffix
		t[td].depth = t[t[td].pr].depth + t[td].r - t[td].l; // the depth will also be reduced
		t[td].idx = qR;
		if (ptr.v == td)ptr.j = t[ptr.v].r - t[ptr.v].l - rr; // change the pointer itself if needed
		que[++qR] = td; // add the new suffix to the queue
		LenSum += t[td].r - t[td].l; endless += (t[td].r == inf); // we have removed only the part of the edge. we have to consider the remaining part when we calculate the sum of edges' lengths
	}
	else { // otherwise
	   // now we have the case when we have to remove some leaf
		t[t[td].pr].next[s[t[td].l]] = 0, // we remove the edge from the leaf's parent to it
			--t[t[td].pr].e; // and, therefore, the number of outgoing edges from the parent should be reduced
			// next, there is a case when we have inner vertice with the number of outgound edges equal to one
			// in the correct suffix tree it's not allowed to have such vertices, but we can "merge" two parts - before and after it
			// then, we'll naturally obtain correct suffix tree again
		if (t[td].pr > 1 && t[t[td].pr].e < 2) { // so, it it's a case
			r = t[td].pr; // we'll remove this node and will merge two parts (before and after it) in one
			cut = t[ptr.v].r - t[ptr.v].l - ptr.j, // we will probably need it later to recalculate the current pointer for adding symbols (if needed)
				rr = t[r].pr; // the new edge will go from the node rr
				// the only edge from the node r will go to the node new_son
			for (j = 0, new_son = 0; j < sigma && !new_son; j++)if (t[r].next[j])new_son = t[r].next[j]; // so here we're simply finding it
			// so, the edge will look like rr -> new_son
			nl = t[r].r - t[r].l + t[new_son].r - t[new_son].l; // and it's length equals to the sum of two old edges' lengths
			// there are two types of edges - endless edge and limited size edge. now we have to decide whether the new edge endless or not
			if (t[new_son].e)
				change(t[new_son].idx + t[rr].depth, t[new_son].idx + t[rr].depth + nl, rr, new_son); else // if new_son have some outgoing edges, this edge is not the end, therefore, it's definitely not endless (because it's inner)
				change(t[new_son].idx + t[rr].depth, inf, rr, new_son); // but otherwise it is
			if (ptr.v == r)ptr.v = new_son, ptr.j = t[new_son].r - t[new_son].l - cut; else // if ptr points to the removed node, we have to recalculate it. corresponding string remains the same, but the edge changes
				if (ptr.v == new_son)ptr.j = t[new_son].r - t[new_son].l - (cut + (t[r].r - t[r].l)); // if it points to the new son, the relative position on the edge changes
		}
	}
	++qL; // remove the suffix from the queue
}
void init()
{
	memset(s, 0, sizeof(s));
	memset(que, 0, sizeof(que));
	for (int i = 1; i < maxn * 2; ++i)
	{
		t[i].l = t[i].r = t[i].link = t[i].idx = t[i].pr = t[i].e = t[i].depth = 0;
		memset(t[i].next, 0, sizeof(t[i].next));
	}
	sz = 1, qL = 1, qR = 0; ptr.v = 1; t[1].link = 1; // create an empty suffix tree
	N = 0;
}
void addchar(char ch)
{
	plusquery(ch - 'a');
}
void popfront()
{
	minusquery();
}
