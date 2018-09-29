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
#include "optimization.h"
using namespace std;
typedef long long ll;

queue<int> q;
int d[100001];
vector<int> edges[100001];

void bfs(int s) {
	d[s] = 0;
 	q.push(s);
	while (!q.empty()) {
		int top = q.front();
		for (int i = 0; i < edges[top].size(); i++) {
			if (d[edges[top][i]] == -1) {
				q.push(edges[top][i]);
				d[edges[top][i]] = d[top] + 1;
			}
		}
		q.pop();
	}
}

int main() {
	for (int i = 0; i < 100001; i++) {
		d[i] = -1;
	}
	int n = 0, m = 0, a = 0, b = 0, s = 0;
	n = readInt();
	s = readInt();
	m = readInt();
	for (int i = 0; i < m; i++) {
		a = readInt();
		b = readInt();
		edges[b - 1].push_back(a - 1);
	}
	bfs(s - 1);
	for (int i = 0; i < n; i++) {
		writeInt(d[i]);
		writeChar(' ');
	}
}
