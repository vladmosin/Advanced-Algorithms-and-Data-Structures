#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <queue>
#include <list>
using namespace std;

int ind = 1, g_cn = 1;
int id[200001];
vector<int> sets[200001];

struct ask {
	int i, a, b;
};

class cnt {
public:
	int a, b, c;
};

class Node {
public:
	Node(int index = 0) {
		i = index;
	};
	int i;
	vector<cnt> j;
	vector<ask> g;
};

Node* nodes[300001];

void join(int a, int b) {
	if (id[a] != id[b]) {
		if (sets[id[a]].size() > sets[id[b]].size())
			swap(a, b);
		for (auto i : sets[id[a]]) {
			id[i] = id[b];
			sets[id[b]].push_back(i);
		}
	}
}

void b_join(int a, int b, int l_id) {
	if (a != b) {
		if (sets[a].size() > sets[b].size())
			swap(a, b);
		for (auto i : sets[a]) {
			id[i] = l_id;
			sets[b].pop_back();
		}
	}
}

void init(int n) {
	for (int i = 1; i <= n; i++)
		id[i] = i, sets[i].push_back(i);
}

bool get(int a, int b) {
	return id[a] == id[b];
}

void g(int a, int b, Node* t) {
	t->g.push_back({g_cn++, a, b});
}

void j(int a, int b, Node* t) {
	Node* tmp = new Node(ind);
	nodes[ind] = tmp;
	t->j.push_back({a, b, ind});
}

vector<pair<int, bool>> res;

int min_id(int a, int b) {
	if (sets[a].size() > sets[b].size())
		return b;
	return a;
}

void solve(Node* t) {
	int v = 0;
	for (auto i : t->g)
		res.push_back({ i.i, get(i.a, i.b)} );
	for (auto i : t->j) {
		int a = id[i.a], b = id[i.b], l_id = min_id(a, b);
		join(a, b);
		solve(nodes[i.c]);
		b_join(a, b, l_id);
	}
}

int main() {
	int n = 0, a = 0, b = 0, c = 0, m = 0;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	nodes[0] = new Node(0);
	char ch;
	for (int i = 1; i <= m; i++) {
		cin >> ch >> a >> b >> c;
		if (ch == '+') {
			j(b, c, nodes[a]);
		}
		else {
			g(b, c, nodes[a]);
		}
		ind++;
	}
	init(n);
	solve(nodes[0]);
	sort(res.begin(), res.end());
	for (auto i : res) {
		i.second ? cout << "YES\n" : cout << "NO\n";
	}
}
