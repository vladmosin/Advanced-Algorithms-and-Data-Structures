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

using namespace std;
double x1 = 0, b1 = 0, r1 = 0;
double x2 = 0, y2 = 0, r2 = 0; 
double x3 = 0, y3 = 0, r3 = 0;
int sum = 0;

bool check(double x, double y) {
	int cou = 0;
	if ((x - x1) * (x - x1) + (y - b1) * (y - b1) <= r1 * r1)
		cou++;
	if ((x - x2) * (x - x2) + (y - y2) * (y - y2) <= r2 * r2)
		cou++;
	if ((x - x3) * (x - x3) + (y - y3) * (y - y3) <= r3 * r3)
		cou++;
	sum += cou;
	if (cou == 3)
		return true;
	return false;
}

int main() {
	cin >> x1 >> b1 >> r1 >> x2 >> y2 >> r2 >> x3 >> y3 >> r3;
	int64_t res = 0;
	for (int i = -1000; i < 2001; i++)
		for (int j = -1000; j < 2001; j++) {
			if (check((1.0 * i) / 1000, (1.0 * j) / 1000))
				res++;
	}
	if (res < 1000) {
		cout << 0;
		return 0;
	}
	cout.precision(10);
	cout << ((res * 1.0) / (1001 * 1001));
}
