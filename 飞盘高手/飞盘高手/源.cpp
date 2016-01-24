#include <iostream>
#include <queue>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		queue<int> q;
		int n;
		cin >> n;
		for (int j = 1; j <= n; j++)
			q.push(j);
		while (q.size() > 1) {
			int cur = q.front();
			cout << cur << " ";
			q.pop();
			int next = q.front();
			q.pop();
			q.push(next);
		}
		cout << q.front() << " " << endl;
	}
}
