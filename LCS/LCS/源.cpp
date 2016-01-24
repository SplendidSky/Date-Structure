#include <iostream>
#include <string>
#include <vector>

using namespace std;



int main() {
	vector<int> a(6) = { 1, 2, 3, 4, 5, 6 };
	cout << a.size() << endl;
	a.resize(4);
	cout << a.size() << endl;
}