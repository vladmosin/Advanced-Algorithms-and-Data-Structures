
//#include "stdafx.h"
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
typedef long double ld;

ll n = 0, m = 0;
ll mult = 1e8;
ll edges[2000][3];
ll d[1000];
ll parent[1000];
bool bit[1000];
vector<ll> path;

bool fb(ll value) {
	bool fl = false;
	for (int i = 0; i < m; i++) {
		edges[i][2] -= value;
	}
	for (int i = 0; i < n; i++) {
		d[i] = 0;
		bit[i] = false;
	}
	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < m; j++) {
			if (d[edges[j][1]] > d[edges[j][0]] + edges[j][2]) {
				d[edges[j][1]] = d[edges[j][0]] + edges[j][2];
				parent[edges[j][1]] = j;
				if (i == n) {
					fl = true;
					path.clear();
					int top = edges[j][1];
					while (!bit[top]) {
						bit[top] = true;
						top = edges[parent[top]][0];
					}
					while (bit[top]) {
						path.push_back(parent[top]);
						bit[top] = false;
						top = edges[parent[top]][0];
					}
					j = m;
				}
			}
		}
	}
	for (int i = 0; i < m; i++) {
		edges[i][2] += value;
	}
	return fl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
		edges[i][0]--;
		edges[i][1]--;
		edges[i][2] *= mult;
	}
	ll left = -1000 * mult - 1, right = 1000 * mult + 1, mid = 0;
	while (right - left > 1) {
		mid = (left + right) / 2;
		if (!fb(mid)) {
			left = mid;
		}
		else {
			right = mid;
		}
	}
	ll sum = 0;
	for (int i = 0; i < path.size(); i++) {
		sum += edges[path[i]][2];
	}
	cout.precision(12);
	cout << ld(sum) / path.size() / mult << '\n' << path.size() << '\n';
	for (int i = 0; i < path.size(); i++) {
		cout << path[path.size() - 1 - i] + 1 << ' ';
	}
}
