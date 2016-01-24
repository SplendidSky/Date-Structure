#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int money, count = 0;
		cin >> money;
		count += money / 100;
		money = money - money / 100 * 100;
		count += money / 50;
		money = money - money / 50 * 50;
		count += money / 20;
		money = money - money / 20 * 20;
		count += money / 10;
		money = money - money / 10 * 10;
		count += money / 5;
		money = money - money / 5 * 5;
		count += money;
		cout << count << endl;
	}
}