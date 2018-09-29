#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <map>
#include <queue>
#include <string>
#include <list>
#include <time.h>
#include <unordered_set>
#include "optimization.h"

using namespace std;
typedef pair<int, int> pii;

unordered_set<int> edges[110000];

class node {
public:
	node *l, *r, *p;
	int pr, cnt, i, j;
	node(int i_, int j_) {
		j = j_;
		cnt = 1;
		i = i_;
		pr = rand() * rand();
		l = nullptr;
		r = nullptr;
		p = nullptr;
	};
};

void output(node* t);

int cnt(node* t) {
	return t ? t->cnt : 0;
}

void update(node* t) {
	if (t) {
		t->p = nullptr;
		t->cnt = 1 + cnt(t->l) + cnt(t->r);
		if (t->l)
			t->l->p = t;
		if (t->r)
			t->r->p = t;
	}
}

void split(node* t, node *&l, node*& r, int key, int add = 0) {
	if (!t) {
		l = r = nullptr;
		return;
	}
	int cnt_key = add + cnt(t->l);
	if (key <= cnt_key)
		split(t->l, l, t->l, key, add), r = t;
	else
		split(t->r, t->r, r, key, add + 1 + cnt(t->l)), l = t;
	update(t);
}

node* merge(node* l, node* r) {
	if (!l || !r) {
		return l ? l : r;
	}
	if (l->pr > r->pr) {
		l->r = merge(l->r, r);
		update(l);
		return l;
	}
	r->l = merge(l, r->l);
	update(r);
	return r;
}

void output(node *t) {
	if (!t)  return;
	output(t->l);
	output(t->r);
}

node* rotate(node* t, int l) {
	if (!t)
		return nullptr;
	node *t1, *t2, *t3;
	split(t, t1, t2, l);
	if (t2)
		t2->p = nullptr;
	if (t3)
		t1->p = nullptr;
	t3 = merge(t2, t1);
	if (t3)
		t3->p = nullptr;
	return t3;
}

node* del(node* t, int ind = 0) {
	node *t1, *t2;
	split(t, t1, t2, ind + 1);
	if (t2)
		t2->p = nullptr;
	if (t1)
		t1->p = nullptr;
	return t2;
}

node* getRoot(node* t) {
	if (!t)
		return nullptr;
	while (t->p)
		t = t->p;
	return t;
}

struct pair_hash {
    std::size_t operator () (const std::pair<int,int> &p) const {
        auto h1 = hash<int>{}(p.first);
        auto h2 = hash<int>{}(p.second);
        return h1 ^ h2;  
    }
};
 
map<pii, node*> Node;

node* getEdge(int a) {
	if (edges[a].size())
		return Node[{ a, *edges[a].begin() }];
	return nullptr;
}

int isConnected(int a, int b) {
	if (a == b)
		return 1;
	if (!getEdge(a))
		return 0;
	return (getRoot(getEdge(a)) == getRoot(getEdge(b))) ? 1 : 0;
}

int getPos(node* t) {
	if (!t)
		return 0;
	int res = cnt(t->l);
	while (t->p) {
		if (t == t->p->r) {
			res += cnt(t->p->l) + 1;
		}
		t = t->p;
	}
	return res;
}

void del_edge(int a, int b) {
	edges[a].erase(b);
	edges[b].erase(a);
	Node.erase({b, a});
	Node.erase({a, b});
}

void cut(int a1, int b1) {
	node* node1 = Node[{a1, b1}];
	node* node2 = Node[{b1, a1}];
	int i = getPos(node1), j = getPos(node2);
	if (i > j) swap(i, j);
	node *root = getRoot(node1), *a = nullptr, *b = nullptr, *c = nullptr;
	split(root, a, b, i);
	split(b, b, c, j - i);
	del(b);
	del_edge(a1, b1);
	merge(a, del(c));
}

void link(int a, int b) {
	node *pa = getEdge(a), *pb = getEdge(b);
	rotate(getRoot(pa), getPos(pa));
	rotate(getRoot(pb), getPos(pb));
	node *e1 = new node(a, b), *e2 = new node(b, a);
	Node[{a, b}] = e1;
	Node[{b, a}] = e2;
	edges[a].insert(b);
	edges[b].insert(a);
	merge(merge(getRoot(pa), e1), merge(getRoot(pb), e2));
}

int main() {
	int n = 0, k = 0, a = 0, b = 0;
	n = readInt();
	k = readInt();
	char cmd[5], r = ' ';
	while (k--) {
		readWord(cmd);
		a = readInt();
		b = readInt();
		a--, b--; 
		if (cmd[0] == 'g') {
			if (isConnected(a, b))
				writeChar('1');
			else
				writeChar('0');
		}
		if (cmd[0] == 'l')
			link(a, b);
		if (cmd[0] == 'c')
			cut(a, b);
	}
	return 0;
}
