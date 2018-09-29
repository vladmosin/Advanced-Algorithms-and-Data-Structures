#include <vector>
#include <iostream>
#include <time.h>
#include <algorithm>

typedef long long ll;
using std::vector;
using std::cin;
using std::cout;
using std::fill;

vector<int> visa, visb, pair, used;
vector<int> g[4002];

bool dfs(int v) {
	if (used[v])
		return false;
	used[v] = 1;
	for (int i : g[v])
		if ((pair[i] == -1) || (dfs(pair[i]))) {
			pair[i] = v;
			return true;
		}
	return false;
}

void dfs_simple(int v) {
	visa[v] = 1;
	for (int i : g[v]) {
		visb[i] = 1;
		if (pair[i] && (visa[pair[i]] != 1))
			dfs_simple(pair[i]);
	}
}

void invert(int boys, int girls) {
	vector<int> tmp;
	for (int i = 1; i <= boys; i++) {
		std::sort(g[i].begin(), g[i].end());
		int ind = 0;
		tmp.resize(0);
		for (int j = 1; j <= girls; j++) {
			if ((ind == g[i].size()) || g[i][ind] != j)
				tmp.push_back(j);
			else
				ind++;
		}
		g[i] = tmp;
	}
}

void input(int boys) {
	for (int i = 1; i <= boys; i++) {
		for (int x : g[i])
			cout << x << ' ';
		cout << '\n';
	}
}

int main()
{
	int a = 0, b = 0, c = 0, val = 0, k = 0;
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> k;

	for (int k1 = 0; k1 < k; k1++) {
		cin >> a >> b;
		for (int i = 1; i <= a; i++) {
			g[i].resize(0);
			while (true) {
				cin >> val;
				if (!val)
					break;
				g[i].push_back(val);
			}
		}

		invert(a, b);

		visa.resize(a + 1);
		visb.resize(b + 1);
		fill(visa.begin(), visa.end(), 0);
		fill(visb.begin(), visb.end(), 0);

		used.resize(a + 1);
		fill(used.begin(), used.end(), 0);
		pair.resize(b + 1);
		fill(pair.begin(), pair.end(), -1);

		for (int i = 1; i <= a; i++) {
			if (dfs(i)) {
				fill(used.begin(), used.end(), 0);
			}
		}

		for (int i = 1; i <= b; i++) {
			if (pair[i] != -1) {
				visa[pair[i]] = -1;
			}
		}

		for (int i = 1; i <= a; i++)
			if (visa[i] == 0)
				dfs_simple(i);

		vector<int> resa, resb;
		for (int i = 1; i <= a; i++)
			if (visa[i] == 1)
				resa.push_back(i);
		for (int i = 1; i <= b; i++) {
			if (visb[i] != 1)
				resb.push_back(i);
		}

		cout << resa.size() + resb.size() << '\n';

		cout << resa.size() << ' ' << resb.size() << '\n';
		for (int x : resa)
			cout << x << ' ';
		cout << '\n';

		for (int x : resb)
			cout << x << ' ';
		cout << '\n';
	}
	return 0;
}
