#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

struct edge {
	ll fr;
	ll to;
	ll w;
	ll c;
	ll fl;
	ll num;
};

ll n = 0, m = 0, inf = 1000000000000, t;
vector<edge> edges;
vector<vector<int>> graph;
vector<ll> dist;

void fb() {
	bool fl;
	dist[0] = 0;
	for (ll i = 0; i < n; i++) {
		fl = false;
		for (ll j = 0; j < 2 * m; j++) {
			if ((dist[edges[j].fr] != inf) && (edges[j].c > edges[j].fl) && 
				(dist[edges[j].fr] + edges[j].w < dist[edges[j].to])) {
				fl = true;
				dist[edges[j].to] = dist[edges[j].fr] + edges[j].w;
			}
		}
		if (!fl)
			break;
	}
}

vector<ll> used;

int push(ll v, ll flow) {
	ll res = 0;
	used[v] = 1;
	if (v == t)
		return flow;
	for (int i = 0; i < graph[v].size(); i++) {
		if (!used[edges[graph[v][i]].to] && 
			dist[edges[graph[v][i]].to] == dist[edges[graph[v][i]].fr] + edges[graph[v][i]].w &&
			edges[graph[v][i]].c - edges[graph[v][i]].fl > 0) {
			res = push(edges[graph[v][i]].to, min(flow, edges[graph[v][i]].c - edges[graph[v][i]].fl));
			if (res > 0) {
				edges[graph[v][i]].fl += res;
				if (edges[graph[v][i]].num < m)
					edges[graph[v][i] + m].fl -= res;
				else
					edges[graph[v][i] - m].fl -= res;
				return res;
			}
		}
	}
	return 0;
}

int main() {
	cin >> n >> m;
	edges.resize(2 * m);
	used.resize(n);
	graph.resize(n);
	dist.resize(n);
	for (int i = 0; i < m; i++) {
		cin >> edges[i].fr >> edges[i].to >> edges[i].c >> edges[i].w;
		edges[i].fr--, edges[i].to--;
		edges[i].num = i, edges[i].fl = 0;
		edges[m + i].fr = edges[i].to, edges[m + i].to = edges[i].fr, edges[m + i].c = 0;
		edges[m + i].w = -edges[i].w, edges[m + i].num = m + i, edges[m + i].fl = 0;
		graph[edges[i].fr].push_back(i);
		graph[edges[i].to].push_back(m + i);
	}
	t = n - 1;
	while (true) {
		bool fl = false;
		fill(dist.begin(), dist.end(), inf);
		fb();
		while (true) {
			fill(used.begin(), used.end(), 0);
			if (push(0, inf))
				fl = true;
			else
				break;
		}
		if (!fl)
			break;
	}
	ll res = 0;
	for (int i = 0; i < m; i++) {
		res += edges[i].fl * edges[i].w;
	}
	cout << res << '\n';
	return 0;
}
