#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	char A_Z[26], a_z[26], zero_nine[10];

	if (argc != 2) {
		cout << "Enter the amount of pattern.\n";
		exit(0);
	}

	for (int i = 0; i < 26; i++) {
		A_Z[i] = 65 + i;
		a_z[i] = 97 + i;
	}

	for (int i = 0; i < 10; i++)
		zero_nine[i] = 48 + i;

	istringstream iss(argv[1]);
	int amount = 0;
	try {
		iss >> amount;
		cout << argv[1] << endl;
		cout << amount << endl;
	}
	catch (exception e) {
		cout << e.what();
		exit(0);
	}

	string output;

	int a = 0;

	for (int f = 0; f < 26 && a < amount; f++) {
		for (int s = 0; s < 26 && a < amount; s++) {
			for (int t = 0; t < 10 && a < amount; t++, a = a + 3) {
				char temp[4];
				temp[0] = A_Z[f];
				temp[1] = a_z[s];
				temp[2] = zero_nine[t];
				temp[3] = '\0';
				output += string(temp);
			}
		}
	}

	cout << output << endl;

}