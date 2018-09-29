#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <set>
#include <string>

using namespace std;
typedef long long ll;

struct Edge {
	int v, w;
};

int level[50000], parent[50000];

vector <Edge> g[50000];

int dfs(int v, int size, int &center, int p = -1) {
	int sum = 1;
	for (auto i : g[v])
		if (level[i.v] == -1 && i.v != p)
			sum += dfs(i.v, size, center, v);
	if (center == -1 && (2 * sum >= size || p == -1))
		center = v;
	return sum;
}

int getCenter(int a, int b) {
	while (level[a] > level[b]) a = parent[a];
	while (level[b] > level[a]) b = parent[b];
	while (a != b) a = parent[a], b = parent[b];
	return a;
}

int f[20][50000];
void calc(int v, int depth, int p = -1, int m = 1e9) {
	f[depth][v] = m;
	for (auto i : g[v])
		if (level[i.v] == -1 && i.v != p)
			calc(i.v, depth, v, min(m, i.w));
}

void build(int v, int size, int depth, int last) {
	int center = -1;
	dfs(v, size, center);
	calc(center, depth);
	level[center] = depth;
	parent[center] = last;
	for (auto i : g[center])
		if (level[i.v] == -1)
			build(i.v, size / 2, depth + 1, center);
}

int get(int a, int b) {
	int c = getCenter(a, b);
	return min(f[level[c]][a], f[level[c]][b]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		level[i] = -1;
		parent[i] = -1;
		for (int j = 0; j < 20; j++)
			f[j][i] = 1e9;
	}
	for (int i = 0; i < n - 1; i++) {
		int x, w;
		cin >> x >> w;
		g[x - 1].push_back({ i + 1, w });
		g[i + 1].push_back({ x - 1, w });
	}

	build(0, n, 0, -1);

	int m = 0, b = 0, a = 0;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		cout << get(a - 1, b - 1) << '\n';
	}
}
