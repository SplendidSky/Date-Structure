#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
	int n;
	cin >> n;
	string dict;
	cin >> dict;
	vector<string> d;
	for (int i = 0; i < n; i++)
		d.push_back(dict.substr(i, 1));
	string seq;
	cin >> seq;
	istringstream is(seq);
	int ord, ords[102];
	string output;
	int j = 0;
	while (is >> ord) {
		if (ord < 0)
			ords[j++] = -ord;
		else
			ords[j++] = ord;
	}
	int q = 0;
	while (q < j) {
		if (ords[q] == 0) {
			bool flag = 1;
			for (int k = q + 1; k < j; k++)
				if (ords[q] == 0)
					flag = 0;
			if (flag)
				cout << output;
			else {
				cout << output << " ";
				d.push_back(output);
				output = "";
			}
		}
		else {
			output += d[ords[q] - 1];
		}
		q++;
	}
	cout << endl;
}