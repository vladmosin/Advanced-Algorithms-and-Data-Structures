#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

int ind = 1;
class Node {
public:
	Node(int val = 0, int index = 0) {
		v = val;
		i = index;
	};
	int v, i;
	vector<Node*> push, pop;
};

Node* nodes[300001];

void push(int index, int value) {
	int n = 0;
	Node *p = nodes[index];
	Node *tmp = new Node(value, ind);
	nodes[ind++] = tmp;
	p->push.push_back(tmp);
}

void pop(int index) {
	Node *p = nodes[index];
	Node *tmp = new Node(0, ind);
	nodes[ind++] = tmp;
	p->pop.push_back(tmp);
}

vector<int> tasks;
vector<pair<int, int>> res;
deque<int> q;
void solve(Node* t) {
	int val = 0;
	bool fl = q.empty();
	if (t == nullptr)
		return;
	if (!fl)
		res.push_back({ t->i, q.front() });
	else 
		res.push_back({ t->i, 0 });
	for (auto i : t->push) {
		q.push_back(i->v);
		solve(i);
		q.pop_back();
	}
	for (auto i : t->pop) {
		val = q.front();
		q.pop_front();
		solve(i);
		q.push_front(val);
	}
}

int main() {
	int n = 0, a = 0, b = 0, c = 0;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	nodes[0] = new Node(0, 0);
	for (int i = 1; i <= n; i++) {
		cin >> a >> b;
		if (a == -1) {
			tasks.push_back(nodes[b]->i);
			pop(b);
		}
		else {
			cin >> c;
			push(b, c);
		}
	}
	solve(nodes[0]);
	sort(res.begin(), res.end());
	for (auto i : tasks) {
		cout << res[i].second << '\n';
	}
}
