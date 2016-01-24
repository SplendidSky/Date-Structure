#include <iostream>

using namespace std;


int main() {
	int N, K;
	cin >> N >> K;
	int *a = new int[1000000];
	for (int i = 0; i < 1000000; i++)
		a[i] = 0;
	int num;
	for (int i = 0; i < N; i++) {
		cin >> num;
		num += 10000002;
		int index = num / 32;
		int bit = num % 32;
		int b = 1;
		for (int j = 0; j < 32 - bit; j++)
			b = b << 1;
		a[index] = (a[index] | b);
	}
	int k = 0, last = num;
	for (int i = 999999; i >= 0; i--) {
		int b = 1;
		for (int j = 0; j < 32; j++) {
			if ((b & a[i]) == b) {
				k++;
				last = (i + 1) * 32 - j - 10000002;
			}
			if (k == K) {
				cout << last << endl;
				return 0;
			}
			b = b << 1;
		}
	}
	cout << last << endl;
}
