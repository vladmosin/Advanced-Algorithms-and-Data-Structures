#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdint.h>
#include <cmath>

using namespace std;
typedef unsigned long long ll;

ll func(ll a, ll p) {
	unsigned __int128 c = a;
	return (c * c + 1) % p;
}

ll multi(ll a, ll b, ll n) {
	unsigned __int128 c = a, d = b;
	return (c * d) % n;
}

ll gcd(ll a, ll b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

int ilog(ll p) {
	int counter = 0;
	while (p > 0) {
		p /= 2;
		counter++;
	}
	return counter;
}

ll to_degr(ll a, ll t, ll p) {
//	cout << a << " sdkjk " << t << '\n';
	ll arr[100];
	ll res = 1, tmp = t;
	arr[1] = a % p;
	for (int i = 2; i <= ilog(t); i++) {
		arr[i] = multi(arr[i - 1], arr[i - 1], p);
	}
	for (int i = 1; i <= ilog(t); i++) {
		if (tmp % 2 == 1)
			res = multi(res, arr[i], p);
	//	cout << res << '\n';
		tmp /= 2;
	}
	return res;
}

bool isPrime(ll p) {
	if (p < 2)
		return 0;
	ll s = 0, a = 0, t = p - 1, g = 0;
	while (t % 2 == 0) {
		t /= 2;
		s++;
	}
//	cout << s << ' ';
	for (int j = 0; j < 10; j++) {
		a = (rand() * ll(rand())) % (p - 2) + 2;
		//cout << a << ' ' << t << ' ' << p << '\n';
		g = to_degr(a, t, p);
	//	cout << g << ' ' << a << '\n';
		for (int i = 0; i < s; i++) {
			if (g == 1)
				break;
			if ((g % p) != p - 1 && multi(g, g, p) == 1)
				return false;
			g = multi(g, g, p);
		}
		if (g != 1) {
		//	cout << g << ' ' << j << '\n';
			return false;
		}
	}
	return true;
}

bool small_int(ll p) {
	for (ll i = 2; i < min(ll(100000), p - 1); i++) {
		if (p % i == 0) {
			cout << i << ' ' << p / i;
			return true;
		}
	}
	return false;
}

int main () {
	srand(time(NULL));
	ll n = 0;
	cin >> n;
	if (n < 1e10) {
		if(!small_int(n))
			cout << "IMPOSSIBLE";
		return 0;
	}
	if (isPrime(n)) {
		cout << "IMPOSSIBLE";
		return 0;
	}
	if (small_int(n)) {
		return 0;
	}
	for (int j = 0; j < 100; j++) {
	ll x = 0, g = 0, mult = 1, y = 0, last = 0;
	int k = 0, counter = 0;
	x = rand() % (n - 2) + 2; 
	k = 4 * int(pow(n, 1.0 / 4));
//	cout << k << '\n';
	for (int i = 0; i < k - 1; i++) {
		x = func(x, n);
	/*	if (tr[x % 6700417] != 0) {
			cout << x % 6700417 << ' ' << i - tr[x % 6700417] << ' ' << '\n';
			last = i;
		}
		tr[x % 6700417] = i;*/
	}
	y = func(x, n);
	for (int i = 0; i < k - 1; i++) {
		if (counter == 19) {
			counter = 0;
		//	cout << mult << ' ' << n << ' ' << gcd(mult, n) << '\n';
			g = gcd(mult, n);
		//	cout << g << '\n';
			if (g != 1 && g != n) {
				cout << g << ' ' << n / g;
				return 0;
			}
			mult = 1;
		}
		else {
			counter++;
			if (x > y)
				mult = multi(mult, (x - y),  n);
			else
				mult = multi(mult, (y - x),  n);
		//	cout << mult << '\n';
		}
		y = func(y, n);
	}
}
	//cout << to_degr(194047, 67280421310720 / 2, 67280421310721);
	cout << "IMPOSSIBLE";
}
