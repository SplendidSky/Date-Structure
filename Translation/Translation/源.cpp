#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

int main() {
	string kv;
	map<string, string> dict;
	do {
		string k, v;
		getline(cin, kv);
		istringstream is(kv);
		is >> v >> k;
		dict[k] = v;
	} while (kv != "");

	string w;
	while (cin >> w) {
		if (dict.find(w) != dict.end())
			cout << dict[w] << endl;
		else
			cout << "eh" << endl;
	}
}