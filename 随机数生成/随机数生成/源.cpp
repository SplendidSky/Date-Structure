#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ofstream of("C:\\Users\\Administrator\\Desktop\\testData.txt");
	auto oldCout = cout.rdbuf(of.rdbuf());
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cout << rand() << " ";
}