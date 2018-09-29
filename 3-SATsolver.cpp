
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>

using namespace std;

int arr[1000][3];
int bit[1000][3];
int val_set[120];
int aux_set[120];

inline bool true_var(int k, int num) {
	int value = arr[k][num];
	if (val_set[value - 1] == bit[k][num])
		return true;
	return false;
}

inline bool true_gate(int k) {
	if (true_var(k, 0) || true_var(k, 1) || true_var(k, 2))
		return true;
	return false;
}

int true_set(int m) {
	for (int i = 0; i < m; i++) {
		if (!true_gate(i))
			return i;
	}
	return -1;
}

inline void gen_point(int n) {
	for (int i = 0; i < n; i++) {
		aux_set[i] = rand() % 2;
	}
}

inline long long get_range(int n) {
	return (long long)(2 * pow(2, n * (5.0 / 3)) / pow(3, n));
}

inline void copy_set(int n) {
	for (int i = 0; i < n; i++) {
		val_set[i] = aux_set[i];
	}
}

inline void print_set(int n) {
	for (int i = 0; i < n; i++) {
		cout << val_set[i];
	}
	cout << '\n';
}

inline void change_pos(int pos) {
	//cout << pos << val_set[pos];
	if (val_set[pos] == 0)
		val_set[pos] = 1;
	else
		val_set[pos] = 0;
	//cout << val_set[pos] << " ";
}

inline bool walk(int m, int n) {
	for (int i = 0; i < 4 * n + 8; i++) {
		int pos = true_set(m);
		//cout << pos;
		//print_set(n);
		if (pos == -1)
			return true;
		change_pos(arr[pos][rand() % 3] - 1);
		//print_set(n);
	}
	return false;
}

inline long long get_steps(int n) {
	if (n < 36)
		return (long long)(pow(2, n / 3));
        if (n < 91)
	    return (long long)(pow(2, n / 3)) / 4;
        return (long long)(pow(2, n / 5));
}

int main()
{
	int n = 0, m = 0;
	srand(time(NULL));
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> arr[i][0] >> bit[i][0] >> arr[i][1] >> bit[i][1] >> arr[i][2] >> bit[i][2];
	}
	for (long long i = 0; i < get_range(n); i++) {
		gen_point(n);
		for (long long j = 0; j < get_steps(n); j++) {
			copy_set(n);
			if (walk(m, n)) {
				print_set(n);
				return 0;
			}
		}
	}
	return 0;
}
