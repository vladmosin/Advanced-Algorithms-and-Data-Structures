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
#include "optimization.h"
using namespace std;

typedef long long ll;
int p[50000];
int type[150000];
int edges[150000][2];
vector<bool> ans;

int get(int a) {
	if (a == p[a])
		return a;
	p[a] = get(p[a]);
	return p[a];
}

void join(int a, int b) {
	p[get(a)] = get(b);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n = 0, m = 0, k = 0, a = 0, b = 0;
	char com[5];
	n = readInt();
	m = readInt();
	k = readInt();
	for (int i = 0; i < n; i++) {
		p[i] = i;
	}

	for (int i = 0; i < m; i++) {
		a = readInt();
		b = readInt();
	}
	for (int i = 0; i < k; i++) {
		readWord(com);
		a = readInt();
		b = readInt();
		edges[i][0] = a - 1;
		edges[i][1] = b - 1;
		if (!strcmp(com, "ask")) {
			type[i] = 0;
		}
		if (!strcmp(com, "cut")) {
			type[i] = 1;
		}
	}

	for (int i = k - 1; i > -1; i--) {
		if (type[i] == 0) {
			if (get(edges[i][0]) == get(edges[i][1]))
				ans.push_back(true);
			else
				ans.push_back(false);
		}
		if (type[i] == 1) {
			join(edges[i][1], edges[i][0]);
		}
	}
	for (int i = ans.size() - 1; i > -1; i--) {
		if (ans[i])
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}
