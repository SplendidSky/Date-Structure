#include <iostream>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

int numName(string name) {
	int sum = 0;
	for (int i = 0; i < name.length(); i++)
		sum += name[i] - 96;
	return sum;
}

int hashFindLength(string name, string room[], int M) {
	int numN = numName(name);
	int s = numN % M;
	int l = 1;
	int k = s;
	while (room[s] != "NULL") {
		s = (k + l * l) % M;
		l++;
	}
	room[s] = name;
	return l;
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		string room[10001];
		for (int i = 0; i < m; i++)
			room[i] = "NULL";
		double sumLength = 0;
		for (int i = 0; i < n; i++) {
			string name;
			cin >> name;
			sumLength += hashFindLength(name, room, m);
		}
		for (int i = 0; i < m; i++)
			cout << i << ":" << room[i] << endl;
		double avg = sumLength / n;
		cout << setiosflags(ios::fixed);
		cout << setprecision(3) << avg << endl;
	}
}
