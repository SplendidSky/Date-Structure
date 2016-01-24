#include "БъЭЗ.h"
#include <iostream>

using namespace std;

int main() {
	MyList<int> ml;
	int choose;
	int pos, entry;
	while (1) {
		cout << "1.insert  2.remove  3. replace  4.size  5.empty  6.retrive  7.display" << endl;
		cin >> choose;
		switch (choose) {
		case 1:
			cin >> pos >> entry;
			ml.insert(pos, entry);
			break;
		case 2:
			cin >> pos;
			ml.remove(pos, entry);
			cout << entry << endl;
			break;
		case 3:
			cin >> pos >> entry;
			ml.replace(pos, entry);
			break;
		case 4:
			cout << ml.size() << endl;
			break;
		case 5:
			cout << ml.empty() << endl;
			break;
		case 6:
			cin >> pos;
			ml.retrieve(pos, entry);
			cout << entry << endl;
			break;
		case 7:
			ml.display();
		}
	}
}