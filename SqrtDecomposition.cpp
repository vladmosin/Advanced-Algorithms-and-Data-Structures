

//#include "stdafx.h"
#include <vector>
#include <cstring>
#include <iostream>
#include <utility>
#include <algorithm>
#include <queue>
#include <list>
#include <time.h>

using namespace std;

int p[100100], s_p[100100];
int flags[1001];

void calc(int ind) {
	for (int i = 0; i < 100; i++)
		s_p[ind * 100 + i] = p[ind * 100 + i] = p[ind * 100 + i] + flags[ind];
	flags[ind] = 0;
	sort(s_p + ind * 100, s_p + (ind + 1) * 100);
}

bool check(int ind, int num) {
	num -= flags[ind];
	auto iter = lower_bound(s_p + ind * 100, s_p + 100 * (ind + 1), num);
	return (iter < s_p + (ind + 1) * 100) && (*iter == num);
}

int main() {
	int n = 0, m = 0, l = 0, r = 0, s = 0;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> p[i];
	for (int i = 0; i < n / 100 + 1; i++) {
		calc(i);
	}
	char cmd;
	for (int i = 0; i < m; i++) {
		cin >> cmd;
		cin >> l;
		l--;
		cin >> r;
		cin >> s;
		int lf = l / 100, rg = r / 100;
		int fr = 100 * (lf + 1), to = rg * 100;
		if (cmd == '?') {
			bool fl = false;
			while (l < r && l < fr)
				fl |= (p[l++] == s - flags[lf]);
			while (l < r && r > to) 
				fl |= (p[--r] == s - flags[rg]);
			for (int j = lf++; (lf < rg) && (!fl); lf++)
				fl |= check(lf, s);
			fl ? cout << "YES\n" : cout << "NO\n";
		}
		else {
			if (l < fr) {
				while (l < r && l < fr)
					p[l++] += s;
				calc(lf);
			}
			if (r > to) {
				while (l < r && r > to)
					p[--r] += s;
				calc(rg);
			}
			for (int j = lf++; lf < rg; lf++)
				flags[lf] += s;
		}
	}
}

