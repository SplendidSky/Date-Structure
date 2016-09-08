#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Provide EIP\n";
		exit(0);
	}

	string EIP(argv[1]);
	int offset = 0;
	string pattern;

	if (EIP.length() == 8) {
		for (int i = 3; i >= 0; i--) {
			char temp[2];
			int f = 0, s = 0;
			if (EIP[i * 2] > '0' && EIP[i * 2] < '9')
				f = EIP[i * 2] - '0';
			else if (EIP[i * 2] >= 'a' && EIP[i * 2] <= 'f')
				f = EIP[i * 2] - 'a' + 10;
			else if (EIP[i * 2] >= 'A' && EIP[i * 2] <= 'F')
				f = EIP[i * 2] - 'A' + 10;
			if (EIP[i * 2 + 1] > '0' && EIP[i * 2 + 1] < '9')
				s = EIP[i * 2 + 1] - '0';
			else if (EIP[i * 2 + 1] >= 'a' && EIP[i * 2 + 1] <= 'f')
				s = EIP[i * 2 + 1] - 'a' + 10;
			else if (EIP[i * 2 + 1] >= 'A' && EIP[i * 2 + 1] <= 'F')
				s = EIP[i * 2 + 1] - 'A' + 10;
			temp[0] = f * 16 + s;
			temp[1] = '\0';
			pattern += string(temp);
		}
	}

	cout << pattern << endl;


	char A_Z[26], a_z[26], zero_nine[10];

	for (int i = 0; i < 26; i++) {
		A_Z[i] = 65 + i;
		a_z[i] = 97 + i;
	}

	for (int i = 0; i < 10; i++)
		zero_nine[i] = 48 + i;

	string std_pattern;

	for (int f = 0; f < 26; f++) {
		for (int s = 0; s < 26; s++) {
			for (int t = 0; t < 10; t++) {
				char temp[4];
				temp[0] = A_Z[f];
				temp[1] = a_z[s];
				temp[2] = zero_nine[t];
				temp[3] = '\0';
				std_pattern += string(temp);
			}
		}
	}

	if (std_pattern.find(pattern) == -1)
		cout << "Can't find the offset\n";
	else
		cout << std_pattern.find(pattern) << endl;

}