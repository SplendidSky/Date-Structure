#include <iostream>

using namespace std;

int res = 0;

void climb_stairs(int n) {
	if (n == 1)
		climb_stairs(n - 1);
	else if (n > 1) {
		climb_stairs(n - 1);
		climb_stairs(n - 2);
	}
	else
		res++;
}

int main() {
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;
		climb_stairs(n);
		cout << res << endl;
		res = 0;
	}
}