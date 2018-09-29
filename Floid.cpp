
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
ll edges[6000][3];
ll d[2000];
ll inf = 5000000000000000000;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n = 0, m = 0, s = 0;
	cin >> n >> m >> s;
	for (int i = 0; i < m; i++) {
		cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
		edges[i][0]--;
		edges[i][1]--;
	}
	for (int i = 0; i < n; i++) {
		d[i] = inf;
	}
	d[--s] = 0;
	for (int i = 0; i < 2 * n; i++) {
		for (int j = 0; j < m; j++) {
			if ((d[edges[j][0]] != inf) && (d[edges[j][1]] > d[edges[j][0]] + edges[j][2])) {
				if (i >= n) {
					d[edges[j][1]] = -inf;
				}
				else {
					d[edges[j][1]] = max(d[edges[j][0]] + edges[j][2], -inf);
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (d[i] == inf) {
			cout << "*\n";
			continue;
		}
		if (d[i] == -inf) {
			cout << "-\n";
			continue;
		}
		cout << d[i] << '\n';
	}
}
