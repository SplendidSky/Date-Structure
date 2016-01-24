#include <iostream>

using namespace std;

void swap(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}

int partition(int a[], int lo, int hi) {
	int pivot = a[lo];
	while (lo < hi) {
		while (pivot <= a[hi]) {
			hi--;
			if (lo == hi) {
				a[lo] = pivot;
				return lo;
			}
		}
		swap(a[lo], a[hi]);
		while (a[lo] <= pivot) {
			lo++;
			if (lo == hi) {
				a[lo] = pivot;
				return lo;
			}
		}
		swap(a[lo], a[hi]);
	}

}

void quickSort(int a[], int lo, int hi) {
	int p = partition(a, lo, hi);
	if (p < hi - 1) quickSort(a, p + 1, hi);
	if (lo + 1 < p) quickSort(a, lo, p - 1);
}

int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		int N, K, a[100002];
		cin >> N >> K;
		for (int j = 0; j < N; j++)
			cin >> a[j];
		quickSort(a, 0, N - 1);
		if (K % 2 == 1)
			cout << a[N - K / 2 - 1] - a[K / 2] << endl;
		else
			cout << (a[N - K / 2] + a[N - K / 2 - 1]) / 2 - (a[K / 2 - 1] + a[K / 2]) / 2 << endl;
	}
}
