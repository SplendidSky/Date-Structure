#include <iostream>

using namespace std;

void swap(int &a, int &b) {
	int c;
	c = a;
	a = b;
	b = c;
}

void selectSort(int a[], int lo, int hi, int n) {
	while (lo < hi - 1) {
		int min_index = lo;
		for (int i = lo; i < hi; i++) {
			if (a[i] < a[min_index])
				min_index = i;
		}
		swap(a[lo++], a[min_index]);
		for (int i = 0; i < n; i++) {
			if (i == n - 1)
				cout << a[i] << endl;
			else
				cout << a[i] << " ";
		}
	}
}

int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		int N, a[1002];
		cin >> N;
		for (int j = 0; j < N; j++)
			cin >> a[j];
		selectSort(a, 0, N, N);
	}
}
