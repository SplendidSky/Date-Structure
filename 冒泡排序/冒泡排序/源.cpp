#include <iostream>

using namespace std;

void swap(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}

void bubble_sort(int a[], int lo, int hi) {
	int last = hi; //记录最后一次发生交换的位置，在此位置之前，数组有序
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		int s = last;
		for (int i = lo; i < last - 1; i++) {
			if (a[i + 1] < a[i]) { //如果发现逆序，交换两数，将数组标记为无序
				swap(a[i], a[i + 1]);
				s = i + 1;  //记录发生交换的位置，但不一定是最后一个位置
				sorted = false;
			}
		}
		last = s;  //从循环退出后，s一定是最后一次发生交换的位置
	}
}

int main() {
	int a[] = { 10, 5, 2, 55, 28, 33, 52, 10, 1, 10 };
	bubble_sort(a, 0, 10);
	for (auto n : a)
		cout << n << " ";
}