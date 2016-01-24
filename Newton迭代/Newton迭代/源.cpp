#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
	vector<pair<double, double>> cp;
	double first, second;
	cin >> first >> second;
	cp.push_back(make_pair(first, second));
	while (cin >> first >> second)
		cp.push_back(make_pair(first, second));
	double x = rand(), x0;
	do {
		x0 = x;
		double fx = 0, dfx = 0;
		for (auto const &c : cp) {
			fx += c.first * pow(x0, c.second);
			double d;
			if (c.second - 1 >= 0)
				d = pow(x0, c.second - 1);
			else
				d = 0;
			dfx += c.first * c.second * d;
		}
		x = x0 - fx / dfx;
	} while (abs(x - x0) > 0.000000001);
	cout << x << endl;
}
