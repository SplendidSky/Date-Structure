#include <iostream>

using namespace std;

bool isSorted(int a[], int N) {
	for (int i = 0; i < N - 1; i++)
		if (a[i] > a[i + 1])
			return false;
	return true;
}

bool insert(int a[], int n, int lo, int hi) {
	int i = lo;
	bool hasSorted = false;
	while (i < hi && a[i] < n) i++;
	int temp = a[i];
	a[i] = n;
	int self;
	for (int j = i + 1; j <= hi; j++) {
		hasSorted = true;
		self = a[j];
		a[j] = temp;
		temp = self;
	}
	return hasSorted;
}

int insert_sort(int a[], int N) {
	int times = 0;
	for (int i = 1;; i++) {
		if (isSorted(a, N))
			break;
		times += insert(a, a[i], 0, i);
	}
	return times;
}

int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		int N, a[10010];
		cin >> N;
		for (int j = 0; j < N; j++)
			cin >> a[j];
		cout << 5 * insert_sort(a, N) << endl;
	}
}