#include <iostream>

using namespace std;

void merge(int a[], int lo, int hi) {
	int mi = (lo + hi) >> 1;
	int *A = new int[mi - lo];
	for (int i = lo; i < mi; i++)
		A[i - lo] = a[i];
	int *B = a;
	for (int i = 0, j = mi, k = lo; i < mi - lo;) {
		if (j >= hi || A[i] <= B[j]) a[k++] = A[i++];
		if (j < hi && B[j] < A[i]) a[k++] = B[j++];
	}
}

void mergeSort(int a[], int lo, int hi) {
	if (hi - lo <= 1)
		return;
	int mi = (lo + hi) >> 1;
	mergeSort(a, lo, mi);
	mergeSort(a, mi, hi);
	merge(a, lo, hi);
}

int main() {
	int n, a[100];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	mergeSort(a, 0, n);
	for (int i = 0; i < n - 1; i++)
		cout << a[i] << " ";
	cout << a[n - 1] << endl;
	if (n % 2 == 1)
		cout << a[n / 2];
	else
		cout << (a[n / 2] + a[n / 2 - 1]) / 2 << endl;
}