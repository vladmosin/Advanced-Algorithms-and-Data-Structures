#include <string>
#include <queue>
#include <iostream>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <utility>  
#include <cstdlib>
#include <iomanip>
#include "optimization.h"
using namespace std;

long long down[100000];
long long arr[100000][2];
long long last[100000];
vector<long long> edges[100000];

int df(int v, int prev) {
	last[v] = prev;
	down[v] = 1;
	for (int i = 0; i < edges[v].size(); i++)
		if (edges[v][i] != prev)
			down[v] += df(edges[v][i], v);
	return down[v];
}
int d[100000];
void dfs(int start, int num) {
	d[start] = num;
	for (int i = 0; i < edges[start].size(); i++)
		if (d[edges[start][i]] == 0) {
			d[edges[start][i]] = num;
			dfs(edges[start][i], num);
			}
}

int main() {
	int n = 0, m = 0, a = 0, b = 0;
//	cin >> n >> m;
	n = readInt();
	m = readInt();
	for (int i = 0; i < m; i++) {
		//cin >> a >> b;
		a = readInt();
		b = readInt();
		edges[a - 1].push_back(b - 1);
		edges[b - 1].push_back(a - 1);
		arr[i][0] = b - 1;
		arr[i][1] = a - 1;
	}
	int top = 0, num = 1;
	for (int i = 0; i < n; i++)
		if (d[i] == 0)
			dfs(i, num++);
	vector<long long> child(num - 1);
	vector<long long> lastchild(num - 1);
	for (int i = 0; i < n; i++) {
		child[d[i] - 1]++;
		if (edges[i].size() == 1) {
			lastchild[d[i] - 1] = i;
		}
	}
	//cout << child[0] << ' ';
	for (int i = 0; i < num - 1; i++)
		df(lastchild[i], -1);
	//for (int i = 0; i < n; i++)
		//cout << down[i] << ' ';
	//cout << '\n';
	int k = 0;
	k = readInt();
		for (int i = 0; i < k; i++) {
			a = readInt();
			if (arr[a - 1][0] == last[arr[a - 1][1]]) {
				writeInt((child[d[arr[a - 1][0]] - 1] - down[arr[a - 1][1]]) * down[arr[a - 1][1]]);
				writeWord(" ");
			}
			else {
				writeInt((child[d[arr[a - 1][0]] - 1] - down[arr[a - 1][0]]) * down[arr[a - 1][0]]);
				writeWord(" ");
			}
		}
	//cin >> n;
}
