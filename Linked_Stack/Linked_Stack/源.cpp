#include "Queue.h"
#include <iostream>

using namespace std;

int main() {
	Queue myQ;
	while(1) {
		char choice;
		cout << "append serve empty display" << endl;
		cin >> choice;
		if (choice == 'a') {
			Entry e;
			cin >> e;
			myQ.append(e);
		}
		else if (choice == 's') {
			myQ.serve();
		}
		else if (choice == 'e')
			cout << "is empty ?" << myQ.empty() << endl;
		myQ.display();
	}
}