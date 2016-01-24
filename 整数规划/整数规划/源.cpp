#include <iostream>

using namespace std;

void integer_partition(int n, int l) {
	if (l == 0)
		cout << n << endl;
	integer_partition(n - 1, l + 1);
	cout << n - l << " + " << l;
}

int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		int n;
		cin >> n;
		integer_partition(n, 0);
	}
}