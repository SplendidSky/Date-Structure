
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
	if (a.first < b.first || (a.first == b.first && a.second < b.second))
		return true;
	return false;
}

int bestArrangement(vector<pair<int, int> > a) {
	int res = a.size();
	for (vector<pair<int, int> >::iterator it = a.begin(); it != a.end(); it++) {
		if ((it + 1) != a.end()) {
			if (it->second > (it + 1)->first) {
				vector<pair<int, int> > b = a;
				vector<pair<int, int> > c = a;
				b.erase(b.begin() + (it - a.begin()));
				c.erase(c.begin() + (it - a.begin() + 1));
				int r1 = bestArrangement(b);
				int r2 = bestArrangement(c);
				res = r1 > r2 ? r1 : r2;
			}
		}
	}
	return res;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int m;
		cin >> m;
		vector<pair<int, int> > apply;
		for (int j = 0; j < m; j++) {
			int l, r;
			cin >> l >> r;
			apply.push_back(make_pair(l, r));
		}
		sort(apply.begin(), apply.end(), cmp);
		cout << bestArrangement(apply) << endl;
	}
}
