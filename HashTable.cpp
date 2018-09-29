#include <string>
#include <iostream>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <utility>  
#include <cstdlib>
#include <unordered_map>
#include <iomanip> 
#include "optimization.h"
using namespace std;

int N = 300000;

long long d[N];
int a[N];
int from[N];
int last[N];
int main() {
	int n = 0, j = 0, answer = 0;
	n = readInt();
	for (int i = 0; i < n; i++) {
		d[i] = 1e9;
		a[i] = readInt();
	}
	d[0] = -1e9;
	for (int i = 0; i < n; i++) {
		j = upper_bound(d, d + n, -a[i]) - d;
		last[i] = from[j - 1];
		d[j] = -a[i];
		from[j] = i;
		answer = max(answer, j);
	}
	writeInt(answer, '\n');
	int c = from[answer];
	vector<int> num;
	for (int i = 1; i < answer + 1; i++) {
		num.push_back(c + 1);
		c = last[c];
	}
	for (int i = num.size() - 1; i > -1; i--)
		writeInt(num[i], '\n');
}
