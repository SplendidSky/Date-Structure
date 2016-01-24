#include <iostream>
#include "MyQueue.h"

using namespace std;

int flag = 1;
MyQueue<int> q;

void menu() {
	cout << endl;
	cout << "-----------------Queue--------------------" << endl;
	cout << "1 --- append\t2 --- retrieve and serve\n";
	cout << "3 --- retrieve\t4 --- size\n";
	cout << "5 --- serve\t6 --- empty\n";
	cout << "7 --- clear\t8 --- traverse\n";
	cout << "0 --- quit\n";
	cout << endl;
}

void do_command() {
	int command, position, value;
	int error_type;
	cout << "please input your command\n";
	cin >> command;
	cout << endl;
	switch (command) {
	case 1:
	{
		cout << "please input the value\n";
		cin >> value;
		error_type = q.append(value);
		if (error_type == 2)
			cout << "the list is full\n";
		else
			cout << "insert success!\n";
		break;
	}
	case 2:
	{
		cout << "retrieve and serve\n";
		error_type = q.retrieve_and_serve(value);
		if (error_type == 1)
			cout << "the list is empty\n";
		else
			cout << "remove success and the value is " << value << endl;
		break;
	}
	case 3:
	{
		cout << "retrieve\n";
		error_type = q.retrieve(value);
		if (error_type == 1)
			cout << "the list is empty\n";
		else
			cout << "retrieve success and the value is " << value << endl;
		break;
	}
	case 4:
	{
		cout << "the size of the list is " << q.size() << endl;
		break;
	}
	case 5:
	{
		cout << "serve\n";
		error_type = q.serve();
		if (error_type == 1)
			cout << "the list is empty\n";
		else
			cout << "serve success\n";
		break;
	}
	case 6:
	{
		cout << "the list is ";
		if (q.empty())
			cout << "empty";
		else cout << "not empty";
		cout << endl;
		break;
	}
	case 7:
	{
		q.clear();
		cout << "the list clear success!\n";
		break;
	}
	case 8:
	{
		cout << "retrieve is not finish!\n";
		break;
	}
	case 0:
	{
		flag = 0;
		break;
	}
	default: break;
	}
}

int main(void) {
	while (flag) {
		menu();
		do_command();
	}
	return 0;
}
