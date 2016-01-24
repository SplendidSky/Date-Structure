#include <iostream>

using namespace std;

void movePlates(int n, char a, char b) {
	cout << "move disk " << n << " from peg " << a << " to peg " << b << endl;
}

void hanoi(int n, char x, char y, char z) {
	if (n == 1)
		movePlates(n, x, z);
	else {
		hanoi(n - 1, x, z, y);
		movePlates(n, x, z);
		hanoi(n - 1, y, x, z);
	}
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		hanoi(n, '1', '2', '3');
	}
	return 0;
}