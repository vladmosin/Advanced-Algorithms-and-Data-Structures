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

using namespace std;
typedef long long ll;
int n = 0;
ll  a = 0, b = 0, c = 0, m = 0, cur = 0;
ll counter = 0;
ll c2 = 0;

ll calc(ll i) {
	ll tmp = i * a;
	counter++;
	if (tmp > 1000000000000)
		tmp %= m;
	return (tmp * i + b * i + c) % m;
}

bool solve(int dep, ll index) {
	bool res1 = 0, res2 = 0, res3 = 0, res4 = 0;
	ll cur1 = 0, cur2 = 0;
	if (dep == n)
		return (calc(index - (1 << dep)) >= cur);
	if (dep == n - 1) {
		cur1 = calc(2 * index - (1 << (dep + 1)));
		cur2 = calc(2 * index  + 1 - (1 << (dep + 1)));
		return (max(cur1, cur2) >= cur);
	}
	int bit = rand() % 2;
	res1 = solve(dep + 2, index * 4 + bit * 2);
	if (res1)
		res2 = solve(dep + 2, index * 4 + bit * 2 + 1);
	if (res1 && res2) {
		c2++;
		return true;
	}
	bit = 1 - bit;
	res3 = solve(dep + 2, index * 4 + 2 * bit);
	if (!res3)
		return false;
	res4 = solve(dep + 2, index * 4 + 2 * bit + 1);
	return (res3 && res4);
}

int main() {
	srand(time(NULL));
	cin >> n >> a >> b >> c >> m;
	ll l = 0, r = m, med = 0;
	bool fl = false;
	while (l < r - 1) {
		med = (r + l) / 2;
		cur = med;
		fl = solve(0, 1);
		if (fl)
			l = med;
		else
			r = med;
	}
	cur = r;
	fl = solve(0, 1);
	if (fl)
		cout << cur;
	else
		cout << l;
}
