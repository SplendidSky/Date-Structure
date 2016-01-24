#include <iostream>

using namespace std;

int f(int m, int n) {
	if (m == 0 || n == 1) return 1;
	if (m < n) return f(m, m);
	if (m >= n) return f(m, n - 1) + f(m - n, n);
}




int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		int m, n;
		cin >> m >> n;
		cout << f(m, n) << endl;
	}
}