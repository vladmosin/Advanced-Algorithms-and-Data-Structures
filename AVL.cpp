
//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <string>
#include <unordered_map>

using namespace std;
typedef long long ll;
ll index = 1;

void height(ll);
void add(ll);
void del(ll);
ll rrotate(ll);
ll lrotate(ll);
void ch_size(ll, ll);
ll go_left(ll);
ll find(ll);
ll get_k(ll, ll);
void rebalance(ll);
void recount(ll);


struct Node {
	ll  l, r, p;
	ll size, value, h;
	ll sum, min, max;
} arr[200001];

void add(ll t, ll val) {
	ll iter = 0;
	if (t > arr[arr[0].l].size || arr[0].l == 0) {
		iter = go_left(0);
		arr[index].size = 0;
		arr[index].l = 0;
		arr[index].r = 0;
		arr[index].p = iter;
		arr[iter].l = index;
		arr[index].value = val;
		arr[index].min = val;
		arr[index].max = val;
		arr[index].sum = val;
		recount(index);
		height(index);
		ch_size(index++, 1);
		rebalance(index - 1);
	}
	else {
		iter = get_k(arr[0].l, t);
		if (arr[iter].r != 0) {
			iter = go_left(arr[iter].r);
			arr[index].size = 0;
			arr[index].p = iter;
			arr[iter].l = index;
			arr[index].l = 0;
			arr[index].r = 0;
			arr[index].value = val;
			arr[index].min = val;
			arr[index].max = val;
			arr[index].sum = val;
			recount(index);
			height(index);
			ch_size(index++, 1);
			rebalance(index - 1);
		}
		else {
			arr[index].size = 0;
			arr[index].p = iter;
			arr[iter].r = index;
			arr[index].l = 0;
			arr[index].r = 0;
			arr[index].value = val;
			arr[index].min = val;
			arr[index].max = val;
			arr[index].sum = val;
			recount(index);
			height(index);
			ch_size(index++, 1);
			rebalance(index - 1);
		}
	}
};

void ch_size(ll ind, ll val) {
	ll iter = ind;
	while (iter != 0) {
		arr[iter].size += val;
		iter = arr[iter].p;
	}
}

ll go_left(ll ind) {
	while (arr[ind].l != 0)
		ind = arr[ind].l;
	return ind;
}

void height(ll x) {
	if (x == 0)
		return;
	arr[x].h = max(arr[arr[x].l].h + 1, arr[arr[x].r].h + 1);
	height(arr[x].p);
}

void del(ll ind) {
	if ((arr[ind].l == 0) && (arr[ind].r == 0)) {
		if (arr[arr[ind].p].l == ind)
			arr[arr[ind].p].l = 0;
		else
			arr[arr[ind].p].r = 0;
		ch_size(arr[ind].p, -1);
		height(arr[ind].p);
		rebalance(arr[ind].p);
		return;
	}
	if (arr[ind].l == 0) {
		arr[arr[ind].r].p = arr[ind].p;
		if (arr[arr[ind].p].l == ind)
			arr[arr[ind].p].l = arr[ind].r;
		else
			arr[arr[ind].p].r = arr[ind].r;
		ch_size(arr[ind].p, -1);
		height(arr[ind].p);
		rebalance(arr[ind].p);
		return;
	}
	if (arr[ind].r == 0) {
		arr[arr[ind].l].p = arr[ind].p;
		if (arr[arr[ind].p].l == ind)
			arr[arr[ind].p].l = arr[ind].l;
		else
			arr[arr[ind].p].r = arr[ind].l;
		ch_size(arr[ind].p, -1);
		height(arr[ind].p);
		rebalance(arr[ind].p);
		return;
	}
	ll next = go_left(arr[ind].r);
	arr[ind].value = arr[next].value;
	del(next);
}

ll find(ll val) {
	ll ind = arr[0].l;
	while (true) {
		if (arr[ind].value == val || ind == 0)
			return ind;
		if (arr[ind].value < val) {
			ind = arr[ind].r;
		}
		else {
			ind = arr[ind].l;
		}
	}
	return ind;
}

void rebalance(ll ind) {
	int res = arr[ind].p;
	if (ind == 0)
		return;
	if (arr[arr[ind].l].h - 1 > arr[arr[ind].r].h)
		res = lrotate(ind);
	else
		if (arr[arr[ind].r].h - 1 > arr[arr[ind].l].h) {
			res = rrotate(ind);
		}
	if (res != 0)
		rebalance(res);
}

ll lrotate(ll x) {
	ll k = 0;
	ll y = arr[x].l;
	ll p = arr[x].p;
	arr[x].l = arr[y].r;
	arr[y].r = x;
	arr[y].p = p;
	if (arr[x].l != 0)
		arr[arr[x].l].p = x;
	if (arr[p].l == x)
		arr[p].l = y;
	else
		arr[p].r = y;
	arr[x].p = y;
	height(x);
	recount(x);
	arr[x].size = arr[arr[x].l].size + arr[arr[x].r].size + 1;
	arr[y].size = arr[arr[y].l].size + arr[arr[y].r].size + 1;
	return arr[y].p;
}

ll rrotate(ll x) {
	ll y = arr[x].r;
	ll p = arr[x].p;
	arr[x].r = arr[y].l;
	arr[y].l = x;
	arr[y].p = p;
	if (arr[x].r != 0)
		arr[arr[x].r].p = x;
	if (arr[p].l == x)
		arr[p].l = y;
	else
		arr[p].r = y;
	arr[x].p = y;
	height(x);
	recount(x);
	arr[x].size = arr[arr[x].l].size + arr[arr[x].r].size + 1;
	arr[y].size = arr[arr[y].l].size + arr[arr[y].r].size + 1;
	return arr[y].p;
}

ll get_k(ll ind, ll size) {
	if (size - 1 == arr[arr[ind].r].size)
		return ind;
	if (size <= arr[arr[ind].r].size)
		return get_k(arr[ind].r, size);
	return get_k(arr[ind].l, size - arr[arr[ind].r].size - 1);
}

void recount(ll ind) {
	if (ind == 0)
		return;
	if (arr[ind].l == 0 && arr[ind].r == 0) {
		arr[ind].sum = arr[ind].value;
		arr[ind].min = arr[ind].value;
		arr[ind].max = arr[ind].value;
	}
	if (arr[ind].r != 0) {
		arr[ind].sum = min(arr[ind].value, arr[arr[ind].r].sum);
		arr[ind].min = min(arr[ind].min, arr[arr[ind].r].min);
		arr[ind].max = max(arr[ind].max, arr[arr[ind].r].max);
	}
	if (arr[ind].l != 0) {
		arr[ind].sum = min(arr[ind].value, arr[arr[ind].l].sum);
		arr[ind].min = min(arr[ind].min, arr[arr[ind].l].min);
		arr[ind].max = max(arr[ind].max, arr[arr[ind].l].max);
	}
	if (arr[ind].l != 0 && arr[ind].r != 0)
		arr[ind].sum = min(arr[ind].sum, arr[arr[ind].r].sum);
	recount(arr[ind].p);
}

ll find_sum(ll ind, ll l, ll r, ll size) {
	if (ind == 0)
		return int(2e9);
	int left = size + 1, right = size + arr[ind].size;
	if (right < l || left > r)
		return int(2e9);
	if (left >= l && right <= r)
		return arr[ind].sum;
	ll res = min(find_sum(arr[ind].l, l, r, size), find_sum(arr[ind].r, l, r, arr[arr[ind].l].size + 1 + size));
	if (arr[arr[ind].l].size + size + 1 <= r && arr[arr[ind].l].size + size + 1 >= l)
		res = min(res, arr[ind].value);
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n = 0, m = 0;
	cin >> m;
	int val = 0, a = 0, b = 0;
	char s[5];
	arr[0].value = ll(2e9);
	ll k = 0, tmp = ll(2e9);
	for (int i = 0; i < m; i++) {
		cin >> s;
		if (s[0] == '+') {
			cin >> a >> b;
			val++;
			add(val - a, b);
		}
		else {
			cin >> a >> b;
			cout << find_sum(arr[0].l, a, b, 0) << '\n';
		}
	}
}
