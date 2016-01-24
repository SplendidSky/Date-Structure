#include <iostream>

using namespace std;

void insert_heap(int cur, int a[], int lo, int hi) {
	int large = 2 * lo + 1;
	while (large < hi) {
		if (large + 1 < hi && a[large] < a[large + 1])
			large++;
		if (a[large] < cur)
			break;
		else {
			a[lo] = a[large];
			lo = large;
			large= 2 * lo + 1;
		}
		a[lo] = cur;
	}
}

void build_heap(int a[], int lo, int hi) {
	for (int i = (hi - lo) / 2; i >= 0; i--) {
		int cur = a[i];
		insert_heap(cur, a, (hi - lo) / 2, hi);
	}
}

void heap_sort(int a[], int lo, int hi) {
	build_heap(a, lo, hi);		
	for (int i = 0; i < hi - lo; i++)
		cout << a[i] << " ";
	cout << endl;
	for (int last_sorted = hi - lo - 1; last_sorted >= 0; last_sorted--) {
		int cur = a[last_sorted];
		a[last_sorted] = a[lo];
		insert_heap(cur, a, lo, last_sorted);
		for (int i = 0; i < hi - lo; i++)
			cout << a[i] << " ";
		cout << endl;
	}
}

int main() {
	do {
		int n, a[10020];
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		heap_sort(a, 0, n);
	} while (!cin.eof());
}