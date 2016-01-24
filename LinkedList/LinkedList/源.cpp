#include "LinkedList.h"

using namespace std;

int main() {
	LinkedList ll;
	ll.insert(10, 1);
	ll.insert(10, 2);
	ll.insert(10, 3);
	ll.insert(10, 4);
	ll.insert(10, 5);
	ll.insert(10, 6);
	ll.print();
	ll.deleteByPosition(3);
	ll.print();
	ll.deleteByPosition(1);
	ll.print();
	ll.deleteByPosition(3);
	ll.print();
	ll.deleteByPosition(3);
	ll.print();
	ll.deleteByPosition(2);
	ll.print();
	ll.deleteByPosition(1);
	ll.print();
	ll.deleteByPosition(0);
	ll.print();
	system("pause");
}