#include <iostream>
#include <stack>

using namespace std;

int cnt = 0;

void shoot_roll(int b, int l) {
	if (b == 0 && l == 0) cnt++;
	else {
		if (b == 0) shoot_roll(b + 1, l - 1);
		if (l == 0) shoot_roll(b - 1, l);
		if (b != 0 && l != 0) {
			shoot_roll(b + 1, l - 1);
			shoot_roll(b - 1, l);
		}
	}
}


int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		int n;
		cin >> n;
		shoot_roll(0, n);
		cout << cnt << endl;
		cnt = 0;
	}
}