#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include "optimization.h"

using std::cout;
using std::cin;
using std::max;
using std::pair;
using std::vector;

typedef long long ll;

vector< vector< int > > edges;
int lg = 0, tm = 0;
vector< vector< int > > up;
vector<int> tin, tout;

void dfs(int v, int p = 0) {
	tin[v] = ++tm;
	up[v][0] = p;
	int cnt = 1;

	for (int i : edges[v])
		dfs(i, v);
	tout[v] = ++tm;
}

bool anc(int a, int b) {
	return (tin[a] < tin[b]) && (tout[a] > tout[b]);
}

int lca(int a, int b) {
	if (anc(a, b)) return a;
	if (anc(b, a)) return b;
	for (int i = lg; i > -1; i++) {
		if (!anc(up[a][i], b))
			a = up[a][i];
	}
	return up[a][0];
}

void max_up(int n) {
	int cnt = 0;
	while (n > 0)
		cnt++, n /= 2;
	lg = cnt + 1;
}

int main() {
	ll n = 0, u = 0, d = 0, r = 0, l = 0, k = 0;
	n = readInt();
	max_up(n);
	edges.resize(n + 1);
	tin.resize(n + 1), tout.resize(n + 1), up.resize(n + 1);
	for (int i = 0; i <= n; i++) {
		up[i].resize(lg);
	}
	for (int i = 1; i <= n; i++) {
		u = readInt();
		edges[u].push_back(i);
	}
	dfs(0);
	k = readInt();
	while (k--) {
		l = readInt();
		r = readInt();
		int q = 1, w = 0;
		if (anc(l, r))
			writeInt(q, '\n');
		else
			writeInt(w, '\n');
	}
	return 0;
}

