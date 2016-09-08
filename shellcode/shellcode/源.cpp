#include <iostream>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <stdlib.h>

using namespace std;

int main() {
	string shellcode, result;
	cin >> shellcode;
	for (int i = 0; i < shellcode.length(); i++) {
		if (shellcode[i] != '\\' && shellcode[i] != 'x')
			result += shellcode[i];
	}
	cout << result << endl;
}