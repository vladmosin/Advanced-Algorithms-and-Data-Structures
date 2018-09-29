#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdint.h>
#include <unordered_map>
#include <cmath>
#include <random>
#include <queue>
#include <functional>

using namespace std;

typedef long long ll;
vector<pair<ll, ll>> weight;
ll p[20000];
ll edges[100000][2];
ll ans = 0;

ll get(ll a) {
	if (a == p[a])
		return a;
	p[a] = get(p[a]);
	return p[a];
}

void join(ll a, ll b) {
	p[get(a)] = get(b);
}

void crascal(ll m) {
	for (ll i = 0; i < m; i++) {
		if (get(p[edges[weight[i].second][0]]) != get(p[edges[weight[i].second][1]])) {
			ans += weight[i].first;
			join(edges[weight[i].second][0], edges[weight[i].second][1]);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll n = 0, m = 0, k = 0, a = 0, b = 0;
	char com[5];
 	cin >> n >> m;
	for (ll i = 0; i < n; i++) {
		p[i] = i;
	}

	for (ll i = 0; i < m; i++) {
		cin >> a >> b >> k;
		weight.push_back({k, i});
		edges[i][0] = a - 1;
		edges[i][1] = b - 1;
	}
	sort(weight.begin(), weight.end());
	crascal(m);
	cout << ans;
}
