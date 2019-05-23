#include <set>
#include <random>
#include <cassert>
#include <functional>

// Sources: https://habr.com/ru/post/119852/, https://en.wikipedia.org/wiki/HyperLogLog

class UniqCounter {
	// no more than 32kb of memory should be used here
private:
	static const int N = 1 << 11;
	double alpha = (0.7213 * N) / (N + 1.079);
	static const int MAX_RANK = 33;

	int rankHolder[N];

	int rank(unsigned long long hash) {
		int rank = 1;

		if (hash == 0) {
			return MAX_RANK;
		}

		while ((hash & 1) == 0) {
			rank++;
			hash /= 2;
		}

		return rank;
	}

	unsigned long long fnv1a(int n)
	{
		unsigned long long hash = 2166136261;
		while (n > 0)
		{
			hash ^= (n % 10);
			hash += (hash << 1) + (hash << 4) + (hash << 7) + (hash << 8) + (hash << 24);
			n /= 10;
		}
		return hash;
	}

public:
	UniqCounter() {
		std::fill(rankHolder, rankHolder + N, 0);
	}

	void add(int x) {
		unsigned long long hash = fnv1a(x);
		int index = hash & (N - 1);
		rankHolder[index] = std::max(rank(hash >> 12), rankHolder[index]);
	}

	int get_uniq_num() const {
		double coef = 0.0;
		for (int i = 0; i < N; i++) {
			coef += 1 / double(1 << rankHolder[i]);
		}

		int E = alpha * N * N / coef;
		if (E <= 2.5 * N)
		{
			int empty = 0; 
			for (int i = 0; i < N; i++) {
				if (rankHolder[i] == 0) empty++;
			}

			E = N * log(N / double(empty));
		}

		return E;
	}
};

double relative_error(int expected, int got) {
	return abs(got - expected) / (double)expected;
}

int main() {
	std::random_device rd;
	std::mt19937 gen(rd());

	const int N = (int) 1e6;
	for (int k : {1, 10, 100, 1000, 10000, N / 10, N, N * 10}) {
		std::uniform_int_distribution<> dis(1, k);
		std::set<int> all;
		UniqCounter counter;
		for (int i = 0; i < N; i++) {
			int value = dis(gen);
			all.insert(value);
			counter.add(value);
		}
		int expected = (int)all.size();
		int counter_result = counter.get_uniq_num();
		double error = relative_error(expected, counter_result);
		printf("%d numbers in range [1 .. %d], %d uniq, %d result, %.5f relative error\n", N, k, expected, counter_result, error);
		assert(error <= 0.1);
	}

	return 0;
}