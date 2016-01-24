#include <iostream>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

bool cmp(int a, int b) {
	return a > b;
}

bool legal(int a[]) {
	for (int i = 0; i < 10; i++) {
		list<int> less;
		for (int j = i + 1; j < 10; j++) {
			if (a[j] < a[i])
				less.push_back(a[j]);
		}
		list<int> temp = less;
		less.sort(cmp);
		if (less != temp)
			return false;
	}
	return true;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a[10];
		for (int j = 0; j < 10; j++)
			cin >> a[j];
		if (legal(a))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
}