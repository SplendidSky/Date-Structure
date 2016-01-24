#include <iostream>
#include <list>
#include <vector>
#include <iomanip>

using namespace std;

void Hash(vector<list<int>> &group, int luckyNum, int m) {
	int s = luckyNum % m;
	group[s].push_front(luckyNum);
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		int luckyNum[1002];
		vector<list<int>> group;
		for (int i = 0; i < m; i++)
			group.push_back(list<int>());
		for (int i = 0; i < n; i++) {
			cin >> luckyNum[i];
			Hash(group, luckyNum[i], m);
		}
		double count = 0;
		for (int i = 0; i < group.size(); i++) {
			int k = 1;
			for (list<int>::iterator it = group[i].begin(); it != group[i].end(); it++, k++) {
				cout << *it << " ";
				count += k;
			}
			cout << endl;
		}
		double avg = count / n;
		cout << setiosflags(ios::fixed);
		cout << setprecision(3) << avg << endl;
	}
}
