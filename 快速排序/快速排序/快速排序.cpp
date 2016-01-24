// 快速排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

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
		a[lo] = a[hi];
		while (a[lo] <= pivot) {
			lo++;
			if (lo == hi) {
				a[lo] = pivot;
				return lo;
			}
		}
		a[hi] = a[lo];
	}
}

void quickSort(int a[], int lo, int hi) {
	int p = partition(a, lo, hi);
	if (p < hi - 1) quickSort(a, p + 1, hi);
	if (lo + 1 < p) quickSort(a, lo, p - 1);
}

int main()
{
	int arr[] = { 5,8, 6, 1, -3, 22, 0, 0, 5 };
	quickSort(arr, 0, 8);
	for (int i = 0; i < 9; i++)
		cout << arr[i] << " ";
	cout << endl;
	return 0;
}

