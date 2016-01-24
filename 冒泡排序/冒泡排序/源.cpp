#include <iostream>

using namespace std;

void swap(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}

void bubble_sort(int a[], int lo, int hi) {
	int last = hi; //��¼���һ�η���������λ�ã��ڴ�λ��֮ǰ����������
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		int s = last;
		for (int i = lo; i < last - 1; i++) {
			if (a[i + 1] < a[i]) { //����������򣬽�����������������Ϊ����
				swap(a[i], a[i + 1]);
				s = i + 1;  //��¼����������λ�ã�����һ�������һ��λ��
				sorted = false;
			}
		}
		last = s;  //��ѭ���˳���sһ�������һ�η���������λ��
	}
}

int main() {
	int a[] = { 10, 5, 2, 55, 28, 33, 52, 10, 1, 10 };
	bubble_sort(a, 0, 10);
	for (auto n : a)
		cout << n << " ";
}