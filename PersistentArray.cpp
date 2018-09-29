#include <vector>
#include <iostream>
using namespace std;

int ind = 1;
class Node {
public:
	Node(int index = 0, int val = 0, Node* left = nullptr, Node* right = nullptr) {
		v = val;
		l = left;
		r = right;
		i = index;
	};
	int v, i;
	Node *l, *r;
};

Node* roots[200001];
int arr[200001];

Node* build(int l, int r) {
	if (l > r)
		return nullptr;
	return (new Node((l + r) / 2, arr[(l + r) / 2], build(l, (r + l) / 2 - 1), build((r + l) / 2 + 1, r)));
}

Node* add(Node* t, int index, int value) {
	if (index == t->i)
		return (new Node(index, value, t->l, t->r));
	if (index < t->i) {
		return (new Node(t->i, t->v, add(t->l, index, value), t->r));
	}
	return (new Node(t->i, t->v, t->l, add(t->r, index, value)));
}

int get(Node *t, int index) {
	if (index == t->i)
		return t->v;
	if (index < t->i) {
		return get(t->l, index);
	}
	return get(t->r, index);
}

int main() {
	int n = 0;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	roots[ind++] = build(1, n);
	int m = 0, a = 0, b = 0, c = 0;
	cin >> m;
	char com[10];
	for (int i = 0; i < m; i++) {
		cin >> com >> a >> b;
		if (com[0] == 'c') {
			cin >> c;
			roots[ind++] = add(roots[a], b, c);
		}
		else {
			cout << get(roots[a], b) << endl;
		}
	}
}
