#include <iostream>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		int n, a[27];
		cin >> n;
		for (int j = 0; j < n; j++)
			a[j] = 0;
		int pos = 0;
		for (int j = 0; j < n; j++) {
			int p = 0;
			while (p < j) {
				if (a[pos] == 0)
					p++;
				pos = (pos + 1 == n) ? 0 : pos + 1;
			}
			while (a[pos] != 0)
				pos = (pos + 1 == n) ? 0 : pos + 1;
			a[pos] = j + 1;
		}
		for (int j = 0; j < n; j++)
			cout << a[j] << " ";
		cout << endl;
	}
}