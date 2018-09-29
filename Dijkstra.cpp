#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <string>
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

priority_queue<pair<int, pair<int, int>>> q;
int d[100001];
int parent[100001];
bool used[100001];
vector<pair<int, int>> edges[100000];

void Dijk(int v) {
	bool fl = false;
	int val = 0;
	pair<int, pair<int, int>> top = { 0, {0, 0} };
	q.push({ 0, {v, -1 } });
	while (!q.empty()) {
		fl = false;
		top = { -1, {-1, -1} };
		while (!q.empty()) {
			top = q.top();
			q.pop();
			if (!used[top.second.first]) {
				fl = true;
				break;
			}
		}
		int vertex = top.second.first, weight = top.first, par = top.second.second;
		if (fl) {
			d[vertex] = weight;
			parent[vertex] = par;
			used[vertex] = true;
			for (int i = 0; i < edges[vertex].size(); i++) {
				if (!used[edges[vertex][i].first])
					q.push({ d[vertex] + edges[vertex][i].second, {edges[vertex][i].first, vertex} });
			}
		}
	}
}

int main() {
	vector<int> path;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	for (int i = 0; i < 100001; i++) {
		d[i] = INT_MAX;
	}
	int n = 0, m = 0, first = 0, second = 0, a = 0, b = 0, wei = 0;
	cin >> n >> m >> first >> second;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> wei;
		edges[a - 1].push_back({ b - 1, -wei });
		edges[b - 1].push_back({ a - 1, -wei });
	}
	Dijk(first - 1);
	if (d[second - 1] == INT_MAX) {
		cout << "-1";
		return 0;
	}
	else {
		cout << -d[second - 1] << '\n';
	}
}
